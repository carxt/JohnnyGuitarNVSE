#include "NiInterpController.hpp"

void NiInterpController::SetManagerControlled(bool abManagerControlled) {
    SetManagerControlledBit(abManagerControlled);
}

bool NiInterpController::GetManagerControlled() const {
    return GetManagerControlledBit();
}