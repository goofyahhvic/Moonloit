#pragma once
#include "mlt_core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace moonloit {
	using Logger = std::shared_ptr<spdlog::logger>;

	class MOONLOIT_API Log {
	public:
		static void init();

		static inline Logger get_renderer_logger() { return renderer_logger; }
		static inline Logger get_vxl_logger() { return vxl_logger; }
		static inline Logger get_app_logger() { return app_logger; }
	private:
		Log();
	private:
		static Logger renderer_logger;
		static Logger vxl_logger;
		static Logger app_logger;
	};
}

#ifndef MLT_DISTRIBUTION
	#define MOONLOIT_RENDERER_TRACE(...)    ::moonloit::Log::get_renderer_logger()->trace(__VA_ARGS__)
	#define MOONLOIT_RENDERER_INFO(...)     ::moonloit::Log::get_renderer_logger()->info(__VA_ARGS__)
	#define MOONLOIT_RENDERER_WARN(...)     ::moonloit::Log::get_renderer_logger()->warn(__VA_ARGS__)
	#define MOONLOIT_RENDERER_ERROR(...)    ::moonloit::Log::get_renderer_logger()->error(__VA_ARGS__)
	#define MOONLOIT_RENDERER_CRITICAL(...) ::moonloit::Log::get_renderer_logger()->critical(__VA_ARGS__)

	#define MOONLOIT_VXL_TRACE(...)         ::moonloit::Log::get_vxl_logger()->trace(__VA_ARGS__)
	#define MOONLOIT_VXL_INFO(...)          ::moonloit::Log::get_vxl_logger()->info(__VA_ARGS__)
	#define MOONLOIT_VXL_WARN(...)          ::moonloit::Log::get_vxl_logger()->warn(__VA_ARGS__)
	#define MOONLOIT_VXL_ERROR(...)         ::moonloit::Log::get_vxl_logger()->error(__VA_ARGS__)
	#define MOONLOIT_VXL_CRITICAL(...)      ::moonloit::Log::get_vxl_logger()->critical(__VA_ARGS__)
  
	#define MOONLOIT_APP_TRACE(...)         ::moonloit::Log::get_app_logger()->trace(__VA_ARGS__)
	#define MOONLOIT_APP_INFO(...)          ::moonloit::Log::get_app_logger()->info(__VA_ARGS__)
	#define MOONLOIT_APP_WARN(...)          ::moonloit::Log::get_app_logger()->warn(__VA_ARGS__)
	#define MOONLOIT_APP_ERROR(...)         ::moonloit::Log::get_app_logger()->error(__VA_ARGS__)
	#define MOONLOIT_APP_CRITICAL(...)      ::moonloit::Log::get_app_logger()->critical(__VA_ARGS__)
#else 
	#define MOONLOIT_RENDERER_TRACE(...)    
	#define MOONLOIT_RENDERER_INFO(...)     
	#define MOONLOIT_RENDERER_WARN(...)     
	#define MOONLOIT_RENDERER_ERROR(...)    
	#define MOONLOIT_RENDERER_CRITICAL(...) 

	#define MOONLOIT_VXL_TRACE(...)         
	#define MOONLOIT_VXL_INFO(...)          
	#define MOONLOIT_VXL_WARN(...)          
	#define MOONLOIT_VXL_ERROR(...)         
	#define MOONLOIT_VXL_CRITICAL(...)      
  
	#define MOONLOIT_APP_TRACE(...)         
	#define MOONLOIT_APP_INFO(...)          
	#define MOONLOIT_APP_WARN(...)          
	#define MOONLOIT_APP_ERROR(...)         
	#define MOONLOIT_APP_CRITICAL(...)      
#endif