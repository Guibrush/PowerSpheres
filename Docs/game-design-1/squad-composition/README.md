---
description: What are the squads and how the player builds them
---

# Squad composition

## User Story

As a player I want to manage the squads on my army up to the minimum detail in order to fully personalise not only the appearance of my army but the tactics I'm going to employ on the battlefield.

## Overview

Every army in the game is composed by a certain number of squads, decided by the player. The squad is the entity the players are going to manage all the time and is what they personalise and equip Power Spheres on. The idea behind this is give the player total control over how they want to build their army. They are going to be fully on control of how many squads their armies have, how many and what type of units their squads have and how they behave on the battlefield.

Apart from certain rules when equipping Power Spheres, the only limit here is the point cost of the army. Each one of the customisation options for the squads has a cost in the form of points that adds up to the total point cost of the army. As long as the point limit is meet, whatever combination of squads, units, Power Spheres, etc is permitted.

## Description

The minimal entity that the player is going to be in control \(both on the battlefield and on the customisation mode\) is the squad. **A squad is a group of units, potentially of different types with different Power Spheres applied to them.** Even when they are in control of only one unit \(a hero or something similar\) we consider that a squad composed of only one unit.

### Building a squad

When on building mode, the player can fully personalise a given squad interacting with the different aspects that formed the squad.

#### Units

We let player chose how many units a given squad has **from 1 unit up to a maximum of 9**. There is only one requirement for all the squads in the game: a captain must be present. A captain is a special type of unit with better base stats than the rest of the units. The stats of the units are explain in more detail on [Unit stats](units-stats.md). If a squad only has one member, then that unit will be a captain. Apart from that, the rest of the squad can be formed by any number of the other two types of units: basic and special units. The difference between all the types of units is better explained on [Unit types](unit-types.md).

This means that we let the player a huge amount of freedom on what type of squads they want to have in their armies. They can have squads with only one unit \(the captain\), squads formed by the captain and special units only or a mix of both.

There are more than one type of unit per category. That means that even given that a squad can only have one captain, that captain can be any type of captain available in the game. Same thing with each one of the special units and the rest of the basic units forming the squad. Each one of the sub-types of units has unique stats and characteristics better described on [Unit types](unit-types.md).

All of this options have a cost in form of points. A basic unit cost a certain amount of points, a special unit cost a little more than a basic unit and the captain is the most expensive of the three, all of this also depending on the specific sub-type of unit selected \(some captains cost more than others, for example\). The final cost of the squad is calculated depending on how many and what type of units are in the squad and which Power Spheres are equipped on it.

#### Power Spheres

The player can equip Power Spheres to all the squads that forms their army. We have several types of Power Spheres classified depending on the benefit given to the squad or unit.

There is no global limit on how many Power Spheres a given squad can have, but the different types of them have different restrictions.

Even taking into account that we have many types of Power Spheres we have classified them in two global categories: Abilities and Effects.

{% tabs %}
{% tab title="Abilities" %}
Every squad in the game can be equipped with Power Spheres that give abilities to the squad. There are several types of abilities present in the game but for the purposes of the squad building we only care about three: Movement Abilities, Attacking Abilities and the rest \(General Abilities from now on\). All the types of abilities are explained in detail on [Abilities](power-spheres/abilities.md).

The rules for equipping abilities are as follow:

* Each ability equipped on the squad category is going to be applied to each unit in the squad unless otherwise is specified.
* The player can decide to equip abilities only on the captain and also can decide if those abilities overwrite the ones of the squad or adds to them. This means that the captain can have the abilities equipped on the squad and on itself or only the abilities equipped on itself.
* The player also can decide to equip each one of the special units with different abilities applying the same rules as the captain. This means that the player can have squads formed only with very specialised units each one with a different set of abilities or the same set of abilities for the whole squad or a mix of both.

**Each type of unit on the squad can be equipped with 1 Movement Ability and 1 Attacking Ability**. At the same time **the whole squad can be quipped with a maximum of 4 General Abilities**. This number is shared between all the types of units a squad is formed of. This means that the user can make any type of combination of General Abilities that fits in that rule; 2 General Abilities on the basic units and other 2 only for the captain or 1 on the basic units, 1 on the special units and 2 on the captain, for example.
{% endtab %}

{% tab title="Effects" %}
Every squad in the game can be equipped with Power Spheres that give effects to the squad. These are passive effects that are applied to the units in the squad during the whole duration of the battle \(some of them can have different rules depending on the effect\). All the effects are explained in detail on [Effects](power-spheres/effects.md).

**There are no limits on how many or what type of effects can be equipped on a squad**. As mentioned on other pages, the only limit here is that the amount of points that a given effect cost is going to rise the total cost of the squad, which means that the real limit is the total point cost of the army. Anyway we give total freedom to the player to build any type of army they want. Maybe they want an army formed by only one very powerful squad or many small, weak, very low cost squads.

The rules for equipping effects to the squad are exactly the same as equipping abilities. This means that the player has the freedom of choosing if they want the whole squad to share the same effects or to have the captain to have a different set of effects or each one of the special units to have their own set of effects as well.
{% endtab %}
{% endtabs %}

### Controlling a squad on the battlefield

**On the battlefield the controls are the same as any other RTS game like Starcraft or Warhammer 40K: Dawn of War**. This means that the player has to select the entities in the world in order to give them orders like "move", "attack" or "use an ability". The entities that the players are going to select are their squads. The units forming the squad cannot be selected individually, **when a player clicks on an unit to select it, the whole squad is going to be selected instead**.

When giving orders to a selected squad, all the eligible units in the squad are going to execute the order immediately. All the orders that the player can give to a squad are always going to be abilities that the squad has equipped, even the movement is an ability in our game! This means that the previously mentioned "eligible units" are those that have the ability that the player wants to execute equipped. If only one unit has the ability that the player wants to execute, then that unit will execute it while the rest of the squad will stay still executing whatever passive behaviour is selected at the moment.

Whenever a squad is not executing an order, that squad is executing a passive behaviour. This passive behaviour indicates how the player wants this unit to behave automatically when certain things happen on the battlefield unless a explicit order is given by the player. An explicit order is always going to override whatever the passive behaviour is telling the squad to do. The passive behaviours are better explained on [Passive behaviours](../passive-behaviours.md).

