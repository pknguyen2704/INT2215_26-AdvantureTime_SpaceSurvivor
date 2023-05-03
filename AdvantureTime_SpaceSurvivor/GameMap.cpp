#include "GameMap.h"

using namespace std;

GameMap::GameMap()
{

}
GameMap::~GameMap()
{

}
Map GameMap::GetMap() const
{
	return gameMap_;
}
void GameMap::SetMap(const Map& gMap)
{
	gameMap_ = gMap;
}
void GameMap::LoadMap(char* fileName)
{
	ifstream inputFile(fileName);
	gameMap_.maxX_ = 0;
	gameMap_.maxY_ = 0;
	if (inputFile.is_open())
	{
		for (int i = 0; i < MAX_MAP_Y; i++)
		{
			for (int j = 0; j < MAX_MAP_X; j++)
			{
				inputFile >> gameMap_.tile_[i][j];
			}
		}
		gameMap_.maxX_ = MAX_MAP_X - 1;
		gameMap_.maxY_ = MAX_MAP_Y - 1;
		gameMap_.maxX_ = (gameMap_.maxX_ + 1) * TILE_SIZE;
		gameMap_.maxY_ = (gameMap_.maxY_ + 1) * TILE_SIZE;
		gameMap_.startX_ = 0;
		gameMap_.startY_ = 0;
		gameMap_.fileName_ = fileName;
	}
	inputFile.close();
}
void GameMap::LoadMapTiles(SDL_Renderer* screen, int& map)
{
	string mapTilesName = "";
	mapTilesName = "asset/map/";
	mapTilesName += char(map + 48);
	mapTilesName += '/';
	for (int i = 0; i < MAX_TILES; i++)
	{
		std::string str;
		int tmp = i;
		if (tmp == 0)
			str = "0";
		else
		{
			while (tmp > 0)
			{
				str = char(tmp % 10 + 48) + str;
				tmp = tmp / 10;
			}
		}
		str += ".png";
		tileMat_[i].LoadImg(mapTilesName + str, screen);
		str.clear();
	}
	mapTilesName.clear();
}
void GameMap::DrawMap(SDL_Renderer* des)
{
	int mapX = 0;
	int x1 = 0;
	int x2 = 0;

	int mapY = 0;
	int y1 = 0;
	int y2 = 0;

	x1 = (gameMap_.startX_ % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	y1 = (gameMap_.startY_ % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	mapY = gameMap_.startY_ / TILE_SIZE;
	for (int i = y1; i < y2; i += TILE_SIZE)
	{
		mapX = gameMap_.startX_ / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE)
		{
			//if(gameMap.tile[mapY][mapX] != 0)
			{
				tileMat_[gameMap_.tile_[mapY][mapX]].SetRect(j, i);
				tileMat_[gameMap_.tile_[mapY][mapX]].Render(des);
			}
			mapX++;
		}
		mapY++;
	}
}