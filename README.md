# 🎮 🚨 **NoPSSDK** _v1.0.3_
[![GitHub All Releases](https://img.shields.io/github/downloads/dandykong/nopssdk/total.svg)](https://github.com/dandykong/nopssdk/releases)

### A tiny library that fully strips the PlayStation PC SDK runtime requirement for God of War Ragnarok.

## Why?

There is a number of people that encountered various unexpected errors and issues, e.g. a sudden error message popup and more.
This library attempts to resolve all the possible issues related to the PlayStation PC SDK.

## Notes

This project does not touch or modify any original game code and is NOT intended to encourage piracy.

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

![image](https://web.archive.org/web/20240922203227/https://private-user-images.githubusercontent.com/47572179/369656331-ea39abda-e315-4d67-9b8d-7a08467272ad.png?jwt=eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3MjcwMzc0NDcsIm5iZiI6MTcyNzAzNzE0NywicGF0aCI6Ii80NzU3MjE3OS8zNjk2NTYzMzEtZWEzOWFiZGEtZTMxNS00ZDY3LTliOGQtN2EwODQ2NzI3MmFkLnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNDA5MjIlMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjQwOTIyVDIwMzIyN1omWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPWY0YTY4ZWIzZGY1MWY5MTAxOThkZDVjY2RhY2UyZjE5ZmFlMmI4M2ZkODFkOWM1YWJhYzFkYmQ0YmQyMjI1MmQmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0In0.i_6pFW2GjNufp-KsNxVMUxQGcYce6vc96Xv9veHTbDI)

## NexusMods link
- [Find it here](https://www.nexusmods.com/godofwarragnarok/mods/51)

## Stuff used

- **Microsoft Detours** (https://github.com/microsoft/Detours)

## Credits

- *jason098* (Linux tests and tips)
- *Ameribear* (Reuploading the latest Nexus Mods version)

## Compilation notes

- **Visual Studio 2022** is required to compile this project
- **PlayStation PC Runtime SDK** is not included in the source code. I have no idea what iArtorias was doing with it or why it was being redistributed.
