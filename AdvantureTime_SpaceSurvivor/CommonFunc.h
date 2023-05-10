#ifndef COMMON_FUNC_H_
#define COMMON_FUNC_H_

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <math.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

using namespace std;


// file link 
static char gGameStat[]						= "asset/img/gameStat/gameStat.png";
static char gBackgroundMenu[]				= "asset/img/menu/menu.png";
static char gFrameMenuOption[]				= "asset/img/menu/frame.png";

static char gBackgroundSelectMainObject[]	= "asset/img/menu/main_object_selection/selectPlayer.png";
static char gHoldFrameMainObject[]			= "asset/img/menu/main_object_selection/holdPlayerBackground.png";
static char gFrameMainObject[]				= "asset/img/menu/main_object_selection/playerBackground.png";

static char gBackgroundSelectMap[]			= "asset/img/menu/map_selection/selectMap.png";
static char gFrameMap[]						= "asset/img/menu/map_selection/mapBackground.png";
static char gHoldFrameMap[]					= "asset/img/menu/map_selection/holdMapBackground.png";

static char gGameMap[]						= "asset/map/0/map.dat";
static char gBullet[]						= "asset/img/player_bullet.png";

static char gMainObject[]					= "asset/img/main_object/0/right.png";
static char gMainRight[]					= "asset/img/main_object/0/right.png";
static char gMainLeft[]						= "asset/img/main_object/0/left.png";
static char gMainDown[]						= "asset/img/main_object/0/down.png";
static char gMainUp[]						= "asset/img/main_object/0/up.png";
static char gMainUpLeft[]					= "asset/img/main_object/0/up_left.png";
static char gMainUpRight[]					= "asset/img/main_object/0/up_right.png";
static char gMainDownRight[]				= "asset/img/main_object/0/down_right.png";
static char gMainDownLeft[]					= "asset/img/main_object/0/down_left.png";

static char gBackgroundSetting[]			= "asset/img/menu/setting/setting_background.png";
static char gButton[]						= "asset/img/menu/setting/slider_button.png";
static char gSlider[]						= "asset/img/menu/setting/slider.png";
static char gSlider2[]						= "asset/img/menu/setting/slider2.png";
static char gOption[]						= "asset/img/menu/setting/option1.png";
static char gOption2[]						= "asset/img/menu/setting/option2.png";

static char gBackgroundTutorial[]			= "asset/img/menu/tutorial/tutorial.png";
static char gThum[]							= "asset/img/gameStat/thumnail/0.png";
static char gWin[] = "asset/img/win.png";
static char gLose[] = "asset/img/lose.png";
static Mix_Chunk* sButton;
static Mix_Chunk* sSelect1;
static Mix_Chunk* sMana;
static Mix_Chunk* enemy;
static Mix_Chunk* loss;
static Mix_Music* sMenuMusic;
static Mix_Music* gIngame;
static Mix_Music* over;
static Mix_Chunk* emptyGun;
static SDL_Window* gWindow = NULL;
static SDL_Renderer* gScreen = NULL;
static SDL_Event gEvent;
static SDL_Surface* iconSurface = NULL;

#define EASY 0
#define MEDIUM 1
#define HARD 2
// Set FPS;
const int FRAME_PER_SECOND = 60;

// Set Window dimension
const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 960;
const int SCREEN_BPP = 32;

// Set Render Color Key 
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

const int RENDER_DRAW_COLOR = 0xFF;
const int MAX_VOLUME = 127;

// Define max map size
#define MAX_MAP_X 50
#define MAX_MAP_Y 30

// Define tile size
#define TILE_SIZE 64
#define BLANK_TILE 0

// Defile main and map object selection
#define MAIN_OBJECT_NUM 4
#define MAP_NUM 2
const int maxHP = 1000;
const int maxEnergy = 250;
static Mix_Chunk* sGunSound[MAIN_OBJECT_NUM];


// Define map
struct Map
{
	int startX_;
	int startY_;

	int maxX_;
	int maxY_;

	int tile_[MAX_MAP_Y][MAX_MAP_X];
	char* fileName_;
};

struct Input
{
	int left_;
	int right_;
	int up_;
	int down_;
};

namespace SDLCommonFunc
{
	enum MenuSelection
	{
		NONE = -1,
		PLAYGAME = 4,
		SETTING = 6,
		TUTORIAL = 5,
		EXIT = 7,

		SELECTPLAYER = 8,
		SELECTMAP = 8,
		BACK = 10,

		INTOGAME = 11
	};
	bool CheckCollision(const SDL_Rect& objectA, const SDL_Rect& objectB);
	int ShowMenu(SDL_Renderer* screen, TTF_Font* font, 
		const string& menu1,
		const string& menu2,
		const string& menu3,
		const string& menu4,
		const string& fileName, 
		Mix_Chunk* sButton);
	int ShowMainObjectMenu(SDL_Renderer* screen, TTF_Font* font, const string& fileName, int& mainObject, Mix_Chunk* sButton, Mix_Chunk* sSelect1);
	int ShowMapMenu(SDL_Renderer* screen, TTF_Font* font, const string& fileName, int& map, Mix_Chunk* sButton, Mix_Chunk* sSelect1);
	int ShowSetting(SDL_Renderer* screen, TTF_Font* font, const string& back, const string& fileName, int& widthSlider1, int& widthSlider2, int& gameMode, Mix_Chunk* sButton);
	int ShowTutorial(SDL_Renderer* screen, TTF_Font* font, const string& back, const string& fileName, Mix_Chunk* sButton);
	int ShowEnd(SDL_Renderer* screen, TTF_Font* font, const string& win, const string& lose, int status, Mix_Chunk* sButton);
	
}
#endif // !COMMON_FUNC_H_
