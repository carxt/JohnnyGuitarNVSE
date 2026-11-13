#pragma once

#include "Gamebryo/NiObject.hpp"

class BGSSaveGameBuffer;
class BGSLoadGameBuffer;
class BGSLoadFormBuffer;
class TESObjectCELL;
class NiNode;
class TESForm;

NiSmartPointer(BSTempEffect);

class BSTempEffect : public NiObject {
public:
	struct _Type {
		enum Type : uint32_t {
			GEO_DECAL			= 1,
			PARTICLE			= 2,
			SIMPLE_DECAL		= 3,
			MAGIC_HIT			= 4,
			MAGIC_MODEL_HIT		= 5,
			MAGIC_SHADER_HIT	= 6,
		};
	};
	using Type = _Type::Type;

	BSTempEffect();
	virtual ~BSTempEffect();

	virtual void			Initialize();									// 35
	virtual void			Detach();										// 36
	virtual bool			Update(float afTime);							// 37 | Returns true if effect is finished
	virtual NiNode*			Get3D() const;									// 38
	virtual Type			GetType() const;								// 39
	virtual bool			CheckShouldSave() const;						// 40
	virtual uint32_t		GetSaveSize();									// 41
	virtual void			SaveGameBGS(BGSSaveGameBuffer* apBuffer);		// 42
	virtual void			SaveGameTES();									// 43
	virtual void 			LoadGameBGS(BGSLoadGameBuffer* apBuffer);		// 44
	virtual bool			LoadGameTES();									// 45
	virtual void			SetTarget(TESForm* apTarget);					// 46 | Used by MagicHitEffect
	virtual void			FinishLoadGame(BGSLoadGameBuffer* apBuffer);	// 47
	virtual bool			IsFirstPerson() const;							// 48 | Used by shell casings

	float			fLifetime;
	TESObjectCELL*	pCell;
	float			fAge;
	bool			bInitialized;

	NIRTTI_ADDRESS(0x11D6A44);
};

ASSERT_SIZE(BSTempEffect, 0x18);