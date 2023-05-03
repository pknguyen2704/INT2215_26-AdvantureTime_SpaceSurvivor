#ifndef EXPLOSION

#include "CommonFunc.h"
#include "BaseObject.h"

#define  EXPLOSION_FRAMES 8

class ExplosionObject : public BaseObject
{
public:
    ExplosionObject(void);
    ~ExplosionObject(void);

    void SetClips();
    void SetFrame(const int& fr) { frame_ = fr; }
    virtual bool LoadImg(std::string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    int GetFrameWidth() const { return frameWidth_; }
    int GetFrameHeight() const { return frameHeight_; }
private:
    int frameWidth_;
    int frameHeight_;
    unsigned int frame_;
    SDL_Rect frameClip[EXPLOSION_FRAMES];
};
#endif // EXPLOSION
