#include "Geometric.h"

void Geometric::RenderRectangle(const GeometricFormat& geoSize, const ColorData& colorData, SDL_Renderer* screen)
{
	SDL_Rect fillRect = { geoSize.left_, geoSize.top_, geoSize.width_, geoSize.height_ };
	SDL_SetRenderDrawColor(screen, colorData.red_, colorData.green_, colorData.blue_, 0);
	SDL_RenderFillRect(screen, &fillRect);
}
void Geometric::RenderOutline(const GeometricFormat& geoSize, const ColorData& colorData, SDL_Renderer* screen)
{
	SDL_Rect outRect = { geoSize.left_, geoSize.top_, geoSize.width_, geoSize.height_ };
	SDL_SetRenderDrawColor(screen, colorData.red_, colorData.green_, colorData.blue_, 0);
	SDL_RenderDrawRect(screen, &outRect);
}