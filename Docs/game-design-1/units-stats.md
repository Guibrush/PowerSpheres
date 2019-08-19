---
description: List and description of the stats that each unit in the game possesses
---

# Units stats

## User Story

As a player I want to have stats to represent how strong and capable my units are in the battlefield by having each stat represented by a number that I can improve equipping Power Spheres or by buffing my units on the battlefield.

## Overview

Each unit in the game will have 5 stats very easy to understand and to relate to one another. This stats will be modified equipping Power Spheres, buffing the unit on the battlefield through and ability or both. To avoid unnecessary complications from the point of view of the player we will always show the final value with all the modifications applied in the UI. At the same time it will be this final value with all the modifications the one we will use for every calculation in the middle of the game.

## Description

### Health

The health indicates how close an units is from being dead. Each time an unit receives damage, this damage reduces the number of health points of the unit. When this stat reaches zero, the unit will die.

### Movement

Indicates the speed of the unit´s movement regardless of the method used by the unit to perform the movement. Potentially each unit can use a different method to move which will change how the unit can reach their objective and the type of obstacles that can avoid but all of them will use this stat to determine the speed.

### Attack

This stat indicates how powerful this unit is in combat. Higher Attack means that potentially this unit can deal more damage to the enemy. More info in [Combat](combat.md#damage).

### Defence

Indicates how resistant this unit is to damage. Higher Defence means that potentially this unit can resist enemies with higher Attack stat. More info in [Combat](combat.md#damage).

### Elemental Defence

Indicates how resistant this unit is to elemental status effects. Apart from the normal damage, an attack can have elemental status effects added such as fire, electricity, ice, poison, etc. The result of this effects varies depending on the element associated but they are always going to apply some numerical calculation to the target such as damage per second, movement reduction, etc. Elemental Defence reduces those numbers so an unit receives less damage per second during less amount of time, for example. More info in [Combat](combat.md#elemental-effects).

### Vision Radius

Indicates how far this unit is able to see through the Fog of War. Without this attribute the map is covered completely by the Fog of War, hiding enemies and other important elements for the gameplay. This attribute indicates the radius around itself in which this unit eliminates the Fog of War, showing enemies and other important actors.

