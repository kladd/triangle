all: build\triangle.exe

build\triangle.exe: build\vert.c build\frag.c always
	cd build
	cl /Zi /IC:\VulkanSDK\1.3.296.0\Include ..\src\main.c /link /machine:x64 /out:triangle.exe /libpath:C:\VulkanSDK\1.3.296.0\Lib User32.lib vulkan-1.lib

build\vert.c: shaders\triangle.vert
	C:\VulkanSDK\1.3.296.0\Bin\glslc.exe -mfmt=c shaders\triangle.vert -o build\vert.c

build\frag.c: shaders\triangle.frag
	C:\VulkanSDK\1.3.296.0\Bin\glslc.exe -mfmt=c shaders\triangle.frag  -o build\frag.c

debug: build\triangle.exe
	devenv triangle.exe

build:
	mkdir build

clean:
	del build\*

always:
	;
