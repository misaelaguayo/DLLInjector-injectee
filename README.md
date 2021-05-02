# DLLInjector-injectee
This projects builds a dll injector and a dll file to be injected. This allows changes to be made to either with only one deployment. This project builds a DLL injector for WINDOWS and also currently only 32 bit. It uses mingw which is a windows compiler variant of gcc and it also uses cmake to build both the exe and dll.

I made this project to learn more about dll injection, cmake, and also to do some investigation on the binding of isaac.

Make sure to have TDM-GCC and CMake (>= 3.0) in your path.
To Build:

1.) cmake -G "MinGW Makefiles" . -DCMAKE_BUILD_TYPE=debug -DCMAKE_MAKE_PROGRAM=mingw32-make.exe -S . -B ./out/build


2.) cd to ./out/build and run mingw32-make.exe to build the executable and dll
