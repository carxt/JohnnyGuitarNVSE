#pragma once

#include "NiProperty.hpp"
#include "Bethesda/BSMemObject.hpp"

class NiAlphaProperty;
class NiCullingProperty;
class NiMaterialProperty;
class NiShadeProperty;
class NiStencilProperty;
class NiTexturingProperty;

class NiPropertyState {
public:
	NiPropertyState();
	NiPropertyState(const NiPropertyState& arSource);
	~NiPropertyState();

	union {
		struct {
			NiPointer<NiAlphaProperty>		m_spAlphaProperty;
			NiPointer<NiCullingProperty>	m_spCullingProperty;
			NiPointer<NiMaterialProperty>	m_spMaterialProperty;
			NiPointer<NiShadeProperty>		m_spShadeProperty;
			NiPointer<NiStencilProperty>	m_spStencilProperty;
			NiPointer<NiTexturingProperty>	m_spTextureProperty;
			NiPointer<NiProperty>			m_spWireframeProperty;
		};
		NiPointer<NiProperty>				m_aspProps[NiProperty::MAX_TYPES];
	};

	void Reset();

	void SetProperty(NiProperty* apProperty);

	NiPointer<NiProperty>& operator[] (uint32_t auiIndex) { return m_aspProps[auiIndex]; }

	NiAlphaProperty* GetAlphaProperty() const { return m_spAlphaProperty.m_pObject; };

	NiCullingProperty* GetCullingProperty() const { return m_spCullingProperty.m_pObject; };

	NiMaterialProperty* GetMaterialProperty() const { return m_spMaterialProperty.m_pObject; };

	template <class T> 
	T* GetShadeProperty() const { return static_cast<T*>(m_spShadeProperty.m_pObject); };

	NiStencilProperty* GetStencilProperty() const { return m_spStencilProperty.m_pObject; };

	NiTexturingProperty* GetTexturingProperty() const { return m_spTextureProperty.m_pObject; };
};

ASSERT_SIZE(NiPropertyState, 0x1C);