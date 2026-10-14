#pragma once

// GAME - 0x869840
template<class T_Data>
inline SPEC_RESTRICT T_Data* NiTNewInterface<T_Data>::Allocate(uint32_t auiNumElements) {
    return new T_Data[auiNumElements];
}

// GAME - 0x8696C0
template<class T_Data>
inline void NiTNewInterface<T_Data>::Deallocate(T_Data* apData) {
    delete[] apData;
};