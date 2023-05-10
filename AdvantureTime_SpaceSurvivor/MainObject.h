#ifndef MAIN_OBJECT_H_
#define MAIN_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

using namespace std;

#define MAIN_OBJECT_FRAMES 8
#define PLAYER_SPEED 2
#define PLAYER_CROSS_SPEED 1.5
#define BULLET_SPEED 15
class MainObject :public BaseObject
{
public:
	MainObject();
	~MainObject();

	enum WalkType {
		WALK_NONE = 0,
		WALK_RIGHT = 1,
		WALK_LEFT = 2,
		WALK_UP = 3,
		WALK_DOWN = 4,
		WALK_UP_LEFT = 5,
		WALK_UP_RIGHT = 6,
		WALK_DOWN_LEFT = 7,
		WALK_DOWN_RIGHT = 8,
	};
	void SetClips();
	bool LoadImg(std::string path, SDL_Renderer* screen, const int& mainObject);
	void Show(SDL_Renderer* des, const int& mainObject);
	void HandleInputAction(SDL_Event events, SDL_Renderer* screen, int& playerGun,Mix_Chunk* gunSound[1], Mix_Chunk* emptyGun);
	void SetMapXY(const int& mapX, const int& mapY);
	void Reset();
	void DoPlayer(Map& gMap);
	void UpdateImagePlayer(SDL_Renderer* des, const int& mainObject);

	void CenterEntityOnMap(Map& gMap);
	void CheckToMap(Map& gMap);
	
	void SetBulletList(std::vector<BulletObject*> p_bulletList);
	vector<BulletObject*> GetBulletList() const;

	void HandleBullet(SDL_Renderer* des);
	void RemoveBullet(const int& idx);
	float GetXPos()const { return xPos_; }
	float GetYPos()const { return yPos_; }
	SDL_Rect GetRectFrame();

private:
	std::vector<BulletObject*> p_bulletList_;
	float xVal_;
	float yVal_;
	float xPos_;
	float yPos_;

	int mapX_;
	int mapY_;

	int widthFrame_;
	int heightFrame_;
	SDL_Rect frameClip_[MAIN_OBJECT_FRAMES];
	Input inputType_;

	int frame_;
	int status_;
};
#endif // !MAIN_OBJECT_H_
