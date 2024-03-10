#pragma once
#include "mlt_core.h"

#define MOONLOIT_SET_VERSION(x, _variant, _major, _minor, _patch) (x).variant = _variant; (x).major = _major; (x).minor = _minor; (x).patch = _patch; 

namespace mlt {
	struct MOONLOIT_API InitInfo {
		struct Version {
			uint32_t variant = 0, major = 1, minor = 0, patch = 0;
		};

		uint32_t width, height;
		const char *app_name, *engine_name;
		const Version *app_version, *engine_version;
		std::function<std::vector<const char*>(const bool)> VULKAN_get_extensions;
	};

	// thrown at vulkan validation layer debug callback when severity is error
	class VulkanError : public std::exception {
	public:
		VulkanError(const char* msg, const char* msg_type)
			: m_Msg(msg), m_MsgType(msg_type),
			m_What(fmt::format("Vulkan Error [{0}]: {1}", m_MsgType, m_Msg)) {

		}
		char* what() {
			return m_What.data();
		}
		const std::string& what(bool string) {
			return m_What;
		}
		const char* type() {
			return m_MsgType;
		}
		const char* msg() {
			return m_Msg;
		}
	private:
		const char *m_Msg, *m_MsgType;
		std::string m_What;
	};

	class MOONLOIT_API RenderAPI {
		class Instance;
		friend class Instance;
	public:
		inline static void Init(InitInfo& init) { Init_VulkanImpl(init); }
		inline static void CleanUp() { CleanUp_VulkanImpl(); }
	private:
		static void Init_VulkanImpl(InitInfo& init);
		static void CleanUp_VulkanImpl();
	};
}