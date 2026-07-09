#pragma once

#include "BSSimpleArrayRefCounted.hpp"
#include "PathingAvoidNode.hpp"

NiSmartPointer(PathingAvoidNodeArray);

class PathingAvoidNodeArray : public BSSimpleArrayRefCounted<PathingAvoidNode> {
public:
};