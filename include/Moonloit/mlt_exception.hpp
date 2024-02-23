#pragma once
#include "mlt_core.h"

#include <spdlog/fmt/fmt.h>

namespace mlt {
	class MOONLOIT_API Exception {
	public:
		Exception(const std::string& msg) : msg(msg) {}
		virtual ~Exception() {}
	public:
		virtual std::string ToString() const {	return fmt::format("{0} thrown: {1}", get_type(), this->msg); }
		virtual inline const char* get_type() const { return "Exception"; }
	protected:
		std::string msg;
	};

	inline std::ostream& operator << (std::ostream& os, const Exception& e) { return os << e.ToString(); }
}