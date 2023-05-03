#include "Explosion.h"


ExplosionObject::ExplosionObject(void)
{
    frameHeight_ = 0;
    frameWidth_ = 0;
    frame_ = 0;
}


ExplosionObject::~ExplosionObject(void)
{
}


bool ExplosionObject::LoadImg(std::string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path, screen);

    if (ret == true)
    {
        frameWidth_ = rect_.w / EXPLOSION_FRAMES;
        frameHeight_ = rect_.h;
    }
    return ret;
}

void ExplosionObject::SetClips()
{
    if (frameWidth_ > 0 && frameHeight_ > 0)
    {
        for (int i = 0; i < EXPLOSION_FRAMES; i++)
        {
            frameClip[i].x = i * frameWidth_;
            frameClip[i].y = 0;
            frameClip[i].w = frameWidth_;
            frameClip[i].h = frameHeight_;
        }
    }
}


void ExplosionObject::Show(SDL_Renderer* screen)
{
    SDL_Rect* currentClip = &frameClip[frame_];
    SDL_Rect renderQuad = { rect_.x, rect_.y, frameWidth_, frameHeight_ };
    if (currentClip != NULL)
    {
        renderQuad.w = currentClip->w;
        renderQuad.h = currentClip->h;
    }

    SDL_RenderCopy(screen, p_object_, currentClip, &renderQuad);
}