#pragma once

class NiUpdateData {
public:
	explicit NiUpdateData(float afTime = 0.f, bool abUpdateControllers = false, bool abParallelUpdate = false)
		: fTime(afTime), bUpdateControllers(abUpdateControllers), bParallelUpdate(abParallelUpdate), bFoundParticles(false), bFoundMorphController(false), bSceneGraphChange(false)
	{}
	~NiUpdateData() {};

	float	fTime;
	bool	bUpdateControllers;
	bool	bParallelUpdate;
	bool	bFoundParticles;
	bool	bFoundMorphController;
	bool	bSceneGraphChange;
};

ASSERT_SIZE(NiUpdateData, 0xC);