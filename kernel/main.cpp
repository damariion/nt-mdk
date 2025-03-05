#if DBG
#include "driver.h"

extern "C" NTSTATUS DriverEntry(DRIVER_OBJECT* driver, UNICODE_STRING* registry)
{
	// redirect to object-oriented implementation
	return driver::load(driver, registry); 
}
#endif