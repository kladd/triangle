// #include "vulkan/vulkan_core.h"
#include "vulkan/vulkan_core.h"
#include <Windows.h>
#include <assert.h>
#include <stdint.h>
#include <vulkan\vulkan.h>
#include <vulkan\vulkan_win32.h>

static const uint32_t FRAG_SHADER[] = {
    0x07230203, 0x00010000, 0x000d000b, 0x00000013, 0x00000000, 0x00020011,
    0x00000001, 0x0006000b, 0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e,
    0x00000000, 0x0003000e, 0x00000000, 0x00000001, 0x0007000f, 0x00000004,
    0x00000004, 0x6e69616d, 0x00000000, 0x00000009, 0x0000000c, 0x00030010,
    0x00000004, 0x00000007, 0x00030003, 0x00000002, 0x000001c2, 0x000a0004,
    0x475f4c47, 0x4c474f4f, 0x70635f45, 0x74735f70, 0x5f656c79, 0x656e696c,
    0x7269645f, 0x69746365, 0x00006576, 0x00080004, 0x475f4c47, 0x4c474f4f,
    0x6e695f45, 0x64756c63, 0x69645f65, 0x74636572, 0x00657669, 0x00040005,
    0x00000004, 0x6e69616d, 0x00000000, 0x00050005, 0x00000009, 0x4374756f,
    0x726f6c6f, 0x00000000, 0x00050005, 0x0000000c, 0x67617266, 0x6f6c6f43,
    0x00000072, 0x00040047, 0x00000009, 0x0000001e, 0x00000000, 0x00040047,
    0x0000000c, 0x0000001e, 0x00000000, 0x00020013, 0x00000002, 0x00030021,
    0x00000003, 0x00000002, 0x00030016, 0x00000006, 0x00000020, 0x00040017,
    0x00000007, 0x00000006, 0x00000004, 0x00040020, 0x00000008, 0x00000003,
    0x00000007, 0x0004003b, 0x00000008, 0x00000009, 0x00000003, 0x00040017,
    0x0000000a, 0x00000006, 0x00000003, 0x00040020, 0x0000000b, 0x00000001,
    0x0000000a, 0x0004003b, 0x0000000b, 0x0000000c, 0x00000001, 0x0004002b,
    0x00000006, 0x0000000e, 0x3f800000, 0x00050036, 0x00000002, 0x00000004,
    0x00000000, 0x00000003, 0x000200f8, 0x00000005, 0x0004003d, 0x0000000a,
    0x0000000d, 0x0000000c, 0x00050051, 0x00000006, 0x0000000f, 0x0000000d,
    0x00000000, 0x00050051, 0x00000006, 0x00000010, 0x0000000d, 0x00000001,
    0x00050051, 0x00000006, 0x00000011, 0x0000000d, 0x00000002, 0x00070050,
    0x00000007, 0x00000012, 0x0000000f, 0x00000010, 0x00000011, 0x0000000e,
    0x0003003e, 0x00000009, 0x00000012, 0x000100fd, 0x00010038};

