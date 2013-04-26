/*****************************************************************************
@doc            INT EXT
******************************************************************************
* $ProjectName:  $
* $ProjectRevision:  $
*-----------------------------------------------------------------------------
* $Source: z:/pr/okbase/sw/ok/rcs/ok.h $
* $Revision: 1.2 $
*-----------------------------------------------------------------------------
* $Author: TBruendl $
*-----------------------------------------------------------------------------
* History: see EOF
*-----------------------------------------------------------------------------
*
* Copyright (c) 2000 OMNIKEY AG
******************************************************************************/

/*****************************************************************************
** @module OK Overview on OK.H Common Include File |
**
** This file is intended to be used by all Omnikey written code. It's main
** purpose is to provide a common coding style and help to keep the code
** operating system independent.
** <nl>It contains type definitions for all common data types and pointers to
** them. Furthermore commonly used macros and company-wide error codes are
** defined here.
** <nl>There is another include file called OKOS.H that contains some pragmas
** that
** disable certain unimportant warnings for the Microsoft Compiler. This is
** necessary to compile WINDOWS.H under 32-bit at warning level 4. The same
** pragmas occur in OK.H for the case where OKOS.H is not present. They are
** properly guarded to be activated only when MSC is in use.
** <nl>In any C-Code the include file order should be that way:
** <nl>
** 1. Include 'okos.h' if necessary (e.g. an '#include <lt>windows.h<gt>'
** statement will follow). <cr>
** 2. Include the standard compiler files like 'windows.h' and 'stdio.h'. <cr>
** 3. Include 'ok.h' to get all the Omnikey definitions and types. <cr>
** 4. Include the Omnikey module include files like 'mem.h' or 'errl.h' which
** rely upon the presence of 'ok.h'.
**
**
** @module OK Structure Packing Conventions |
**
** Currently the following packing is used by the compiler settings in our
** environment: 16-Bit PC - 2, 32-Bit Windows - 8, OS/2 - 4.
** <nl>Every external include file that contains structures must include
** 'okpon.h' at the beginning and 'okpoff.h' at the end. These include files
** set the structure packing to the above values in dependence of the target
** operating system and compiler (#pragma statement syntax depends on the
** compiler used) overriding the compiler flags. To set a specific other
** packing (e.g. 1) for a certain structure inside an include file use:
** <nl>#include <lt>okpon1.h<gt>
** <cr>... define the structure that shall get packing 1 here ...
** <cr>#include <lt>okpon.h<gt>
** <nl>There are include files named 'OKPONx.H', where 'x' may be 1, 2, 4 or
** 8. Do NOT write #pragma statements directly into your code for reasons
** described above!
*****************************************************************************/

#ifndef _INC_OK
#define _INC_OK

/***************************************************************************/
/* Standard Constants                                                      */
/***************************************************************************/

#ifndef LINT_ARGS
   #define LINT_ARGS       1            /* Turn on Parameter checking????? */
#endif

/*****************************************************************************
** @module OK Operating System Identifiers |
**
** One of the following constants <b has to be set> at compile time to identify
** the operating system the code is compiled under. These are usually in the
** compiler options (e.g. -DS_MSDOS). The appropriate constant is automatically
** defined when compiling in the Common Development Environment depending on the
** OS-identifier used when calling the makefile. The following list shows first
** the constant that has to be defined, next the letter that is used as
** OS-identifier when the code is compiled (e.g. 'xwd' during makefile
** invocation for general Windows debug code), finally the operating system
** as plain text.
** <nl>
**      <bl> S_MSDOS   <tab> (D) <tab> MS-DOS or PC-DOS
** <cr> <bl> S_BOOT    <tab> (B) <tab> PC Boot-Code Environment
** <cr> <bl> S_WIN     <tab> (W) <tab> Windows 3.x
** <cr> <bl> S_VXD     <tab> (X) <tab> Windows VxD
** <cr> <bl> S_WNT     <tab> (N) <tab> Windows NT
** <cr> <bl> S_KNT     <tab> (M) <tab> Windows NT Kernel Mode
** <cr> <bl> S_WDM     <tab> (L) <tab> Windows 98 Kernel Mode
** <cr> <bl> S_OS2     <tab> (O) <tab> OS/2 (16 bit)
** <cr> <bl> S_OS2_32  <tab> (O) <tab> OS/2 (32 bit)
** <cr> <bl> S_KOS2_16 <tab> (P) <tab> OS/2 Kernel Mode (16 bit)
** <cr> <bl> S_KOS2_32 <tab> (Q) <tab> OS/2 Kernel Mode (32 bit)
** <cr> <bl> S_UNIX    <tab> --- <tab> Standard Unix; may be used instead of
**                               S_AIX, S_SOLARIS, S_HPUX, S_LINUX in the code
**                               for standard UNIX constructs. Must be defined
**                               in addition to one of the special UNIX
**                               constants.
** <cr> <bl> S_AIX     <tab> (A) <tab> IBM AIX (define also S_UNIX)
** <cr> <bl> S_SOLARIS <tab> (S) <tab> Sun Solaris (define also S_UNIX)
** <cr> <bl> S_HPUX    <tab> (H) <tab> HP-Unix (define also S_UNIX)
** <cr> <bl> S_U6000   <tab> --- <tab> Unisys 6000 (define also S_UNIX)
** <cr> <bl> S_OSF     <tab> --- <tab> Digital OSF/1 (define also S_UNIX)
** <cr> <bl> S_SINIX   <tab> (I) <tab> SINIX (define also S_UNIX)
** <cr> <bl> S_LINUX   <tab> (U) <tab> LINUX (define also S_UNIX)
** <cr> <bl> S_OS400   <tab> (4) <tab> IBM OS/400
** <cr> <bl> S_VMS     <tab> (V) <tab> DEC Open-VMS
** <cr> <bl> S_MVS     <tab> --- <tab> IBM MVS
** <cr> <bl> S_SHARC   <tab> --- <tab> ADSP 21062 "Sharc" (CARDMAN-S)
** <cr> <bl> S_PSION   <tab> --- <tab> Psion Organizer
** <cr> <bl> S_SBFW    <tab> (F) <tab> SAFE-Board Firmware
**
** for historical reasons some OS Identifiers are ambiguous (S_U6000 = S_LINUX = U)
** (S_OSF = S_SINIX = I) !!
**
** @module OK Processor Identifiers |
**
** Processor identifiers may be defined like the operating system
** identifiers to make the target processor known to the code. This
** identifier is at least necessary to know the integer byte ordering
** (little or big endian). Therefore, depending on the processor type the
** constants LITTLE_ENDIAN and LENDIAN, resp. BIG_ENDIAN and BENDIAN are
** defined by OK.H. Because of compatibility reasons, there are two constants
** meaning the same thing.
** <nl>If the processor type is not defined in
** the compiler options, a default processor is derived from the
** <m OK Operating System Identifiers>.
** <nl>
**      <bl> P_86      <tab> Intel 8086/88        <tab> default for S_BOOT
** <cr> <bl> P_286     <tab> Intel 80286          <tab> default for S_MSDOS,
**                                                S_WIN, S_OS2
** <cr> <bl> P_386     <tab> Intel 80386          <tab> default for S_WNT, S_WDM,
**                                                S_OS2_32, S_VXD, S_KNT, S_LINUX,
**                                                S_KOS2_16, S_KOS2_32, S_U6000
** <cr> <bl> P_PENTIUM <tab> Intel Pentium        <tab>
** <cr> <bl> P_SPARC   <tab> SUN Sparc            <tab> default for S_SOLARIS
** <cr> <bl> P_RS6000  <tab> IBM Risc 6000        <tab> default for S_AIX
** <cr> <bl> P_PA_RISC <tab> HP-UX Workstations   <tab> default for S_HPUX
** <cr> <bl> P_ALPHA   <tab> DEC Alpha            <tab>
** <cr> <bl> P_AS400   <tab> IBM AS/400           <tab> default for S_OS400
** <cr> <bl> P_VAX     <tab> DEC Vax              <tab> default for S_VMS
** <cr> <bl> P_MVS     <tab> IBM MVS              <tab> default for S_MVS
** <cr> <bl> P_2106x   <tab> ADSP 2106x "Sharc"   <tab> default for S_SHARC
** <cr> <bl> P_6303    <tab> Hitachi 6301 or 6303 <tab> default for S_PSION,
**                                                S_SBFW
******************************************************************************
*/

/* Set Default OS Identifiers */

