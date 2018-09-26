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
	static const int SCREEN_WIDTH = 800;
	static const int SCREEN_HEIGHT = 600;
	static const int TILE_WIDTH = 100;
	static const int TILE_HEIGHT = 25;
	static const int PADDLE_WIDTH = 150;
	static const int PADDLE_HEIGHT = 25;
	static const int SPACE_TOP = 75;
	static const int MAX_COLUMNS = 8;
	static const int MAX_ROWS = 6;
	static const int BALL_SIZE = 25;
};