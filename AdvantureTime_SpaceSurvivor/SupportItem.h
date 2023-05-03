#ifndef SUPPORT_ITEM_H_
#define SUPPORT_ITEM_H_

#include "CommonFunc.h"
#include "BaseObject.h"

using namespace std;

class SupportItem :public BaseObject
{
public:
	SupportItem();
	~SupportItem();

	
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	void SetMapXY(const int& mapX, const int& mapY);

	void SetXPos(const float& x) { xPos_ = x; }
	void SetYPos(const float& y) { yPos_ = y; }
	float GetXPos()const { return xPos_; }
	float GetYPos()const { return yPos_; }
	SDL_Rect GetRectFrame();

private:

	float xPos_;
	float yPos_;

	int mapX_;
	int mapY_;

	int widthFrame_;
	int heightFrame_;
};
#endif // !SUPPORT_ITEM_H_
