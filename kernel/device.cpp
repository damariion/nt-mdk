#include "driver.h"
#include "link.h"

// initial declaration
UNICODE_STRING driver::device::name = RTL_CONSTANT_STRING(L"");
UNICODE_STRING driver::device::link = RTL_CONSTANT_STRING(L"");

// currently (mostly) identical
// {
NTSTATUS driver::device::create(DEVICE_OBJECT* _device, IRP* _irp)
{
	// silence compiler
	UNREFERENCED_PARAMETER(_device);

	KdPrint(("[!] creating driver device\n"));
	_irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(_irp, 0);
	
	KdPrint(("[+] created driver device\n"));
	return _irp->IoStatus.Status;
}

NTSTATUS driver::device::close(DEVICE_OBJECT* _device, IRP* _irp)
{
	// silence compiler
	UNREFERENCED_PARAMETER(_device);

	KdPrint(("[!] closing driver device\n"));
	_irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest(_irp, 0);

	KdPrint(("[+] closed driver device\n"));
	return _irp->IoStatus.Status;
}
// }

NTSTATUS driver::device::control(DEVICE_OBJECT* _device, IRP* _irp)
{
	// silence compiler
	UNREFERENCED_PARAMETER(_device);

	KdPrint(("[!] locating ctl code\n"));
	auto stack = IoGetCurrentIrpStackLocation(_irp);
	
	switch (stack->Parameters.DeviceIoControl.IoControlCode)
	{
		case CTL_ADD:
		{
			auto nums = (pNUMS)stack->Parameters.DeviceIoControl.Type3InputBuffer;
			ADD(nums); _irp->UserBuffer = nums;

			break;
		}

		default:
			KdPrint(("[-] couldn't locate ctl code\n"));
			break;
	}

	IoCompleteRequest(_irp, 0);

	KdPrint(("[+] controlled driver device\n"));
	return STATUS_SUCCESS;
}