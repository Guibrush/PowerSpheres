---
description: Mechanics of the combat and the maths behind it
---

# Combat

## User story

As a player I want to experience a rich and easy to learn combat experience through easily understandable and not random rules which I can combine to achieve the desired combat strategy.

## Overview

The intention behind the rules of the combat is provide an easy and quickly understandable system whose outcomes can be easy to predict and to understand from the point of view of the player. Randomness is strictly forbidden due to the potential unpredictability and frustration that can cause to an average user. Every result of a combat situation \(damage output, status effects, units destroyed, etc\) should be very clear and the player should never have any doubts why certain things had happened. Understanding this concept is really important because it will allow us to create a wide range of rules around this system while maintaining the core concept as simple as possible. As a general rule we should never create a mechanic that obscures how the combat works or makes it more difficult to understand.

A lot of this will be better achieved by adding VFX, sound and other feedback to the game. But even taking into account that we should aim to have clear and easy to understand mechanics from the beginning. The game should be very clear to read and understand with simple and placeholder feedback mechanisms.

## Description

### Damage

The damage received by an unit is the result of a very simple formula taking the Attack stat of the attacker and Defence stat of the receiver of the attack. It goes like this:

```text
Damage = max((Attack - Defence), 0)
```

As we can see, the damage is never going to be less than zero. The healing of the units is another different mechanic.

Also is worth noting that when this calculation gets done all the modifiers for the Attack and Defence has already been applied. When this calculation takes place there is no further modifications to the damage output, whatever is the result of this formula is the final amount that is going to be subtracted from the target's Health stat.

### Elemental effects

Elemental effects doesn't deal any additional damage immediately. The specifics of how it works will be described on each one of the elemental effects or abilities that applies them. Each time an elemental effect gets applied the mechanics of the effect itself will decide if it has to be stacked or not.

As a general rule every effect will add some kind of negative bonus to the target in the form of damage, attack or speed reduction for example. Also it can be permanently or not depending on each effect. What matters at this point is that every effect will have some kind of negative bonus in the form of some numbers applied to the target of the attack, we will call this numbers "Effect Stats". To try to avoid the penalisation every target unit will have an Elemental Defence stat that will reduce the Effect Stats using the following formula:

```text
FinalEffectStat = EffectStat * (1 - (ElementalDefence * 0.01))
```

What this formula means from the point of view of the player is that the Elemental Defence is a stat which goes from 0 to 100 and represents the amount of resistance to the Effect Stats.

#### Example

There is an elemental effect which deals 10 damage points during 100 seconds every second. This effect has two Effect Stats: damage points \(10\) and the duration of the effect in seconds \(100\). That means that we have to do two Effect Stats calculation before applying the effect to the target. Lets assume that the target has an Elemental Defence value of 25. Therefore the calculations will go like this:

```text
FinalDamagePoints: (1 - (25 * 0.01)) * 10 = 7.5
FinalDuration: (1 - (25 * 0.01) * 100) = 75
```

This means that after applying the Elemental Defence, the target will suffer 7.5 damage points every second during 75 seconds.

#### Common Elemental Effects

The following elemental effects are those that are common throughout the whole game. This list of common elemental effects will allow us describe rules like "if the target has Elemental Effect Fire, doubles the damage", for example. This doesn't mean these are the only elemental effects in the game; for example, a Power Sphere can apply a specific elemental effect whose mechanic will be described on the Sphere itself. In any case if we want to apply a specific elemental effect which is not common through another gameplay mechanic we need to explicitly say it in order to let the player know that we are going to apply the elemental effect damage formula when executing that effect.

We are going to describe how the elemental effects works in general terms but the value for the Effect Stats will be defined by the mechanic applying the effect. We are going to describe every value that needs to be an Effect Stat as "&lt;Letter&gt;", such as "&lt;X&gt;" or "&lt;Y&gt;".

* **Elemental Effect Fire**: It deals &lt;X&gt; amount of damage during &lt;Y&gt; amount of seconds every second.
* **Elemental Effect Ice**: It reduces the Movement stat by &lt;X&gt; amount during &lt;Y&gt; seconds.
* **Elemental Effect Lightning**: It paralyses the unit during &lt;X&gt; seconds. The unit will not be able to move or use any ability but it can take damage.
* **Elemental Effect Poison**: It reduces the Attack and Defence stats by &lt;X&gt; amount during &lt;Y&gt; seconds.
* **Elemental Effect Darkness**: It reduces the Vision Radius stat by &lt;X&gt; amount during &lt;Y&gt; seconds.
* **Elemental Effect Elemental Mark**: It applies one Elemental Mark to the target during &lt;X&gt; seconds. It can be stacked if the effect is applied again but it doesn't reset the duration of the previously applied Marks. There is no maximum of how many Marks an unit can have.