#ifdef __2106x__
   #ifndef S_SHARC
      #define S_SHARC
   #endif
   #ifndef SWSPEED
      #define SWSPEED
   #endif
#endif

#ifdef MVS
   #ifndef S_MVS
      #define S_MVS
   #endif
#endif

#ifdef VMS
   #ifndef S_VMS
      #define S_VMS
   #endif
#endif

/* Check if OS constant is set */
#if   defined S_MSDOS || defined S_BOOT || defined S_WIN
#elif defined S_VXD || defined S_WNT || defined S_KNT || defined S_OS2
#elif defined S_OS2_32 || defined S_KOS2_16 || defined S_KOS2_32
#elif defined S_UNIX || defined S_OS400 || defined S_VMS || defined S_MVS
#elif defined S_SHARC || defined S_PSION || defined S_SBFW
#else
   #error "No target Operating system defined (e.g. S_WIN), see OK.H"
#endif

/* Automatic Setting of Processor Type */

#if defined S_MSDOS || defined S_WIN || defined S_OS2
   #if !defined P_86 && !defined P_286 && !defined P_386 && !defined P_PENTIUM
      #define P_286
   #endif
#elif defined S_BOOT
   #if !defined P_86 && !defined P_286 && !defined P_386 && !defined P_PENTIUM
      #define P_86
   #endif
#elif defined S_WNT || defined S_OS2_32 || defined S_VXD || defined S_KNT || \
      defined S_KOS2_16 || defined S_KOS2_32 || defined S_U6000 || defined S_WDM
   #if !defined P_386 && !defined P_PENTIUM && !defined P_ALPHA
      #define P_386
   #endif
#elif defined S_LINUX
   #if !defined P_386 && !defined P_PENTIUM
      #define P_386
   #endif
#elif defined S_AIX
   #ifndef P_RS6000
      #define P_RS6000
   #endif
#elif defined S_SOLARIS
   #ifndef P_SPARC
      #define P_SPARC
   #endif
#elif defined S_HPUX
   #ifndef P_PA_RISC
      #define P_PA_RISC
   #endif
#elif defined S_OS400
   #if !defined P_AS400
      #define P_AS400
   #endif
#elif defined S_VMS
   #if !defined P_VAX && !defined P_ALPHA
      #define P_VAX
   #endif
#elif defined S_MVS
   #if !defined P_MVS
      #define P_MVS
   #endif
#elif defined S_PSION
   #ifndef P_6303
      #define P_6303
   #endif
#elif defined S_SBFW
   #ifndef P_6303
      #define P_6303
   #endif
#elif defined S_SHARC
   #ifndef P_2106x
      #define P_2106x
   #endif
#else
   #error "No target system defined"
#endif

/* Integer Byte Ordering */

#if defined P_VAX || defined P_86 || defined P_286 || defined P_386 ||\
    defined P_PENTIUM
   #ifndef LITTLE_ENDIAN
      #define LITTLE_ENDIAN             /* used by OK  */
   #endif
   #ifndef LENDIAN
      #define LENDIAN                   /* used by third party code */
   #endif
#elif defined P_SPARC || defined P_SHARC || defined P_MVS ||\
   defined P_PA_RISC || defined P_RS6000 || defined P_AS400
   #ifndef BIG_ENDIAN
      #define BIG_ENDIAN                /* used by OK  */
   #endif
   #ifndef BENDIAN
      #define BENDIAN                   /* used by third party code */
   #endif
#endif

/* Logical Checks for Operating System */

#ifndef WINVER
   #define WINVER  0x0300
#endif

/* Disabling warnings allows usage of WIN32 <windows.h> at warning level 4 */

#if defined _MSC_VER
   /* remove S_BOOT because MSC6.00 doesn't support #pragma warning         */
   #if defined S_MSDOS || defined S_WIN
      #pragma warning (disable: 4001) /*nonstd. extension 'single line comm.*/
      #pragma warning (disable: 4057) /*indirection to slightly diff. types*/
      #pragma warning (disable: 4699) /*Precompiled Headers ...*/
      #pragma warning (disable: 4209) /*non.ex. benign typedef redefinition*/
   #elif defined S_VXD || defined S_WNT || defined S_KNT
      #pragma warning (disable: 4001) /*nonstd. extension 'single line comm.*/
      #pragma warning (disable: 4057) /*'uns. char *' differs in indirection*/
      #pragma warning (disable: 4115) /*named type definition in parentheses*/
      #pragma warning (disable: 4200) /*non.ex. zero-sized array in str/union*/
      #pragma warning (disable: 4201) /*non.ex. nameless struct/union*/
      #pragma warning (default: 4209) /*non.ex. benign typedef redefinition*/
      #pragma warning (disable: 4214) /*non.ex. bit field types other th. int*/
      #pragma warning (disable: 4514) /*unreferenced inline function removed*/
   #endif
#endif /* _MSC_VER */

#include <okpon.h>

/*
** @module OK General Modifiers |
** For portability reasons, the following modifiers are defined which have to
** be used instead of writing e.g. '__far' directly. Especially every external
** callable function should contain the ENTRY keyword. For functions with
** variable length argument lists use CENTRY.
** <nl>
** For description of the entries in the 'System' column, see
** <m OK Operating System Identifiers> resp. <m OK Processor Identifiers>.
**
** <nl> <b Modifier> <tab>  <b System>              <tab><tab><tab> <b Value>
** <cr> NEAR     <tab> S_OS2, S_KOS2_16 (16-Bit)   <tab><tab> near
** <cr> NEAR     <tab> S_WIN, S_MSDOS, S_BOOT      <tab> _near
** <cr> NEAR     <tab> empty in all other systems
**
** <cr> FAR      <tab> S_OS2, S_KOS2_16 (16-Bit)   <tab><tab> far
** <cr> FAR      <tab> S_WIN, S_MSDOS, S_BOOT      <tab> _far
** <cr> FAR      <tab> empty in all other systems
**
** <cr> PASCAL   <tab> S_OS2, S_KOS2_16 (16-Bit)   <tab><tab> pascal
** <cr> PASCAL   <tab> S_WIN, S_MSDOS              <tab><tab> _pascal
** <cr> PASCAL   <tab> empty in all other systems
**
** <cr> ENTRY    <tab> S_OS2_32, S_KOS2_32 <tab><tab> _System
** <cr> ENTRY    <tab> S_OS2, C-Set2 Comp. <tab><tab><tab> _Far16 _Pascal
** <cr> ENTRY    <tab> S_OS2, other Comp.  <tab><tab><tab>
**                                                    _far _pascal _loadds
** <cr> ENTRY    <tab> S_KOS2_16           <tab><tab><tab> near _pascal
** <cr> ENTRY    <tab> S_WIN               <tab><tab><tab>
**                                                    _far _pascal _loadds
** <cr> ENTRY    <tab> S_WNT, S_VXD, S_KNT <tab><tab> _stdcall
** <cr> ENTRY    <tab> empty in all other systems
**
** <cr> CENTRY   <tab> S_OS2_32, S_KOS2_32 <tab><tab> _System
** <cr> CENTRY   <tab> S_OS2, C-Set2 Comp. <tab><tab><tab> _Far16 _Cdecl
** <cr> CENTRY   <tab> S_OS2, other Comp.  <tab><tab><tab>
**                                                    _far _cdecl _loadds
** <cr> CENTRY   <tab> S_KOS2_16           <tab><tab><tab> near _cdecl
** <cr> CENTRY   <tab> S_WIN               <tab><tab><tab>
**                                                    _far _cdecl _loadds
** <cr> CENTRY   <tab> S_WNT, S_VXD, S_KNT <tab><tab> _cdecl
** <cr> CENTRY   <tab> empty in all other systems
**
** <cr> REGISTER <tab> P_6303              <tab><tab>
** <cr> REGISTER <tab> all other systems   <tab><tab><tab> register
*/

#if defined S_OS2 || defined S_KOS2_16
   #ifndef OS2_INCLUDED
      #define FAR     far
      #define NEAR    near
   #endif
#elif defined S_MSDOS || defined S_WIN || defined S_BOOT
   #define FAR     _far
   #define NEAR    _near
#else
   #ifndef _WINDEF_
      #define FAR
      #define NEAR
   #endif
#endif

#if defined S_OS2 || defined S_KOS2_16
   #ifndef OS2_INCLUDED
      #define PASCAL  pascal
   #endif
#elif defined S_MSDOS || defined S_WIN
   #define PASCAL  _pascal
#else
   #ifndef _WINDEF_
      #define PASCAL
   #endif
#endif

#if defined P_6303
   #define REGISTER
