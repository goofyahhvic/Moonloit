#include "mlt_pch.hpp"
#include "mlt_log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ansicolor_sink.h>

namespace moonloit {
	Logger Log::renderer_logger;
	Logger Log::vxl_logger;
	Logger Log::app_logger;

	void Log::init() {
		renderer_logger = spdlog::stdout_color_mt("MOONLOIT_RENDERER");
		vxl_logger = spdlog::stdout_color_mt("MOONLIGHT_VXL");
		app_logger = spdlog::stdout_color_mt("CLIENT");

		renderer_logger->set_level(spdlog::level::trace);
		vxl_logger->set_level(spdlog::level::trace);
		app_logger->set_level(spdlog::level::trace);

		spdlog::set_pattern("%^[%T] [%n]%$: %v");
	}
}