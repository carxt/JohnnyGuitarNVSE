#pragma once

class NiAVObject;
class NiFixedString;

class BSUtilities {
public:
    static NiAVObject* GetObjectByName(const NiAVObject* apScene, const NiFixedString& arName);

    static NiAVObject* GetObjectByName(const NiAVObject* apScene, const NiFixedString& arName, bool abTestScenegraph);
};