#else
   #define REGISTER register
#endif

#if defined S_OS2_32  || defined S_KOS2_32
   #define ENTRY   _System              /* Library entry Pascal convention */
   #define CENTRY  _System              /* Library entry C convention */
#elif defined S_WIN
   #define ENTRY   _far _pascal _loadds
   #define CENTRY  _far _cdecl _loadds
#elif defined S_OS2 && defined C_C2     /* C-Set/2 Compiler */
   #define ENTRY   _Far16 _Pascal
   #define CENTRY  _Far16 _Cdecl
#elif defined S_OS2 && !defined C_C2    /* other Compiler */
   #define ENTRY   _far _pascal _loadds
   #define CENTRY  _far _cdecl _loadds
#elif defined S_WNT || defined S_VXD || defined S_KNT
   #define ENTRY   _stdcall
   #define CENTRY  _cdecl
#elif defined S_KOS2_16
   #define ENTRY   near _pascal
   #define CENTRY  near _cdecl
#else
   #define ENTRY
   #define CENTRY
#endif

/*
** @types OK Common Types | Every common C language type has been redefined
** here to insure a common coding style and ease portability problems. In
** addition to the standard types also some frequently used additional types
** like 'BOOL' are defined here.
** <nl>The following list shows in brackets the header that has to be used for
** a variable of that type (hungarian notation) e.g.
** <nl>ULONG ulLength;
** <nl>NOTE: Since type definitions can not be overwritten and every type may
** only
** be defined once, each type definition is guarded against the most common
** standard include files as e.g. windows.h. So these types will only be defined
** here if they have not already been defined in a standard include file.
** <nl>NOTE: 'short' is 32 bit on some Machines!!!
** On SHARC processor even CHAR is 32 bit!!!
** Therefore for portability reasons xxx16 Datatypes should not be
** used, because one can't rely on the fact that those types will
** always be of 16-bit size.
*/

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED)
   typedef char CHAR;             /* @type (ch) <tab> ASCII character signed */
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED)
   typedef int INT;               /* @type (i) <tab> native signed integer */
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED)
   typedef short SHORT;           /* @type (sh) <tab> 16-bit signed integer */
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && !defined(__AFX_H__) \
    && !defined(_INC_WINDOWS)
   typedef long LONG;             /* @type (l) <tab> 32-bit signed integer */
#endif

#if (defined(S_WNT) || defined(S_VXD) || defined(S_KNT))
   typedef __int64  LONG64;       /* @type (ll) <tab> 64-bit signed integer (Win95 & NT) */
#elif (defined(S_UNIX))
   typedef long long LONG64;      /* @type (ll) <tab> 64-bit signed integer (UNIX) */
#else
   typedef double LONG64;         /* @type (ll) <tab> 64-bit signed integer (all other systems) */
#endif

#ifndef VOID
   typedef void VOID;             /* @type (v) <tab> Void */
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_)
   typedef unsigned char  UCHAR;  /* @type (uch) <tab> 8-bit unsigned
                                                       integer */
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_)
   typedef unsigned short USHORT; /* @type (us) <tab> 16-bit unsigned integer */
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_) && \
    ((WINVER < 0x030a) || defined S_KNT) && !defined(__AFX_H__)
   typedef unsigned int   UINT;   /* @type (ui) <tab> native unsigned integer */
#endif


#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_) && defined(S_KNT) && \
    !defined(__AFX_H__)
   typedef unsigned int   UINT16; /* @type (ui) <tab> native unsigned integer */
#endif
#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_) && defined(S_KNT) && \
    !defined(__AFX_H__)
   typedef unsigned long  UINT32; /* @type (ui) <tab> native unsigned integer */
#endif


#if !defined(_INC_WINDOWS) && !defined(OS2_INCLUDED) && \
    !defined(DEFS_INCLUDED) && !defined(__vtoolsd_h_) && \
    !defined(_WINDEF_) && !defined(__AFX_H__)
   typedef unsigned short WORD;   /* @type (w) <tab> 16-bit unsigned integer */
#elif (defined S_OS2_32 || S_KOS2_32) && !(defined DEFS_INCLUDED)
   typedef unsigned short WORD;   /* (w)   16-bit unsigned integer */
#elif defined S_KOS2_16
   typedef unsigned short WORD;   /* (w)   16-bit unsigned integer */
#endif

typedef unsigned short bit16;     /* @type (w) <tab> 16-bit unsigned integer */

#if !defined(_INC_WINDOWS) && !defined(__vtoolsd_h_) && \
    !defined(_WINDEF_) && !defined(__AFX_H__) && !defined(OS2_INCLUDED) && \
    !defined(DEFS_INCLUDED)
   typedef unsigned long  DWORD;  /* @type (dw) <tab> 32-bit unsigned integer */
#elif (defined S_OS2_32 || S_KOS2_32) && !(defined DEFS_INCLUDED)
   typedef unsigned long  DWORD;
#elif defined S_KOS2_16
   typedef unsigned long  DWORD;
#endif

typedef unsigned long  bit32;     /* @type (dw) <tab> 32-bit unsigned integer */

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_)
   typedef unsigned long  ULONG;  /* @type (ul) <tab> 32-bit unsigned integer */
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_) && !defined(_INC_WINDOWS) && \
    !defined(XMD_H) && !defined(__AFX_H__)
   typedef unsigned char  BYTE;   /* @type (b) <tab> 8-bit unsigned integer */
#endif

#if (defined(S_WNT) || defined(S_VXD) || defined(S_KNT))
   typedef unsigned __int64  ULONG64;  /* @type (ull) <tab> 64-bit unsigned integer (Win95 & NT) */
#elif (defined(S_UNIX))
   typedef unsigned long long ULONG64; /* @type (ull) <tab> 64-bit unsigned integer (UNIX) */
#else
   typedef double            ULONG64;  /* @type (ull) <tab> 64-bit unsigned integer (all other systems) */
#endif

#if (defined(S_WNT) || defined(S_VXD) || defined(S_KNT)) && \
    (!defined(__vtoolsd_h_) && !defined(_WINDEF_))
   typedef unsigned int   BOOL;   /* @type (f) <tab> Bool for S_WNT, S_VXD,
                                                     S_KNT */
#elif (defined(S_WIN) || defined(S_MSDOS) || defined(S_BOOT) || \
       defined(S_OS2) || defined(S_KOS2_16) || defined(S_SBFW)) && \
      !defined(_INC_WINDOWS) && !defined(__AFX_H__)
   typedef unsigned short BOOL;   /* @type (f) <tab> Bool for S_WIN, S_MSDOS,
                                               S_BOOT */
#elif (defined(S_UNIX) && !defined(XMD_H)) ||\
      (defined(S_OS2_32) && !defined(OS2_INCLUDED)) ||\
      (defined(S_KOS2_32) && !defined(DEFS_INCLUDED) && \
      !defined(OS2_INCLUDED)) ||\
      defined(S_SHARC) || defined(S_OS400) || defined(S_VMS) || defined(S_MVS)
   typedef unsigned long BOOL;    /* @type (f) <tab> Bool for all other
                                               operating systems */
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED)
   typedef unsigned long  BOOL32; /* @type (f) <tab> explicit 32-bit bool */

   typedef unsigned short BOOL16; /* @type (f) <tab> explicit 16-bit bool */
#elif defined S_KOS2_16
   typedef unsigned long  BOOL32; /* @type (f) <tab> explicit 32-bit bool */

   typedef unsigned short BOOL16; /* @type (f) <tab> explicit 16-bit bool */
#endif

#if !defined(_WINNT_) && !defined(__vtoolsd_h_) && \
    !defined(_WINDEF_) && !defined(_WCHAR_DEFINED) && \
    !defined(_MAPINLS_H_) && !defined(MAPIDEFS_H)
   typedef WORD WCHAR;             /* @type (wc) <tab> Unicode character */
#endif

typedef const CHAR  CONSTCHAR;    /* @type (ch) <tab> character */

typedef LONG  OKERR;             /* @type (e) <tab> standard OK Errorcode */
typedef SHORT OKERR16;           /* @type (e) <tab> explicit 16-bit OK
                                           Errorcode */
typedef LONG  OKERR32;           /* @type (e) <tab> explicit 32-bit OK
                                           Errorcode */

#if defined(S_UNIX)
   typedef int HANDLE;            /* @type (h) <tab> generic handle (UNIX only) */
#endif

