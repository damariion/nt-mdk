#pragma once
#include "core.h"

extern "C" class driver
{
public:
	
	static DRIVER_OBJECT* self;
	static DEVICE_OBJECT* device;
	static UNICODE_STRING* registry;

	// (de)initialization
	static NTSTATUS load(DRIVER_OBJECT*, UNICODE_STRING*);
	static VOID unload(DRIVER_OBJECT*);


	class device
	{
	public:

		static UNICODE_STRING name;
		static UNICODE_STRING link;

		static NTSTATUS create(DEVICE_OBJECT*, IRP*);
		static NTSTATUS close(DEVICE_OBJECT*, IRP*);
		static NTSTATUS control(DEVICE_OBJECT*, IRP*);
	};
};