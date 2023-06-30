# Ideas

Focus/Goals:
============
As of 2023-JUN-30:
- My primary consideration is an accurate clock which boots and shows the time as quickly as possible.
- The DS3231 chip is a concern of mine: it must be better protected from illogical input and undefined states. I'd also like to wring as much use out of it as possible. And although it probably won't matter in my lifetime, I'd like to put in place a mechanism to correct it's state when it starts incorrectly identifying leap years from 2100 onwards.
- I have usability concerns, some of which may be counter to the firmwares original programmer/maintainer.
- I have little to no interest in IR control, passive buzzer, or add on environmental sensors; because i don't have any of those.

List of ideas:
==============
- Current work: 3 button interface. I intend to guard against unspecified/unintended action when pressing more than one button, provide user feedback when long press condition is meet (vs on release), and allow the possibility of combinations of buttons performing actions.
- 3 button changes lead to another idea: reset clock to programmed defaults, by clearing and reflashing the settings area of flash memory. The major up side of this is to remove the need to use the one-time section when changing wifi SSID & Password, they'll only ever need to be defined.
- Move all configuration of defaults to it's own file.
- The button settings menu could perhaps be a few sub-menus, eg. SYS (Lang,KeyBeep,Scroll,AutoBright,TempUnit), TIME (Hour,Minute,24/12,Month,DoM,Year,SummerTime,TimeZone), DING (chime stuff), MOON (nightlight stuff).
- Restructuring all the code, for e.g. portability of functions between difference input methods.


PaulBags 2023-JUN-30