/*
** @types OK Pointers to Common Types | For each type defined in OK.H, there
** exist several versions of pointer types to them; e.g.
** <nl>
** <bl> PCHAR  <tab> Pointer to CHAR (usually FAR). Since Windows 3.1 defines
**                   some of the P* pointer types explicitly as NEAR and
**                   therefore overrides our definition, LP* or GP* pointers
**                   should be used instead. <nl>
** <bl> GPCHAR <tab> General pointer to CHAR. Is NEAR for S_MSDOS and FAR
**                   otherwise. <nl>
** <bl> LPCHAR <tab> Long pointer to CHAR. Is always FAR (should be used for
**                   portability of code).
** <nl>
** There are P-, GP- and LP- pointer types available for all types defined in
** OK.H. The default pointer type is LP*.
*/

#ifndef NULL
   #define NULL  ((void *)0)      /* @type define NULL | ((void *)0) |
                                           <tab> NULL Pointer */
#endif

typedef const CHAR FAR *PCONSTCHAR;  /* @type (pch) <tab> pointer to
character*/

typedef const VOID FAR *PCONSTVOID;  /* @type (pv) <tab> pointer to void*/

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_)
   typedef VOID   FAR *PVOID;           /* @type (pv) <tab> pointer to void*/
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_)
   typedef CHAR   FAR *PCHAR;           /* @type (pch) <tab> pointer to
   character*/
#endif

#if !defined(_INC_WINDOWS) && !defined(__vtoolsd_h_) && \
    !defined(_WINDEF_) && !defined(__AFX_H__)
   typedef WCHAR FAR *PWCHAR;           /* @type (pwc) <tab> Unicode character*/
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_)
   typedef UCHAR  FAR *PUCHAR;          /* @type (puch) <tab> pointer to
   unsigned character*/
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_) && !defined(_INC_WINDOWS)
   typedef BYTE   FAR *PBYTE;           /* @type (pb) <tab> pointer to byte*/
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(_WINDEF_)
   typedef CHAR   FAR *PSZ;             /* @type (psz) <tab> pointer to
   string*/
#endif

#if !defined(_INC_WINDOWS) && !defined(__vtoolsd_h_) && \
    !defined(_WINDEF_) && !defined(__AFX_H__)
   typedef WCHAR FAR *PWSZ;             /* @type (pwsz) <tab> Unicode string */
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_) && !defined(_INC_WINDOWS)
   typedef INT    FAR *PINT;            /* @type (pi) <tab> pointer to
   integer*/
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_)
   typedef SHORT  FAR *PSHORT;          /* @type (psh) <tab> pointer to
   short integer*/
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_)
   typedef USHORT FAR *PUSHORT;         /* @type (pus) <tab> pointer to
   unsigned short integer*/
#endif

#ifndef NT_50
   /* already defined in Win2000 */
   #if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
       !defined(__vtoolsd_h_) && !defined(_WINDEF_)
      typedef UINT   FAR *PUINT;           /* @type (pui) <tab> pointer to
      unsigned integer*/
   #endif
#endif

#if !defined(_INC_WINDOWS)
   typedef WORD   FAR *PWORD;           /* @type (pw) <tab> pointer to word*/
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_) && !defined(_INC_WINDOWS)
   typedef LONG   FAR *PLONG;           /* @type (pl) <tab> pointer to long
   integer*/
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_)
   typedef ULONG  FAR *PULONG;          /* @type (pul) <tab> pointer to
   unsigned long integer*/
#endif

#if !defined(_INC_WINDOWS)
   typedef DWORD  FAR *PDWORD;          /* @type (pdw) <tab> pointer to
   double word*/
#endif

typedef LONG64 FAR *PLONG64;            /* @type (pll) <tab> pointer to 64-bit
   signed integer */

typedef ULONG64 FAR *PULONG64;          /* @type (pull) <tab> pointer to 64-bit
   unsigned integer */

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED) && \
    !defined(__vtoolsd_h_) && !defined(_WINDEF_)
   typedef BOOL   FAR *PBOOL;           /* @type (pf) <tab> pointer to
   boolean*/
#endif

#if !defined(OS2_INCLUDED) && !defined(DEFS_INCLUDED)
   typedef BOOL32 FAR *PBOOL32;         /* @type (pf) <tab> pointer to 32 bit
   boolean*/

   typedef BOOL16 FAR *PBOOL16;         /* @type (pf) <tab> pointer to 16 bit
   boolean*/
#endif

typedef OKERR    FAR *POKERR;         /* @type (pe) <tab> pointer to error
code*/
typedef OKERR16  FAR *POKERR16;       /* @type (pe) <tab> pointer to error
code 16 bit*/
typedef OKERR32  FAR *POKERR32;       /* @type (pe) <tab> pointer to error
code 32 bit*/


/*
** consts OK General Exit Codes | Since VMS produces strange error messages
** on the console if an application returns any other value than 1, portable
** applications should use 'exit(CODE_x)' instead of 'exit(x)'.
*/

#ifdef S_VMS
   #define CODE_0  1 /*cnst Exit Code 0, VMS*/
   #define CODE_1  1 /*cnst Exit Code 1, VMS*/
   #define CODE_2  1 /*cnst Exit Code 2, VMS <nl>*/
#else
   #define CODE_0  0 /*cnst Exit Code 0, default*/
   #define CODE_1  1 /*cnst Exit Code 1, default*/
   #define CODE_2  2 /*cnst Exit Code 2, default*/
#endif

/*
** @consts OK General Purpose Constants | These are commonly used definitions.
*/

#ifndef TRUE
   #define TRUE   1                 /*@cnst Boolean value TRUE */
#endif
#ifndef FALSE
   #define FALSE  0                 /*@cnst Boolean value FALSE */
#endif
#ifndef OK
   #define OK     0
#endif
#ifndef NOT_OK
   #define NOT_OK 1
#endif


#define OK_DEF_BUF_SIZE       256  /*@cnst Default size for buffers */

#if defined S_UNIX
   #if defined _POSIX_PATH_MAX
      #define OK_DEF_PATH_SIZE _POSIX_PATH_MAX  /*cnst size for pathnames */
   #elif defined PATH_MAX
      #define OK_DEF_PATH_SIZE PATH_MAX  /*cnst size for pathnames */
   #else
      #define OK_DEF_PATH_SIZE 255  /*cnst Default size for pathnames */
   #endif
#else
   #if defined _MAX_PATH
      #define OK_DEF_PATH_SIZE _MAX_PATH /*cnst size for pathnames */
   #else
      #define OK_DEF_PATH_SIZE 255  /*cnst Default size for pathnames */
   #endif
#endif

#define OK_EMPTY_BUFFER      {0, NULL} /*@cnst Empty item buffer, use this to
                                    initialize <t OK_ITEM> or <t OK_NAME>
                                    structures */

/*
** @consts OK File System Constants | The following constants are used in file
** system handling:
*/

#if defined S_UNIX
   #define OK_SEP_DRIVE      '/' /*cnst Drive separator as character, S_UNIX*/
   #define OK_SEP_PATH       '/' /*cnst Directory separator as character,
                                          S_UNIX*/
   #define OK_SEP_PATH_FIRST '/' /*cnst First directory separator as
                                          character, S_UNIX*/
   #define OK_SEP_PATH_LAST  '/' /*cnst Separator behind last directory as
                                          character, S_UNIX*/
   #define OK_SEP_EXT        '.' /*cnst Filename extension character as
                                          character, S_UNIX*/
   #define OK_SEP_DRIVE_STR  "/" /*cnst Drive separator as string, S_UNIX*/
   #define OK_SEP_PATH_STR   "/" /*cnst Path separator as string, S_UNIX*/
   #define OK_SEP_EXT_STR    "." /*cnst Filename extension character as
                                          string, S_UNIX <nl>*/
#elif defined S_VMS
   #define OK_SEP_DRIVE      ':' /*cnst Drive separator as character,
   S_VMS*/
   #define OK_SEP_PATH       '.' /*cnst Directory separator as character,
   S_VMS*/
   #define OK_SEP_PATH_FIRST '[' /*cnst First directory separator as
   character, S_VMS*/
   #define OK_SEP_PATH_LAST  ']' /*cnst Separator behind last directory as
   character, S_VMS*/
   #define OK_SEP_EXT        '.' /*cnst Filename extension character as
   character, S_VMS*/
   #define OK_SEP_DRIVE_STR  ":" /*cnst Drive separator as string, S_VMS*/
   #define OK_SEP_PATH_STR   "." /*cnst Path separator as string, S_VMS*/
   #define OK_SEP_EXT_STR    "." /*cnst Filename extension character as
   string, S_VMS <nl>*/
