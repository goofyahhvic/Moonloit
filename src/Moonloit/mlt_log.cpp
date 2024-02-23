#include "mlt_pch.hpp"
#include "mlt_log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>

namespace mlt {
	Logger Log::sm_RendererLogger;
	Logger Log::sm_VxlLogger;
	Logger Log::sm_AppLogger;

	void Log::Init() {
		sm_RendererLogger = spdlog::stdout_color_mt("MOONLOIT_RENDERER");
		sm_VxlLogger = spdlog::stdout_color_mt("MOONLIGHT_VXL");
		sm_AppLogger = spdlog::stdout_color_mt("CLIENT");

		sm_RendererLogger->set_level(spdlog::level::trace);
		sm_VxlLogger->set_level(spdlog::level::trace);
		sm_AppLogger->set_level(spdlog::level::trace);

		spdlog::set_pattern("%^[%T] [%n]%$: %v");
	}
}