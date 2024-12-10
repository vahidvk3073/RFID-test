#pragma once

#include <stdint.h>
#include <stddef.h>

#include "stm32f1xx_hal.h"

#define sizeof_array(X) (sizeof(X) / sizeof(X[0]))

#define _bytes
#define _mbytes			_bytes*1024*1024
#define _kbytes			_bytes*1024
#define _mbits			_mbytes/8
#define _kbits			_kbytes/8

#define _miliseconds
#define _seconds		*1000
#define _minutes		_seconds*60
#define _hours			_minutes*60
#define _days			_hours*24
#define _months			_days*30
#define _years			_days*365

typedef uint8_t			uchar;
typedef uint16_t		ushort;
typedef uint32_t		uint;
typedef uint64_t		ulong;

typedef uint64_t		QWord;
typedef uint32_t		DWord;
typedef uint16_t		Word;
typedef uint8_t			Byte;

typedef uint64_t		uint64;
typedef uint32_t		uint32;
typedef uint16_t		uint16;
typedef uint8_t			uint8;

typedef int64_t			int64;
typedef int32_t			int32;
typedef int16_t			int16;
typedef int8_t			int8;

typedef volatile uint64_t		vuint64;
typedef volatile uint32_t		vuint32;
typedef volatile uint16_t		vuint16;
typedef volatile uint8_t		vuint8;

typedef volatile int64_t		vint64;
typedef volatile int32_t		vint32;
typedef volatile int16_t		vint16;
typedef volatile int8_t			vint8;

#define FALSE			false
#define TRUE			true
/*
constexpr uint32 INFINITY_32 = (uint32)(-1);

union TInt8
{
	struct {
		uint8 	b0:1,	b1:1,	b2:1,	b3:1,	b4:1,	b5:1,	b6:1,	b7:1;
	} bits;
	uint8	U;
	int8	S;
};

union TInt16
{
	uint8	array[2];

	struct {
		uint8 	b0:1,	b1:1,	b2:1,	b3:1,	b4:1,	b5:1,	b6:1,	b7:1,
				b8:1,	b9:1,	b10:1,	b11:1,	b12:1,	b13:1,	b14:1,	b15:1;
	} bits;

	struct {
		int8	S0, S1;
	} S8;

	struct {
		uint8	B0, B1;
	} U8;

	struct {
		TInt8	T0, T1;
	} T8;

	int16	S16;
	uint16	U16;
};

union TInt32
{
	uint8	array[4];

	struct {
		uint8 	b0:1,	b1:1,	b2:1,	b3:1,	b4:1,	b5:1,	b6:1,	b7:1,
				b8:1,	b9:1,	b10:1,	b11:1,	b12:1,	b13:1,	b14:1,	b15:1,
				b16:1,	b17:1,	b18:1,	b19:1,	b20:1,	b21:1,	b22:1,	b23:1,
				b24:1,	b25:1,	b26:1,	b27:1,	b28:1,	b29:1,	b30:1,	b31:1;
	} bits;

	struct {
		int8	C0, C1, C2, C3;
	} S8;

	struct {
		uint8	B0, B1, B2, B3;
	} U8;

	struct {
		uint16	U0, U1;
	} U16;

	struct {
		int16	S0, S1;
	} S16;

	struct {
		TInt8	T0, T1, T2, T3;
	} T8;

	struct {
		TInt16	T0, T1;
	} T16;

	int32	S32;
	uint32	U32;
};
*/
