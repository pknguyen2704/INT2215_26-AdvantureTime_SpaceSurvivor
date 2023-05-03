#ifndef MAIN_OBJECT_INFO_H_
#define MAIN_OBJECT_INFO_H_

#include "Geometric.h"

namespace MainObjectInfo
{
	void ShowHPInGameStat(SDL_Renderer* screen,const int& x, const int& y, const int& width, const int& height, const int& loseHP);
	void ShowEnergyInGameStat(SDL_Renderer* screen,const int& x, const int& y, const int& width, const int& height, const int& lossEnergy);
	void ShowHPWithMain(SDL_Renderer* screen,SDL_Rect mainObjectRect, const int& maxHPDisplay, const int& lossHP);
};
#endif // !MAIN_OBJECT_INFO_H_
