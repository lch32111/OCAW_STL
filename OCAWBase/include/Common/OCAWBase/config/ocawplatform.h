// config/ocawplatform.h

//    OCAW_PLATFORM_ANDROID
//    OCAW_PLATFORM_APPLE
//    OCAW_PLATFORM_IPHONE
//    OCAW_PLATFORM_IPHONE_SIMULATOR
//    OCAW_PLATFORM_OSX
//    OCAW_PLATFORM_LINUX
//    OCAW_PLATFORM_SAMSUNG_TV
//    OCAW_PLATFORM_WINDOWS
//    OCAW_PLATFORM_WIN32
//    OCAW_PLATFORM_WIN64
//    OCAW_PLATFORM_WINDOWS_PHONE
//    OCAW_PLATFORM_WINRT
//    OCAW_PLATFORM_SUN
//    OCAW_PLATFORM_LRB (Larrabee)
//    OCAW_PLATFORM_POSIX     (pseudo-platform; may be defined along with another platform like OCAW_PLATFORM_LINUX, OCAW_PLATFORM_UNIX, OCAW_PLATFORM_QNX)
//    OCAW_PLATFORM_UNIX      (pseudo-platform; may be defined along with another platform like OCAW_PLATFORM_LINUX)
//    OCAW_PLATFORM_CYGWIN    (pseudo-platform; may be defined along with another platform like OCAW_PLATFORM_LINUX)
//    OCAW_PLATFORM_MINGW     (pseudo-platform; may be defined along with another platform like OCAW_PLATFORM_WINDOWS)
//    OCAW_PLATFORM_MICROSOFT (pseudo-platform; may be defined along with another platform like OCAW_PLATFORM_WINDOWS)
//
//    OCAW_ABI_ARM_LINUX      (a.k.a. "eabi". for all platforms that use the CodeSourcery GNU/Linux toolchain, like Android)
//    OCAW_ABI_ARM_APPLE      (similar to eabi but not identical)
//    OCAW_ABI_ARM64_APPLE    (similar to eabi but not identical) https://developer.apple.com/library/ios/documentation/Xcode/Conceptual/iPhoneOSABIReference/Articles/ARM64FunctionCallingConventions.html
//    OCAW_ABI_ARM_WINCE      (similar to eabi but not identical)
//
// Other definitions emanated from this file inclue:
//    OCAW_PLATFORM_NAME = <string>
//    OCAW_PLATFORM_DESCRIPTION = <string>
//    OCAW_PROCESSOR_XXX
//    OCAW_MISALIGNED_SUPPORT_LEVEL=0|1|2
//    OCAW_SYSTEM_LITTLE_ENDIAN | OCAW_SYSTEM_BIG_ENDIAN
//    OCAW_ASM_STYLE_ATT | OCAW_ASM_STYLE_INTEL | OCAW_ASM_STYLE_MOTOROLA
//    OCAW_PLATFORM_PTR_SIZE = <integer size in bytes>
//    OCAW_PLATFORM_WORD_SIZE = <integer size in bytes>
//    OCAW_CACHE_LINE_SIZE = <integer size in bytes>
//---------------------------------------------------------------------------

/*
	OCAW_PLATFORM_MOBILE
	OCAW_PLATFORM_MOBILE is a peer to OCAW_PLATFORM_DESKTOP and OCAW_PLATFORM_CONSOLE. Their definition is qualitative rather
	than quantative, and refers to the general (usually weaker) capabilities of the machine. Mobile devices have a
	similar set of weaknesses that are useful to generally categorize. The primary motivation is to avoid code that
	tests for multiple mobile platforms on a line and needs to be updated every time we get a new one.
	For example, mobile platforms tend to have weaker ARM processors, don't have full multiple processor support,
	are hand-held, don't have mice (thought may have touch screens or basic cursor controls), have writable solid
	state permanent storage, Production user code shouldn't have too many expectations about the meaning of this define.

	OCAW_PLATFORM_DESKTOP
	This is similar to OCAW_PLATFORM_MOBILE in its qualitative nature and refers to platforms that are powerful.
	For example, they nearly always have virtual memory, mapped memory, hundreds of GB of writable disk storage,
	TCP/IP network connections, mice, keyboards, 512+ MB of RAM< multiprocessing, multiple display support.
	Production user code shouldn't have too many expectations about the meaning of this define.

	OCAW_PLATFORM_CONSOLE
	This is similar to OCAW_PLATFORM_MOBILE in its qualitative nature and refers to platforms that are consoles.
	This means platforms that are connected to TVs, are fairly powerful (especially graphics-wise), are tightly
	controlled by vendors, tend not to have mapped memory, tend to have TCP/IP, don't have multiple process support
	thought they might have multiple CPUs, support TV output only. Production user code shouldn't have too many
	expectations about the meaning of this define.
*/

