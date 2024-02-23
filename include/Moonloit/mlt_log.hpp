#pragma once
#include "mlt_core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace mlt {
	using Logger = std::shared_ptr<spdlog::logger>;

	class MOONLOIT_API Log {
		Log();
	public:
		static void Init();

		static inline Logger GetRendererLogger() { return sm_RendererLogger; }
		static inline Logger GetVxlLogger() { return sm_VxlLogger; }
		static inline Logger GetAppLogger() { return sm_AppLogger; }
	private:
		static Logger sm_RendererLogger;
		static Logger sm_VxlLogger;
		static Logger sm_AppLogger;
	};
}

#ifndef MLT_DISTRIBUTION
	#define MOONLOIT_RENDERER_TRACE(...)    ::mlt::Log::GetRendererLogger()->trace(__VA_ARGS__)
	#define MOONLOIT_RENDERER_INFO(...)     ::mlt::Log::GetRendererLogger()->info(__VA_ARGS__)
	#define MOONLOIT_RENDERER_WARN(...)     ::mlt::Log::GetRendererLogger()->warn(__VA_ARGS__)
	#define MOONLOIT_RENDERER_ERROR(...)    ::mlt::Log::GetRendererLogger()->error(__VA_ARGS__)
	#define MOONLOIT_RENDERER_CRITICAL(...) ::mlt::Log::GetRendererLogger()->critical(__VA_ARGS__)

	#define MOONLOIT_VXL_TRACE(...)         ::mlt::Log::GetVxlLogger()->trace(__VA_ARGS__)
	#define MOONLOIT_VXL_INFO(...)          ::mlt::Log::GetVxlLogger()->info(__VA_ARGS__)
	#define MOONLOIT_VXL_WARN(...)          ::mlt::Log::GetVxlLogger()->warn(__VA_ARGS__)
	#define MOONLOIT_VXL_ERROR(...)         ::mlt::Log::GetVxlLogger()->error(__VA_ARGS__)
	#define MOONLOIT_VXL_CRITICAL(...)      ::mlt::Log::GetVxlLogger()->critical(__VA_ARGS__)
  
	#define MOONLOIT_APP_TRACE(...)         ::mlt::Log::GetAppLogger()->trace(__VA_ARGS__)
	#define MOONLOIT_APP_INFO(...)          ::mlt::Log::GetAppLogger()->info(__VA_ARGS__)
	#define MOONLOIT_APP_WARN(...)          ::mlt::Log::GetAppLogger()->warn(__VA_ARGS__)
	#define MOONLOIT_APP_ERROR(...)         ::mlt::Log::GetAppLogger()->error(__VA_ARGS__)
	#define MOONLOIT_APP_CRITICAL(...)      ::mlt::Log::GetAppLogger()->critical(__VA_ARGS__)
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