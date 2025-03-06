#pragma once
#include "core.h"

#define DEVICE_CODE 0x8000
#define DEVICE_FUNC 0x800

#define CTL_ADD CTL_CODE(DEVICE_CODE, DEVICE_FUNC, METHOD_NEITHER, FILE_ANY_ACCESS)
typedef struct
{
	int a;
	int b;
} _STR_CTL_ADD_OPS;
typedef struct
{
	int ans;
} _STR_CTL_ADD_ANS;