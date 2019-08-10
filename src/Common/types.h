////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
//
//
//
//
//
//
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __TYPES_H__
#define __TYPES_H__

#if defined NDS
#include <nds/jtypes.h>
#elif defined WIN
#include <windows.h>
#elif defined OPENEMU
    #ifndef UINT32
        #define UINT32 uint32_t
    #endif
#endif



#ifdef NULL
#undef NULL
#define NULL	0
#endif

#ifndef BYTE
#define BYTE	unsigned char
#endif

#ifndef WORD
#define WORD	unsigned short
#endif

#ifndef DWORD
#define DWORD	unsigned long
#endif

#ifndef LPCTSTR
#define LPCTSTR const char* 
#endif


#ifndef TRUE
#define BOOL	int
#define TRUE	1
#define FALSE	0
#endif

#ifdef _WIN_

#define BIT(n) (1 << (n))

#define byte   BYTE
//#define word   WORD

#define UINT8	BYTE
#define UINT16	WORD
#define INT8	signed char
#define INT16	signed short
#define INT32	signed long
#define UINT32	unsigned long
#define INT64   signed __int64
#define UINT64  unsigned __int64

#define uint8	UINT8
#define uint16	UINT16
#define uint32	UINT32
#define uint64  UINT64
#define int8	INT8
#define int16	INT16
#define int32	INT32
#define int64   INT64

#define u8		uint8
#define u16		uint16
#define u32		uint32
#define u64		uint64
#define s8		int8
#define s16		int16
#define s32		int32
#define s64		int64

#else

#define BIT(n) (1 << (n))

typedef unsigned char           uint8;
typedef unsigned short int      uint16;
typedef unsigned int            uint32;
typedef unsigned long long int  uint64;

typedef signed char             int8;
typedef signed short int        int16;
typedef signed int              int32;
typedef signed long long int    int64;

typedef float                   float32;
typedef double                  float64;

typedef volatile uint8          vuint8;
typedef volatile uint16         vuint16;
typedef volatile uint32         vuint32;
typedef volatile uint64         vuint64;

typedef volatile int8           vint8;
typedef volatile int16          vint16;
typedef volatile int32          vint32;
typedef volatile int64          vint64;

typedef volatile float32        vfloat32;
typedef volatile float64        vfloat64;

typedef uint8                   byte;

typedef int32                   fixed;
typedef int64                   dfixed;

typedef volatile int32          vfixed;


typedef unsigned char           u8;
typedef unsigned short int      u16;
typedef unsigned int            u32;
typedef unsigned long long int  u64;

typedef signed char             s8;
typedef signed short int        s16;
typedef signed int              s32;
typedef signed long long int    s64;

typedef volatile u8          vu8;
typedef volatile u16         vu16;
typedef volatile u32         vu32;
typedef volatile u64         vu64;

typedef volatile s8           vs8;
typedef volatile s16          vs16;
typedef volatile s32          vs32;
typedef volatile s64          vs64;

#endif

#endif
