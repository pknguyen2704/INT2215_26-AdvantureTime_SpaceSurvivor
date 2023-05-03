#ifndef TEXT_OBJECT_H_
#define TEXT_OBJECT_H_
#include "CommonFunc.h"

class TextObject
{
public:
    TextObject();
    ~TextObject();

    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
        BLUE_TEXT = 3,
        YELLOW_TEXT = 4,
        BROWN_TEXT = 5,
    };

    bool LoadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen);
    void Free();

    //void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColorType(int type);

    void RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    int GetWidth() const;
    int GetHeight() const;

    void SetText(const std::string& text);
    string GetText() const;
    void SetRect(const int& x, const int& y);
    SDL_Rect GetRect() const;

private:
    std::string strVal_;
    SDL_Color textColor_;
    SDL_Texture* texture_;
    int width_;
    int height_;
    SDL_Rect rect_;
};

#endif

