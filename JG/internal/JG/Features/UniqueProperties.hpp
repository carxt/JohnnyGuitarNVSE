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

	void Install();
}