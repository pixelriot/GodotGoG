# GodotGoG
## GOG module for Godot engine

GOG api for the Godot game engine (version 3.x), for Windows, Linux and Mac platforms.

The project and also the documentation is orientated toward the [GodotSteam project](https://github.com/Gramps/GodotSteam) to improve compatibility.
Big thanks to gramps for his work and the GOG support team for answering all related questions.

## Documentation

For now the module supports basic GOG api fuctionality, like initialization, signing in and setting achievements.



---
## How-To

- Download this repository and unpack it.
- Download and unpack the [Godot source](https://github.com/godotengine/godot).
- Download and unpack the [GOG Galaxy SDK](https://devportal.gog.com/galaxy/components/sdk) - this requires a GOG developer account. You need to download the SDK for every plattform you want to suppprt (Windows 32/64 bit, Mac OS, Linux/X11).
- From the Galaxy SDK(s) copy the Libraries- and Include-folders to the godotgog/sdk-folder.
- Now move the godotgog-directory into the modules-directory of the unpacked Godot Engine source.
- The repo's directory contents should now look like this:
````
    godotgog\sdk\Include\galaxy\*
    godotgog\sdk\Libraries\Galaxy64.dll     (Windows 64 only)
    godotgog\sdk\Libraries\Galaxy64.lib     (Windows 64 only)
    godotgog\sdk\Libraries\Galaxy64.pdb     (Windows 64 only)
    godotgog\sdk\Libraries\libGalaxy.dylib  (Mac OS only)
    godotgog\config.py
    godotgog\godotgog.cpp
    godotgog\godotgog.h
    godotgog\register_types.cpp
    godotgog\register_types.h
    godotgog\SCsub
````

- Recompile for your platform:
  - Windows ( http://docs.godotengine.org/en/stable/reference/compiling_for_windows.html )
  - Linux ( http://docs.godotengine.org/en/stable/reference/compiling_for_x11.html )  
  - OSX ( http://docs.godotengine.org/en/stable/reference/compiling_for_osx.html )  
    When creating templates for this, please refer to this post for assistance as the documentation is a bit lacking ( http://steamcommunity.com/app/404790/discussions/0/364042703865087202/ ).
- When recompiling the engine is finished do the following before running it the first time:
  - Copy the shared library (Galaxy64.dll or libGalaxy.dylib depending on the OS) from the Libraries-folders to the Godot binary location (by default in the godot source /bin/ file but you can move them to a new folder).
- Your game must ship with the executable and the the shared library to function. Lack of the DLL/SO/DyLib (for your respective OS) will cause it to fail and crash.
  - **NOTE:** For OSX, the libGalaxy.dylib must be in the Content/MacOS/ folder in your application zip or the game will crash.

From here you should be able to call various functions of GOG api. You should be able to look up the functions in Godot itself under the search section.

## License
MIT license

