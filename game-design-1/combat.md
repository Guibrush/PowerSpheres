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

```cpp
Damage = max((Attack - Defence), 0)
```

As we can see, the damage is never going to be less than zero. The healing of the units is another different mechanic.

Also is worth noting that when this calculation gets done all the modifiers for the Attack and Defence has already been applied. When this calculation takes place there is no further modifications to the damage output, whatever is the result of this formula is the final amount that is going to be subtracted from the target´s Health stat.

### Elemental effects

Elemental effects added to attacks doesn´t deal any additional damage immediately. With every attack they apply a certain status effect depending on the element added to the attack. Each time the attack gets executed this effects gets applied and the mechanics of the effect itself will decide if it has to be stacked or not.

As a general rule every effect will add some kind of negative bonus to the target in the form of damage, attack or speed reduction for example. Also it can be permanently or not depending on each effect. What matters at this point is that every effect will have some kind of negative bonus in the form of some numbers applied to the target of the attack, we will call this numbers "Effect Stats". To try to avoid the penalisation every target unit will have an Elemental Defence stat that will reduce the Effect Stats using the following formula:

```text
FinalEffectStat = EffectStat * (1 - (ElementalDefence * 0.01))
```

What this formula means from the point of view of the player is that the Elemental Defence is a stat which goes from 0 to 100 and represents the amount of resistance to the Effect Stats.

#### Example

There is an elemental effect which deals 10 damage points during 100 seconds every second. This effect has two Effect Stats: damage points \(10\) and duration of the effect in seconds \(100\). That means that we have to do two Effect Stats calculation before applying the effect to the target. Lets assume that the target has an Elemental Defence value of 25. Therefore the calculations will go like this:

```text
FinalDamagePoints: (1 - (25 * 0.01)) * 10 = 7.5
FinalDuration: (1 - (25 * 0.01) * 100) = 75
```

This means that after applying the Elemental Defence, the target will suffer 7.5 damage points every second during 75 seconds.

