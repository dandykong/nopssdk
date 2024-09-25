#pragma once

#define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#define PSPCSDK_API extern "C" __declspec(dllexport)

// Windows header files
#include <windows.h>
#include <string>
#include <cstddef>
#include <ShlObj_core.h>
#include <Shlwapi.h>
#include <filesystem>

namespace fs = std::filesystem;

// Microsoft Detours (https://github.com/microsoft/Detours)
#include <3rdParty/detours/detours.h>