#pragma once
#include "mlt_core.h"

namespace mlt {
	struct MOONLOIT_API InitInfo {
		uint32_t width, height;
	};

	class MOONLOIT_API RenderAPI {
		struct Info;
	public:
		inline static void Init(InitInfo& init) { Init_VulkanImpl(init); }
		inline static void CleanUp() { CleanUp_VulkanImpl(); }
	private:
		static void Init_VulkanImpl(InitInfo& init);
		static void CleanUp_VulkanImpl();
	private:
		static void* info;
	};
}