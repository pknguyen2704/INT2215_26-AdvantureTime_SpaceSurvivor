#ifndef THREAT_OBJECT_H_
#define THREAT_OBJECT_H_

#include "CommonFunc.h"
#include "BaseObject.h"
#include "BulletObject.h"

using namespace std;

#define THREAT_FRAMES 8
//
#define THREAT_SPEED 800 // cang lon toc to di chuyen cang cham
#define THREAT_BULLET_SPEED 15

#define THREAT_BULLET_LIMIT_DISTANCE 300
class ThreatObject :public BaseObject
{
public:
	ThreatObject();
	~ThreatObject();

	void SetXVal(const float& xVal);
	void SetYVal(const float& xVal);
	float GetXVal() const;
	float GetYVal() const;

	void SetXPos(const float& xPos);
	void SetYPos(const float& yPos);
	float GetXPos() const;
	float GetYPos() const;

	void SetMapXY(const int& mpX, const int& mpY);
	void RemoveBullet(const int& idx);
	void SetClip();
	bool LoadImg(std::string path, SDL_Renderer* screen);
	void Show(SDL_Renderer* des);
	int GetWidthFrame() const;
	int GetHeightFrame() const;
	void DoPlayer(Map& gMap, float x, float y, vector <ThreatObject*> threatList);
	void CheckToMap(Map& gMap);
	SDL_Rect GetRectFrame();

	// setting bullet cho threats
	std::vector <BulletObject*> GetBulletList() const;
	void SetBulletList(const std::vector<BulletObject*>& blList);
	void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
	void MakeBullet(SDL_Renderer* screen, const int& x_limit, const int& y_limit);
private:

	float xPos_;
	float yPos_;
	float xVal_;
	float yVal_;

	int widthFrame_;
	int heightFrame_;
	SDL_Rect frameClip_[THREAT_FRAMES];

	int mapX_;
	int mapY_;

	int frame_;

	Input inputType_;
	std::vector <BulletObject*> bulletList;
};
#endif // !THREAT_OBJECT_H_
