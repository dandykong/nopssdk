#pragma once

namespace Utils
{
    // Current module handle ('version.dll')
    extern HMODULE CURRENT_MODULE { nullptr };

    // Was the PlayStation request thread found?
    extern bool PLAYSTATION_THREAD_FOUND { false };

    // Was the Wine environment found?
    extern bool WINE_FOUND { false };

    // Case-insensitive 'ends_with'
    static bool EndsWith(
        const std::string & str,
        const std::string & suffix
    )
    {
        // Check if the string is long enough to contain the suffix
        if (suffix.size() > str.size())
        {
            return false;
        }

        // Compare the suffix with the end of the string in a case-insensitive manner
        return std::equal( suffix.rbegin(), suffix.rend(), str.rbegin(),
            []( char c1, char c2 )
        {
            return std::tolower( c1 ) == std::tolower( c2 ); // Compare characters case-insensitively
        } );
    }


    // Create/remove detour
    template <typename T>
    void Detour( T ** org, T * hook, bool detach = false )
    {
        if ((org && hook))
        {
            LONG err {};

            err = DetourTransactionBegin();

            if (err != NO_ERROR)
                return;

            err = DetourUpdateThread( GetCurrentThread() );

            if (err != NO_ERROR)
            {
                DetourTransactionAbort();
                return;
            }

            if (detach)
                err = DetourDetach( reinterpret_cast<PVOID *>(org), reinterpret_cast<PVOID>(hook) );
            else
                err = DetourAttach( reinterpret_cast<PVOID *>(org), reinterpret_cast<PVOID>(hook) );

            if (err != NO_ERROR)
            {
                DetourTransactionAbort();
                return;
            }

            err = DetourTransactionCommit();

            if (err != NO_ERROR)
            {
                DetourTransactionAbort();
                return;
            }
        }
    }


    // Find the matching std::uint16_t value
    bool CheckUint16( 
        void * func,
        const std::uint16_t word
    )
    {
        const std::uint16_t * ptr = static_cast<std::uint16_t *>(func);

        for (int i { 0 }; i < (0x100 / sizeof( std::uint16_t )); ++i)
        {
            if (ptr[i] == word)
                return true;
        }

        return false;
    }


    // A simple Wine environment check
    void CheckWine()
    {
        const HMODULE ntdll_mod = GetModuleHandleA( "ntdll.dll" );

        if (ntdll_mod)
        {
            if (GetProcAddress( ntdll_mod, "wine_get_version" ) != 0)
                WINE_FOUND = true;
        }
    }
}