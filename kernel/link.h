#pragma once
#include "core.h"

#define DEVICE_CODE 0x8000
typedef struct
{
	int a;
	int b;
	int c;
} NUMS, *pNUMS;

#define CTL_ADD CTL_CODE(DEVICE_CODE, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
VOID ADD(pNUMS nums)
{
	nums->c = nums->a + nums->b;
	KdPrint(("[!] calculated: %d + %d = %d", 
		nums->a, nums->b, nums->c));
}