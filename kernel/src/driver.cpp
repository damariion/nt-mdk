#include "../include/driver.h"

// initial declaration
DRIVER_OBJECT* driver::self = nullptr;
DEVICE_OBJECT* driver::device = nullptr;
UNICODE_STRING* driver::registry = nullptr;

NTSTATUS driver::load(DRIVER_OBJECT* _driver, UNICODE_STRING* _registry)
{
	KdPrint(("[!] identifying driver\n"));
	driver::self = _driver;
	driver::registry = _registry;
	
	driver::device::name = RTL_CONSTANT_STRING(L"\\Device\\Damarioon");
	driver::device::link = RTL_CONSTANT_STRING(L"\\??\\Damarioon");

	KdPrint(("[!] associating methods\n"));
	_driver->DriverUnload = driver::unload;
	_driver->MajorFunction[IRP_MJ_CREATE] = driver::device::create;
	_driver->MajorFunction[IRP_MJ_CLOSE] = driver::device::close;
	_driver->MajorFunction[IRP_MJ_DEVICE_CONTROL] = driver::device::control;

	KdPrint(("[!] creating device\n"));
	NTSTATUS ret = STATUS_SUCCESS;
	
	if ((ret = IoCreateDevice(driver::self, 0, &driver::device::name,
		FILE_DEVICE_UNKNOWN, 0, FALSE, &driver::device)) != STATUS_SUCCESS)
	{
		KdPrint(("[-] couldn't create device\n"));
		return ret;
	}

	KdPrint(("[!] creating symbolic link\n"));
	if ((ret = IoCreateSymbolicLink(&driver::device::link, &driver::device::name)) != STATUS_SUCCESS)
	{
		KdPrint(("[!] deleting device\n"));
		IoDeleteDevice(driver::device);

		KdPrint(("[-] couldn't create symbolic link\n"));
		return ret;
	}

	return STATUS_SUCCESS;
}

VOID driver::unload(DRIVER_OBJECT* _driver)
{
	KdPrint(("[!] deleting symbolic link\n"));
	if (IoDeleteSymbolicLink(&driver::device::link) != STATUS_SUCCESS)
		KdPrint(("[!] couldn't delete symbolic link\n"));
	
	KdPrint(("[!] deleting device\n"));
	IoDeleteDevice(_driver->DeviceObject);

	return;
}