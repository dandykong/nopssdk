#include "pch.h"

#include "utils.h"
#include "proxy.h"

using namespace Utils;

static decltype(LoadLibraryExA) * o_LoadLibraryExA = nullptr;
static decltype(PathCombineA) * o_PathCombineA = nullptr;
static decltype(CreateThread) * o_CreateThread = nullptr;

static HMODULE HookLoadLibraryExA(
    _In_ LPCSTR lpLibFileName,
    _Reserved_ HANDLE hFile,
    _In_ DWORD dwFlags
)
{
    if (lpLibFileName)
    {
        const std::string file( lpLibFileName );

        if (EndsWith( file, "PsPcSdk.dll" ))
        {
            return CURRENT_MODULE;
        }

        if ((WINE_FOUND && EndsWith( file, "GameInput.dll" )))
        {
            return CURRENT_MODULE;
        }
    }

    return o_LoadLibraryExA( lpLibFileName, hFile, dwFlags );
}


// The game wants to combine a static directory path inside the 'ProgramData' folder with:
// 1. '*' that will later be used with 'FindFirstFileExA' API to obtain the first found directory.
// 2. 'PsPcSdk.dll' which is the main required file
static LPSTR HookPathCombineA(
    _Out_writes_( MAX_PATH ) LPSTR pszDest,
    _In_opt_ LPCSTR pszDir, 
    _In_opt_ LPCSTR pszFile
)
{
    if ((pszDir && pszFile))
    {
        const std::string dir( pszDir );
        const std::string file( pszFile );

        // 'S22' might change with the future updates
        if (EndsWith( dir, "\\S22" ))
        {
            const std::string full_path = fs::current_path().string();

            if (file == "*")
                return o_PathCombineA( pszDest, full_path.data(), pszFile );

            return o_PathCombineA( pszDest, full_path.data(), "" );
        }
    }

    return o_PathCombineA( pszDest, pszDir, pszFile );
}


// The game creates a special PlayStation account link thread which
// then is trying to send the request to 'pss-cloud.net'.
// This might be crucial, so we will just block it.
static HANDLE WINAPI HookCreateThread(
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ SIZE_T dwStackSize,
    _In_ LPTHREAD_START_ROUTINE lpStartAddress,
    _In_opt_ __drv_aliasesMem LPVOID lpParameter,
    _In_ DWORD dwCreationFlags,
    _Out_opt_ LPDWORD lpThreadId
)
{
    if (lpStartAddress && !PLAYSTATION_THREAD_FOUND)
    {
        // cmp byte ptr ds:[XXXXXXXX], 0
        if (CheckUint16( lpStartAddress, 0x3D80 ))
        {
            SetLastError( ERROR_INVALID_HANDLE );
            PLAYSTATION_THREAD_FOUND = true;

            return 0;
        }
    }

    return o_CreateThread( lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, 
        dwCreationFlags, lpThreadId );
}


PSPCSDK_API HRESULT sceCommonDialogInitialize()
{
    return S_OK;
};


PSPCSDK_API HRESULT sceNpCheckCallback()
{
    return S_OK;
};


PSPCSDK_API HRESULT sceNpRegisterStateCallbackA(
    std::size_t ptr, std::size_t cb
)
{
    // Since this function registers two 2 callbacks in a row,
    // we only need the first one (main state).
    static std::once_flag flag;

    std::call_once( flag, [cb]()
    {
        if (cb)
        {
            auto flag = reinterpret_cast<std::uint8_t *>(cb + 0x16C);
            *flag = '\05'; // '5' is what needed (optional register flag?)
        }
    } );

    return S_OK;
}


PSPCSDK_API HRESULT sceNpUniversalDataSystemGetMemoryStat( 
    std::size_t ptr
)
{
    return S_OK;
};


PSPCSDK_API HRESULT sceNpUniversalDataSystemInitialize( 
    std::size_t ptr
)
{
    return S_OK;
};


PSPCSDK_API HRESULT sceNpUniversalDataSystemTerminate()
{
    return S_OK;
};


PSPCSDK_API HRESULT sceNpUnregisterStateCallbackA( 
    const std::size_t id
)
{
    return S_OK;
};


PSPCSDK_API HRESULT scePsPcHookApiCall( 
    char * func
)
{
    return S_OK;
};


PSPCSDK_API HRESULT scePsPcInitializeInternal( 
    std::size_t ptr
)
{
    return S_OK;
};


PSPCSDK_API bool scePsPcIsSupportedPlatform()
{
    return true;
};


PSPCSDK_API HRESULT scePsPcSetDeviceDataCollectionSetting(
    std::size_t flag
)
{
    return S_OK;
};


PSPCSDK_API HRESULT scePsPcTerminate()
{
    return S_OK;
};


PSPCSDK_API HRESULT sceSigninDialogGetResult(
    std::size_t ptr
)
{
    // Should be ok with the blocked PlayStation request thread.
    return S_OK;
};


PSPCSDK_API HRESULT sceSigninDialogInitialize()
{
    return S_OK;
}


PSPCSDK_API HRESULT sceSigninDialogOpen( 
    void * ptr
)
{
    return S_OK;
};


PSPCSDK_API HRESULT sceSigninDialogTerminate()
{
    return S_OK;
};


PSPCSDK_API int sceSigninDialogUpdateStatus()
{
    // Looks like '3' is what exactly needed.
    return 3;
};


// The only possible way for now...
HRESULT WINAPI GameInputCreate(
    void ** gameInput
)
{
    // 'E_FAIL'
    return 0x80004005;
}


BOOL APIENTRY DllMain( 
    HMODULE hModule,
    DWORD ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            CURRENT_MODULE = hModule;

            char system_path[MAX_PATH] {};

            if (SHGetFolderPathA( nullptr, CSIDL_SYSTEM, nullptr, SHGFP_TYPE_CURRENT, system_path ) == S_OK)
            {
                const HMODULE mod = LoadLibraryW( (fs::path( system_path ) / "version.dll").c_str() );

                if (mod)
                {
                    for (std::uint32_t i { 0 }; i < (sizeof( exports_version ) / sizeof( exports_version[0] )); i++)
                    {
                        version_dll[i] = GetProcAddress( mod, exports_version[i] );
                    }

                    o_LoadLibraryExA = &LoadLibraryExA;
                    o_PathCombineA = &PathCombineA;
                    o_CreateThread = &CreateThread;

                    Detour( &o_LoadLibraryExA, HookLoadLibraryExA );
                    Detour( &o_PathCombineA, HookPathCombineA );
                    Detour( &o_CreateThread, HookCreateThread );

                    CheckWine();
                }
            }

            break;
        }

        case DLL_PROCESS_DETACH:
        {
            Detour( &o_LoadLibraryExA, HookLoadLibraryExA, true );
            Detour( &o_PathCombineA, HookPathCombineA, true );
            Detour( &o_CreateThread, HookCreateThread, true );
            break;
        }
    }

    return TRUE;
}