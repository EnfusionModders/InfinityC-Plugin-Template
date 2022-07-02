# Infinity 'C' Plugin Template

Template project for creating Infinity plugins.


## Template Enscript

```c
// NOTE: pointer classes do not need `ref` flags anywhere ever
// these are unmanaged !
sealed class ExamplePointerClass : pointer
{
    static proto ExamplePointerClass Create(string indata);
    proto external void Destroy();
    proto external int GetAccessCount();
    proto external void ArgSetTest(out int result);
	
	static proto void PrintTest();
};


void TestExtension() 
{
	ExamplePointerClass test = ExamplePointerClass.Create("test");
	int value;
	test.ArgSetTest(value);
	Print(test);
	Print(value);
}
```


## Building

Ensure you have updated the `InfinityC` submodule.

`git submodule update --init --recursive --remote`

### Windows

You need to install [MinGW-w64](https://www.mingw-w64.org/downloads/) to build.

You need to install `make` to run the make commands.

I recommend installing [Msys2](https://www.msys2.org/) which can provide both of the binaries above.

Run `make windows` to build on windows for windows targets.

### Linux

You need to install [GCC 12.1](https://tutorialforlinux.com/2022/05/25/step-by-step-gcc-12-1-ubuntu-20-04-installation-guide/)

You need to install MAKE.

Run `make linux` to build on linux for linux targets.

_Note: WSL is supported for linux builds_

