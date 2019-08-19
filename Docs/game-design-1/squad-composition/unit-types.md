---
description: List and description of the types of units present in the game
---

# Unit types

## User story

As a player I want enough variety of units to be able to make meaningful decisions when deciding the composition of my squads by having different types of units with different stats.

## Overview

The player can decide what type of units they want to have in their squads. Each type of units has different base stats, thus theoretically serving a different purpose inside the squad or the army.

There is no limit on how many units of one specific type a squad can have, however each squad can only have one captain. Each unit has a different point cost depending on the type of the unit it is. This means that the base cost of any squad is the sum of the base cost of every unit in the squad. Taking into account this, the only limit in the type of units is again the total point cost of the army.

## Description

We have three main categories for the type of units present in the game that are going to define the role inside the squad, how good their base stats are and the point cost of the unit itself.

### Captains

The captains are the leaders of the squads and the most powerful unit of each squad. This unit is the one that has the best base stats of the whole squad and is the most expensive of all of them. Given the fact that a squad must always have a captain but might have no other units, the point cost of the captain is the base cost of any squad in the game. 

The only unique characteristic that all the captains have in common is that **all of them start the game with 200 Health**.

#### Average captain

Is the most balanced of all them in terms of stats. Doesn't excel in anything in particular but it doesn't have any noticeable weakness. Is suppose to be perfect for new players.

| Stat | Value |
| :--- | :--- |
| Health | 200 |
| Movement | 1.2 |
| Attack | 10 |
| Defence | 10 |
| Elemental Defence | 10 |
| Vision Radius | 2500 |
| **Point cost** | **425** |

#### Offensive captain

This captain is better in attack than anything else. This means that has a little bit of defence sacrificed in order to be balanced against the rest of the captains. It also has a little bit more movement with the intention of going to battle and pursue the enemy as quickly as possible. Ideally this captain will be chosen by a little bit experienced players who already know more precisely what type of army they want to build.

| Stat | Value |
| :--- | :--- |
| Health | 200 |
| Movement | 1.4 |
| Attack | 30 |
| Defence | 5 |
| Elemental Defence | 7.5 |
| Vision Radius | 2500 |
| **Point cost** | **442.5** |

#### Defensive captain

This captain is better in defence than anything else. It has sacrificed the attack but in return is has more vision radius to anticipate to the enemy's movements from farther away. Ideally this captain will be chosen by a little bit experienced players who already know more precisely what type of army they want to build.

| Stat | Value |
| :--- | :--- |
| Health | 200 |
| Movement | 1.2 |
| Attack | 0 |
| Defence | 15 |
| Elemental Defence | 12.5 |
| Vision Radius | 3000 |
| **Point cost** | **442.5** |

### Special units

The special units are the ones meant to have better stats and equipment than the basic units. Their function in the squad is to serve as a specialists, focusing on one aspect of the combat or triggering a specific set of abilities. Are suppose to be the next most expensive unit after the captain.

#### Average specialist

Is the most balanced of all special units, not focusing on anything but also not having mayor weaknesses. As with the average captain is suppose to be the one meant to learn the game.

| Stat | Value |
| :--- | :--- |
| Health | 100 |
| Movement | 1 |
| Attack | 5 |
| Defence | 5 |
| Elemental Defence | 5 |
| Vision Radius | 2000 |
| **Point cost** | **260** |

#### Offensive specialist

This special unit is focused on attack. This means that its defence is not as good as the average's one but it has better movement to compensate and be able to get to the enemy quicker.

| Stat | Value |
| :--- | :--- |
| Health | 100 |
| Movement | 1.2 |
| Attack | 20 |
| Defence | 2.5 |
| Elemental Defence | 2.5 |
| Vision Radius | 2000 |
| **Point cost** | **277.5** |

#### Defensive specialist

This special unit is focused on defence, which means that its attack is not as good as the rest of the special units but it has better vision radius to see the enemy advance for afar.

| Stat | Value |
| :--- | :--- |
| Health | 100 |
| Movement | 1 |
| Attack | 0 |
| Defence | 7.5 |
| Elemental Defence | 7.5 |
| Vision Radius | 2500 |
| **Point cost** | **277.5** |

### Base units

The base units are most basic unit in the game. They meant to be a blank page for the player to do whatever they want with them. That is why they don't have attack nor defence. The only thing a basic unit can do is spot enemies and be alive or dead.

Notice that even with 1 point on Movement an unit cannot move unless it has a movement ability equipped, thus the movement stat refers directly to the movement ability in case is equipped. This means that if the unit doesn't have a movement ability equipped it has 100 points that are completely wasted. This consideration can make the calculation of the points really difficult and prone to errors and weird edge cases, for this purpose for now we are ignoring the fact that the unit can have movement ability equipped or not. Further playtests will tell us how dangerous this assumption really is.

| Stat | Value |
| :--- | :--- |
| Health | 100 |
| Movement | 1 |
| Attack | 0 |
| Defence | 0 |
| Elemental Defence | 0 |
| Vision Radius | 2000 |
| **Point cost** | **220** |

