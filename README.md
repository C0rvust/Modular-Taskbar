# Modular-Taskbar
A Rainmeter skin that acts as a taskbar replacement. 

The minimum required version of Rainmeter is version [4.4 Beta Release - r3338](https://www.rainmeter.net/).

![Preview](https://user-images.githubusercontent.com/40166216/73678141-a209e500-46af-11ea-8045-974914203a1c.png)

[Download here](https://github.com/C0rvust/Modular-Taskbar/releases).

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

---

**Certain functionalities require the following software.**

- [MagickMeter | khanhas](https://github.com/khanhas/MagickMeter) Used for image processing in NowPlaying. Please follow the  instructions listed.

- [WebNowPlaying | tjhrulz](https://github.com/tjhrulz/WebNowPlaying) Used for grabbing music info from browsers in NowPlaying. Bundled with the installer.

- [Spicetify | khanhas](https://github.com/khanhas/spicetify-cli) Used for grabbing music info from Spotify in conjunction with WebNowPlaying. Please follow the instructions listed [here](https://github.com/khanhas/spicetify-cli/wiki/Guide-for-Rainmeter-user).

---

**Credits where credits due:**

- [Polybar | Khanhas](https://github.com/khanhas/Polybar) - Design Inspiration. Also uses script(s) found here.
