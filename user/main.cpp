#if !(_DEBUG)
#include <Windows.h>
#include <iostream>

#define CTL_ADD CTL_CODE(0x8000, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
typedef struct _NUMS
{
	int a;
	int b;
	int c;
} NUMS;

int main()
{

	std::cout << "[!] creating file\n";
	HANDLE driver = CreateFile(L"\\\\.\\Damarioon", GENERIC_WRITE, 
		FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);

	if (driver == INVALID_HANDLE_VALUE)
	{
		std::cout << "[-] couldn't create file\n";
		return 1;
	}

	std::cout << "[!] controlling device\n";
	NUMS in;
	NUMS out;
	
	in.a = 5;
	in.b = 3;

	DWORD lpBytesReturned;
	if (!DeviceIoControl(driver, CTL_ADD, &in, sizeof(NUMS), &out, sizeof(NUMS), &lpBytesReturned, nullptr))
		std::cout << "[-] couldn't control device\n";
	else
		std::cout << "[!] " << in.a << " + " << in.b << ": " << out.c << '\n';
	

	std::cout << "[!] closing (file) handle\n";
	CloseHandle(driver);
	
	std::cout << "[+] executed main" << std::endl;
	return 0;
}
#endif