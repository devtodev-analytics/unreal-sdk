Latest Version 
--------------
##### _Sep 29st, 2016_ - v1.8.2


Getting Started
---------------
Full description of the integration process of devtodev SDK and all the accessible features can be found on the page with [official devtodev documentation](https://www.devtodev.com/help/141).

Changelog
---------
See [releases](https://github.com/devtodev-analytics/unreal-sdk/releases).

#### Version 1.8.2
* Added possibility to generate several progression events within one session

#### Version 1.8.1
* Unreal Engine 4.13 support

#### Version 1.8
* Added new "Progression event". First of all, the event is used for the games with short (within one game session) locations, game levels. The event allows you to gather data on passing the locations and get statistics on parameters which vary during the the location passing.

#### Version 1.7.2
* Unreal Engine 4.12 support added

#### Version 1.7.1
* User profile feature is added. Here you can store properties about a specific user.
 - New methods for managing preset and custom properties of user profile are added.
 - Old methods: age, gender and cheater, are removed. These properties are moved to user profile.
* Initial referrer data tracking method is added

#### Version 1.6.7
* Added possibility to call events before SDK initialization
* Calculating session length was improved
