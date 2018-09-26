#pragma once
#include <vector>
#include <SDL.h>

#define PI 3.14159265
#define ORANGE_TILE_PATH "Assets/orange.png"
#define YELLOW_TILE_PATH "Assets/yellow.png"
#define TILE_FILE_PATH "Assets/tiles.txt"
#define MENU_FILE_PATH "Assets/menu.png"
#define BALL_FILE_PATH "Assets/ball2.png" 
#define PADDLE_FILE_PATH "Assets/paddle2.png"
#define FONT_FILE_PATH "Assets/bgothm.ttf"
#define BALLS_TEXT "Balls: "
#define SCORE_TEXT "Score: "

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
	static const int PADDLE_HEIGHT = 10;
	static const int BOTTOM_DISTANCE = 35;
	static const int SPACE_TOP = 75;
	static const int MAX_COLUMNS = 8;
	static const int MAX_ROWS = 6;
	static const int BALL_SIZE = 25;
	static const int MAX_BOUNCE_ANGLE_DEGREES = 30;
	static const int MAX_BALLS = 3;
	static const int BOTTOMTEXT_FONT_SIZE = 18;
	
	

};