#else
   #define OK_SEP_DRIVE      ':'  /*@cnst Drive separator as character,
   default*/
   #define OK_SEP_PATH       '\\' /*@cnst Directory separator as
   character, default*/
   #define OK_SEP_PATH_FIRST '\\' /*@cnst First directory separator as
   character, default*/
   #define OK_SEP_PATH_LAST  '\\' /*@cnst Separator behind last directory
   as character, default*/
   #define OK_SEP_EXT        '.'  /*@cnst Filename extension character as
   character, default*/
   #define OK_SEP_DRIVE_STR  ":"  /*@cnst Drive separator as string,
   default*/
   #define OK_SEP_PATH_STR   "\\" /*@cnst Path separator as string,
   default*/
   #define OK_SEP_EXT_STR    "."  /*@cnst Filename extension character as
   string, default*/
#endif

/*
** consts OK Language Codes | Language code definitions.
*/

#define OK_LANG_GERMAN               1 /* cnst German language */
#define OK_LANG_ENGLISH              2 /* cnst English language */
#define OK_LANG_FRENCH               3 /* cnst French language */
#define OK_LANG_ITALIAN              4 /* cnst Italian language */

#define OK_LANG_DEFAULT   OK_LANG_ENGLISH /* cnst Default language is
                                                     english */


/*
** Macros
*/

#if defined(S_OS2_32) || defined(S_KOS2_32)
   /* @macro HIGH(V) | Extract upper byte of WORD value. */
   #define HIGH(v) ((BYTE) ((ULONG)v >> 8))
   /* @macro LOW(V) | Extract lower byte of WORD value. */
   #define LOW(v) ((BYTE) (v))
   /* @macro HIGHW(V) | Extract upper word of DWORD value. */
   #define HIGHW(v) ((WORD) ((ULONG)v >> 16))
   /* @macro LOWW(V) | Extract lower word of DWORD value. */
   #define LOWW(v) ((WORD) (v))

   /* @macro SWAPW(V) | Unconditional byte swapping of WORD value.  */
   #define SWAPW(v) (WORD) (((ULONG)LOW(v)<<8)|(ULONG)HIGH(v))
   #ifdef S_SBFW
   /* @macro PCSWAPW(V) | Byte swapping of WORD value, PC code only.  */
      #define PCSWAPW(v) v

   /* @macro FWSWAPW(V) | Byte swapping of WORD value, firmware code only.  */
      #define FWSWAPW(v) (WORD) ((LOW(v)<<8)|HIGH(v))
   #else
      #define PCSWAPW(v) (WORD) (((ULONG)LOW(v)<<8)|(ULONG)HIGH(v))
      #define FWSWAPW(v) v
   #endif
#else
   #define HIGH(v) ((BYTE) ((v) >> 8))
   #define LOW(v) ((BYTE) (v))
   #define HIGHW(v) ((WORD) ((v) >> 16))
   #define LOWW(v) ((WORD) (v))

   #define SWAPW(v) (WORD) ((LOW(v)<<8)|HIGH(v))
   #ifdef S_SBFW
      #define PCSWAPW(v) v
      #define FWSWAPW(v) (WORD) ((LOW(v)<<8)|HIGH(v))
   #else
      #define PCSWAPW(v) (WORD) ((LOW(v)<<8)|HIGH(v))
      #define FWSWAPW(v) v
   #endif
#endif

/* @macro SWAPL(V) | Unconditional byte swapping of DWORD value.*/
#define SWAPL(v) (LONG) ((((LONG)(SWAPW(LOWW(v))))<<16)|SWAPW(HIGHW(v)))
#define SWAPUL(v) (ULONG) ((((ULONG)(SWAPW(LOWW(v))))<<16)|SWAPW(HIGHW(v)))
#ifdef S_SBFW
   /* @macro PCSWAPL(V) | Byte swapping of DWORD value, PC code only. */
   #define PCSWAPL(v) v
   /* @macro FWSWAPL(V) | Byte swapping of WORD value, firmware code only. */
   #define FWSWAPL(v) (LONG) ((((LONG)(SWAPW(LOWW(v))))<<16)|SWAPW(HIGHW(v)))
#else
   #define PCSWAPL(v) (LONG) ((((LONG)(SWAPW(LOWW(v))))<<16)|SWAPW(HIGHW(v)))
   #define FWSWAPL(v) v
#endif

/* @macro SStoDS(x) | Only for OS2 32-bit kernel mode (dummy otherwise).
                      Translates SS based address into DS based address. */

#if defined S_KOS2_32
   #ifndef SStoDS
      extern long * _ptkssbase;
      #define SStoDS(x)    ((void*) ((unsigned long) x + *_ptkssbase))
   #endif
#else
   #define SStoDS(x)    x
#endif

/* @macro MINVAL(x, y) | Minimum of two integers. */
#define MINVAL(x, y) (((x) < (y)) ? (x) : (y))

/* @macro LO_NIB(c) | Get low nibble of BYTE value. */
#define LO_NIB(c) ( 0x0F & (c) )

/* @macro HI_NIB(c) | Get high nibble of BYTE value. */
#define HI_NIB(c) ( 0x0F & ((c) >> 4) )


/* @macro PTR_OFF(p) |  Get offset value of 32-bit pointer.*/
#define PTR_OFF(p)  (((LPWORD)&(p))[0])

/* @macro PTR_SEG(p) |  Get seg/sel value of 32-bit pointer.*/
#define PTR_SEG(p)  (((LPWORD)&(p))[1])

/* @macro ADR_OFF(p) |  Get offset value of 32-bit address.*/
#define ADR_OFF(p)  (LOWW((DWORD)(LPBYTE)(&p)))

/* @macro ADR_SEG(p) |  Get seg/sel value of 32-bit address.*/
#define ADR_SEG(p)  (HIGHW((DWORD)(LPBYTE)(&p)))

/* @macro MAKE_LPBYTES(sel, off) | Make 32-bit byte pointer from sel/offset
   values. */
#define MAKE_LPBYTE(sel, off)     ((LPBYTE) MAKE_DWORD(off, sel))

/* @macro MAKE_DWORD(1, h) | Make DWORD (32-bit) value from l/h 16-bit
values. */
#define MAKE_DWORD(l, h)  ((DWORD)(((WORD)(l)) | ((DWORD)((WORD)(h))) << 16))

/* @macro MAKE_LONG(1, h) | Make LONG (32-bit) value from l/h 16-bit values.*/
#define MAKE_LONG(l, h)   ((LONG)MAKE_DWORD(l, h))

/* @macro MAKE_USHORT(1, h) | Make USHORT (32-bit) value from l/h 8-bit
values.*/
#define MAKE_USHORT(lb, hb) ((USHORT)(((BYTE)(lb)) | ((USHORT)((BYTE)(hb)))<<8))


/*
** @struct OK_ITEM |
** Commonly used structure containing an (usually BYTE) array and it's length.
** See also <t OK_NAME>.
*/

typedef struct _OK_ITEM {
      ULONG length;               /* @field Length of value array */
      void *value;                /* @field Array of size <p length> */
} OK_ITEM;

typedef OK_ITEM FAR *GPOK_ITEM;
typedef OK_ITEM FAR *LPOK_ITEM;
typedef OK_ITEM FAR *POK_ITEM;

/*
** @struct OK_NAME |
** Commonly used structure containing an array and it's length. The difference
** to <t OK_ITEM> is, that this structure is considered to be used only for
** strings. <p length> contains the number of readable characters in
** <p value> and <p value> implicitly uses up 1 byte more of memory for the
** terminating '\\0' character.
*/

typedef struct _OK_NAME {
      ULONG length;               /* @field strlen(<p value>) */
      void *value;                /* @field Array of size <p length>+1, last
                                     byte has to be '\\0'. */
} OK_NAME;

typedef OK_NAME FAR *GPOK_NAME;
typedef OK_NAME FAR *LPOK_NAME;
typedef OK_NAME FAR *POK_NAME;

/*
** @consts OK Standard Error Codes |
** These are considered as well known errors throughout Omnikey code.
** Module specific errors are defined in the module include file above
** OKERR_STANDARD_LIMIT.
** <nl>Some of these errors are there for compatibility reasons only. So there
** are
** similar error codes for the same situation (e.g. out of memory). Programmers
** should try to use the error codes defined in OK.H as often as possible
** instead of inventing module specific new error codes.
*/

#define OKERR_STANDARD_LIMIT     0x82000000L  /*@cnst Module specific error codes may be defined above this limit. */
#ifndef NO_ERROR
   #define NO_ERROR                 0       /* @cnst No error */
