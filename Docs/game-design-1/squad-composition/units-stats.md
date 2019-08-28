---
description: List and description of the stats that each unit in the game possesses
---

# Unit stats

## User Story

As a player I want to have stats to represent how strong and capable my units are in the battlefield by  having each stat represented by a number that I can improve equipping Power Spheres or by buffing my units on the battlefield.

## Overview

**Each unit in the game independently of their type will have 6 stats very easy to understand and to relate to one another**. This stats will be modified equipping Power Spheres, buffing the unit on the battlefield through and ability or both. To avoid unnecessary complications from the point of view of the player we will always show the final value with all the modifications applied in the UI. At the same time it will be this final value with all the modifications the one we will use for every calculation in the middle of the game.

Each stat contributes to the total point cost of the unit by a certain amount depending on the value of the stat and a specific formula. This way we can calculate the point cost of every unit in the game only by applying said formula.

## Description

### Health \(H\)

#### Description

The health indicates how close an units is from being dead. Each time an unit receives damage, this damage reduces the number of health points of the unit. When this stat reaches zero, the unit will die.

#### Value calculation

It cannot be zero, so the minimum value is 1. There is no maximum.

The Health value is the final health of the unit in game. There is no additional calculations.

#### Points calculation

```text
1 Health = 0.1 Points
```

### Movement \(M\)

#### Description

Indicates the speed of the unit´s movement regardless of the method used by the unit to perform the movement. Potentially each unit can use a different method to move which will change how the unit can reach their objective and the type of obstacles that can avoid but all of them will use this stat to determine the speed.

The logic of this number to the user is that we are taking the base movement speed of the engine, calculating the percentage indicated by the movement value and adding the result to the base movement speed of the engine.

#### Value calculation

The only restriction with the Movement is that it cannot be negative, so the minimum value is 0 and there is no maximum.

The final movement speed in game is calculated by multiplying the base movement speed of the engine by a factor calculated taking the movement attribute. The formula is as follows:

```text
FinalMovementSpeed = EngineMovementSpeed * (1 + (MovementValue * 0.01))
```

#### Points calculation

```text
1 Movement = 1 Points
```

### Attack \(A\)

#### Description

This stat indicates how powerful this unit is in combat. Higher Attack means that potentially this unit can deal more damage to the enemy. More info in [Combat](../combat.md#damage).

#### Value calculation

It cannot be negative, so the minimum is 0 and there is no maximum.

There is no need of additional calculations here. The Attack value is the one that will be used in game as it is.

#### Points calculation

```text
1 Attack = 0.1 Points
```

### Defence \(D\)

#### Description

Indicates how resistant this unit is to damage. Higher Defence means that potentially this unit can resist enemies with higher Attack stat. More info in [Combat](../combat.md#damage).

#### Value calculation

It cannot be negative, so the minimum is 0 and there is no maximum.

There is no need of additional calculations here. The Defence value is the one that will be used in game as it is.

#### Points calculation

```text
1 Defence = 0.2 Points
```

### Elemental Defence \(ED\)

#### Description

Indicates how resistant this unit is to elemental status effects. Apart from the normal damage, an attack can have elemental status effects added such as fire, electricity, ice, poison, etc. The result of this effects varies depending on the element associated but they are always going to apply some numerical calculation to the target such as damage per second, movement reduction, etc. Elemental Defence reduces those numbers so an unit receives less damage per second during less amount of time, for example. More info in [Combat](../combat.md#elemental-effects).

#### Value calculation

The Elemental Defence is a percentage from 0% to 100% so the minimum value is 0 and the maximum is 100. If the player equips something that makes the Elemental Defence go above 100, the excess is lost.

We present this value to the user as a percentage ranging from 0% to 100% but to use it in game we need to transform it to a value ranging from 0 to 1. For that we need to do the following calculation every time we have to apply this defence to a status effect:

```text
FinalPercentaje = (1 - (ElementalDefence * 0.01))
```

#### Points calculation

```text
1 Elemental Defence = 0.5 Points
```

### Vision Radius \(VR\)

#### Description

Indicates how far this unit is able to see through the Fog of War. Without this attribute the map is covered completely by the Fog of War, hiding enemies and other important elements for the gameplay. This attribute indicates the radius around itself in which this unit eliminates the Fog of War, showing enemies and other important entities.

We present this value to the user as a distance in centimetres.

#### Value calculation

We need a minimum of vision for every unit in the game and that is 100 cm. So the minimum value for the Vision Radius is 100 and there is no maximum.

There is no need of additional calculations here. This value is directly the extent of the map revealer component in the engine.

#### Points calculation

```text
1 Vision Radius = 0.001 Points
```

## Summary

| Stat | Points | Range |
| :--- | :--- | :--- |
| Health | 0.1 | 1 - Inf |
| Movement | 1 | 0 - Inf |
| Attack | 0.1 | 0 - Inf |
| Defence | 0.2 | 0 - Inf |
| Elemental Defence | 0.5 | 0 - 100 |
| Vision Radius | 0.001 | 100 - Inf |

