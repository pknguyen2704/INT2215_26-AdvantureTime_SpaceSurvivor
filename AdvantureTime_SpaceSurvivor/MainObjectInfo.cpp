#include "MainObjectInfo.h"


void MainObjectInfo::ShowHPInGameStat(SDL_Renderer* screen, const int& x, const int& y, const int& width, const int& height, const int& loseHP)

{
	int currentHP = width - loseHP;
	// Background Color
	GeometricFormat rectangleSizeHPBackground(x, y, width, height);
	ColorData colorDataHPBackground(0, 0, 0);
	Geometric::RenderRectangle(rectangleSizeHPBackground, colorDataHPBackground, screen);

	// HP display in game stat
	GeometricFormat rectangleSizeHPinStat(x, y, currentHP > 0 ? currentHP : 0, height);
	ColorData colorDataHP(255, 0, 0);
	Geometric::RenderRectangle(rectangleSizeHPinStat, colorDataHP, screen);

	// Hp outline display in game stat
	GeometricFormat outlineSizeHPinStat(x, y, width, height);
	ColorData colorDataHPOutline(255, 255, 255);
	Geometric::RenderOutline(outlineSizeHPinStat, colorDataHPOutline,screen);
}
void MainObjectInfo::ShowEnergyInGameStat(SDL_Renderer* screen, const int& x, const int& y, const int& width, const int& height, const int& loseEnergy)
{
	int currentEnergy = width - (loseEnergy);
	GeometricFormat rectangleSizeEnergyBackground(x, y, width, height);
	ColorData colorDataEnergyBackground(0, 0, 0);
	Geometric::RenderRectangle(rectangleSizeEnergyBackground, colorDataEnergyBackground, screen);



	GeometricFormat rectangleSizeEnergy(x, y, currentEnergy, height);
	ColorData colorDataEnergy(0, 255, 0);
	Geometric::RenderRectangle(rectangleSizeEnergy, colorDataEnergy, screen);

	GeometricFormat outlineSizeEnergy(x, y, width, height);
	ColorData colorDataEnergyOutline(255, 255, 255);
	Geometric::RenderOutline(outlineSizeEnergy, colorDataEnergyOutline, screen);
}
void MainObjectInfo::ShowHPWithMain(SDL_Renderer* screen, SDL_Rect mainObjectRect, const int& maxHPDisplay, const int& lossHP)
{
	int currentHP = maxHPDisplay - (lossHP);
	GeometricFormat rectangleSizeHP(mainObjectRect.x - (maxHPDisplay - mainObjectRect.w) / 2, mainObjectRect.y - 15, currentHP > 0 ? currentHP : 0, 12);
	ColorData colorDataHP(255, 0, 0);
	Geometric::RenderRectangle(rectangleSizeHP, colorDataHP, screen);


	GeometricFormat outlineSizeHP(mainObjectRect.x - (maxHPDisplay - mainObjectRect.w) / 2, mainObjectRect.y - 15, maxHPDisplay, 12);
	ColorData colorDataHPOutline(255, 255, 255);
	Geometric::RenderOutline(outlineSizeHP, colorDataHPOutline, screen);
}