#ifndef INCLUDED_ocawplatform_H
#define INCLUDED_ocawplatform_H

// Cygwin
// This is a psedu-platform which will be defined along with OCAW_PLATFORM_LINUX when
// using the Cygwin build environment.
#if defined(__CYGWIN__)
	#define OCAW_PLATFORM_CYGWIN 1
	#define OCAW_PLATFORM_DEKTOP 1
#endif

// MinGW
// This is a pseudo-platform which will be defined along with OCAW_PLATFORM_WINDOWS when
// using the MinGW Windows build environment
#if defined(__MINGW32__) || defined(__MINGW64__)
	#define OCAW_PLATFORM_MINGW 1
	#define OCAW_PLATFORM_DESKTOP 1
#endif

#if defined(OCAW_PLATFORM_PS4) || defined(__ORBIS__) || defined(OCAW_PLATFORM_KETTLE)
	// PlayStation 4
	// Orbis was Sony's code-name for the platform, which is not obsolete.
	// Kettle was an EA-specific code-name for the platform, which is now obsolete.
#if defined(OCAW_PLATFORM_PS4)
	#undef OCAW_PLATFORM_PS4
#endif
#define OCAW_PLATFORM_PS4 1

	// Backward compatibility:
		#if defined(OCAW_PLATFORM_KETTLE)
			#undef OCAW_PLATFORM_KETTLE
		#endif
	// End backward compatibility

	#define OCAW_PLATFORM_KETTLE 1
	#define OCAW_PLATFORM_NAME "PS4"
	#define OCAW_SYSTEM_LITTLE_ENDIAN 1
	#define OCAW_PLATFORM_DESCRIPTION "PS4 on x64"
	#define OCAW_PLATFORM_CONSOLE 1
	#define OCAW_PLATFORM_SONY 1
	#define OCAW_PLATFORM_POSIX 1
	// #define OCAW_POSIX_THREADS_AVAILABLE 1 // POSIX threading API is available but discouraged. Sony indicated use of the scePthreads* API is preferred.
	#define OCAW_PROCESSOR_X86_64 1
	#if defined(__GNUC__) || defined(__clang__)
		#define OCAW_ASM_STYLE_ATT 1
	#endif

#elif defined(OCAW_PLATFORM_XBOXONE) || defined(_DURANGO) || defined(_XBOX_ONE) || defined(OCAW_PLATFORM_CAPILANO) || defined(_GAMING_XBOX)
// XBox One
// Durango was Microsoft's code-name for the platform, which is now obsolete.
// Microsoft uses _DURANGO instead of some variation of _XBOX, thought it's not natively defined by the compiler.
// Capilano was an EA-specific code-name for the platform, which is now obsolete.
	#if defined(OCAW_PLATFORM_XBOXONE)
		#undef OCAW_PLATFORM_XBOXONE
	#endif
	#define OCAW_PLATFORM_XBOXONE 1

	// Backward compatibility:
		#if defined(OCAW_PLATFORM_CAPILANO)
			#undef OCAW_PLATFORM_CAPILANO
		#endif
		#define OCAW_PLATFORM_CAPILANO 1
		#if defined(OCAW_PLATFORM_CAPILAND_XDK) && !defined(OCAW_PLATFORM_XBOXONE_XDK)
			#define OCAW_PLATFORM_XBOXONE_XDK 1
		#endif
		#if defined(OCAW_PLATFORM_CAPILANO_ADK) && !defined(OCAW_PLATFORM_XBOXONE_ADK)
			#define OCAW_PLATFORM_XBOXONE_ADK 1
		#endif
	// End backward compatibility

	#if !defined(_DURANGO)
		#define _DURANGO
	#endif
	#define OCAW_PLATFORM_NAME "XBox One"
	//#define OCAW_PROCESSOR_X86 Currently our policy is that we dn't define this, even though x64 is something of a superset of x86.
	#define OCAW_PROCESSOR_X86_64 1
	#define OCAW_SYSTEM_LITTLE_ENDIAN 1
	#define OCAW_PLATFORM_DESCRIPTION "XBox One on x64"
	#define OCAW_ASM_STYLE_INTEL 1
	#define OCAW_PLATFORM_CONSOLE 1
	#define OCAW_PLATFORM_MICROSOFT 1

	// WINAPI_FAMILY defines - mirrored from winapifamily.h
