#
# InfinityC MakeFile
#	use 'make build' to build infinity.
#	Windows requires 'make' and 'gcc'.	
#

# variables

.PHONY: push
push:
	git add .
	git commit -m "new work done :)"
	git push


.PHONY: windows
windows:
	mkdir -p build
	gcc  -DDEBUG -D_WIN64 -Wl,-subsystem,windows --shared -o build/plugin.dll -I ../InfinityC/src -I src/ src/*.c

.PHONY: linux
linux:
	$(error linux builds not supported)