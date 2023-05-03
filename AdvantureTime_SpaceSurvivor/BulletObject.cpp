#include "BulletObject.h"

BulletObject::BulletObject()
{
	xVal_ = 0;
	yVal_ = 0;
	isMove_ = false;
	moveType_ = LINE_TYPE;
	bulletDir_ = DIR_LEFT;
}
BulletObject::~BulletObject()
{

}
void BulletObject::SetXVal(const float& xVal)
{
	xVal_ = xVal;
}
void BulletObject::SetYVal(const float& yVal)
{
	yVal_ = yVal;
}
float BulletObject::GetXVal() const
{
	return xVal_;
}
float BulletObject::GetYVal() const
{
	return yVal_;
}
void BulletObject::SetIsMove(const bool& isMove)
{
	isMove_ = isMove;
}
bool BulletObject::GetIsMove() const
{
	return isMove_;
}
void BulletObject::SetBulletDir(const unsigned int& bulletDir)
{
	bulletDir_ = bulletDir;
}
unsigned int BulletObject::GetBulletDir() const
{
	return bulletDir_;
}

void BulletObject::HandleMove(const int& xBorder, const int& yBorder)
{
	if (bulletDir_ == DIR_RIGHT)
	{
		rect_.x += xVal_;
		if (rect_.x > xBorder)
		{
			isMove_ = false;
		}
	}
	else if (bulletDir_ == DIR_LEFT)
	{
		rect_.x -= xVal_;
		if (rect_.x < 0)
		{
			isMove_ = false;
		}
	}
	else if (bulletDir_ == DIR_UP)
	{
		rect_.y -= yVal_;
		if (rect_.y < 0)
		{
			isMove_ = false;
		}
	}
	else if (bulletDir_ == DIR_DOWN)
	{
		rect_.y += yVal_;
		if (rect_.y > yBorder)
		{
			isMove_ = false;
		}
	}
	else if (bulletDir_ == DIR_UP_LEFT)
	{
		rect_.x -= xVal_;
		if (rect_.x < 0)
		{
			isMove_ = false;
		}
		rect_.y -= yVal_;
		if (rect_.y < 0)
		{
			isMove_ = false;
		}
	}
	else if (bulletDir_ == DIR_UP_RIGHT)
	{
		rect_.x += xVal_;
		if (rect_.x > xBorder)
		{
			isMove_ = false;
		}
		rect_.y -= yVal_;
		if (rect_.y < 0)
		{
			isMove_ = false;
		}
	}
	else if (bulletDir_ == DIR_DOWN_RIGHT)
	{
		rect_.x += xVal_;
		if (rect_.x > xBorder)
		{
			isMove_ = false;
		}
		rect_.y += yVal_;
		if (rect_.y > yBorder)
		{
			isMove_ = false;
		}
	}
	else if (bulletDir_ == DIR_DOWN_LEFT)
	{
		rect_.x -= xVal_;
		if (rect_.x < 0)
		{
			isMove_ = false;
		}
		rect_.y += yVal_;
		if (rect_.y > yBorder)
		{
			isMove_ = false;
		}
	}
}