# Modular Taskbar
Modular Taskbar is a [rainmeter](https://www.rainmeter.net/) skin replicating the functions of the stock windows taskbar, equipped with an array of modules that can be swapped in and out at ease.
It is recommended (but not required) that you remove your stock taskbar via 3party tools.

# Installing
The latest release of Modular Taskbar can be found [here](https://github.com/C0rvust/Modular-Taskbar/releases). Simply run the `.rmskin` file once downloaded.
Modular Taskbar requires the Rainmeter application (minimum version `4.5.17.3700`), the installation instructions can be found on their homepage [here](https://www.rainmeter.net/).

# Preview
<img src="https://user-images.githubusercontent.com/40166216/237038870-dd219d84-b1fa-476f-92cc-6a92bbef91eb.png" width="100%"/>
<img src="https://user-images.githubusercontent.com/40166216/237038878-20f5c516-32e9-4b4b-8acb-b97dc31537fb.png" width="100%"/>
<img src="https://user-images.githubusercontent.com/40166216/237038884-c160225f-c569-4fb4-b0a1-cbd5353c117a.png" width="100%"/>

# Requirements

- [MagickMeter by khanhas](https://github.com/khanhas/MagickMeter) - Follow these [instructions](https://github.com/khanhas/MagickMeter#how-to-install) to install the parent application ImageMagick.

- [WebNowPlaying-Redux by Keifufu & tjhrulz](https://github.com/keifufu/WebNowPlaying-Redux-Rainmeter) - Install the wnp browser extension from [here](https://github.com/keifufu/WebNowPlaying-Redux#installing).

- [Spicetify-CLI by khanhas](https://github.com/khanhas/spicetify-cli) - Open a powershell window and run the following code line by line.
  - _If you don't use Spotify, no further actions are required._

```ps1
Invoke-WebRequest -UseBasicParsing "https://raw.githubusercontent.com/khanhas/spicetify-cli/master/install.ps1" | Invoke-Expression
spicetify
spicetify config extensions webnowplaying.js
```

- [PowershellRM by Khanhas](https://github.com/khanhas/PowershellRM#requirements) - Update your Powershell to (Version `3.x` or above) [here](https://www.microsoft.com/en-us/download/details.aspx?id=54616). 
  - _As Win 10 is shipped with Powershell_ `5.1`_, no further actions are required by Win 10 users; update is required only for Win 7 users._

# Features
## Modules
Modular Taskbar is equipped with an array of modules that can be customized via a setting menu. 
Some modules are equipped with a secondary popup skin, which can be summoned by clicking within the bounds of the module's tile.

### Battery
- Provides information about battery% and device uptime.
- Equipped with a brightness slider.

### NowPlaying
- Provides information about currently playing media/music from media players.
- Equipped with media controls.

The module tile contains a scrolling display which displays media information. 
Hovering over the tile brings up context buttons for media control. 
Bringing up the popup produces a mini player, containing a progress bar and an album art display. 

### Power
- Equipped with a power option control menu.

The popup contains a menu of context buttons for various power options.

### Shortcut
- Equipped with a user-defined shortcut menu.

The list of shortcuts can be managed via the context buttons or by bringing up the context menu within the popup.

### Taskbar
- Provides information about active processes.
- Equipped with controls for such processes.

The module tile displays a bar of icons of currently active processes as well as any pinned processes. 
Clicking the icon brings forth the first child process window; 
right clicking the icon pins/unpins the process; 
middle clicking the icon opens a new child window. 
Hovering over each icon summons the popup, containing the list of child processes of that parent process; 
a particular child process window can be brought forth by clicking a child title, or closed via the context buttons.

### Time
- Provides information about time and date.

The module tile displays current time. 
A calendar popup can be summoned, which can be navigated via the context buttons.

### Volume
- Provides information about volume and audio devices.
- Equipped with a volume controller and audio device controller.

Clicking the volume icon on the module title toggles audio between mutes/unmute; 
scrolling on the module tile roughly changes the volume. 
Summoning the popup brings forth a volume slider allowing for finer control, and the current audio device, which can be cycled through via the context buttons.

## Setting Menu

A setting menu can be summoned via the context menu. 
Right click the taskbar, and click `Edit Settings`. You can navigate the menu via the sidebar.

### Module Settings
A list of all available modules are shown, as well as their active status. 
Clicking the `Active`/`Inactive` tile toggles the module between each. 
Each module is accompanied with a context button which opens a list of all variables associated with that module available for customization. 
To edit a variable, simply click the variable value tile on the right, enter your desired value, and hit enter.

You can return to the previous page containing all modules via the context button at the bottom left.

### General Settings
A list of general variables associated with the skin are shown. 
As with above, to edit a variable, simply click the variable value tile on the right, enter your desired value, and hit enter.