#endif

#define OKERR_OK                   0       /* @cnst No error */

/**************************************************************************/
/*  Parameter errors  0x81000000 -                                        */
/**************************************************************************/
#define OKERR_PARM1       0x81000000L         /* @cnst Error in parameter 1 */
#define OKERR_PARM2       0x81000001L         /* @cnst Error in parameter 2 */
#define OKERR_PARM3       0x81000002L         /* @cnst Error in parameter 3 */
#define OKERR_PARM4       0x81000003L         /* @cnst Error in parameter 4 */
#define OKERR_PARM5       0x81000004L         /* @cnst Error in parameter 5 */
#define OKERR_PARM6       0x81000005L         /* @cnst Error in parameter 6 */
#define OKERR_PARM7       0x81000006L         /* @cnst Error in parameter 7 */
#define OKERR_PARM8       0x81000007L         /* @cnst Error in parameter 8 */
#define OKERR_PARM9       0x81000008L         /* @cnst Error in parameter 9 */
#define OKERR_PARM10      0x81000009L         /* @cnst Error in parameter 10 */
#define OKERR_PARM11      0x8100000AL         /* @cnst Error in parameter 11 */
#define OKERR_PARM12      0x8100000BL         /* @cnst Error in parameter 12 */
#define OKERR_PARM13      0x8100000CL         /* @cnst Error in parameter 13 */
#define OKERR_PARM14      0x8100000DL         /* @cnst Error in parameter 14 */
#define OKERR_PARM15      0x8100000EL         /* @cnst Error in parameter 15 */
#define OKERR_PARM16      0x8100000FL         /* @cnst Error in parameter 16 */
#define OKERR_PARM17      0x81000010L         /* @cnst Error in parameter 17 */
#define OKERR_PARM18      0x81000011L         /* @cnst Error in parameter 18 */
#define OKERR_PARM19      0x81000012L         /* @cnst Error in parameter 19 */


/**************************************************************************/
/*  PW        errors  0x81100000 -                                        */
/**************************************************************************/
#define OKERR_INSUFFICIENT_PRIV    0x81100000L  /* @cnst You currently do not have
the rights to execute the requested action. Usually a password has to be
presented in advance.*/
#define OKERR_PW_WRONG             0x81100001L  /* @cnst The presented password is
wrong */
#define OKERR_PW_LOCKED            0x81100002L  /* @cnst The password has been
presented several times wrong and is therefore locked. Usually use some
administrator tool to unblock it. */
#define OKERR_PW_TOO_SHORT         0x81100003L  /* @cnst The lenght of the password was too short.*/
#define OKERR_PW_TOO_LONG          0x81100004L  /* @cnst The length of the password was too long.*/
#define OKERR_PW_NOT_LOCKED		  0x81100005L  /* @cnst The password is not locked */



/**************************************************************************/
/*  ITEM      errors  0x81200000 -                                        */
/**************************************************************************/
#define OKERR_ITEM_NOT_FOUND       0x81200000L  /* @cnst An item (e.g. a key of
a specific name) could not be found */
#define OKERR_ITEMS_LEFT           0x81200001L  /* @cnst There are still items
left, therefore e.g. the directory / structure etc. can't be deleted.*/
#define OKERR_INVALID_CFG_FILE     0x81200002L  /* @cnst Invalid configuration
file*/
#define OKERR_SECTION_NOT_FOUND    0x81200003L  /* @cnst Section not found*/
#define OKERR_ENTRY_NOT_FOUND      0x81200004L  /* @cnst Entry not found*/
#define OKERR_NO_MORE_SECTIONS     0x81200005L  /* @cnst No more sections*/
#define OKERR_ITEM_ALREADY_EXISTS  0x81200006L  /* @cnst The specified item alread exists.*/
#define OKERR_ITEM_EXPIRED         0x81200007L  /* @cnst Some item (e.g. a certificate) has expired. */


/**************************************************************************/
/*  General   errors  0x81300000 -                                        */
/**************************************************************************/
#define OKERR_UNEXPECTED_RET_VALUE 0x81300000L  /* @cnst Unexpected return value*/
#define OKERR_COMMUNICATE          0x81300001L  /* @cnst General communication error */
#define OKERR_NOT_ENOUGH_MEMORY    0x81300002L  /* @cnst Not enough memory*/
#define OKERR_BUFFER_OVERFLOW      0x81300003L  /* @cnst Buffer overflow*/
#define OKERR_TIMEOUT              0x81300004L  /* @cnst A timeout has occurred*/
#define OKERR_NOT_SUPPORTED        0x81300005L  /* @cnst The requested
functionality is not supported at this time / under this OS / in this situation
etc.*/
#define OKERR_ILLEGAL_ARGUMENT     0x81300006L  /* @cnst Illegal argument*/
#define OKERR_READ_FIO             0x81300007L  /* @cnst File IO read error */
#define OKERR_WRITE_FIO            0x81300008L  /* @cnst File IO write error */
#define OKERR_INVALID_HANDLE       0x81300009L  /* @cnst Invalid handle*/
#define OKERR_GENERAL_FAILURE      0x8130000AL  /* @cnst General failure. Use this
error code in cases where no other errors match and it is not worth to define
a new error code.*/
#define OKERR_FILE_NOT_FOUND       0x8130000BL  /* @cnst File not found*/
#define OKERR_OPEN_FILE            0x8130000CL  /* @cnst File opening failed*/
#define OKERR_SEM_USED             0x8130000DL  /* @cnst The semaphore is currently use by an other process */




/**************************************************************************/
/*  General errors for backwards compatibility   0x81F0000                */
/**************************************************************************/
#define OKERR_NOP                  0x81F00001L  /* @cnst No operation done */
#define OKERR_NOK                  0x81F00002L  /* @cnst Function not executed */
#define OKERR_FWBUG                0x81F00003L  /* @cnst Internal error detected*/
#define OKERR_INIT                 0x81F00004L  /* @cnst Module not initialized */
#define OKERR_FIO                  0x81F00005L  /* @cnst File IO error detected */
#define OKERR_ALLOC                0x81F00006L  /* @cnst Cannot allocate memory */
#define OKERR_SESSION_ERR          0x81F00007L  /* @cnst General error */
#define OKERR_ACCESS_ERR           0x81F00008L  /* @cnst Access not allowed */

#define OKERR_OPEN_FAILURE         0x81F00009L  /* @cnst An open command was not
                                                     successful */
#define OKERR_CARD_NOT_POWERED     0x81F0000AL  /* @cnst Card is not powered*/
#define OKERR_ILLEGAL_CARDTYPE     0x81F0000BL  /* @cnst Illegal cardtype*/
#define OKERR_CARD_NOT_INSERTED    0x81F0000CL  /* @cnst Card not inserted*/
#define OKERR_NO_DRIVER            0x81F0000DL  /* @cnst No device driver
installed*/
#define OKERR_OUT_OF_SERVICE       0x81F0000EL  /* @cnst The service is currently
not available */
#define OKERR_EOF_REACHED          0x81F0000FL  /* @cnst End of file reached*/



#define OKERR_ON_BLACKLIST         0x81F00010L  /* @cnst The ID is on a blacklist,
the requested action is therefore not allowed.*/
#define OKERR_CONSISTENCY_CHECK    0x81F00011L  /* @cnst Error during consistency
check*/
#define OKERR_IDENTITY_MISMATCH    0x81F00012L  /* @cnst The identity does not
match a defined cross-check identity */
#define OKERR_MULTIPLE_ERRORS      0x81F00013L  /* @cnst Multiple errors have
occurred. Use this if there is only the possibility to return one error code,
but there happened different errors before (e.g. each thread returned a
different error and the controlling thread may only report one).*/
#define OKERR_ILLEGAL_DRIVER       0x81F00014L  /* @cnst Illegal driver*/
#define OKERR_ILLEGAL_FW_RELEASE   0x81F00015L  /* @cnst The connected hardware
whose firmware is not useable by this software */
#define OKERR_NO_CARDREADER        0x81F00016L  /* @cnst No cardreader attached*/
#define OKERR_IPC_FAULT            0x81F00017L  /* @cnst General failure of inter
                                                     process communication*/
#define OKERR_WAIT_AND_RETRY       0x81F00018L  /* @cnst The service currently does
not take calls. The task <b has to> go back to the message loop and try
again at a later time (Windows 3.1 only). The code may also be used, in every
situation where a <oq> wait and retry <cq> action is requested.*/




