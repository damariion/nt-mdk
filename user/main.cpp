#if !(_DEBUG)
#include <Windows.h>
#include <iostream>

#define CTL_ADD CTL_CODE(0x8000, 0x800, METHOD_NEITHER, FILE_ANY_ACCESS)
typedef struct
{
	int a;
	int b;
} _STR_CTL_ADD_OPS;
typedef struct
{
	int ans;
} _STR_CTL_ADD_ANS;

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
	
	// parameters
	_STR_CTL_ADD_OPS* ops = new _STR_CTL_ADD_OPS {4, 5};
	_STR_CTL_ADD_ANS* ans = new _STR_CTL_ADD_ANS;

	DWORD lpBytesReturned;
	if (!DeviceIoControl(driver, CTL_ADD, ops, sizeof(_STR_CTL_ADD_OPS), 
		ans, sizeof(_STR_CTL_ADD_ANS), &lpBytesReturned, nullptr))
		std::cout << "[-] couldn't control device\n";
	else
		std::cout << "[!] " << ops->a << " + " << ops->b << " = " << ans->ans << '\n';
	

	std::cout << "[!] closing (file) handle\n";
	CloseHandle(driver);
	delete ops;
	delete ans;
	
	std::cout << "[+] executed main" << std::endl;
	return 0;
}
#endif