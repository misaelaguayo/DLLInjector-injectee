// injectDll.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <strsafe.h>
using namespace std;

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString()
{
    //Get the error message, if any.
    DWORD errorMessageID = ::GetLastError();
    if (errorMessageID == 0)
        return std::string(); //No error message has been recorded

    LPSTR messageBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        0, errorMessageID, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, 0);

    std::string message(messageBuffer, size);

    //Free the buffer.
    LocalFree(messageBuffer);

    return message;
}

int main()
{
    std::cout << "Hello World!\n";
    HANDLE hProcess = nullptr;
    
    //get a handle to the process
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);
    HANDLE snapshot =
        CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (Process32First(snapshot, &entry) == TRUE) {
        while (Process32Next(snapshot, &entry) == TRUE) {
            char *binPath = entry.szExeFile;
            char process[] = "isaac-ng.exe";
            if (strcmp(binPath, process) == 0) {
                cout << "game pid is " << entry.th32ProcessID << "\n";

                hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, entry.th32ProcessID);
                break;
            }
        }
    }
    CloseHandle(snapshot);

    //write the dll name to memory
    const wchar_t* dllName = L"C:\\Users\\misae\\source\\repos\\generiCdLL\\Debug\\genericDll.dll";
    //const wchar_t* dllName = L"dll.dll";
    int namelen = wcslen(dllName) + 1;
    LPVOID remoteString =
        VirtualAllocEx(hProcess, 0, namelen * 2, MEM_COMMIT, PAGE_EXECUTE);
    if (!remoteString) {
        cout << GetLastErrorAsString() << "\n";
    }

    WriteProcessMemory(hProcess, remoteString, dllName, namelen * 2, 0);
    cout << GetLastErrorAsString() << "\n";

    // get the address of LoadLibraryW()
    HMODULE k32 = GetModuleHandleA("kernel32.dll");
    LPVOID funcAdr = (LPVOID) GetProcAddress(k32, "LoadLibraryW");

    // create a thread to call LoadLibraryW(dllName)
    HANDLE thread =
        CreateRemoteThread(hProcess, 0, 0,
            (LPTHREAD_START_ROUTINE)funcAdr,
            remoteString, 0, 0);

    // let the thread finish and clean up
    CloseHandle(hProcess);
    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);

    int c;
    c = getchar();
}