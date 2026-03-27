#pragma once

#include "TESForm.hpp"
#include "PackageList.hpp"

class TESPackage;

class TESAIForm : public BaseFormComponent {
public:
	TESAIForm();
	~TESAIForm();

	virtual uint32_t	GetSaveSize(uint32_t auiChangeFlags);
	virtual void		SaveGameTES(uint32_t auiChangeFlags);
	virtual void		LoadGameTES(uint32_t auiChangeFlags);

	struct Data {
		uint8_t		ucAgression;
		uint8_t		ucConfidence;
		uint8_t		ucEnergyLevel;
		uint8_t		ucResponsibility;
		uint8_t		ucMood;
		uint32_t	uiBuySellsAndServices;
		bool		bTeaches;
		uint8_t		ucMaximumTrainingLevel;
		uint8_t		ucAssistance;
		bool		bAggroRadiusBehavior;
		int32_t		iAggroRadius;
	};

	Data		kData;
	PackageList	kPackages;

	uint32_t GetPackageCount() const;
};

ASSERT_SIZE(TESAIForm, 0x20);