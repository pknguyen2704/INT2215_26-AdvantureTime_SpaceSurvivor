#include "ThreatObject.h"
using namespace std;
ThreatObject::ThreatObject()
{
	rect_.x = 9;
	rect_.y = 0;
	widthFrame_ = 0;
	heightFrame_ = 0;
	xVal_ = 0.0;
	yVal_ = 0.0;
	xPos_ = 0.0;
	yPos_ = 0.0;
	frame_ = 0;
	mapX_ = 0;
	mapY_ = 0;
	inputType_.left_ = 0;
}

ThreatObject::~ThreatObject()
{

	if (bulletList.size() > 0)
	{
		for (int i = 0; i < bulletList.size(); i++)
		{
			BulletObject* p_bullet = bulletList.at(i);
			if (p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
		bulletList.clear();
	}
}
void ThreatObject::SetXVal(const float& xVal)
{
	xVal_ = xVal;
}
void ThreatObject::SetYVal(const float& xVal)
{
	xVal_ = xVal;
}
float ThreatObject::GetXVal() const
{
	return xVal_;
}
float ThreatObject::GetYVal() const
{
	return yVal_;
}
void ThreatObject::SetXPos(const float& xPos)
{
	xPos_ = xPos;
}
void ThreatObject::SetYPos(const float& yPos)
{
	yPos_ = yPos;
}
float ThreatObject::GetXPos() const
{
	return xPos_;
}
float ThreatObject::GetYPos() const
{
	return yPos_;
}
void ThreatObject::SetMapXY(const int& mpX, const int& mpY)
{
	mapX_ = mpX;
	mapY_ = mpY;
}
int ThreatObject::GetWidthFrame() const
{
	return widthFrame_;
}
int ThreatObject::GetHeightFrame() const
{
	return heightFrame_;
}

std::vector <BulletObject*> ThreatObject::GetBulletList() const
{
	return bulletList;
}
void ThreatObject::SetBulletList(const std::vector<BulletObject*>& blList)
{
	bulletList = blList;
}
bool ThreatObject::LoadImg(std::string path, SDL_Renderer* screen)
{
	bool ret = BaseObject::LoadImg(path, screen);
	if (ret == true)
	{
		widthFrame_ = rect_.w / THREAT_FRAMES;
		heightFrame_ = rect_.h;
	}
	return ret;
}
void ThreatObject::SetClip()
{
	if (widthFrame_ > 0 && heightFrame_ > 0)
	{
		for (int i = 0; i < THREAT_FRAMES; i++)
		{
			frameClip_[i].x = i * widthFrame_;
			frameClip_[i].y = 0;
			frameClip_[i].w = widthFrame_;
			frameClip_[i].h = heightFrame_;
		}
	}
}
void ThreatObject::Show(SDL_Renderer* des)
{
	rect_.x = xPos_ - mapX_;
	rect_.y = yPos_ - mapY_;
	frame_++;
	if (frame_ >= THREAT_FRAMES)
	{
		frame_ = 0;
	}
	SDL_Rect* p_currentClip = &frameClip_[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, widthFrame_, heightFrame_ };
	SDL_RenderCopy(des, p_object_, p_currentClip, &renderQuad);
}

void ThreatObject::DoPlayer(Map& gMap, float x, float y, vector <ThreatObject*> threatList)
{
	srand(time(0));
	xVal_ = (x - xPos_) / THREAT_SPEED;
	yVal_ = (y - yPos_) / THREAT_SPEED;
	CheckToMap(gMap);
}
void ThreatObject::CheckToMap(Map& g_map)
{
	//int x1 = 0;
	//int x2 = 0;
	//int y1 = 0;
	//int y2 = 0;

	////Check Horizontal
	//int height_min = heightFrame_ < TILE_SIZE ? heightFrame_ : TILE_SIZE;    //SDLCommonFunc::GetMin(height_frame_ TILE_SIZE);

	//x1 = (xPos_ + xVal_) / TILE_SIZE;
	//x2 = (xPos_ + xVal_ + widthFrame_ - 1) / TILE_SIZE;

	//y1 = (yPos_) / TILE_SIZE;
	//y2 = (yPos_ + height_min - 1) / TILE_SIZE;

	//// Check x1, x2 with full width of map
	//// Check y1, y2 with full heigth of map
	//if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	//{
	//	if (xVal_ > 0) // when object is moving by right  ===>
	//	{
	//		int val1 = g_map.tile_[y1][x2];
	//		int val2 = g_map.tile_[y2][x2];

	//		// Check current position of map. It is not blank_tile.
	//		if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
	//		{
	//			// Fixed post of object at current post of map.
	//			// => Cannot moving when press button
	//			xPos_ = x2 * TILE_SIZE;
	//			xPos_ -= widthFrame_ + 1;
	//			xVal_ = 0; // cannot moving
	//		}
	//	}
	//	else if (xVal_ < 0) // When moving by left    <====
	//	{
	//		int val1 = g_map.tile_[y1][x1];
	//		int val2 = g_map.tile_[y2][x1];
	//		if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
	//		{
	//			xPos_ = (x1 + 1) * TILE_SIZE;
	//			xVal_ = 0;
	//		}
	//	}
	//}

	//// Check vertical
	//int width_min = widthFrame_ < TILE_SIZE ? widthFrame_ : TILE_SIZE;//SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);

	//x1 = (xPos_) / TILE_SIZE;
	//x2 = (xPos_ + width_min) / TILE_SIZE;

	//y1 = (yPos_ + yVal_) / TILE_SIZE;
	//y2 = (yPos_ + yVal_ + heightFrame_ - 1) / TILE_SIZE;

	//if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	//{
	//	if (yVal_ > 0)
	//	{
	//		//Similar for vertical
	//		int val1 = g_map.tile_[y2][x1];
	//		int val2 = g_map.tile_[y2][x2];

	//		if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
	//		{
	//			yPos_ = y2 * TILE_SIZE;
	//			yPos_ -= heightFrame_;
	//			yVal_ = 0;

	//		}
	//	}
	//	else if (yVal_ < 0)
	//	{
	//		int val1 = g_map.tile_[y1][x1];
	//		int val2 = g_map.tile_[y1][x2];

	//		if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
	//		{
	//			yPos_ = (y1 + 1) * TILE_SIZE;
	//			yVal_ = 0;
	//		}
	//	}
	//}

	//If there is not collision with map tile. 
	//yPos_ += 1 / 2 * 10*(xPos_ * xPos_ - (xPos_ + xVal_) * (xPos_ + xVal_)) / (5 * 5);
	xPos_ += xVal_;
	yPos_ += yVal_;

	if (xPos_ < 0)
	{
		xPos_ = 0;
	}
	else if (yPos_ < 0)
	{
		yPos_ = 0;
	}
	else if (xPos_ + widthFrame_ >= g_map.maxX_)
	{
		xPos_ = g_map.maxX_ - widthFrame_ - 1;
	}
	else if (yPos_ + heightFrame_ >= g_map.maxY_)
	{
		yPos_ = g_map.maxY_ - heightFrame_ - 1;
	}
}

// Nhân vật bắn ra đạn (Cái này nên làm để tăng độ khó cho game)
void ThreatObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
	if (p_bullet != NULL)
	{
		p_bullet->LoadImg(gBullet, screen);
		p_bullet->SetIsMove(true);
		p_bullet->SetBulletDir(BulletObject::DIR_RIGHT);
		p_bullet->SetRect(this->rect_.x + 10, this->rect_.y + 10);
		p_bullet->SetXVal(THREAT_BULLET_SPEED);
		bulletList.push_back(p_bullet);
	}
}
void ThreatObject::MakeBullet(SDL_Renderer* screen, const int& x, const int& y)
{
	for (int i = 0; i < bulletList.size(); i++)
	{
		BulletObject* p_bullet = bulletList.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->GetIsMove())
			{
				int bulletDistance = this->rect_.x - p_bullet->GetRect().x;
				if (bulletDistance < THREAT_BULLET_LIMIT_DISTANCE)
				{
					p_bullet->HandleMove(x, y);
					p_bullet->Render(screen, NULL);
				}
				else
					p_bullet->SetIsMove(false);
			}
			else
			{
				p_bullet->SetIsMove(true);
				p_bullet->SetRect(this->rect_.x + 10, this->rect_.y + 10);
			}
		}
	}
}
SDL_Rect ThreatObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = widthFrame_;
	rect.h = heightFrame_;

	return rect;
}
void ThreatObject::RemoveBullet(const int& idx)
{
	int size = bulletList.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = bulletList.at(idx);
		bulletList.erase(bulletList.begin() + idx);
		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
		bulletList.clear();
	}
}