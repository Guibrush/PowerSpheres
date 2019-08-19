---
description: All you need to know to start working in Power Spheres as soon as possible
---

# Getting started

## Plugins

We use 5 plugins to make Power Spheres work.

* **Included in the engine**
  * **GameplayAbilities:** It allows us to use the GameplayAbilities module from UE4 which is perfect for our implementation of our abilities mainly due to how the replication is implemented in this module which is really good in terms of performance.
  * **OnlineSubsystemSteam:** Necessary if we want to validate the prototype with friends and other people external to the development. This plugin allow us to create and join sessions through Steam in order to do online play without being in the same local network.
* **External**
  * **MinimapPlugin:** This plugin also has the implementation of the fog of war in the client. With this plugin we don´t need to worry about implementing a minimap nor the fog of war for the game. We have to take into account that the implementation for the fog of war of this plugin is only on client, which means that if we want to do it for real we need to do some kind of calculation/validation on the server. For the sake of speed we are not going to implement any of this for the prototype.
  * **AdvancedSessions:** This plugin extends and expose a lot of functionality related with creating and joining sessions to blueprints. We are going to use this for the prototype due to the nature of the project. In a real game we probably would want to implement our own system.
  * **AdvancedSteamSessions:** It comes with the previously described plugin. It expose a lot functionality from the Steam API to blueprints that is not even implemented in the OnlineSubsystemSteam. In a real game we would probably want to use a lot of the code of this plugin anyway.

All this plugins are already included in the .uproject file and any new developer doesn´t need to manually activate them. Also the external plugins are included with the project in the "Plugins" folder.

