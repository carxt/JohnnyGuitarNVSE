#pragma once

class NiAlphaProperty;
class NiStencilProperty;
class NiMaterialProperty;

namespace UniqueProperties {

	EXTERN_DLL_EXPORT bool __fastcall GetStencilPropertyUnique(const NiStencilProperty* apProperty);
	EXTERN_DLL_EXPORT void __fastcall SetStencilPropertyUnique(NiStencilProperty* apProperty, bool abUnique);

	EXTERN_DLL_EXPORT bool __fastcall GetAlphaPropertyUnique(const NiAlphaProperty* apProperty);
	EXTERN_DLL_EXPORT void __fastcall SetAlphaPropertyUnique(NiAlphaProperty* apProperty, bool abUnique);

	EXTERN_DLL_EXPORT bool __fastcall GetMaterialPropertyUnique(const NiMaterialProperty* apProperty);
	EXTERN_DLL_EXPORT void __fastcall SetMaterialPropertyUnique(NiMaterialProperty* apProperty, bool abUnique);

	inline bool __fastcall GetPropertyUnique(const NiStencilProperty* apProperty) { return GetStencilPropertyUnique(apProperty); }
	inline void __fastcall SetPropertyUnique(NiStencilProperty* apProperty, bool abUnique) { SetStencilPropertyUnique(apProperty, abUnique); }

	inline bool __fastcall GetPropertyUnique(const NiAlphaProperty* apProperty) { return GetAlphaPropertyUnique(apProperty); }
	inline void __fastcall SetPropertyUnique(NiAlphaProperty* apProperty, bool abUnique) { SetAlphaPropertyUnique(apProperty, abUnique); }

	inline bool __fastcall GetPropertyUnique(const NiMaterialProperty* apProperty) { return GetMaterialPropertyUnique(apProperty); }
	inline void __fastcall SetPropertyUnique(NiMaterialProperty* apProperty, bool abUnique) { SetMaterialPropertyUnique(apProperty, abUnique); }

	void Install();
}