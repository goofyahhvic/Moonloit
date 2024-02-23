#include "mlt_pch.hpp"
#include "mlt_init.hpp"

#define _INFO (*((Info*)info))
#define _INFOPTR ((Info*)info)

struct mlt::RenderAPI::Info {
	const char* title;
};

namespace mlt {
	void* RenderAPI::info;

	void RenderAPI::Init_VulkanImpl(InitInfo& init) {
		info = malloc(sizeof(Info));
		
	}
	void RenderAPI::CleanUp_VulkanImpl() {
		free(info);
	}
}