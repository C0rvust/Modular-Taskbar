# Modular-Taskbar
A Rainmeter skin that acts as a taskbar replacement. 

This skin **does not** effect your stock Windows Taskbar in any way; should you choose to remove it (by whatever means avaliable) is your freedom.

The minimum required version of Rainmeter is version [4.4 Beta Release - r3338](https://www.rainmeter.net/).

![Preview](https://user-images.githubusercontent.com/40166216/73678141-a209e500-46af-11ea-8045-974914203a1c.png)

[Download here](https://github.com/C0rvust/Modular-Taskbar/releases).


---

**Requirements**

- [MagickMeter | khanhas](https://github.com/khanhas/MagickMeter) Follow the [installation instructions](https://github.com/khanhas/MagickMeter#how-to-install). Used for image processing.

- [WebNowPlaying | tjhrulz](https://github.com/tjhrulz/WebNowPlaying) Already bundled within the installer, no followup required.

- [Spicetify | khanhas](https://github.com/khanhas/spicetify-cli) Follow the [installtion instructions](https://github.com/khanhas/spicetify-cli/wiki/Guide-for-Rainmeter-user). Used in conjunction with WebNowPlaying to grap music info from Spotify.

---

**Key Functionalities:**

- Modules can be moved individually by changing certain variables in their respective `.inc` files in `@resources/Modules`.
- Modules can be included / excluded by editing `ModuleList.inc`.

- Current modules include:
  - **Battery**
    - Provides battery information
  - **Clock**
    - Provides current time
  - **NowPlaying**
    - Provides information from current song - Open Popup by right click
  - **Power**
    - Power down Shortcut - Double Click to shutdown, right click to cancel
  - **Start**
    - Shortcut list - Open Popup by left click
  - **Volume**
    - Provides volume information
  - **WSM**
    - Manage your virtual desktops

- Modules planned:
  - **Weather**
    - ~~Jelle Pls grant us the forbidden knowledge~~ Provides information on current weather
  - **ActiveWindow**
    - Provides inforomation on open applications