/******************************************************************************/
/* All for SCARD error codes of the resource manager , a OK error code exists.*/
/******************************************************************************/
#define OKERR_SCARD__E_CANCELLED                0x80100002L /*@cnst  The action was cancelled by an SCardCancel request*/
#define OKERR_SCARD__E_INVALID_HANDLE           0x80100003L /*@cnst  The supplied handle was invalid*/
#define OKERR_SCARD__E_INVALID_PARAMETER        0x80100004L /*@cnst  One or more of the supplied parameters could not be properly interpreted*/
#define OKERR_SCARD__E_INVALID_TARGET           0x80100005L /*@cnst  Registry startup information is missing or invalid*/
#define OKERR_SCARD__E_NO_MEMORY                0x80100006L /*@cnst  Not enough memory available to complete this command*/
#define OKERR_SCARD__F_WAITED_TOO_LONG          0x80100007L /*@cnst  An internal consistency timer has expired*/
#define OKERR_SCARD__E_INSUFFICIENT_BUFFER      0x80100008L /*@cnst  The data buffer to receive returned data is too small for the returned data*/
#define OKERR_SCARD__E_UNKNOWN_READER           0x80100009L /*@cnst  The specified reader name is not recognized*/
#define OKERR_SCARD__E_TIMEOUT                  0x8010000AL /*@cnst  The user-specified timeout value has expired*/
#define OKERR_SCARD__E_SHARING_VIOLATION        0x8010000BL /*@cnst  The smart card cannot be accessed because of other connections outstanding*/
#define OKERR_SCARD__E_NO_SMARTCARD             0x8010000CL /*@cnst  The operation requires a Smart Card, but no Smart Card is currently in the device*/
#define OKERR_SCARD__E_UNKNOWN_CARD             0x8010000DL /*@cnst  The specified smart card name is not recognized*/
#define OKERR_SCARD__E_CANT_DISPOSE             0x8010000EL /*@cnst  The system could not dispose of the media in the requested manner*/
#define OKERR_SCARD__E_PROTO_MISMATCH           0x8010000FL /*@cnst  The requested protocols are incompatible with the protocol currently in use with the smart card*/
#define OKERR_SCARD__E_NOT_READY                0x80100010L /*@cnst  The reader or smart card is not ready to accept commands*/
#define OKERR_SCARD__E_INVALID_VALUE            0x80100011L /*@cnst  One or more of the supplied parameters values could not be properly interpreted*/
#define OKERR_SCARD__E_SYSTEM_CANCELLED         0x80100012L /*@cnst  The action was cancelled by the system, presumably to log off or shut down*/
#define OKERR_SCARD__F_COMM_ERROR               0x80100013L /*@cnst  An internal communications error has been detected*/
#define OKERR_SCARD__F_UNKNOWN_ERROR            0x80100014L /*@cnst  An internal error has been detected, but the source is unknown*/
#define OKERR_SCARD__E_INVALID_ATR              0x80100015L /*@cnst  An ATR obtained from the registry is not a valid ATR string*/
#define OKERR_SCARD__E_NOT_TRANSACTED           0x80100016L /*@cnst  An attempt was made to end a non-existent transaction*/
#define OKERR_SCARD__E_READER_UNAVAILABLE       0x80100017L /*@cnst  The specified reader is not currently available for use*/
#define OKERR_SCARD__P_SHUTDOWN                 0x80100018L /*@cnst  The operation has been aborted to allow the server application to exit*/
#define OKERR_SCARD__E_PCI_TOO_SMALL            0x80100019L /*@cnst  The PCI Receive buffer was too small*/
#define OKERR_SCARD__E_READER_UNSUPPORTED       0x8010001AL /*@cnst  The reader driver does not meet minimal requirements for support*/
#define OKERR_SCARD__E_DUPLICATE_READER         0x8010001BL /*@cnst  The reader driver did not produce a unique reader name*/
#define OKERR_SCARD__E_CARD_UNSUPPORTED         0x8010001CL /*@cnst  The smart card does not meet minimal requirements for support*/
#define OKERR_SCARD__E_NO_SERVICE               0x8010001DL /*@cnst  The Smart card resource manager is not running*/
#define OKERR_SCARD__E_SERVICE_STOPPED          0x8010001EL /*@cnst  The Smart card resource manager has shut down*/
#define OKERR_SCARD__E_UNEXPECTED               0x8010001FL /*@cnst  An unexpected card error has occurred*/
#define OKERR_SCARD__E_ICC_INSTALLATION         0x80100020L /*@cnst  No Primary Provider can be found for the smart card*/
#define OKERR_SCARD__E_ICC_CREATEORDER          0x80100021L /*@cnst  The requested order of object creation is not supported*/
#define OKERR_SCARD__E_UNSUPPORTED_FEATURE      0x80100022L /*@cnst  This smart card does not support the requested feature*/
#define OKERR_SCARD__E_DIR_NOT_FOUND            0x80100023L /*@cnst  The identified directory does not exist in the smart card*/
#define OKERR_SCARD__E_FILE_NOT_FOUND           0x80100024L /*@cnst  The identified file does not exist in the smart card*/
#define OKERR_SCARD__E_NO_DIR                   0x80100025L /*@cnst  The supplied path does not represent a smart card directory*/
#define OKERR_SCARD__E_NO_FILE                  0x80100026L /*@cnst  The supplied path does not represent a smart card file*/
#define OKERR_SCARD__E_NO_ACCESS                0x80100027L /*@cnst  Access is denied to this file*/
#define OKERR_SCARD__E_WRITE_TOO_MANY           0x80100028L /*@cnst  An attempt was made to write more data than would fit in the target object*/
#define OKERR_SCARD__E_BAD_SEEK                 0x80100029L /*@cnst  There was an error trying to set the smart card file object pointer*/
#define OKERR_SCARD__E_INVALID_CHV              0x8010002AL /*@cnst  The supplied PIN is incorrect*/
#define OKERR_SCARD__E_UNKNOWN_RES_MNG          0x8010002BL /*@cnst  An unrecognized error code was returned from a layered component*/
#define OKERR_SCARD__E_NO_SUCH_CERTIFICATE      0x8010002CL /*@cnst  The requested certificate does not exist*/
#define OKERR_SCARD__E_CERTIFICATE_UNAVAILABLE  0x8010002DL /*@cnst  The requested certificate could not be obtained*/
#define OKERR_SCARD__E_NO_READERS_AVAILABLE     0x8010002EL /*@cnst  Cannot find a smart card reader*/
#define OKERR_SCARD__E_COMM_DATA_LOST           0x8010002FL /*@cnst  A communications error with the smart card has been detected*/
#define OKERR_SCARD__W_UNSUPPORTED_CARD         0x80100065L /*@cnst  The reader cannot communicate with the smart card, due to ATR configuration conflicts*/
#define OKERR_SCARD__W_UNRESPONSIVE_CARD        0x80100066L /*@cnst  The smart card is not responding to a reset*/
#define OKERR_SCARD__W_UNPOWERED_CARD           0x80100067L /*@cnst  Power has been removed from the smart card, so that further communication is not possible*/
#define OKERR_SCARD__W_RESET_CARD               0x80100068L /*@cnst  The smart card has been reset, so any shared state information is invalid*/
#define OKERR_SCARD__W_REMOVED_CARD             0x80100069L /*@cnst  The smart card has been removed, so that further communication is not possible*/
#define OKERR_SCARD__W_SECURITY_VIOLATION       0x8010006AL /*@cnst  Access was denied because of a security violation*/
#define OKERR_SCARD__W_WRONG_CHV                0x8010006BL /*@cnst  The card cannot be accessed because the wrong PIN was presented*/
#define OKERR_SCARD__W_CHV_BLOCKED              0x8010006CL /*@cnst  The card cannot be accessed because the maximum number of PIN entry attempts has been reached*/
#define OKERR_SCARD__W_EOF                      0x8010006DL /*@cnst  The end of the smart card file has been reached*/
#define OKERR_SCARD__W_CANCELLED_BY_USER        0x8010006EL /*@cnst  The action was cancelled by the user*/




/*****************************************************************************/
/* Definitions for Compatibility to old OK code                             */
/*****************************************************************************/

