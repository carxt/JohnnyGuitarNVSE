#pragma once

#include <string>

namespace oldstd {

	template <typename T>
	struct vector {
		uint32_t	unk00 = 0;
		void*		unk04 = 0;
		uint32_t	unk08 = 0;
		T*			_Myfirst;
		T*			_Mylast;
		T*			_Myend;
	};
	ASSERT_SIZE(oldstd::vector<float>, 0x18);

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