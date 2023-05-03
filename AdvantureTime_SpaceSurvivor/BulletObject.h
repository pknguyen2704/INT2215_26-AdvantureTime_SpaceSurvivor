#ifndef BULLET_OBJECT_H_
#define BULLET_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"


class BulletObject :public BaseObject
{
public:
	BulletObject();
	~BulletObject();


	enum BulletDir
	{
		DIR_RIGHT = 20,
		DIR_LEFT = 21,
		DIR_UP = 22,
		DIR_DOWN = 23,
		DIR_UP_LEFT = 24,
		DIR_UP_RIGHT = 25,
		DIR_DOWN_LEFT = 26,
		DIR_DOWN_RIGHT = 27,
	};
	enum BulletType
	{
		NONE,
		LASER,
		SPHERE
	};
	enum MoveType
	{
		LINE_TYPE = 10,
		SIN_TYPE = 11
	};
	void HandleMove(const int& xBorder, const int& yBorder);

	void SetXVal(const float& xVal);
	void SetYVal(const float& yVal);
	float GetXVal() const;
	float GetYVal() const;
	void SetIsMove(const bool& isMove);
	bool GetIsMove() const;

	void SetMoveType(const int& moveType) { moveType_ = moveType; }
	void SetBulletDir(const unsigned int& bulletDir);
	unsigned int GetBulletDir() const;

private:
	float xVal_;
	float yVal_;

	bool isMove_;
	int moveType_;
	unsigned int bulletDir_;
};
#endif // !BULLET_OBJECT_H_
