#pragma once
#include <vector>
#include <SDL.h>
class Globals {
public:
	// A way of globally storing all input events
	// This is needed so that I can split up input events to different game objects
	static std::vector<SDL_Event>& GetFrameEvents() {
		static std::vector<SDL_Event> frame_events;
		return frame_events;
	}
};