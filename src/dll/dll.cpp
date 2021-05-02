// dllmain.cpp : Defines the entry point for the DLL application.
#include <windows.h>
#include <stdio.h>
#include <iostream>

DWORD WINAPI runBot(LPVOID lpParam) {
    AllocConsole();
    FILE* f;

    freopen_s(&f, "CONOUT$", "w", stdout);

    //get module base
    uintptr_t moduleBase = (uintptr_t)GetModuleHandle("isaac-ng.exe");
    std::cout << "Initialized dll injection on isaac. module Base is: " << std::hex << moduleBase << "\n";

    while (true)
    {
        if (GetAsyncKeyState(VK_END) & 1)
        {
            std::cout << "Normal register values: \n";
            //std::cout << "First param: " << std::hex << firstParam << " Second param: " << secondParam << std::hex << " Third param: " << std::hex << thirdParam << "\n";
            std::cout << std::endl;
        }

        if (GetAsyncKeyState(0X4A) & 1)
        {
            //*(float*)xPos += 1;
        }
        Sleep(5);
    }

    return 1;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        {
            auto thread = CreateThread(NULL, 0, &runBot, NULL, 0, NULL);
            CloseHandle(thread);
        }
        break;
    case DLL_PROCESS_DETACH:
        printf("DLL detached!\n");
        break;
    }
    return TRUE;
}