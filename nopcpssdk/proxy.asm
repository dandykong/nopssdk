.code
	extern version_dll:QWORD
	GetFileVersionInfoA proc
		jmp QWORD ptr version_dll[0 * 8]
	GetFileVersionInfoA endp
	GetFileVersionInfoByHandle proc
		jmp QWORD ptr version_dll[1 * 8]
	GetFileVersionInfoByHandle endp
	GetFileVersionInfoExA proc
		jmp QWORD ptr version_dll[2 * 8]
	GetFileVersionInfoExA endp
	GetFileVersionInfoExW proc
		jmp QWORD ptr version_dll[3 * 8]
	GetFileVersionInfoExW endp
	GetFileVersionInfoSizeA proc
		jmp QWORD ptr version_dll[4 * 8]
	GetFileVersionInfoSizeA endp
	GetFileVersionInfoSizeExA proc
		jmp QWORD ptr version_dll[5 * 8]
	GetFileVersionInfoSizeExA endp
	GetFileVersionInfoSizeExW proc
		jmp QWORD ptr version_dll[6 * 8]
	GetFileVersionInfoSizeExW endp
	GetFileVersionInfoSizeW proc
		jmp QWORD ptr version_dll[7 * 8]
	GetFileVersionInfoSizeW endp
	GetFileVersionInfoW proc
		jmp QWORD ptr version_dll[8 * 8]
	GetFileVersionInfoW endp
	VerFindFileA proc
		jmp QWORD ptr version_dll[9 * 8]
	VerFindFileA endp
	VerFindFileW proc
		jmp QWORD ptr version_dll[10 * 8]
	VerFindFileW endp
	VerInstallFileA proc
		jmp QWORD ptr version_dll[11 * 8]
	VerInstallFileA endp
	VerInstallFileW proc
		jmp QWORD ptr version_dll[12 * 8]
	VerInstallFileW endp
	VerLanguageNameA proc
		jmp QWORD ptr version_dll[13 * 8]
	VerLanguageNameA endp
	VerLanguageNameW proc
		jmp QWORD ptr version_dll[14 * 8]
	VerLanguageNameW endp
	VerQueryValueA proc
		jmp QWORD ptr version_dll[15 * 8]
	VerQueryValueA endp
	VerQueryValueW proc
		jmp QWORD ptr version_dll[16 * 8]
	VerQueryValueW endp
end