#include "FurnitureMark.hpp"

// GAME - 0x509890
FurnitureMark::FurnitureMark(uint32_t auiNumber) : usHeading(0), ucNumber(auiNumber) {
}

// GAME - 0xC54CC0
bool FurnitureMark::operator==(const FurnitureMark& arOther) const {
    return kPos == arOther.kPos && ucNumber == arOther.ucNumber && usHeading == arOther.usHeading;
}

bool FurnitureMark::operator<(const FurnitureMark& arOther) const {
    return ucNumber < arOther.ucNumber;
}
