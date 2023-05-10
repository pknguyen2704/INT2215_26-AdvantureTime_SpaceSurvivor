#include "MainObject.h"

MainObject::MainObject()
{
	frame_ = 0;
	xPos_ = SCREEN_WIDTH / 2 + SCREEN_WIDTH;
	yPos_ = SCREEN_HEIGHT / 2 + SCREEN_HEIGHT;
	xVal_ = 0;
	yVal_ = 0;

	widthFrame_ = 0;
	heightFrame_ = 0;

	status_ = WALK_NONE;
	mapX_ = 0;
	mapY_ = 0;
	inputType_.left_ = 0;
	inputType_.right_ = 0;
	inputType_.up_ = 0;
	inputType_.down_ = 0;
	for (int i = 0; i < MAIN_OBJECT_FRAMES; i++)
	{
		frameClip_[i] = { 0,0,0,0 };
	}
}

MainObject::~MainObject()
{
	Free();
}

void MainObject::SetMapXY(const int& mapX, const int& mapY)
{
	mapX_ = mapX;
	mapY_ = mapY;
}

bool MainObject::LoadImg(std::string path, SDL_Renderer* screen, const int& mainObject)
{
	//SDLCommonFunc::UpdateMainObject(mainObject);
	//cout << mainObject << endl;
	path[22] = char(mainObject + 48);
	//cout << path << endl;
	bool ret = BaseObject::LoadImg(path, screen);

	if (ret == true)
	{
		widthFrame_ = rect_.w / MAIN_OBJECT_FRAMES;
		heightFrame_ = rect_.h;
	}
	path.clear();
	return ret;
}

void MainObject::SetBulletList(std::vector<BulletObject*> p_bulletList)
{
	p_bulletList_ = p_bulletList;
}
void MainObject::Reset()
{
	inputType_.left_ = 0;
	inputType_.right_ = 0;
	inputType_.up_ = 0;
	inputType_.down_ = 0;
}
std::vector<BulletObject*> MainObject::GetBulletList() const
{
	return p_bulletList_;
}

void MainObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen, int& lossEnergy, Mix_Chunk* gunSound[1], Mix_Chunk* emptyGun)
{
	// when a key pressed;
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			inputType_.right_ = 1;
			inputType_.left_ = 0;
			break;
		}
		case SDLK_a:
		{
			inputType_.left_ = 1;
			inputType_.right_ = 0;
			break;
		}
		case SDLK_w:
		{
			inputType_.up_ = 1;
			inputType_.down_ = 0;

			break;
		}
		case SDLK_s:
		{
			inputType_.down_ = 1;
			inputType_.up_ = 0;
			break;
		}
		default:
			break;
		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_d:
		{
			inputType_.right_ = 0;
			break;
		}
		case SDLK_a:
		{
			inputType_.left_ = 0;
			break;
		}
		case SDLK_w:
		{
			inputType_.up_ = 0;
			break;
		}
		case SDLK_s:
		{
			inputType_.down_ = 0;
			break;
		}
		default:
			break;
		}
	}
	// multi press
	if (inputType_.down_ == 1 && inputType_.right_ == 1)
		status_ = WALK_DOWN_RIGHT;
	else if (inputType_.down_ == 1 && inputType_.left_ == 1)
		status_ = WALK_DOWN_LEFT;
	else if (inputType_.up_ == 1 && inputType_.right_ == 1)
		status_ = WALK_UP_RIGHT;
	else if (inputType_.up_ == 1 && inputType_.left_ == 1)
		status_ = WALK_UP_LEFT;
	// update main direct status
	else if (inputType_.left_ == 1)
		status_ = WALK_LEFT;
	else if (inputType_.right_ == 1)
		status_ = WALK_RIGHT;
	else if (inputType_.down_ == 1)
		status_ = WALK_DOWN;
	else if (inputType_.up_ == 1)
		status_ = WALK_UP;


	if (events.type == SDL_MOUSEBUTTONDOWN)
	{
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			if (lossEnergy < maxEnergy)
			{
				lossEnergy += 5;
				BulletObject* p_bullet = new BulletObject();
				p_bullet->LoadImg(gBullet, screen);

				if (status_ == WALK_LEFT)
				{
					p_bullet->SetBulletDir(BulletObject::DIR_LEFT);
					p_bullet->SetRect(this->rect_.x + widthFrame_ * 0.21, this->rect_.y + heightFrame_ * 0.5);
				}
				else if (status_ == WALK_RIGHT)
				{
					p_bullet->SetBulletDir(BulletObject::DIR_RIGHT);
					p_bullet->SetRect(this->rect_.x + widthFrame_ - widthFrame_ * 0.4, this->rect_.y + heightFrame_ * 0.5);
				}
				else if (status_ == WALK_UP)
				{
					p_bullet->SetBulletDir(BulletObject::DIR_UP);
					p_bullet->SetRect(this->rect_.x + widthFrame_ - widthFrame_ * 0.4, this->rect_.y + heightFrame_ * 0.5);
				}
				else if (status_ == WALK_DOWN)
				{
					p_bullet->SetBulletDir(BulletObject::DIR_DOWN);
					p_bullet->SetRect(this->rect_.x + widthFrame_ * 0.21, this->rect_.y + heightFrame_ * 0.68);
				}
				else if (status_ == WALK_DOWN_LEFT)
				{
					p_bullet->SetBulletDir(BulletObject::DIR_DOWN_LEFT);
					p_bullet->SetRect(this->rect_.x - widthFrame_ * 0.2, this->rect_.y + heightFrame_ - heightFrame_ * 0.2);
				}
				else if (status_ == WALK_DOWN_RIGHT)
				{
					p_bullet->SetBulletDir(BulletObject::DIR_DOWN_RIGHT);
					p_bullet->SetRect(this->rect_.x - widthFrame_ * 0.2, this->rect_.y + heightFrame_ * 0.2);
				}
				else if (status_ == WALK_UP_RIGHT)
				{
					p_bullet->SetBulletDir(BulletObject::DIR_UP_RIGHT);
					p_bullet->SetRect(this->rect_.x + widthFrame_ * 0.21, this->rect_.y + heightFrame_ * 0.68);
				}
				else if (status_ == WALK_UP_LEFT)
				{
					p_bullet->SetBulletDir(BulletObject::DIR_UP_LEFT);
					p_bullet->SetRect(this->rect_.x + widthFrame_ * 0.21, this->rect_.y + heightFrame_ * 0.6);
				}

				p_bullet->SetXVal(BULLET_SPEED);
				p_bullet->SetYVal(BULLET_SPEED);
				p_bullet->SetIsMove(true);
				p_bulletList_.push_back(p_bullet);
				Mix_PlayChannel(-1, gunSound[0], 0);
			}
			else if(lossEnergy >= maxEnergy)
			{
				Mix_PlayChannel(-1, emptyGun, 0);
			}
			
		}
		if (events.button.button == SDL_BUTTON_RIGHT && lossEnergy < maxEnergy)
		{
			lossEnergy += 30;
			if (status_ == WALK_LEFT)
			{
				xPos_ -= 100*PLAYER_SPEED;
			}
			else if (status_ == WALK_RIGHT)
			{
				xPos_ += 100* PLAYER_SPEED;

			}
			else if (status_ == WALK_UP)
			{
				yPos_ -= 100 * PLAYER_SPEED;
			}
			else if (status_ == WALK_DOWN)
			{
				yPos_ += 100 * PLAYER_SPEED;

			}
			else if (status_ == WALK_DOWN_LEFT)
			{
				xPos_ -= 100 * PLAYER_CROSS_SPEED;
				yPos_ += 100 * PLAYER_CROSS_SPEED;

			}
			else if (status_ == WALK_DOWN_RIGHT)
			{
				yPos_ += 100 * PLAYER_CROSS_SPEED;
				xPos_ += 100 * PLAYER_CROSS_SPEED;

			}
			else if (status_ == WALK_UP_RIGHT)
			{
				xPos_ += 100 * PLAYER_CROSS_SPEED;
				yPos_ -= 100 * PLAYER_CROSS_SPEED;

			}
			else if (status_ == WALK_UP_LEFT)
			{
				xPos_ -= 100 * PLAYER_CROSS_SPEED;
				yPos_ -= 100 * PLAYER_CROSS_SPEED;
			}
		}
	}
	else if (events.type == SDL_MOUSEBUTTONUP)
	{
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			;//
		}
		else
		{
			;//
		}
	}
}
void MainObject::HandleBullet(SDL_Renderer* des)
{
	for (int i = 0; i < p_bulletList_.size(); i++)
	{
		BulletObject* p_bullet = p_bulletList_.at(i);
		if (p_bullet != NULL)
		{
			if (p_bullet->GetIsMove() == true)
			{
				p_bullet->HandleMove(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_bullet->Render(des);
			}
			else
			{
				if (p_bullet != NULL)
				{
					p_bulletList_.erase(p_bulletList_.begin() + i);
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
	}
}
void MainObject::RemoveBullet(const int& idx)
{
	int size = p_bulletList_.size();
	if (size > 0 && idx < size)
	{
		BulletObject* p_bullet = p_bulletList_.at(idx);
		p_bulletList_.erase(p_bulletList_.begin() + idx);
		if (p_bullet)
		{
			delete p_bullet;
			p_bullet = NULL;
		}
	}
}
void MainObject::SetClips()
{
	// clip the sprites
	if (widthFrame_ > 0 && heightFrame_ > 0)
	{
		for (int i = 0; i < MAIN_OBJECT_FRAMES; i++)
		{
			frameClip_[i].x = i * widthFrame_;
			frameClip_[i].y = 0;
			frameClip_[i].w = widthFrame_;
			frameClip_[i].h = heightFrame_;
		}
	}
}

void MainObject::Show(SDL_Renderer* des, const int& mainObject)
{
	UpdateImagePlayer(des, mainObject);
	if (inputType_.left_ == 1 || inputType_.right_ == 1 || inputType_.down_ == 1 || inputType_.up_ == 1)
	{
		frame_++;
	}
	else
	{
		frame_ = 0;
	}

	if (frame_ >= MAIN_OBJECT_FRAMES)
	{
		frame_ = 0;
	}
	rect_.x = xPos_ - mapX_;
	rect_.y = yPos_ - mapY_;
	SDL_Rect* p_currentClip = &frameClip_[frame_];
	SDL_Rect renderQuad = { rect_.x, rect_.y, widthFrame_, heightFrame_ };
	if (p_currentClip != NULL)
	{
		renderQuad.w = p_currentClip->w;
		renderQuad.h = p_currentClip->h;
	}
	SDL_RenderCopy(des, p_object_, p_currentClip, &renderQuad);
}
void MainObject::DoPlayer(Map& gMap)
{
	xVal_ = 0;
	yVal_ = 0;

	// Cross Move
	if (inputType_.up_ == 1 && inputType_.right_ == 1)
	{
		yVal_ -= PLAYER_CROSS_SPEED;
		xVal_ += PLAYER_CROSS_SPEED;
	}
	else if (inputType_.up_ == 1 && inputType_.left_ == 1)
	{
		yVal_ -= PLAYER_CROSS_SPEED;
		xVal_ -= PLAYER_CROSS_SPEED;
	}
	else if (inputType_.down_ == 1 && inputType_.right_ == 1)
	{
		yVal_ += PLAYER_CROSS_SPEED;
		xVal_ += PLAYER_CROSS_SPEED;
	}
	else if (inputType_.down_ == 1 && inputType_.left_ == 1)
	{
		yVal_ += PLAYER_CROSS_SPEED;
		xVal_ -= PLAYER_CROSS_SPEED;
	}
	// Basic Move
	else if (inputType_.left_ == 1)
		xVal_ -= PLAYER_SPEED;
	else if (inputType_.up_ == 1)
		yVal_ -= PLAYER_SPEED;
	else if (inputType_.right_ == 1)
		xVal_ += PLAYER_SPEED;
	else if (inputType_.down_ == 1)
		yVal_ += PLAYER_SPEED;
	CheckToMap(gMap);
	CenterEntityOnMap(gMap);
}
void MainObject::CenterEntityOnMap(Map& gMap)
{
	gMap.startX_ = xPos_ - (SCREEN_WIDTH / 2);

	if (gMap.startX_ < 0)
	{
		gMap.startX_ = 0;
	}

	else if (gMap.startX_ + SCREEN_WIDTH >= gMap.maxX_)
	{
		gMap.startX_ = gMap.maxX_ - SCREEN_WIDTH;
	}

	gMap.startY_ = yPos_ - (SCREEN_HEIGHT / 2);

	if (gMap.startY_ < 0)
	{
		gMap.startY_ = 0;
	}

	else if (gMap.startY_ + SCREEN_HEIGHT >= gMap.maxY_)
	{
		gMap.startY_ = gMap.maxY_ - SCREEN_HEIGHT;
	}
}
void MainObject::CheckToMap(Map& gMap)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	//Check Horizontal
	int height_min = heightFrame_ < TILE_SIZE ? heightFrame_ : TILE_SIZE;    //SDLCommonFunc::GetMin(height_frame_ TILE_SIZE);

	x1 = (xPos_ + xVal_) / TILE_SIZE;
	x2 = (xPos_ + xVal_ + widthFrame_ - 1) / TILE_SIZE;

	y1 = (yPos_) / TILE_SIZE;
	y2 = (yPos_ + height_min - 1) / TILE_SIZE;

	// Check x1, x2 with full width of map
	// Check y1, y2 with full heigth of map
	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (xVal_ > 0) // when object is moving by right  ===>
		{
			int val1 = gMap.tile_[y1][x2];
			int val2 = gMap.tile_[y2][x2];

			// Check current position of map. It is not blank_tile.
			if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
			{
				// Fixed post of object at current post of map.
				// => Cannot moving when press button
				xPos_ = x2 * TILE_SIZE;
				xPos_ -= widthFrame_ + 1;
				xVal_ = 0; // cannot moving
			}
		}
		else if (xVal_ < 0) // When moving by left    <====
		{
			int val1 = gMap.tile_[y1][x1];
			int val2 = gMap.tile_[y2][x1];
			if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
			{
				xPos_ = (x1 + 1) * TILE_SIZE;
				xVal_ = 0;
			}
		}
	}

	// Check vertical
	int width_min = widthFrame_ < TILE_SIZE ? widthFrame_ : TILE_SIZE;//SDLCommonFunc::GetMin(width_frame_, TILE_SIZE);

	x1 = (xPos_) / TILE_SIZE;
	x2 = (xPos_ + width_min) / TILE_SIZE;

	y1 = (yPos_ + yVal_) / TILE_SIZE;
	y2 = (yPos_ + yVal_ + heightFrame_ - 1) / TILE_SIZE;

	if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
	{
		if (yVal_ > 0)
		{
			//Similar for vertical
			int val1 = gMap.tile_[y2][x1];
			int val2 = gMap.tile_[y2][x2];

			if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
			{
				yPos_ = y2 * TILE_SIZE;
				yPos_ -= heightFrame_;
				yVal_ = 0;

			}
		}
		else if (yVal_ < 0)
		{
			int val1 = gMap.tile_[y1][x1];
			int val2 = gMap.tile_[y1][x2];

			if ((val1 != BLANK_TILE) || (val2 != BLANK_TILE))
			{
				yPos_ = (y1 + 1) * TILE_SIZE;
				yVal_ = 0;
			}
		}
	}

	//If there is not collision with map tile. 
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
	else if (xPos_ + widthFrame_ >= gMap.maxX_)
	{
		xPos_ = gMap.maxX_ - widthFrame_ - 1;
	}
	else if (yPos_ + heightFrame_ >= gMap.maxY_)
	{
		yPos_ = gMap.maxY_ - heightFrame_ - 1;
	}
}
void MainObject::UpdateImagePlayer(SDL_Renderer* des, const int& mainObject)
{

	if (status_ == WALK_RIGHT)
	{
		LoadImg(gMainRight, des, mainObject);
	}
	else if (status_ == WALK_LEFT)
	{
		LoadImg(gMainLeft, des, mainObject);
	}
	else if (status_ == WALK_DOWN)
	{
		LoadImg(gMainDown, des, mainObject);
	}
	else if (status_ == WALK_UP)
	{
		LoadImg(gMainUp, des, mainObject);
	}
	else if (status_ == WALK_UP_RIGHT)
	{
		LoadImg(gMainUpRight, des, mainObject);
	}
	else if (status_ == WALK_UP_LEFT)
	{
		LoadImg(gMainUpLeft, des, mainObject);
	}
	else if (status_ == WALK_DOWN_LEFT)
	{
		LoadImg(gMainDownLeft, des, mainObject);
	}
	else if (status_ == WALK_DOWN_RIGHT)
	{
		LoadImg(gMainDownRight, des, mainObject);
	}
	SetClips();
}

SDL_Rect MainObject::GetRectFrame()
{
	SDL_Rect rect;
	rect.x = rect_.x;
	rect.y = rect_.y;
	rect.w = widthFrame_;
	rect.h = heightFrame_;

	return rect;
}