#pragma once

#include <netimmerse.h>
#include <shared/Utils/CustomClass.hpp>

namespace NewNiObjects {

	class NiLightRadiusController : public CustomClass<NiFloatInterpController> {
	public:
		NiNewRTTI(NiLightRadiusController, NiFloatInterpController);

		static NiLightRadiusController* CreateObject();
		NiLightRadiusController*		_CreateClone(NiCloningProcess& arCloneProc);
		void							_Update(NiUpdateData& arUpdateData);
	};

	void Install();

}