#include "TextObject.h"


TextObject::TextObject()
{
    textColor_.r = 255;
    textColor_.g = 255;
    textColor_.b = 255;
    texture_ = NULL;
}


TextObject::~TextObject()
{
    Free();
}
int TextObject::GetWidth() const 
{ 
    return width_; 
}
int TextObject::GetHeight() const
{ 
    return height_; 
}
void TextObject::SetText(const std::string& text)
{ 
    strVal_ = text; 
}
string TextObject::GetText() const
{ 
    return strVal_; 
}
void TextObject::SetRect(const int& x, const int& y)
{
    rect_.x = x;
    rect_.y = y;
}

SDL_Rect TextObject::GetRect() const
{
    return rect_;
}

bool TextObject::LoadFromRenderedText(TTF_Font* gFont, SDL_Renderer* screen)
{
    Free();
    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, strVal_.c_str(), textColor_);
    if (textSurface != NULL)
    {
        //Create texture from surface pixels
        texture_ = SDL_CreateTextureFromSurface(screen, textSurface);
        if (texture_ != NULL)
        {
            //Get image dimensions
            width_ = textSurface->w;
            height_ = textSurface->h;
            rect_.w = textSurface->w;
            rect_.h = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }

    //Return success
    return texture_ != NULL;
}

void TextObject::Free()
{
    if (texture_ != NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}



void TextObject::SetColorType(int type)
{
    if (type == RED_TEXT)
    {
        SDL_Color color = { 255, 0, 0 };
        textColor_ = color;
    }
    else if (type == WHITE_TEXT)
    {
        SDL_Color color = { 255, 255, 255 };
        textColor_ = color;
    }
    else if (type == BLACK_TEXT)
    {
        SDL_Color color = { 0, 0, 0 };
        textColor_ = color;
    }
    else if (type == YELLOW_TEXT)
    {
        SDL_Color color = { 255, 255, 0 };
        textColor_ = color;
    }
    else if (type == BLUE_TEXT)
    {
        SDL_Color color = { 0, 255, 255 };
        textColor_ = color;
    }
    else if (type == BROWN_TEXT)
    {
        SDL_Color color = { 102,51,0 };
        textColor_ = color;
    }
    else
    {
        SDL_Color color = { 0, 255, 255 };
        textColor_ = color;
    }
}
void TextObject::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip /* = NULL */, double angle /* = 0.0 */, SDL_Point* center /* = NULL */, SDL_RendererFlip flip /* = SDL_FLIP_NONE */)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width_, height_ };

    //Set clip rendering dimensions
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(screen, texture_, clip, &renderQuad, angle, center, flip);
}
