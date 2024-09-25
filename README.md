### A complete restoration of this repo is currently underway.

# 🎮 🚨 **NoPSSDK** _v1.0.3_
[![GitHub All Releases](https://img.shields.io/github/downloads/dandykong/nopssdk/total.svg)](https://github.com/dandykong/nopssdk/releases)

### A tiny library that fully strips the PlayStation PC SDK runtime requirement for God of War Ragnarok.

## Why?

There is a number of people that encountered various unexpected errors and issues, e.g. a sudden error message popup and more.
This library attempts to resolve all the possible issues related to the PlayStation PC SDK.

## Notes

This project does not touch or modify any original game code and is NOT intended to encourage the piracy.

## Usage

### Windows

1. Download the [latest release](https://github.com/dandykong/nopssdk/releases/latest)
2. Copy the `version.dll` and `PsPcSdk.dll` to the game folder
3. Enjoy!

### Linux (Wine)

1. Download the [latest release](https://github.com/dandykong/nopssdk/releases/latest)
2. Copy the `version.dll` and `PsPcSdk.dll` to the game folder
3. Add the following launch parameters to the game executable: `SteamDeck=0 WINEDLLOVERRIDES="version=n,b" %command%`
4. Enjoy!

## Troubleshooting:

If you still encounter the login screen error, make sure to remove this file first: 

- `C:\Users\[Username]\\Saved Games\God of War Ragnarök\[AccountID]\userpreferences`

Upon the first popup when it asks to link the Steam account, press `NO` button.

![image](https://github.com/user-attachments/assets/ea39abda-e315-4d67-9b8d-7a08467272ad)

## NexusMods link
- [Find it here](https://www.nexusmods.com/godofwarragnarok/mods/51)

## Stuff used

- **Microsoft Detours** (https://github.com/microsoft/Detours)

## Credits

- *jason098* (Linux tests and tips)

## Compilation notes

- **Visual Studio 2022** is required to compile this project
- **PlayStation PC Runtime** is not included in the source code. I have no idea what iArtorias is doing to it.
