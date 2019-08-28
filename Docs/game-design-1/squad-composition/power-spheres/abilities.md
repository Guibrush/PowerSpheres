---
description: >-
  List and description of the abilities that the players can equip on their
  squads
---

# Abilities

## User Story

As a player I want to be able to use my army in different and unique ways depending on the strategy I want to use on every battle by equipping different sets of abilities to my squads.

## Overview

There are a wide range of Power Spheres that we are going to consider abilities. From movement to healing or weapons, every Power Sphere that adds some kind of action or new way to interact with the world and/or other units is considered an ability.

We understand as ability any type of action executed by an unit. In our game everything is an action that the player can equip on their squads, even the movement! This way we allow the player a huge amount of freedom and ownership on their own playstyle.

The main intention behind converting something as basic as the movement on an ability is allowing the players to equip whatever they want and converting every squad in whatever they can imagine. We want to allow crazy combinations and encourage experimentation as much as possible.

There are certain limits on how many abilities can be equipped on a given squad as defined on [Squad composition](../#building-a-squad).

## Description

We are going to divide the abilities in three groups: Movement, Weapons and General.

### Movement Abilities

In this category we have all the abilities that move the units from one place to another using the Movement stat of every unit in the squad. It doesn't matter if the ability makes the units move by foot, fly or mount a horse, if the ability moves the units using the Movement stat then is a movement ability.

The only movement abilities that we won't put on this category are the ones that for some reason doesn't use the Movement stat of the unit, such as instant teleportation, for example. Those will be treated as general abilities.

| Ability | Description | Cost |
| :--- | :--- | :--- |
| **Walk** | Move the unit on the ground. | **10/Unit** |

### Weapons

This abilities are the ones that give the unit a weapon, has a fire rate and uses the Attack stat of the unit. On the battlefield this ability will be the "basic attack" the unit will execute when using the order of attacking an enemy.

Not all the weapons in the game are range weapons. We are going to put close combat weapons on this category as well, such as hammers, swords or axes. In those cases the fire rate of the weapon will mean the time between hits.

|  | Fire Rate | Range | Cost |
| :--- | :---: | :---: | :---: |
| Assault Rifle | 0.5 s | 1500 cm | **15/Unit** |
| Pistol | 0.25 s | 1500 cm | **20/Unit** |
| Shotgun | 1 s | 1500 cm | **10/Unit** |
| Sniper Rifle | 2 s | 1500 cm | **5/Unit** |

### General Abilities

Every ability that for some reason doesn't fit in any of the previous categories is a general ability.

#### Fragmentation Grenade

Select this ability and the click on the map on the point where you want the grenade to explode. The explosion will do a certain amount of damage to every unit in the area of effect.

|  | XP | Range | Area of effect | Damage | Cooldown | Cost |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| Level 1 | 0 | 2000 cm | 200 cm | 200 | 30 s | **50/Unit** |

#### Fire Explosion

Select this ability and click on an unit affected with [Elemental Effect Fire](../../combat.md#common-elemental-effects). The elemental effect is consumed and an explosion is triggered with its centre on the target unit. Every unit in the explosion radius receives an amount of damage dependant on how much time was left on the elemental effect. This ability cannot be triggered if the player clicks on an unit which it is not affected by Elemental Effect Fire.

|  | XP | Range | Explosion radius | Damage | Cooldown | Cost |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| Level 1 | 0 | 2000 cm | 200 cm | 100 per second left on the effect | 60 s | **150/Unit** |

#### Ice Wall

Select this ability and click on an unit affected with [Elemental Effect Ice](../../combat.md#common-elemental-effects). The elemental effect is consumed and an ice wall with circular form appears with its centre on the target unit trapping every unit inside a certain radius inside. The wall last a certain amount of time but it can be destroyed by attacking it. Both the duration and the health of the wall depends on how much time was left on the elemental effect. This ability cannot be triggered if the player clicks on an unit which it is not affected by Elemental Effect Ice.

|  | XP | Range | Wall radius  | Wall duration | Wall health | Cooldown | Cost |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| Level 1 | 0 | 2000 cm | 200 cm | 10 s/second left | 100/second left | 40 s | **75/Unit** |

#### Lightning Chain

Select this ability and click on an unit affected with [Elemental Effect Lightning](../../combat.md#common-elemental-effects). The elemental effect is consumed and a lightning jumps from the target to a random nearby unit paralysing it. Then a new lightning jumps from the new unit to another random nearby unit also paralysing it. This effect repeats a number of times dependant on how much time was left on the original elemental effect. The paralysing effect applied to the additional units uses the same stats than the one applied by the original Elemental Effect Lightning. This additional paralysing effects are not considered Elemental Effects. This ability cannot be triggered if the player clicks on an unit which it is not affected by Elemental Effect Lightning.

|  | XP | Range | Nearby unit distance | Cooldown | Cost |
| :--- | :---: | :---: | :---: | :---: | :---: |
| Level 1 | 0 | 2000 cm | 100 cm | 70 s | **150/Unit** |