#ifdef S_MSDOS             /* only MS-DOS defines generic pointers as near */
                           /* pointers                                     */
   typedef CONSTCHAR *GPCONSTCHAR;
   typedef const VOID *GPCONSTVOID;
   typedef VOID *GPVOID;
   typedef CHAR *GPCHAR;
   typedef WCHAR *GPWCHAR;
   typedef WCHAR *GPWSZ;
   typedef CHAR *GPSZ;
   typedef UCHAR *GPUCHAR;
   typedef BYTE *GPBYTE;
   typedef CHAR *GPSTR;
   typedef INT  *GPINT;
   typedef SHORT *GPSHORT;
   typedef USHORT *GPUSHORT;
   typedef UINT *GPUINT;
   typedef WORD *GPWORD;
   typedef LONG *GPLONG;
   typedef ULONG *GPULONG;
   typedef LONG64 *GPLONG64;
   typedef ULONG64 *GPULONG64;
   typedef DWORD *GPDWORD;
   typedef BOOL *GPBOOL;
   typedef BOOL16 *GPBOOL16;
   typedef BOOL32 *GPBOOL32;
#else
   typedef CONSTCHAR FAR *GPCONSTCHAR;
   typedef const VOID FAR *GPCONSTVOID;
   typedef VOID FAR *GPVOID;
   typedef CHAR FAR *GPCHAR;
   typedef WCHAR FAR *GPWSZ;
   typedef CHAR FAR *GPSZ;
   typedef WCHAR FAR *GPWCHAR;
   typedef UCHAR FAR *GPUCHAR;
   typedef BYTE FAR *GPBYTE;
   typedef CHAR FAR *GPSTR;
   typedef INT  FAR *GPINT;
   typedef SHORT FAR *GPSHORT;
   typedef USHORT FAR *GPUSHORT;
#ifndef NT_50
   /* already defined in Win2000 */
   typedef UINT FAR *GPUINT;
#endif
   typedef WORD FAR *GPWORD;
   typedef LONG FAR *GPLONG;
   typedef ULONG FAR *GPULONG;
   typedef LONG64 *GPLONG64;
   typedef ULONG64 *GPULONG64;
   typedef DWORD FAR *GPDWORD;
   typedef BOOL FAR *GPBOOL;
   typedef BOOL16 FAR *GPBOOL16;
   typedef BOOL32 FAR *GPBOOL32;
#endif


#if !defined(_INC_WINDOWS)
   typedef VOID FAR *LPVOID;
#endif

typedef CHAR FAR *LPCHAR;

typedef WCHAR FAR *LPWCHAR;
typedef WCHAR FAR *LPWSZ;
typedef CHAR FAR *LPSZ;

typedef UCHAR FAR *LPUCHAR;

#if !defined(_INC_WINDOWS)
   typedef BYTE FAR *LPBYTE;
#endif

#if !defined(_INC_WINDOWS) && !defined(__AFX_H__)
   typedef CHAR FAR *LPSTR;
#endif

#if !defined(_INC_WINDOWS)
   typedef INT  FAR *LPINT;
#endif

typedef SHORT FAR *LPSHORT;

typedef USHORT FAR *LPUSHORT;

#ifndef NT_50
   /* already defined in Win2000 */
   #if !defined(_WINDEF_) || _MSC_VER >= 1020
      typedef UINT FAR *LPUINT;
   #endif
#endif

#if !defined(_INC_WINDOWS)
   typedef WORD FAR *LPWORD;
#endif

#if !defined(_INC_WINDOWS)
   typedef LONG FAR *LPLONG;
#endif

#if !defined(_INC_WINDOWS)
   typedef DWORD FAR *LPDWORD;
#endif

typedef ULONG FAR *LPULONG;

typedef LONG64 *LPLONG64;

typedef ULONG64 *LPULONG64;

#if !defined(_WINDEF_)
   typedef BOOL FAR *LPBOOL;
#endif

typedef BOOL16 FAR *LPBOOL16;

typedef BOOL32 FAR *LPBOOL32;

#ifdef S_WIN
/* @macro sprintf(...) | Redefines 'sprintf' by 'wsprintf' in case of S_WIN. */
   #if (WINVER >= 0x030a)
      #define sprintf wsprintf
   #else
      #define sprintf WSPRINTF
      int FAR cdecl WSPRINTF (LPSTR lpszOut, LPSTR lpszFmt, ...);
   #endif
#endif

#ifdef S_BOOT
   /** In Boot-Model ERROR-Logging will be disabled                         **/
   #define NO_ERRL
#endif

#include <okpoff.h>

#endif /* _INC_OK */

/*****************************************************************************
* History:
* $Log: ok.h $
* Revision 1.2  2001/01/05 10:06:57  TBruendl
* No comment given
*
* Revision 1.1  2000/12/19 14:05:42  TBruendl
* No comment given
*
* Revision 1.1  2000/11/27 08:57:30  TBruendl
* No comment given
*
* Revision 2.25  2000/01/03 14:49:25  cw
* removed accidentially added character
*
* Revision 2.24  1999/12/29 10:06:36  cw
* Added defines for Linux
*
* Revision 2.23  1999/11/23 08:02:40  HMurauer
* I removed these famous end-of-file  delimiters:
* @xy USCRCS_CheckIn:4245 3180
* @xy USCRCS_Explorer:930 75 13620 10980
*
* Revision 2.22  1999/11/23 07:19:19  HMurauer
* No comment given
*
* Revision 2.21  1999/11/23 07:03:59  UKreuzeder
* Changes (uncomments) for Win2000
*
* Revision 2.20  1999/11/09 14:18:43  CGusenbauer
* added OKERR_PW_NOT_LOCKED error code
*
* Revision 2.19  1998/06/02 07:57:56  CGusenbauer
* No comment given
*
* Revision 2.18  1998/04/28 12:21:33  MSchuster
* path size
*
* Revision 2.17  1998/04/22 11:32:16  CGusenbauer
* MSDEV 4.2 does not define LPUINT in windef.h - so we do it now
*
* Revision 2.16  2019/04/14 14:06:36  ESpiegl
* OKERR_ITEM_EXPIRED added
*
* Revision 2.15  1998/01/14 12:46:48  AWenzel
* Added LONG64 (all) and HANDLE (Unix) data types
*
* Revision 2.14  1997/10/06 12:54:33  CGusenbauer
* added OSF/1 constant S_OSF
*
* Revision 2.13  1997/09/24 06:51:35  CGusenbauer
* copyright, next try
* Revision 2.12  1997/09/23 12:48:10  CGusenbauer
* removed Safe Concept copyright
* Revision 2.11  1997/08/26 13:19:07  TBruendl
* New error codes:
* OKERR_ITEM_ALREADY_EXISTS, OKERR_PW_TOO_SHORT
* OKERR_PW_TOO_LONG
* Revision 2.10  1997/04/10 14:16:49  GWildmann
* Add  #define NO_ERRL if we build a Boot-Model components
* Revision 2.9  1997/04/03 18:34:19  GWildmann
* Remove defined S_BOOT because MSC6.00 doesn't support #pragma warning
* Revision 2.8  1997/01/17 13:08:28  GW
* Modifications for VXD model implementation of GSENC
* Revision 2.7  1996/12/20 10:12:47  CGusenbauer
* Define 'WCHAR' if '__AFX_H__' is defined.
* Revision 2.6  1996/12/13 08:49:11  CGusenbauer
* Changed the WCHAR definition.
* Revision 2.5  1996/12/13 08:12:32  CGusenbauer
* Added WCHAR for MS_DOS
* Revision 2.4  1996/12/10 11:42:46  RAufreiter
* WCHAR added, modified type prefixes
* Revision 2.3  1996/11/21 17:33:08  RAufreiter
* Fixed Bux in #error Statement if no OS is defined
* Revision 2.2  1996/11/21 16:24:21  RAufreiter
* Added OS Check, improved documentation
* Revision 2.1  1996/11/19 16:33:58  AWenzel
* Initial revision in 2.1 environment
* Revision 1.1  1996/11/19 16:33:58  AWenzel
* Initial revision
* Revision 1.7  1996/11/18 17:50:27  RAufreiter
* Changed Documentation
* Revision 1.6  1996/11/15 10:57:58  NGruber
* changes for S_KOS2_32 Environment
* Revision 1.5  1996/11/13 06:43:54  HHoffmann
* ENTRY und CENTRY für S_KNT definiert.
* Revision 1.4  1996/11/12 14:40:37  CGusenbauer
* New Autoduck version
* Revision 1.3  1996/11/12 11:55:44  NGruber
* changes made for S_KOS2_32 (missed it in the revision before)
* Revision 1.2  1996/11/12 11:46:26  NGruber
* make changes to get no compiler warnings for S_KOS2_32
* Revision 1.1  1996/10/23 14:10:40  HSchuetz
* Initial revision
******************************************************************************/