#define OCAW_WINAPI_FAMILY_APP         1000
#define OCAW_WINAPI_FAMILY_DESKTOP_APP 1001
#define OCAW_WINAPI_FAMILY_PHONE_APP   1002
#define OCAW_WINAPI_FAMILY_TV_APP      1003
#define OCAW_WINAPI_FAMILY_TV_TITLE    1004
#define OCAW_WINAPI_FAMILY_GAMES       1006

	#if defined(WINAPI_FAMILY) 
		#include <winapifamily.h>
		#if defined(WINAPI_FAMILY_TV_TITLE) && WINAPI_FAMILY == WINAPI_FAMILY_TV_TITLE
			#define OCAW_WINAPI_FAMILY OCAW_WINAPI_FAMILY_TV_TITLE
		#elif defined(WINAPI_FAMILY_DESKTOP_APP) && WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP
			#define OCAW_WINAPI_FAMILY OCAW_WINAPI_FAMILY_DESKTOP_APP
		#elif defined(WINAPI_FAMILY_GAMES) && WINAPI_FAMILY == WINAPI_FAMILY_GAMES
			#define OCAW_WINAPI_FAMILY OCAW_WINAPI_FAMILY_GAMES
		#else
			#error Unsupported WINAPI_FAMILY
		#endif
	#else
		#error WINAPI_FAMILY should always be defined on Capilano.
	#endif

	// Macro to determine if a partition is enabled.
	#define OCAW_WINAPI_FAMILY_PARTITION(Partition)	(Partition)

	#if OCAW_WINAPI_FAMILY == OCAW_WINAPI_FAMILY_DESKTOP_APP
		#define OCAW_WINAPI_PARTITION_CORE     1
		#define OCAW_WINAPI_PARTITION_DESKTOP  1
		#define OCAW_WINAPI_PARTITION_APP      1
		#define OCAW_WINAPI_PARTITION_PC_APP   0
		#define OCAW_WIANPI_PARTITION_PHONE    0
		#define OCAW_WINAPI_PARTITION_TV_APP   0
		#define OCAW_WINAPI_PARTITION_TV_TITLE 0
		#define OCAW_WINAPI_PARTITION_GAMES    0
	#elif OCAW_WINAPI_FAMILY == OCAW_WINAPI_FAMILY_TV_TITLE
		#define OCAW_WINAPI_PARTITION_CORE     1
		#define OCAW_WINAPI_PARTITION_DESKTOP  0
		#define OCAW_WINAPI_PARTITION_APP      0
		#define OCAW_WINAPI_PARTITION_PC_APP   0
		#define OCAW_WIANPI_PARTITION_PHONE    0
		#define OCAW_WINAPI_PARTITION_TV_APP   0
		#define OCAW_WINAPI_PARTITION_TV_TITLE 1
		#define OCAW_WINAPI_PARTITION_GAMES    0
	#elif OCAW_WINAPI_FAMILY == OCAW_WINAPI_FAMILY_GAMES
		#define OCAW_WINAPI_PARTITION_CORE     1
		#define OCAW_WINAPI_PARTITION_DESKTOP  0
		#define OCAW_WINAPI_PARTITION_APP      0
		#define OCAW_WINAPI_PARTITION_PC_APP   0
		#define OCAW_WIANPI_PARTITION_PHONE    0
		#define OCAW_WINAPI_PARTITION_TV_APP   0
		#define OCAW_WINAPI_PARTITION_TV_TITLE 0
		#define OCAW_WINAPI_PARTITION_GAMES    1
	#else
	#error Unsupported WINAPI_FAMILY
	#endif

	#if OCAW_WINAPI_FAMILY_PARTITION(OCAW_WINAPI_PARTITION_GAMES)
	#define CS_UNDEFINED_STRING 			1
	#define CS_UNDEFINED_STRING 		1
	#endif

	#if OCAW_WINAPI_FAMILY_PARTITION(OCAW_WINAPI_PARTITION_TV_TITLE)
	#define OCAW_PLATFORM_XBOXONE_XDK 	1
	#endif
#elif defined(OCAW_PLATFORM_LRB) || defined(__LRB__) || (defined(__EDG__) && defined(__ICC) && defined(__x86_64__))
	#undef  OCAW_PLATFORM_LRB
	#define OCAW_PLATFORM_LRB         1
	#define OCAW_PLATFORM_NAME        "Larrabee"
	#define OCAW_PLATFORM_DESCRIPTION "Larrabee on LRB1"
	#define OCAW_PROCESSOR_X86_64 1
	#if defined(BYTE_ORDER) && (BYTE_ORDER == 4321)
		#define OCAW_SYSTEM_BIG_ENDIAN 1
	#else
		#define OCAW_SYSTEM_LITTLE_ENDIAN 1
	#endif
	#define OCAW_PROCESSOR_LRB 1
	#define OCAW_PROCESSOR_LRB1 1       // Larrabee version 1
	#define OCAW_ASM_STYLE_ATT 1        // Both types of asm style
	#define OCAW_ASM_STYLE_INTEL 1      // are supported.
	#define OCAW_PLATFORM_DESKTOP 1