static const uint32_t VERT_SHADER[] = {
    0x07230203, 0x00010000, 0x000d000b, 0x00000036, 0x00000000, 0x00020011,
    0x00000001, 0x0006000b, 0x00000001, 0x4c534c47, 0x6474732e, 0x3035342e,
    0x00000000, 0x0003000e, 0x00000000, 0x00000001, 0x0008000f, 0x00000000,
    0x00000004, 0x6e69616d, 0x00000000, 0x00000022, 0x00000026, 0x00000031,
    0x00030003, 0x00000002, 0x000001c2, 0x000a0004, 0x475f4c47, 0x4c474f4f,
    0x70635f45, 0x74735f70, 0x5f656c79, 0x656e696c, 0x7269645f, 0x69746365,
    0x00006576, 0x00080004, 0x475f4c47, 0x4c474f4f, 0x6e695f45, 0x64756c63,
    0x69645f65, 0x74636572, 0x00657669, 0x00040005, 0x00000004, 0x6e69616d,
    0x00000000, 0x00050005, 0x0000000c, 0x69736f70, 0x6e6f6974, 0x00000073,
    0x00040005, 0x00000017, 0x6f6c6f63, 0x00007372, 0x00060005, 0x00000020,
    0x505f6c67, 0x65567265, 0x78657472, 0x00000000, 0x00060006, 0x00000020,
    0x00000000, 0x505f6c67, 0x7469736f, 0x006e6f69, 0x00070006, 0x00000020,
    0x00000001, 0x505f6c67, 0x746e696f, 0x657a6953, 0x00000000, 0x00070006,
    0x00000020, 0x00000002, 0x435f6c67, 0x4470696c, 0x61747369, 0x0065636e,
    0x00070006, 0x00000020, 0x00000003, 0x435f6c67, 0x446c6c75, 0x61747369,
    0x0065636e, 0x00030005, 0x00000022, 0x00000000, 0x00060005, 0x00000026,
    0x565f6c67, 0x65747265, 0x646e4978, 0x00007865, 0x00050005, 0x00000031,
    0x67617266, 0x6f6c6f43, 0x00000072, 0x00030047, 0x00000020, 0x00000002,
    0x00050048, 0x00000020, 0x00000000, 0x0000000b, 0x00000000, 0x00050048,
    0x00000020, 0x00000001, 0x0000000b, 0x00000001, 0x00050048, 0x00000020,
    0x00000002, 0x0000000b, 0x00000003, 0x00050048, 0x00000020, 0x00000003,
    0x0000000b, 0x00000004, 0x00040047, 0x00000026, 0x0000000b, 0x0000002a,
    0x00040047, 0x00000031, 0x0000001e, 0x00000000, 0x00020013, 0x00000002,
    0x00030021, 0x00000003, 0x00000002, 0x00030016, 0x00000006, 0x00000020,
    0x00040017, 0x00000007, 0x00000006, 0x00000002, 0x00040015, 0x00000008,
    0x00000020, 0x00000000, 0x0004002b, 0x00000008, 0x00000009, 0x00000003,
    0x0004001c, 0x0000000a, 0x00000007, 0x00000009, 0x00040020, 0x0000000b,
    0x00000006, 0x0000000a, 0x0004003b, 0x0000000b, 0x0000000c, 0x00000006,
    0x0004002b, 0x00000006, 0x0000000d, 0x00000000, 0x0004002b, 0x00000006,
    0x0000000e, 0xbf000000, 0x0005002c, 0x00000007, 0x0000000f, 0x0000000d,
    0x0000000e, 0x0004002b, 0x00000006, 0x00000010, 0x3f000000, 0x0005002c,
    0x00000007, 0x00000011, 0x00000010, 0x00000010, 0x0005002c, 0x00000007,
    0x00000012, 0x0000000e, 0x00000010, 0x0006002c, 0x0000000a, 0x00000013,
    0x0000000f, 0x00000011, 0x00000012, 0x00040017, 0x00000014, 0x00000006,
    0x00000003, 0x0004001c, 0x00000015, 0x00000014, 0x00000009, 0x00040020,
    0x00000016, 0x00000006, 0x00000015, 0x0004003b, 0x00000016, 0x00000017,
    0x00000006, 0x0004002b, 0x00000006, 0x00000018, 0x3f800000, 0x0006002c,
    0x00000014, 0x00000019, 0x00000018, 0x0000000d, 0x0000000d, 0x0006002c,
    0x00000014, 0x0000001a, 0x0000000d, 0x00000018, 0x0000000d, 0x0006002c,
    0x00000014, 0x0000001b, 0x0000000d, 0x0000000d, 0x00000018, 0x0006002c,
    0x00000015, 0x0000001c, 0x00000019, 0x0000001a, 0x0000001b, 0x00040017,
    0x0000001d, 0x00000006, 0x00000004, 0x0004002b, 0x00000008, 0x0000001e,
    0x00000001, 0x0004001c, 0x0000001f, 0x00000006, 0x0000001e, 0x0006001e,
    0x00000020, 0x0000001d, 0x00000006, 0x0000001f, 0x0000001f, 0x00040020,
    0x00000021, 0x00000003, 0x00000020, 0x0004003b, 0x00000021, 0x00000022,
    0x00000003, 0x00040015, 0x00000023, 0x00000020, 0x00000001, 0x0004002b,
    0x00000023, 0x00000024, 0x00000000, 0x00040020, 0x00000025, 0x00000001,
    0x00000023, 0x0004003b, 0x00000025, 0x00000026, 0x00000001, 0x00040020,
    0x00000028, 0x00000006, 0x00000007, 0x00040020, 0x0000002e, 0x00000003,
    0x0000001d, 0x00040020, 0x00000030, 0x00000003, 0x00000014, 0x0004003b,
    0x00000030, 0x00000031, 0x00000003, 0x00040020, 0x00000033, 0x00000006,
    0x00000014, 0x00050036, 0x00000002, 0x00000004, 0x00000000, 0x00000003,
    0x000200f8, 0x00000005, 0x0003003e, 0x0000000c, 0x00000013, 0x0003003e,
    0x00000017, 0x0000001c, 0x0004003d, 0x00000023, 0x00000027, 0x00000026,
    0x00050041, 0x00000028, 0x00000029, 0x0000000c, 0x00000027, 0x0004003d,
    0x00000007, 0x0000002a, 0x00000029, 0x00050051, 0x00000006, 0x0000002b,
    0x0000002a, 0x00000000, 0x00050051, 0x00000006, 0x0000002c, 0x0000002a,
    0x00000001, 0x00070050, 0x0000001d, 0x0000002d, 0x0000002b, 0x0000002c,
    0x0000000d, 0x00000018, 0x00050041, 0x0000002e, 0x0000002f, 0x00000022,
    0x00000024, 0x0003003e, 0x0000002f, 0x0000002d, 0x0004003d, 0x00000023,
    0x00000032, 0x00000026, 0x00050041, 0x00000033, 0x00000034, 0x00000017,
    0x00000032, 0x0004003d, 0x00000014, 0x00000035, 0x00000034, 0x0003003e,
    0x00000031, 0x00000035, 0x000100fd, 0x00010038};

