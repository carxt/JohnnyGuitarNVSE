#pragma once

#include "NiAVObject.hpp"
#include "NiGeometryData.hpp"
#include "NiSkinInstance.hpp"
#include "NiPropertyState.hpp"

class NiRenderer;
class NiShader;

NiSmartPointer(NiGeometry);

class NiGeometry : public NiAVObject {
public:
	NiGeometry();
	virtual ~NiGeometry();

	virtual void	RenderImmediate(NiRenderer* apRenderer);
	virtual void	OnlyRenderImmediate(NiRenderer* apRenderer);
	virtual void	SetModelData(NiGeometryData* apModelData);
	virtual void	CalculateNormals();
	virtual void	CalculateConsistency(bool abTool);

	struct RendererData {};

	NiPropertyState		m_kProperties;
	NiGeometryDataPtr	m_spModelData;
	NiSkinInstancePtr	m_spSkinInstance;
	NiShader*			m_pShader;

	NIRTTI_ADDRESS(0x11F4ACC);

	NiAlphaProperty* GetAlphaProperty() const { return m_kProperties.GetAlphaProperty(); };

	NiCullingProperty* GetCullingProperty() const { return m_kProperties.GetCullingProperty(); };

	NiMaterialProperty* GetMaterialProperty() const { return m_kProperties.GetMaterialProperty(); };

	template <class T = NiShadeProperty>
	T* GetShadeProperty() const { return m_kProperties.GetShadeProperty<T>(); };

	NiStencilProperty* GetStencilProperty() const { return m_kProperties.GetStencilProperty(); };

	NiTexturingProperty* GetTexturingProperty() const { return m_kProperties.GetTexturingProperty(); };

	NiGeometryData* GetModelData() const;

	NiSkinInstance* GetSkinInstance() const;
	void SetSkinInstance(NiSkinInstance* apSkinInstance);

	NiShader* GetShader() const;
	void SetShader(NiShader* apShader);
	
	NiPoint3* GetVertices() const;

	NiPoint3* GetNormals() const;

	NiColorA* GetColors() const;

	NiPoint2* GetTextures() const;

	uint16_t GetVertexCount() const;

	uint16_t GetTextureSets() const;
	NiPoint2* GetTextureSet(uint16_t ausSet) const;

	const NiBound& GetModelBound() const;
};

ASSERT_SIZE(NiGeometry, 0xC4);