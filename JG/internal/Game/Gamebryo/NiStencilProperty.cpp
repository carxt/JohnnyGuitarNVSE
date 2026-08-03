#include "NiStencilProperty.hpp"

bool NiStencilProperty::GetStencilOn() const {
	return m_usFlags.bEnabled;
}

void NiStencilProperty::SetStencilOn(bool abEnabled) {
	m_usFlags.bEnabled = abEnabled;
}

uint32_t NiStencilProperty::GetStencilReference() const {
	return m_uiRef;
}

void NiStencilProperty::SetStencilReference(uint32_t auiRef) {
	m_uiRef = auiRef;
}

uint32_t NiStencilProperty::GetStencilMask() const {
	return m_uiMask;
}

void NiStencilProperty::SetStencilMask(uint32_t auiMask) {
	m_uiMask = auiMask;
}

NiStencilProperty::Action NiStencilProperty::GetStencilFailAction() const {
	return static_cast<Action>(m_usFlags.ucFailAction);
}

// GAME - 0x533FB0
void NiStencilProperty::SetStencilFailAction(Action aeAction) {
	m_usFlags.ucFailAction = aeAction;
}

NiStencilProperty::Action NiStencilProperty::GetStencilZFailAction() const {
	return static_cast<Action>(m_usFlags.ucZFailAction);
}

// GAME - 0x49EE10
void NiStencilProperty::SetStencilZFailAction(Action aeAction) {
	m_usFlags.ucZFailAction = aeAction;
}

NiStencilProperty::Action NiStencilProperty::GetStencilPassAction() const {
	return static_cast<Action>((m_usFlags.Get(Flags::PASS_ACTION, Flags::PASS_ACTION_POS)));
}

// GAME - 0x49EDE0
void NiStencilProperty::SetStencilPassAction(Action aeAction) {
	m_usFlags.Set(aeAction, Flags::PASS_ACTION, Flags::PASS_ACTION_POS);
}

NiStencilProperty::DrawMode NiStencilProperty::GetDrawMode() const {
	return static_cast<NiStencilProperty::DrawMode>(m_usFlags.ucDrawMode);
}

// GAME - 0x49EE30
void NiStencilProperty::SetDrawMode(NiStencilProperty::DrawMode aeDraw) {
	m_usFlags.ucDrawMode = aeDraw;
}

NiStencilProperty::TestFunc NiStencilProperty::GetStencilFunction() const {
	return static_cast<NiStencilProperty::TestFunc>(m_usFlags.ucTestFunc);
}

// GAME - 0x49EDB0
void NiStencilProperty::SetStencilFunction(NiStencilProperty::TestFunc aeFunc) {
	m_usFlags.ucTestFunc = aeFunc;
}