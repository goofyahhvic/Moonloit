#include "mlt_pch.hpp"
#include "mlt_init.hpp"

#ifndef MLT_DISTRIBUTION
#define __VLS_ENABLED 1
#else
#define __VLS_ENABLED 0
#endif

VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    }
}

class mlt::RenderAPI::Instance {
	friend class RenderAPI;
	static VkInstance instance;
	static VkDebugUtilsMessengerEXT debug_messenger;
	static VkPhysicalDevice physical_device;
    static std::vector<const char*> validation_layers;
    static mlt::InitInfo::Version api_version;

    static void PopulateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& info) {
        info = {};
        info.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        info.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
        info.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        info.pfnUserCallback = DebugCallback;
    }
    static bool CheckValidationLayerSupport() {
        uint32_t layer_count;
        vkEnumerateInstanceLayerProperties(&layer_count, nullptr);

        std::vector<VkLayerProperties> available_layers(layer_count);
        vkEnumerateInstanceLayerProperties(&layer_count, available_layers.data());

        for (const char* layer_name : validation_layers) {
            bool layer_found = false;

            for (const auto& layer_properties : available_layers) {
                if (strcmp(layer_name, layer_properties.layerName) == 0) {
                    layer_found = true;
                    break;
                }
            }

            if (!layer_found) {
                return false;
            }
        }

        return true;
    }

    static const char* to_string(VkDebugUtilsMessageTypeFlagsEXT type) {
        switch (type) {
            case VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT:
                return "General";
            case VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT:
                return "Validation";
            case VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT:
                return "Performance";
            default:
                return "Unknown";
        }
    }
    static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
        if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            throw VulkanError(pCallbackData->pMessage, to_string(messageType));
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            MOONLOIT_RENDERER_WARN("Vulkan Validation Layer [{0}]: {1}", to_string(messageType), pCallbackData->pMessage);
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
            MOONLOIT_RENDERER_INFO("Vulkan Validation Layer [{0}]: {1}", to_string(messageType), pCallbackData->pMessage);
        }
        else if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
            MOONLOIT_RENDERER_TRACE("Vulkan Validation Layer [{0}]: {1}", to_string(messageType), pCallbackData->pMessage);
        }

        return VK_FALSE;
    }
};

VkInstance               mlt::RenderAPI::Instance::instance;
VkDebugUtilsMessengerEXT mlt::RenderAPI::Instance::debug_messenger;
VkPhysicalDevice         mlt::RenderAPI::Instance::physical_device;
std::vector<const char*> mlt::RenderAPI::Instance::validation_layers;
mlt::InitInfo::Version   mlt::RenderAPI::Instance::api_version;

namespace mlt {
	void RenderAPI::Init_VulkanImpl(InitInfo& init) {
        try {
            Instance::physical_device = VK_NULL_HANDLE;
            Instance::validation_layers.empty();
            Instance::validation_layers.push_back("VK_LAYER_KHRONOS_validation");

            // Creating instance
            {
                if (__VLS_ENABLED && !Instance::CheckValidationLayerSupport()) {
                    throw std::runtime_error("Validation Layers requested, but not available!");
                }

                VkApplicationInfo app_info {};
                app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
                app_info.pApplicationName = init.app_name;
                app_info.engineVersion = VK_MAKE_API_VERSION(
                    init.app_version->variant,
                    init.app_version->major,
                    init.app_version->minor,
                    init.app_version->patch
                );
                app_info.pEngineName = init.engine_name;
                app_info.engineVersion = VK_MAKE_API_VERSION(
                    init.engine_version->variant,
                    init.engine_version->major,
                    init.engine_version->minor,
                    init.engine_version->patch
                );
                app_info.apiVersion = VK_MAKE_API_VERSION(
                    Instance::api_version.variant,
                    Instance::api_version.major,
                    Instance::api_version.minor,
                    0
                );;

                VkInstanceCreateInfo create_info {};
                create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
                create_info.pApplicationInfo = &app_info;

                auto extensions = init.VULKAN_get_extensions(__VLS_ENABLED);
                create_info.enabledExtensionCount = (uint32_t)(extensions.size());
                create_info.ppEnabledExtensionNames = extensions.data();

                VkDebugUtilsMessengerCreateInfoEXT debug_create_info {};

#if __VLS_ENABLED 1
                create_info.enabledLayerCount = (uint32_t)(Instance::validation_layers.size());
                create_info.ppEnabledLayerNames = Instance::validation_layers.data();

                Instance::PopulateDebugMessengerCreateInfo(debug_create_info);
                create_info.pNext = (VkDebugUtilsMessengerCreateInfoEXT*)&debug_create_info;
#else
                create_info.enabledLayerCount = 0;
                create_info.pNext = nullptr;
#endif

                if (vkCreateInstance(&create_info, nullptr, &Instance::instance) != VK_SUCCESS) {
                    throw std::runtime_error("failed to create instance!");
                }

            }
        } catch (VulkanError& e) {
            if (e.what(true).find("EOSOverlayVkLayer-Win64.json") != std::string::npos) {
                MOONLOIT_RENDERER_ERROR(e.what());
                return;
            }
            MOONLOIT_RENDERER_CRITICAL(e.what());
            throw std::runtime_error(e.what());
        }
	}
	void RenderAPI::CleanUp_VulkanImpl() {
        vkDestroyInstance(Instance::instance, nullptr);
	}
}