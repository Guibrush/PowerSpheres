---
description: How the Power Spheres works in our game
---

# Power Spheres

## User Story

As a player I want a way to fully customise my army and being able to build any combination of abilities, effects, weapons, etc by using an easy understandable and powerful system

## Overview

The Power Spheres are the base of the customisation system on our game. They work as the stepping stone of everything related with improving the player's army. From simple stats buffs to equipping weapons, everything is done using Power Spheres.

Most of the Power Spheres can be improved using experience points \(XP from now\). That will improve all the stats and effects related with that Power Sphere, sometimes even adding new effects or unique abilities. There is a maximum level which each Power Sphere can reach that will be defined by that specific Power Sphere, the amount of XP required to level up an Sphere also will be defined individually in a case by case basis. Some Power Spheres will be way more powerful and valuable than others, so make sense that those ones are more expensive to level up.

Also is worth noting that the point cost of every Power Sphere will be calculated by what benefit exactly that Sphere adds, plus a fixed amount just because is a Power Sphere. This mechanism is there to avoid players building basic units as powerful as captains with no additional cost just by using the right combination of Power Spheres. As explained on [Unit types](../unit-types.md), it will be always more efficient and cheaper to equip a captain with certain base stats than building those stats from a base unit.

## Description

**Every Power Sphere in the game has a base point cost of 5 points**. Added to that, the point cost of every Power Sphere is calculated adding all the benefits that the Power Sphere provides taking into account the point costs of the stats defined on [Unit stats](../units-stats.md). If the Power Sphere gives an ability, equips a weapon or something not as quantifiable as the unit stats we have to assign a specific point cost to that Power Sphere depending on how powerful is the benefit. This will require iteration and proper playtesting to detect as soon as possible which abilities are over or below the cost curve.

We are going to classify all Power Spheres in the game in two large groups: Abilities and Effects. This two groups will have subgroups at the same time, but every future Power Sphere should be classified first in one of those two groups.

