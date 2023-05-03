#ifndef GAME_MAP_H_
#define GAME_MAP_H_

#include "CommonFunc.h"
#include "BaseObject.h"

#define MAX_TILES 30
#define SCROLL_SPEED 4

class TileMat :public BaseObject
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap
{
public:
	GameMap();
	~GameMap();

	void LoadMap(char* fileName);
	void DrawMap(SDL_Renderer* des);
	void LoadMapTiles(SDL_Renderer* screen, int& map);

	Map GetMap() const;
	void SetMap(const Map& gMap);
private:
	Map gameMap_;
	TileMat tileMat_[MAX_TILES];
	Input inputType_;
};
#endif // !GAME_MAP_H_
