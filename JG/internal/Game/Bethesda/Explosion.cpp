#include "Explosion.hpp"
#include "BGSExplosion.hpp"

BGSExplosion* Explosion::GetExplosionBase() const {
    return static_cast<BGSExplosion*>(GetObjectReference());
}
