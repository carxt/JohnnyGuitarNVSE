#pragma once

#include <string>

namespace oldstd {

	template <typename T>
	struct vector {
		uint32_t	unk00 = 0;
		void*		unk04 = 0;
		uint32_t	unk08 = 0;
		T**			pfValues = 0;
		uint32_t	uiUseOffset = 0;
		uint32_t	uiMaxOffset = 0;
	};

#ifdef _DEBUG
	struct string : public std::string {
	};
#else
	class string {
	public:
		string() : str() {}
		string(const char* apStr) : str(apStr) {}

		void* fakeProxy = nullptr;
		std::string str;

		operator const std::string& () const {
			return str;
		}

		operator std::string& () {
			return str;
		}
	};
#endif
}