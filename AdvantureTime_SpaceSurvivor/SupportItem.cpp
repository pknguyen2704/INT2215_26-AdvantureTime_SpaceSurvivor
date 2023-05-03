#include "SupportItem.h"

SupportItem::SupportItem()
{

}
SupportItem::~SupportItem()
{

}

void SupportItem::Show(SDL_Renderer* des)
{
	rect_.x = xPos_ - mapX_;
	rect_.y = yPos_ - mapY_;
	SDL_Rect renderQuad = { rect_.x, rect_.y, rect_.w, rect_.h };
	SDL_RenderCopy(des, p_object_, NULL, &renderQuad);
}
bool SupportItem::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	path.clear();
	return ret;
}
void SupportItem::SetMapXY(const int& mapX, const int& mapY)
{
	mapX_ = mapX;
	mapY_ = mapY;
}
SDL_Rect SupportItem::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = widthFrame_;
	rect.h = heightFrame_;

	return rect;
}
