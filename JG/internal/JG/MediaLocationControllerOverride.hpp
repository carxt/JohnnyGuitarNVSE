#pragma once

class MediaLocationController;

namespace MediaLocationControllerOverride {

	void Install();

	void Reset();

	void Set(MediaLocationController* apController);

}