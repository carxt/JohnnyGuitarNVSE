#pragma once

namespace JIPFixes {
	void InitData();
	void InitEarlyHooks(bool abGECK);
	void InitHooks(bool abGECK);
	void InitCommandHooks(bool abGECK);
	void InitDeferredHooks(bool abGECK);
}