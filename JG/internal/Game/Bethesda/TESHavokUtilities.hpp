#pragma once

class NiAVObject;
class NiPoint3;

class TESHavokUtilities {
public:

	static void RemoveHavokFromSceneGraph(NiAVObject* apObject);

	static void AddVelocity(NiAVObject* apObject, const NiPoint3& arVector, bool abReset);

};