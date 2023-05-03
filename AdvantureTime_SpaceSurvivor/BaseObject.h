#ifndef BASE_OBJECT_H_
#define BASE_OBJECT_H_

#include "CommonFunc.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	virtual bool LoadImg(const string path, SDL_Renderer* screen);
	void Render(SDL_Renderer* des, const SDL_Rect* clip = NULL);

	void Free();
	void SetRect(const int& x, const int& y);
	void SetWidth(const int& w);
	SDL_Rect GetRect() const;
	SDL_Texture* GetObject();

	void SetColor(const Uint8& red, const Uint8& green, const Uint8& blue);
	void SetAlpha(const Uint8& alpha);
	void SetBlendMode(const SDL_BlendMode& blending);

protected:
	SDL_Texture* p_object_;
	SDL_Rect rect_;
};
#endif // !BASE_OBJECT_H_
