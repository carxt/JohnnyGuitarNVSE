#pragma once

class MediaLocationController;

namespace MediaLocationControllerTweaks {

	void Install();

	void ResetOverride();

	void SetOverride(MediaLocationController* apController);

}