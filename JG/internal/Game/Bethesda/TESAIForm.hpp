#pragma once

#include "TESForm.hpp"
#include "PackageList.hpp"
#include "ActorValue.hpp"

class TESPackage;
class TESObject;

class TESAIForm : public BaseFormComponent {
public:
	TESAIForm();
	~TESAIForm();

	virtual uint32_t	GetSaveSizeTES(uint32_t auiChangeFlags);
	virtual void		SaveGameTES(uint32_t auiChangeFlags);
	virtual void		LoadGameTES(uint32_t auiChangeFlags);

	struct Data {
		uint8_t					ucAgression;
		uint8_t					ucConfidence;
		uint8_t					ucEnergy;
		uint8_t					ucResponsibility;
		uint8_t					ucMood;
		Bitfield<_ServiceFlags>	uiServiceFlags;
		uint8_t					ucTrainingSkill;
		uint8_t					ucTrainingLevel;
		uint8_t					ucAssistance;
		bool					bAggroRadius;
		uint32_t				uiAggroRadius;
	};

	Data		kData;
	PackageList	kPackages;

	uint8_t GetAggression() const;
	void SetAggression(uint8_t aucVal, bool abAddChange);

	uint8_t GetConfidence() const;
	void SetConfidence(uint8_t aucVal, bool abAddChange);
	float GetConfidenceLevel() const;
	static float GetConfidenceLevel(uint8_t aucConfidence);

	uint8_t GetEnergy() const;
	void SetEnergy(uint8_t aucVal, bool abAddChange);

	uint8_t GetResponsibility() const;
	void SetResponsibility(uint8_t aucVal, bool abAddChange);

	uint8_t GetMood() const;
	void SetMood(uint8_t aucVal, bool abAddChange);

	uint32_t GetServiceFlags() const;
	bool GetOffersService(uint32_t auiServiceFlag) const;
	void SetServiceFlags(uint32_t auiFlags, bool abAddChange);

	ActorValue::Index GetTrainingSkill() const;
	void SetTrainingSkill(ActorValue::Index aeSkill);

	uint8_t GetTrainingSkillLevel() const;
	void SetTrainingSkillLevel(uint8_t aucLevel);

	uint8_t GetAssistance() const;
	void SetAssistance(uint8_t aucVal);

	bool GetHasAggroRadius() const;
	void SetHasAggroRadius(bool abVal);

	uint32_t GetAggroRadius() const;
	void SetAggroRadius(uint32_t auiRadius);

	const PackageList* GetPackageList() const;
	PackageList* GetPackageList();
	uint32_t GetPackageCount() const;

	void CopyAIPackageList(const TESAIForm* apSource);

#ifdef GAME
	void AddFormChange(uint32_t auiChangeFlags);

	bool SellBuysItem(const TESObject* apObject) const;

	static TESPackage* GetCurrentPackage(Actor* apActor);

	static void GetMissedPackages(Actor* apActor, BSSimpleList<TESPackage*>& arOut, float afStartDate, float afHour);
#endif
};

ASSERT_SIZE(TESAIForm, 0x20);