LRESULT CALLBACK TraingleMain(HWND window, UINT message, WPARAM wp, LPARAM lp)
{
    LRESULT result = 0;

    switch (message) {
        case WM_CLOSE: {
            OutputDebugStringA("WM_CLOSE\n");
            PostQuitMessage(0);
        } break;
        default: {
            result = DefWindowProc(window, message, wp, lp);
        };
    }

    return result;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                     LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSW wc = {.style = CS_CLASSDC,
                    .lpfnWndProc = TraingleMain,
                    .hInstance = hInstance,
                    .lpszClassName = L"Triangle"};

    RegisterClassW(&wc);
    HWND window = CreateWindowExW(
        0, wc.lpszClassName, L"Triangle", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, 0, 0, hInstance, 0);

    VkApplicationInfo vkAppInfo = {.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
                                   .pApplicationName = "Triangle",
                                   .applicationVersion =
                                       VK_MAKE_VERSION(1, 0, 0),
                                   .pEngineName = "None",
                                   .engineVersion = VK_MAKE_VERSION(1, 0, 0),
                                   .apiVersion = VK_API_VERSION_1_0};

    const char *validationLayers[] = {"VK_LAYER_KHRONOS_validation"};
    const char *enabledExtensions[] = {VK_KHR_SURFACE_EXTENSION_NAME,
                                       VK_KHR_WIN32_SURFACE_EXTENSION_NAME};

    VkInstanceCreateInfo vkInstanceInfo = {
        .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
        .pApplicationInfo = &vkAppInfo,
        .enabledLayerCount = 1,
        .ppEnabledLayerNames = validationLayers,
        .enabledExtensionCount = 2,
        .ppEnabledExtensionNames = enabledExtensions};

    VkInstance vkInstance;
    if (vkCreateInstance(&vkInstanceInfo, 0, &vkInstance) != VK_SUCCESS) {
        OutputDebugStringA("CreateVKInstance failed.\n");
    }

    uint32_t vkDeviceCount = 0;
    vkEnumeratePhysicalDevices(vkInstance, &vkDeviceCount, 0);

    if (!vkDeviceCount) {
        OutputDebugStringA("No GPU found.\n");
    }
    VkPhysicalDevice *vkDevices = (VkPhysicalDevice *)VirtualAlloc(
        0, sizeof(VkPhysicalDevice) * vkDeviceCount, MEM_COMMIT,
        PAGE_READWRITE);
    vkEnumeratePhysicalDevices(vkInstance, &vkDeviceCount, vkDevices);

    VkPhysicalDeviceProperties vkDeviceProperties;
    for (int i = 0; i < vkDeviceCount; i++) {
        vkGetPhysicalDeviceProperties(vkDevices[i], &vkDeviceProperties);
        OutputDebugString("Device found: ");
        OutputDebugString(vkDeviceProperties.deviceName);
        OutputDebugString("\n");
    }
    assert(vkDeviceCount == 1);

    uint32_t vkQueueFamilyCount = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(vkDevices[0], &vkQueueFamilyCount,
                                             0);
    VkQueueFamilyProperties *vkQueueFamilies =
        (VkQueueFamilyProperties *)VirtualAlloc(
            0, sizeof(VkQueueFamilyProperties) * vkDeviceCount, MEM_COMMIT,
            PAGE_READWRITE);
    vkGetPhysicalDeviceQueueFamilyProperties(vkDevices[0], &vkQueueFamilyCount,
                                             vkQueueFamilies);
    assert(vkQueueFamilyCount);
    int vkGfxQueueIndex = -1;
    for (int i = 0; i < vkQueueFamilyCount; i++) {
        if (vkQueueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            vkGfxQueueIndex = i;
            break;
        }
    }
    assert(vkGfxQueueIndex >= 0);

    float vkGfxQueuePriority = 1.0f;
    VkDeviceQueueCreateInfo vkQueueCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
        .queueFamilyIndex = vkGfxQueueIndex,
        .queueCount = 1,
        .pQueuePriorities = &vkGfxQueuePriority};

    VkPhysicalDeviceFeatures vkDeviceFeatures = {};

    const char *vkDeviceExtensions[] = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME,
    };

    VkDeviceCreateInfo vkDeviceCreateInfo = {
        .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
        .queueCreateInfoCount = 1,
        .pQueueCreateInfos = &vkQueueCreateInfo,
        .pEnabledFeatures = &vkDeviceFeatures,
        .enabledExtensionCount = 1,
        .ppEnabledExtensionNames = vkDeviceExtensions};

    VkWin32SurfaceCreateInfoKHR vkCreateSurfaceInfo = {};
    vkCreateSurfaceInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
    vkCreateSurfaceInfo.hwnd = window;
    vkCreateSurfaceInfo.hinstance = hInstance;

    VkSurfaceKHR vkSurface = {};
    if (vkCreateWin32SurfaceKHR(vkInstance, &vkCreateSurfaceInfo, 0,
                                &vkSurface)) {
        OutputDebugString("Failed to create Win32 surface.");
        goto exit;
    }

    VkDevice vkDevice = {};
    if (vkCreateDevice(vkDevices[0], &vkDeviceCreateInfo, 0, &vkDevice) !=
        VK_SUCCESS) {
        OutputDebugString("Failed to create logical device.");
        goto exit;
    }

    VkQueue vkGfxQueue = {};
    vkGetDeviceQueue(vkDevice, vkGfxQueueIndex, 0, &vkGfxQueue);
    VkQueue *vkPresentQueue = &vkGfxQueue;

    VkSurfaceCapabilitiesKHR vkCapabilites = {};
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vkDevices[0], vkSurface,
                                              &vkCapabilites);

    VkSurfaceFormatKHR vkSurfaceFormat = {
        .format = VK_FORMAT_B8G8R8A8_SRGB,
        .colorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};

    VkPresentModeKHR vkPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;

    VkSwapchainCreateInfoKHR vkSwapChainCreateInfo = {
        .clipped = VK_TRUE,
        .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        .imageArrayLayers = 1,
        .imageColorSpace = vkSurfaceFormat.colorSpace,
        .imageExtent = vkCapabilites.currentExtent,
        .imageFormat = vkSurfaceFormat.format,
        .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,
        .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
        .minImageCount = vkCapabilites.minImageCount + 1,
        .oldSwapchain = VK_NULL_HANDLE,
        .preTransform = vkCapabilites.currentTransform,
        .presentMode = vkPresentMode,
        .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
        .surface = vkSurface};
    VkSwapchainKHR vkSwapChain = {};

    if (vkCreateSwapchainKHR(vkDevice, &vkSwapChainCreateInfo, 0,
                             &vkSwapChain) != VK_SUCCESS) {
        OutputDebugString("Failed to create swapchain.\n");
        goto exit;
    }

    uint32_t vkImageCount = 0;
    VkImage *vkImages = 0;
    vkGetSwapchainImagesKHR(vkDevice, vkSwapChain, &vkImageCount, 0);
    assert(vkImageCount > 0);
    vkImages = (VkImage *)VirtualAlloc(0, sizeof(VkImage) * vkImageCount,
                                       MEM_COMMIT, PAGE_READWRITE);
    vkGetSwapchainImagesKHR(vkDevice, vkSwapChain, &vkImageCount, vkImages);
    VkImageView *vkImageViews = (VkImageView *)VirtualAlloc(
        0, sizeof(VkImageView) * vkImageCount, MEM_COMMIT, PAGE_READWRITE);

    for (int i = 0; i < vkImageCount; i++) {
        VkImageViewCreateInfo createInfo = {
            .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
            .image = vkImages[i],
            .viewType = VK_IMAGE_VIEW_TYPE_2D,
            .format = vkSurfaceFormat.format,
            .components =
                {
                    .a = VK_COMPONENT_SWIZZLE_IDENTITY,
                    .r = VK_COMPONENT_SWIZZLE_IDENTITY,
                    .g = VK_COMPONENT_SWIZZLE_IDENTITY,
                    .b = VK_COMPONENT_SWIZZLE_IDENTITY,
                },
            .subresourceRange = {.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
                                 .levelCount = 1,
                                 .layerCount = 1}};
        if (vkCreateImageView(vkDevice, &createInfo, 0, &vkImageViews[i]) !=
            VK_SUCCESS) {
            OutputDebugString("Failed to create ImageView.\n");
            goto exit;
        }
    }

    VkShaderModule vkVertShader = {};
    {
        VkShaderModuleCreateInfo module = {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .codeSize = sizeof(VERT_SHADER),
            .pCode = VERT_SHADER,
        };
        if (vkCreateShaderModule(vkDevice, &module, 0, &vkVertShader)) {
            OutputDebugString("Failed to create vert shader.\n");
            goto exit;
        }
    }

    VkShaderModule vkFragShader = {};
    {
        VkShaderModuleCreateInfo create = {
            .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
            .codeSize = sizeof(FRAG_SHADER),
            .pCode = FRAG_SHADER,
        };
        if (vkCreateShaderModule(vkDevice, &create, 0, &vkFragShader)) {
            OutputDebugString("Failed to create frag shader.\n");
            goto exit;
        }
    }

    VkPipelineShaderStageCreateInfo vkStageCreateInfos[] = {
        {.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
         .stage = VK_SHADER_STAGE_VERTEX_BIT,
         .module = vkVertShader,
         .pName = "main"},
        {.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
         .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
         .module = vkFragShader,
         .pName = "main"}};

    VkDynamicState vkDynamicStates[] = {VK_DYNAMIC_STATE_VIEWPORT,
                                        VK_DYNAMIC_STATE_SCISSOR};

    VkPipelineDynamicStateCreateInfo vkDynamicState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = 2,
        .pDynamicStates = vkDynamicStates};

    VkPipelineVertexInputStateCreateInfo vkVertexInputState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    };

    VkPipelineInputAssemblyStateCreateInfo vkInputAssemblyState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
        .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST,
        .primitiveRestartEnable = VK_FALSE,
    };

    VkViewport vkViewport = {.x = 0.0f,
                             .y = 0.0f,
                             .width = vkCapabilites.currentExtent.width,
                             .height = vkCapabilites.currentExtent.height,
                             .minDepth = 0.0f,
                             .maxDepth = 1.0f};

    VkRect2D vkScissor = {.offset = {0, 0},
                          .extent = vkCapabilites.currentExtent};

    VkPipelineViewportStateCreateInfo vkViewportState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .scissorCount = 1,
    };

    VkPipelineRasterizationStateCreateInfo vkRasterizerState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode = VK_POLYGON_MODE_FILL,
        .lineWidth = 1.0f,
        .cullMode = VK_CULL_MODE_BACK_BIT,
        .frontFace = VK_FRONT_FACE_CLOCKWISE,
        .depthBiasEnable = VK_FALSE};

    VkPipelineMultisampleStateCreateInfo vkMultisampleState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
        .minSampleShading = 1.0f,
    };

    VkPipelineColorBlendAttachmentState vkColorBlendAttachment = {
        .colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
                          VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
        .blendEnable = VK_FALSE,
        .srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ZERO,
        .colorBlendOp = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
        .alphaBlendOp = VK_BLEND_OP_ADD,
    };

    VkPipelineColorBlendStateCreateInfo vkColorBlendState = {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .attachmentCount = 1,
        .pAttachments = &vkColorBlendAttachment};

    VkPipelineLayout vkPipelineLayout = {};
    {
        VkPipelineLayoutCreateInfo pipelineLayout = {
            .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO,
        };
        if (vkCreatePipelineLayout(vkDevice, &pipelineLayout, 0,
                                   &vkPipelineLayout) != VK_SUCCESS) {
            OutputDebugString("Failed to create pipeline layout.\n");
            goto exit;
        }
    }

    VkAttachmentDescription vkColorAttachment = {
        .format = vkSurfaceFormat.format,
        .samples = VK_SAMPLE_COUNT_1_BIT,
        .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
        .storeOp = VK_ATTACHMENT_STORE_OP_STORE,
        .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
        .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
        .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
        .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR};

    VkAttachmentReference vkAttachmentRef = {
        .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};
    VkSubpassDescription vkSubpass = {.pipelineBindPoint =
                                          VK_PIPELINE_BIND_POINT_GRAPHICS,
                                      .colorAttachmentCount = 1,
                                      .pColorAttachments = &vkAttachmentRef};

    VkRenderPass vkRenderPass = {};
    {
        VkSubpassDependency subpassDeps = {
            .srcSubpass = VK_SUBPASS_EXTERNAL,
            .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,
            .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT};
        VkRenderPassCreateInfo renderPass = {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO,
            .attachmentCount = 1,
            .pAttachments = &vkColorAttachment,
            .subpassCount = 1,
            .pSubpasses = &vkSubpass,
            .dependencyCount = 1,
            .pDependencies = &subpassDeps};

        if (vkCreateRenderPass(vkDevice, &renderPass, 0, &vkRenderPass) !=
            VK_SUCCESS) {
            OutputDebugString("Failed to create render pass.\n");
            goto exit;
        }
    }

    VkPipeline vkGfxPipeline = {};
    {
        VkGraphicsPipelineCreateInfo gfxPipelineCreate = {
            .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
            .stageCount = 2,
            .pStages = vkStageCreateInfos,
            .pVertexInputState = &vkVertexInputState,
            .pInputAssemblyState = &vkInputAssemblyState,
            .pViewportState = &vkViewportState,
            .pRasterizationState = &vkRasterizerState,
            .pMultisampleState = &vkMultisampleState,
            .pColorBlendState = &vkColorBlendState,
            .pDynamicState = &vkDynamicState,
            .layout = vkPipelineLayout,
            .renderPass = vkRenderPass};

        if (vkCreateGraphicsPipelines(vkDevice, VK_NULL_HANDLE, 1,
                                      &gfxPipelineCreate, 0,
                                      &vkGfxPipeline) != VK_SUCCESS) {
            OutputDebugString("Failed to create graphics pipeline.\n");
            goto exit;
        }
    }

    VkFramebuffer *vkFrameBuffers = (VkFramebuffer *)VirtualAlloc(
        0, sizeof(VkFramebuffer) * vkImageCount, MEM_COMMIT, PAGE_READWRITE);
    for (int i = 0; i < vkImageCount; i++) {
        VkImageView attachments[] = {vkImageViews[i]};
        VkFramebufferCreateInfo fbInfo = {
            .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
            .renderPass = vkRenderPass,
            .attachmentCount = 1,
            .pAttachments = attachments,
            .width = vkCapabilites.currentExtent.width,
            .height = vkCapabilites.currentExtent.height,
            .layers = 1};
        if (vkCreateFramebuffer(vkDevice, &fbInfo, 0, &vkFrameBuffers[i]) !=
            VK_SUCCESS) {
            OutputDebugString("Failed to create frame buffer.\n");
            goto exit;
        }
    }

    VkCommandPool vkCommandPool = {};
    {
        VkCommandPoolCreateInfo commandPoolInfo = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,
            .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT,
            .queueFamilyIndex = vkGfxQueueIndex};
        if (vkCreateCommandPool(vkDevice, &commandPoolInfo, 0,
                                &vkCommandPool) != VK_SUCCESS) {
            OutputDebugString("Failed to create command pool.\n");
            goto exit;
        }
    }

    VkCommandBuffer vkCommandBuffer = {};
    {
        VkCommandBufferAllocateInfo cmdBufferAlloc = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO,
            .commandPool = vkCommandPool,
            .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
            .commandBufferCount = 1};

        if (vkAllocateCommandBuffers(vkDevice, &cmdBufferAlloc,
                                     &vkCommandBuffer) != VK_SUCCESS) {
            OutputDebugString("Failed to allocate command buffer.\n");
            goto exit;
        }
    }

    VkSemaphore vkImageAvailable = {};
    VkSemaphore vkRenderFinished = {};
    VkFence vkInFlightFence = {};
    {
        VkSemaphoreCreateInfo createSemaphore = {
            .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO};
        VkFenceCreateInfo createFence = {
            .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO,
            .flags = VK_FENCE_CREATE_SIGNALED_BIT};
        if (vkCreateSemaphore(vkDevice, &createSemaphore, 0,
                              &vkImageAvailable) != VK_SUCCESS ||
            vkCreateSemaphore(vkDevice, &createSemaphore, 0,
                              &vkRenderFinished) != VK_SUCCESS ||
            vkCreateFence(vkDevice, &createFence, 0, &vkInFlightFence) !=
                VK_SUCCESS) {

            OutputDebugString("Failed to create sync structures.\n");
            goto exit;
        }
    }

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};

    MSG message;
    while (GetMessageW(&message, 0, 0, 0)) {
        TranslateMessage(&message);
        DispatchMessageW(&message);

        vkWaitForFences(vkDevice, 1, &vkInFlightFence, VK_TRUE, UINT64_MAX);
        vkResetFences(vkDevice, 1, &vkInFlightFence);
        uint32_t image = 0;
        vkAcquireNextImageKHR(vkDevice, vkSwapChain, UINT64_MAX,
                              vkImageAvailable, VK_NULL_HANDLE, &image);

        vkResetCommandBuffer(vkCommandBuffer, 0);

        VkCommandBufferBeginInfo vkCommandBufferBegin = {
            .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO};
        if (vkBeginCommandBuffer(vkCommandBuffer, &vkCommandBufferBegin) !=
            VK_SUCCESS) {
            OutputDebugString("Failed to begin command buffer.\n");
            goto exit;
        }

        VkRenderPassBeginInfo vkRenderPassBegin = {
            .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO,
            .renderPass = vkRenderPass,
            .framebuffer = vkFrameBuffers[image],
            .renderArea = {.extent = vkCapabilites.currentExtent,
                           .offset = {0, 0}},
            .clearValueCount = 1,
            .pClearValues = &clearColor};
        vkCmdBeginRenderPass(vkCommandBuffer, &vkRenderPassBegin,
                             VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(vkCommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,
                          vkGfxPipeline);
        vkCmdSetViewport(vkCommandBuffer, 0, 1, &vkViewport);
        vkCmdSetScissor(vkCommandBuffer, 0, 1, &vkScissor);
        vkCmdDraw(vkCommandBuffer, 3, 1, 0, 0);
        vkCmdEndRenderPass(vkCommandBuffer);

        if (vkEndCommandBuffer(vkCommandBuffer) != VK_SUCCESS) {
            OutputDebugString("Failed to end command buffer.\n");
            goto exit;
        }

        VkSemaphore waitSemaphores[] = {vkImageAvailable};
        VkSemaphore signalSemaphores[] = {vkRenderFinished};
        VkPipelineStageFlags waitStages[] = {
            VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
        VkSubmitInfo submitInfo = {.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
                                   .waitSemaphoreCount = 1,
                                   .pWaitSemaphores = waitSemaphores,
                                   .pWaitDstStageMask = waitStages,
                                   .commandBufferCount = 1,
                                   .pCommandBuffers = &vkCommandBuffer,
                                   .signalSemaphoreCount = 1,
                                   .pSignalSemaphores = signalSemaphores};
        if (vkQueueSubmit(vkGfxQueue, 1, &submitInfo, vkInFlightFence) !=
            VK_SUCCESS) {
            OutputDebugString("Queue submit failed\n");
            goto exit;
        }

        VkSwapchainKHR swapChains[] = {vkSwapChain};

        VkPresentInfoKHR presentInfo = {.sType =
                                            VK_STRUCTURE_TYPE_PRESENT_INFO_KHR,
                                        .waitSemaphoreCount = 1,
                                        .pWaitSemaphores = signalSemaphores,
                                        .swapchainCount = 1,
                                        .pSwapchains = swapChains,
                                        .pImageIndices = &image};

        vkQueuePresentKHR(vkGfxQueue, &presentInfo);
    }

    vkDeviceWaitIdle(vkDevice);

exit:
    vkDestroySemaphore(vkDevice, vkImageAvailable, 0);
    vkDestroySemaphore(vkDevice, vkRenderFinished, 0);
    vkDestroyFence(vkDevice, vkInFlightFence, 0);
    vkDestroyCommandPool(vkDevice, vkCommandPool, 0);
    for (int i = 0; i < vkImageCount; i++) {
        vkDestroyFramebuffer(vkDevice, vkFrameBuffers[i], 0);
    }
    if (vkFrameBuffers) {
        VirtualFree(vkFrameBuffers, 0, MEM_RELEASE);
    }
    vkDestroyPipeline(vkDevice, vkGfxPipeline, 0);
    vkDestroyRenderPass(vkDevice, vkRenderPass, 0);
    vkDestroyPipelineLayout(vkDevice, vkPipelineLayout, 0);
    vkDestroyShaderModule(vkDevice, vkVertShader, 0);
    vkDestroyShaderModule(vkDevice, vkFragShader, 0);
    for (int i = 0; i < vkImageCount; i++) {
        vkDestroyImageView(vkDevice, vkImageViews[i], 0);
    }
    vkDestroySwapchainKHR(vkDevice, vkSwapChain, 0);
    vkDestroySurfaceKHR(vkInstance, vkSurface, 0);
    vkDestroyDevice(vkDevice, 0);
    if (vkDevices) {
        VirtualFree(vkImageViews, 0, MEM_RELEASE);
    }
    if (vkDevices) {
        VirtualFree(vkImages, 0, MEM_RELEASE);
    }
    if (vkQueueFamilies) {
        VirtualFree(vkQueueFamilies, 0, MEM_RELEASE);
    }
    if (vkDevices) {
        VirtualFree(vkDevices, 0, MEM_RELEASE);
    }
    vkDestroyInstance(vkInstance, 0);

    return 0;
}
