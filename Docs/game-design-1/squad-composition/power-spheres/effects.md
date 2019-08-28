---
description: List and description of the effects that the players can equip on their squads
---

# Effects

## User Story

As a player I want to customise the stats and the passive effects of my army according to the specific tactics I want to use on the battlefield by being able to equip different Power Spheres that allow me to do any combination I want.

## Overview

Every Power Sphere that adds some kind of passive benefit to the squad is considered an effect. This includes a huge range of stats boosts and passive abilities that are going to be applied or executed every time a certain condition is met.

Taking that into account we can say that an effect is every stat boost or ability that doesn't require a direct activation from the player. This means, for example that an ability that is applied every time an unit moves is considered an effect; the player has triggered the ability by ordering the unit to move but the direct action of the player was the move ability, not the ability that triggers when moving.

There is no limit on how many effects a given squad can have. As defined on [Squad composition](../#building-a-squad), the only limit here would be the total point cost of the army.

## Description

For now there is no need of any special classification regarding the effects. When building their armies, the players will equip all the effects in the same slot and all of them will be applied equally.

### List of effects

#### Health Boost

|  | XP | Stat increase | Cost |
| :--- | :---: | :---: | :---: |
| **Level 1** | 0 | +50 Health | **10/Unit** |
| **Level 2** | 0 | +100 Health | **15/Unit** |
| **Level 3** | 0 | +150 Health | **20/Unit** |
| **Level 4** | 0 | +200 Health | **25/Unit** |
| **Level 5** | 0 | +250 Health | **30/Unit** |

#### Movement Boost

|  | XP | Stat increase | Cost |
| :--- | :---: | :---: | :---: |
| **Level 1** | 0 | +5% Movement | **10/Unit** |
| **Level 2** | 0 | +10% Movement | **15/Unit** |
| **Level 3** | 0 | +15% Movement | **20/Unit** |
| **Level 4** | 0 | +20% Movement | **25/Unit** |
| **Level 5** | 0 | +25% Movement | **30/Unit** |

#### Attack Boost

|  | XP | Stat increase | Cost |
| :--- | :---: | :---: | :---: |
| **Level 1** | 0 | +50 Attack | **10/Unit** |
| **Level 2** | 0 | +100 Attack | **15/Unit** |
| **Level 3** | 0 | +150 Attack | **20/Unit** |
| **Level 4** | 0 | +200 Attack | **25/Unit** |
| **Level 5** | 0 | +250 Attack | **30/Unit** |

#### Defence Boost

|  | XP | Stat increase | Cost |
| :--- | :---: | :---: | :---: |
| **Level 1** | 0 | +25 Defence | **10/Unit** |
| **Level 2** | 0 | +50 Defence | **15/Unit** |
| **Level 3** | 0 | +75 Defence | **20/Unit** |
| **Level 4** | 0 | +100 Defence | **25/Unit** |
| **Level 5** | 0 | +125 Defence | **30/Unit** |

#### Elemental Defence Boost

|  | XP | Stat increase | Cost |
| :--- | :---: | :---: | :---: |
| **Level 1** | 0 | +10% Elemental Defence | **10/Unit** |
| **Level 2** | 0 | +20% Elemental Defence | **15/Unit** |
| **Level 3** | 0 | +30% Elemental Defence | **20/Unit** |
| **Level 4** | 0 | +40% Elemental Defence | **25/Unit** |
| **Level 5** | 0 | +50% Elemental Defence | **30/Unit** |

#### Vision Radius Boost

|  | XP | Stat increase | Cost |
| :--- | :---: | :---: | :---: |
| **Level 1** | 0 | +1000 cm Vision Radius | **6/Unit** |
| **Level 2** | 0 | +2000 cm Vision Radius | **7/Unit** |
| **Level 3** | 0 | +3000 cm Vision Radius | **8/Unit** |
| **Level 4** | 0 | +4000 cm Vision Radius | **9/Unit** |
| **Level 5** | 0 | +5000 cm Vision Radius | **10/Unit** |

#### Splash Damage

Every attack explodes on the target hitting every additional unit withing a certain radius, including the target. Those hits are resolved using the normal [damage formula](../../combat.md#damage). This effect gets triggered even if the final damage to the target unit is 0.

|  | XP | Radius | Cost |
| :--- | :---: | :---: | :---: |
| **Level 1** | 0 | 100 cm | **30/Unit** |
| **Level 2** | 0 | 150 cm | **35/Unit** |
| **Level 3** | 0 | 200 cm | **40/Unit** |
| **Level 4** | 0 | 250 cm | **45/Unit** |
| **Level 5** | 0 | 300 cm | **50/Unit** |

#### Piercing Damage

The shots of the unit equipped with this, doesn't stop when collide with the first enemy unit. Every shot goes in a straight line up until certain distance, hitting every unit along the way. The hits gets resolved with the normal [damage formula](../../combat.md#damage).

|  | XP | Distance | Cost |
| :--- | :---: | :---: | :---: |
| **Level 1** | 0 | 1750 cm | **20/Unit** |
| **Level 2** | 0 | 2000 cm | **25/Unit** |
| **Level 3** | 0 | 2250 cm | **30/Unit** |
| **Level 4** | 0 | 2500 cm | **35/Unit** |
| **Level 5** | 0 | 2750 cm | **40/Unit** |

#### Fire bullets

Every hit achieved by this unit which is not triggered by an ability applies the [Elemental Effect Fire](../../combat.md#common-elemental-effects) to the target. This effect will get applied even if the final damage on the target unit is 0.

|  | XP | Duration | Damage per second | Cost |
| :--- | :---: | :---: | :---: | :---: |
| **Level 1** | 0 | 10 s | 20 | **25/Unit** |
| **Level 2** | 0 | 12.5 s | 30 | **37/Unit** |
| **Level 3** | 0 | 15 s | 40 | **60/Unit** |
| **Level 4** | 0 | 17.5 s | 50 | **87/Unit** |
| **Level 5** | 0 | 20 s | 60 | **120/Unit** |

#### Ice bullets

Every hit achieved by this unit which is not triggered by an ability applies the [Elemental Effect Ice](../../combat.md#common-elemental-effects) to the target. This effect will get applied even if the final damage on the target unit is 0.

|  | XP | Duration | Effect | Cost |
| :--- | :---: | :---: | :---: | :---: |
| **Level 1** | 0 | 2 s | -5% Movement | **15/Unit** |
| **Level 2** | 0 | 4 s | -7% Movement | **22/Unit** |
| **Level 3** | 0 | 6 s | -10% Movement | **30/Unit** |
| **Level 4** | 0 | 8 s | -12% Movement | **37/Unit** |
| **Level 5** | 0 | 10 s | -15% Movement | **45/Unit** |

#### Lightning bullets

Every hit achieved by this unit which is not triggered by an ability applies the [Elemental Effect Lightning](../../combat.md#common-elemental-effects) to the target. This effect will get applied even if the final damage on the target unit is 0.

|  | XP | Duration | Cost |
| :--- | :---: | :---: | :---: |
| **Level 1** | 0 | 1 s | **30/Unit** |
| **Level 2** | 0 | 2 s | **60/Unit** |
| **Level 3** | 0 | 3 s | **90/Unit** |
| **Level 4** | 0 | 4 s | **120/Unit** |
| **Level 5** | 0 | 5 s | **150/Unit** |

#### Poison bullets

Every hit achieved by this unit which is not triggered by an ability applies the [Elemental Effect Poison](../../combat.md#common-elemental-effects) to the target. This effect will get applied even if the final damage on the target unit is 0.

|  | XP | Duration | Effect | Cost |
| :--- | :---: | :---: | :---: | :---: |
| **Level 1** | 0 | 2 s | -50 Attack, -25 Defence | **20/Unit** |
| **Level 2** | 0 | 4 s | -75 Attack, -37 Defence | **30/Unit** |
| **Level 3** | 0 | 6 s | -100 Attack, -50 Defence | **40/Unit** |
| **Level 4** | 0 | 8 s | -125 Attack, -62 Defence | **50/Unit** |
| **Level 5** | 0 | 10 s | -150 Attack, -75 Defence | **60/Unit** |

#### Dark bullets

Every hit achieved by this unit which is not triggered by an ability applies the [Elemental Effect Darkness](../../combat.md#common-elemental-effects) to the target. This effect will get applied even if the final damage on the target unit is 0.

|  | XP | Duration | Effect | Cost |
| :--- | :---: | :---: | :---: | :---: |
| **Level 1** | 0 | 2 s | -1000 cm Vision Radius | **11/Unit** |
| **Level 2** | 0 | 4 s | -1500 cm Vision Radius | **17/Unit** |
| **Level 3** | 0 | 6 s | -2000 cm Vision Radius | **22/Unit** |
| **Level 4** | 0 | 8 s | -2500 cm Vision Radius | **28/Unit** |
| **Level 5** | 0 | 10 s | -3000 cm Vision Radius | **33/Unit** |

#### Mark bullets

Every hit achieved by this unit which is not triggered by an ability applies the [Elemental Effect Elemental Mark](../../combat.md#common-elemental-effects) to the target. This effect will get applied even if the final damage on the target unit is 0.

|  | XP | Duration | Cost |
| :--- | :---: | :---: | :---: |
| **Level 1** | 0 | 10 s | **5/Unit** |
| **Level 2** | 0 | 15 s | **7/Unit** |
| **Level 3** | 0 | 20 s | **10/Unit** |
| **Level 4** | 0 | 25 s | **12/Unit** |
| **Level 5** | 0 | 30 s | **15/Unit** |

#### Healing aura

Every unit within a certain radius of the unit equipped with this effect is healed by a certain amount every period of time.

|  | XP | Radius | Healing | Period | Cost |
| :--- | :---: | :---: | :---: | :---: | :---: |
| **Level 1** | 0 | 200 cm | 10 | 2 s | **10/Unit** |
| **Level 2** | 0 | 200 cm | 20 | 2 s | **20/Unit** |
| **Level 3** | 0 | 400 cm | 20 | 1 s | **40/Unit** |
| **Level 4** | 0 | 400 cm | 40 | 1 s | **80/Unit** |
| **Level 5** | 0 | 500 cm | 40 | 0.5 s | **160/Unit** |

