#ifndef GEOMETRIC_H_
#define GEOMETRIC_H_


#include "CommonFunc.h"

struct GeometricFormat
{
	GeometricFormat(int left, int top, int width, int height) { left_ = left;  top_ = top; width_ = width; height_ = height; }
	int left_;
	int top_;
	int width_;
	int height_;
};
struct ColorData
{
	ColorData(Uint8 r, Uint8 g, Uint8 b) { red_ = r; green_ = g; blue_ = b; }
	Uint8 red_;
	Uint8 green_;
	Uint8 blue_;
};
class Geometric
{
public:
	static void RenderRectangle(const GeometricFormat& geoSize, const ColorData& colorData, SDL_Renderer* screen);
	static void RenderOutline(const GeometricFormat& geoSize, const ColorData& colorData, SDL_Renderer* screen);
};
#endif // !GEOMETRIC_H_
