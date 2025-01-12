all: build\triangle.exe

build\triangle.exe: build\vert.spv build\frag.spv always
	cd build
	cl /Zi /IC:\VulkanSDK\1.3.296.0\Include ..\src\main.c /link /machine:x64 /out:triangle.exe /libpath:C:\VulkanSDK\1.3.296.0\Lib User32.lib vulkan-1.lib

build\vert.spv: shaders\triangle.vert
	C:\VulkanSDK\1.3.296.0\Bin\glslc.exe shaders\triangle.vert -o build\vert.spv

build\frag.spv: shaders\triangle.frag
	C:\VulkanSDK\1.3.296.0\Bin\glslc.exe shaders\triangle.frag -o build\frag.spv

debug: build\triangle.exe
	devenv triangle.exe

build:
	mkdir build

clean:
	del build\*

always:
	;
