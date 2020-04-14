# GodotGoG
## GOG module for Godot engine

GOG api for the Godot game engine (version 3.x), for Windows, Linux and Mac platforms.

# Documentation

For now the module supports basic GOG api fuctionality, like initialization, signing in and setting achievements.

## Initialization
`Error Init(String CLIENT_ID, String CLIENT_SECRET)`  
Initializes the Galaxy Peer with specified credentials.

`void ProcessData()`  
Makes the Galaxy Peer process its input and output streams. This method should be called in a loop, preferably every frame, so that Galaxy is able to process input and output streams.

`void Shutdown()`  
Shuts down the Galaxy Peer. 

## User
`uint64_t GetGalaxyID()`  
Returns the ID of the user, provided that the user is signed in. 

`void SignIn()`  
Authenticates the Galaxy Peer based on Galaxy Client authentication.

`void SignOut()`  
Signs the Galaxy Peer out.

`bool SignedIn()`  
Checks if the user is signed in to Galaxy.

`bool IsLoggedOn()`  
Checks if the user is logged on to Galaxy backend services. 

## Stats & Achievements
`void ClearAchievement(String achievement_id)`  
Clears an achievement.

`String GetAchievementDescription(String achievement_id)`  
Returns description of a specified achievement. 

`String GetAchievementDisplayName(String achievement_id)`  
Returns display name of a specified achievement. 

`uint32_t GetUserTimePlayed()`  
Reads the number of seconds played by a specified user. 

`bool IsAchievementVisible(String achievement_id)`  
Returns visibility status of a specified achievement. 

`void SetAchievement(String achievement_id)`  
Unlocks an achievement. 

## Friends
`String GetPersonaName()`  
Returns the user's nickname. 

`int GetPersonaState()`  
Returns the user's state. 


## Callbacks/Signals
`void OnAuthSuccess()`  
Notification for the event of successful sign in.

`void OnAuthFailure()`  
Notification for the event of unsuccessful sign in. 

`void OnAuthLost()`  
Notification for the event of loosing authentication. 



