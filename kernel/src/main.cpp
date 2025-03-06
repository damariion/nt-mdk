#if DBG
#include "../include/driver.h"

extern "C" NTSTATUS DriverEntry(DRIVER_OBJECT* driver, UNICODE_STRING* registry)
{
	KdPrint(("[!] redirecting driver entry...\n"));
	return driver::load(driver, registry); 
}
#endif