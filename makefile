#
# InfinityC MakeFile
#	use 'make build' to build infinity.
#	Windows requires 'make' and 'gcc'.	
#

# variables

.PHONY: windows
windows:
	mkdir -p build
	gcc -D_WIN64 -Wl,-subsystem,windows --shared -o build/plugin.dll -I InfinityC/src -I src/ src/*.c

.PHONY: linux
linux:
	mkdir -p build
	gcc -D_GNU_SOURCE -fvisibility=hidden -fPIC -Wno-attributes --shared -o build/plugin.so -I InfinityC/src -I src/ src/*.c