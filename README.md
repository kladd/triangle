# triangle

(Incomplete)

The [Vulkan "Drawing a triangle"](https://docs.vulkan.org/tutorial/latest/00_Introduction.html)
tutorial but in C instead of C++ and with the Win32 API instead of GLFW.

## Compiling

`nmake`

## Shaders

It's late and I didn't want look up Win32 file I/O so the compiled shader is
hexdumped into a byte array. (They're actually `uint32_t[]` because that's the
Vulkan input type.)