// Android (Google phone OS)
#elif defined(OCAW_PLATFORM_ANDROID) || defined(__ANDROID__)
	#undef OCAW_PLATFORM_ANDROID
	#define OCAW_PLATFORM_ANDROID 1
	#define OCAW_PLATFORM_LINUX 1
	#define OCAW_PLATFORM_UNIX 1
	#define OCAW_PLATFORM_POSIX 1
	#define OCAW_PLATFORM_NAME "Android"
	#define OCAW_ASM_STYLE_ATT 1
	#if defined(__arm__)
		#define OCAW_ABI_ARM_LINUX 1 // a.k.a. "ARM eabi"
		#define OCAW_PROCESSOR_ARM32 1
		#define OCAW_PLATFORM_DESCRIPTION "Android on ARM"
	#elif defined(__aarch64__)
		#define OCAW_PROCESSOR_ARM64 1
		#define OCAW_PLATFORM_DESCRIPTION "Android on ARM64"
	#elif defined(__i386__)
		#define OCAW_PROCESSOR_X86 1
		#define OCAW_PLATFORM_DESCRIPTION "Android on x86"
	#elif defined(__x86_64)
		#define OCAW_PROCESSOR_X86_64 1
		#define OCAW_PLATFORM_DESCRIPTION "Android on x64"
	#else
		#error Unknown processor
	#endif
	#if !defined(OCAW_SYSTEM_BIG_ENDIAN) && !defined(OCAW_SYSTEM_LITTLE_ENDIAN)
		#define OCAW_SYSTEM_LITTLE_ENDIAN 1
	#endif
	#define OCAW_PLATFORM_MOBILE 1

// Samsung SMART TV - a Linux-based smart TV
#elif defined(OCAW_PLATFORM_SAMSUNG_TV)
	#undef  OCAW_PLATFORM_SAMSUNG_TV
	#define OCAW_PLATFORM_SAMSUNG_TV 1
	#define OCAW_PLATFORM_LINUX 1
	#define OCAW_PLATFORM_UNIX 1
	#define OCAW_PLATFORM_POSIX 1
	#define OCAW_PLATFORM_NAME "SamsungTV"
	#define OCAW_PLATFORM_DESCRIPTION "Samsung SMART TV on ARM"
	#define OCAW_ASM_STYLE_ATT 1
	#define OCAW_SYSTEM_LITTLE_ENDIAN 1
	#define OCAW_PROCESSOR_ARM32 1
	#define OCAW_ABI_ARM_LINUX 1 // a.k.a. "ARM eabi"
	#define OCAW_PROCESSOR_ARM7 1

#elif defined(__APPLE__) && __APPLE__
#include <TargetConditionals.h>

	// Apple family of operating systems.
	#define OCAW_PLATFORM_APPLE
	#define OCAW_PLATFORM_POSIX 1

// iPhone
// TARGET_OS_IPHONE will be undefined on an unknown compiler, and will be defined on gcc.
	#if defined(OCAW_PLATFORM_IPHONE) || defined(__IPHONE__) || (defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE) || (defined(TARGET_IPHONE_SIMULATOR) && TARGET_IPHONE_SIMULATOR)
		#undef OCAW_PLATFORM_IPHONE
		#define OCAW_PLATFORM_IPHONE 1
		#define OCAW_PLATFORM_NAME "iPhone"
		#define OCAW_ASM_STYLE_ATT 1
		#define OCAW_POSIX_THREADS_AVAILABLE 1
		#if defined(__arm__)
			#define OCAW_ABI_ARM_APPLE 1
			#define OCAW_PROCESSOR_ARM32 1
			#define OCAW_SYSTEM_LITTLE_ENDIAN 1
			#define OCAW_PLATFORM_DESCRIPTION "iPhone on ARM"
		#elif defined(__aarch64__) || defined(__AARCH64)
			#define OCAW_ABI_ARM64_APPLE 1
			#define OCAW_PROCESSOR_ARM64 1
			#define OCAW_SYSTEM_LITTLE_ENDIAN 1
			#define OCAW_PLATFORM_DESCRIPTION "iPhone on ARM64"
		#elif defined(__i386__)
			#define OCAW_PLATFORM_IPHONE_SIMULATOR 1
			#define OCAW_PROCESSOR_X86 1
			#define OCAW_SYSTEM_LITTLE_ENDIAN 1
			#define OCAW_PLATFORM_DESCRIPTION "iPhone simulator on x86"
		#elif defined(__x86_64) || defined(__amd64)
			#define OCAW_PROCESSOR_X86_64 1
			#define OCAW_SYSTEM_LITTLE_ENDIAN 1
			#define OCAW_PLATFORM_DESCRIPTION "iPhone simulator on x64"
		#else
			#error Unknown processor
		#endif
		#define OCAW_PLATFORM MOBILE1
	#elif	
	#endif

#endif
