#include "CommonFunc.h"
#include "BaseObject.h"
#include "TextObject.h"

bool SDLCommonFunc::CheckCollision(const SDL_Rect& objectA, const SDL_Rect& objectB)
{
    int leftA = objectA.x;
    int rightA = objectA.x + objectA.w;
    int topA = objectA.y;
    int bottomA = objectA.y + objectA.h;

    int leftB = objectB.x;
    int rightB = objectB.x + objectB.w;
    int topB = objectB.y;
    int bottomB = objectB.y + objectB.h;

    // Case 1: size object 1 < size object 2
    if (leftA > leftB && leftA < rightB)
    {
        if (topA > topB && topA < bottomB)
        {
            return true;
        }
    }

    if (leftA > leftB && leftA < rightB)
    {
        if (bottomA > topB && bottomA < bottomB)
        {
            return true;
        }
    }

    if (rightA > leftB && rightA < rightB)
    {
        if (topA > topB && topA < bottomB)
        {
            return true;
        }
    }

    if (rightA > leftB && rightA < rightB)
    {
        if (bottomA > topB && bottomA < bottomB)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (leftB > leftA && leftB < rightA)
    {
        if (topB > topA && topB < bottomA)
        {
            return true;
        }
    }

    if (leftB > leftA && leftB < rightA)
    {
        if (bottomB > topA && bottomB < bottomA)
        {
            return true;
        }
    }

    if (rightB > leftA && rightB < rightA)
    {
        if (topB > topA && topB < bottomA)
        {
            return true;
        }
    }

    if (rightB > leftA && rightB < rightA)
    {
        if (bottomB > topA && bottomB < bottomA)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (topA == topB && rightA == rightB && bottomA == bottomB)
    {
        return true;
    }

    return false;
}
int SDLCommonFunc::ShowMenu(SDL_Renderer* screen, TTF_Font* font,
    const string& menu1,
    const string& menu2,
    const string& menu3,
    const string& menu4,
    const string& fileName,
    Mix_Chunk* sButton)

{
    char* ch1 = (char*)menu1.c_str();
    char* ch2 = (char*)menu2.c_str();
    char* ch3 = (char*)menu3.c_str();
    char* ch4 = (char*)menu4.c_str();

    int size1 = menu1.length();
    int size2 = menu2.length();
    int size3 = menu3.length();
    int size4 = menu4.length();

    int time = 0;
    int x = 0;
    int y = 0;
    const int kMenuNum = 4;
    char* labels[kMenuNum];

    labels[0] = new char[size1 + 1];
    labels[1] = new char[size2 + 1];
    labels[2] = new char[size3 + 1];
    labels[3] = new char[size4 + 1];

    strcpy_s(labels[0], size1 + 1, ch1);
    strcpy_s(labels[1], size2 + 1, ch2);
    strcpy_s(labels[2], size3 + 1, ch3);
    strcpy_s(labels[3], size4 + 1, ch4);

    // Set XRect for MenuSet;
    const int textRectX = SCREEN_WIDTH * 0.085;
    const int frameRectX = SCREEN_WIDTH * 0.035;

    TextObject textObject[kMenuNum];
    BaseObject frameObject[kMenuNum];

    for (int i = 0; i < kMenuNum; i++)
    {
        frameObject[i].LoadImg(gFrameMenuOption, screen);
        frameObject[i].SetRect(frameRectX, SCREEN_HEIGHT * 0.5 + i * 120);
        textObject[i].SetText(labels[i]);
        textObject[i].SetColorType(TextObject::WHITE_TEXT);
        textObject[i].LoadFromRenderedText(font, screen);
        textObject[i].SetRect(textRectX, SCREEN_HEIGHT * 0.5 + 18 + i * 120);

    }
    BaseObject gBackgroundMenu;
    bool ret = gBackgroundMenu.LoadImg(fileName, screen);
    bool haveSelected = false;
    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                for (int i = 0; i < kMenuNum; i++)
                {
                    textObject[i].Free();
                    frameObject[i].Free();
                }

                gBackgroundMenu.Free();
                return SDLCommonFunc::EXIT;
                break;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                for (int i = 0; i < kMenuNum; i++)
                {
                    if (x >= frameObject[i].GetRect().x && x <= frameObject[i].GetRect().x + frameObject[i].GetRect().w && y >= frameObject[i].GetRect().y && y <= frameObject[i].GetRect().y + frameObject[i].GetRect().h)
                    {

                        textObject[i].Free();
                        textObject[i].SetText(labels[i]);
                        textObject[i].SetColorType(TextObject::BROWN_TEXT);
                        textObject[i].SetRect(textRectX + 30, textObject[i].GetRect().y);
                        textObject[i].LoadFromRenderedText(font, screen);

                        frameObject[i].SetRect(frameRectX + 30, frameObject[i].GetRect().y);
                    }
                    else
                    {
                        haveSelected = false;
                        textObject[i].Free();
                        textObject[i].SetText(labels[i]);
                        textObject[i].SetColorType(TextObject::WHITE_TEXT);
                        textObject[i].SetRect(textRectX, textObject[i].GetRect().y);
                        textObject[i].LoadFromRenderedText(font, screen);

                        frameObject[i].SetRect(frameRectX, frameObject[i].GetRect().y);
                    }
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < kMenuNum; i++)
                {
                    if (x >= frameObject[i].GetRect().x && x <= frameObject[i].GetRect().x + frameObject[i].GetRect().w && y >= frameObject[i].GetRect().y && y <= frameObject[i].GetRect().y + frameObject[i].GetRect().h)
                    {
                        Mix_PlayChannel(-1, sButton, 0);
                        return i + 4;
                    }
                }
                break;
            }
        }

        gBackgroundMenu.Render(screen, NULL);
        for (int i = 0; i < kMenuNum; i++)
        {
            frameObject[i].Render(screen, NULL);
            textObject[i].RenderText(screen, textObject[i].GetRect().x, textObject[i].GetRect().y);
        }
        SDL_RenderPresent(screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
    return SDLCommonFunc::NONE;
}
// chot show menu
int SDLCommonFunc::ShowMainObjectMenu(SDL_Renderer* screen, TTF_Font* font, const string& fileName, int& mainObject, Mix_Chunk* sButton, Mix_Chunk* sSelect1)
{
    BaseObject gBackgroundSelectMainObject;
    bool ret = gBackgroundSelectMainObject.LoadImg(fileName, screen);

    // mainObject option
    BaseObject gCharacterFrame[MAIN_OBJECT_NUM];
    BaseObject gCharacter[MAIN_OBJECT_NUM];

    // Description
    BaseObject gCharDes[MAIN_OBJECT_NUM];
    BaseObject gCharDesFrame[MAIN_OBJECT_NUM];
    TextObject textDescript[MAIN_OBJECT_NUM];
    textDescript[0].SetText("Hi, I'm Finn.");
    textDescript[1].SetText("Hi, I'm Jake.");
    textDescript[2].SetText("Hi, I'm Pricess.");
    textDescript[3].SetText("Hi, I'm Ice King.");

    for (int i = 0; i < MAIN_OBJECT_NUM; i++)
    {
        textDescript[i].SetColorType(TextObject::WHITE_TEXT);
        textDescript[i].LoadFromRenderedText(font, screen);
        textDescript[i].SetRect(SCREEN_WIDTH * 0.235 + 250, SCREEN_HEIGHT * 0.69 + 70);
    }

    TextObject textObjectConfirm;
    textObjectConfirm.SetText("CONFIRM");
    TextObject textObjectBack;
    textObjectBack.SetText("BACK");


    textObjectConfirm.SetRect(SCREEN_WIDTH * 0.66, SCREEN_HEIGHT * 0.748);
    textObjectConfirm.SetColorType(TextObject::WHITE_TEXT);
    textObjectConfirm.LoadFromRenderedText(font, screen);

    textObjectBack.SetRect(SCREEN_WIDTH * 0.294, SCREEN_HEIGHT * 0.032);
    textObjectBack.SetColorType(TextObject::WHITE_TEXT);
    textObjectBack.LoadFromRenderedText(font, screen);

    for (int i = 0; i < MAIN_OBJECT_NUM; i++)
    {
        gCharacterFrame[i].LoadImg(gFrameMainObject, screen);
        gCharDesFrame[i].LoadImg(gHoldFrameMainObject, screen);
        std::string str = "";
        std::string characterName = "asset/img/menu/main_object_selection/";
        int tmp = i;
        if (tmp == 0)
            str = "0";
        else
        {
            while (tmp > 0)
            {
                str = char(tmp % 10 + 48) + str;
                tmp = tmp / 10;
            }
        }
        str += ".png";
        gCharacter[i].LoadImg(characterName + str, screen);
        gCharDes[i].LoadImg(characterName + str, screen);
        str.clear();
        gCharacterFrame[i].SetRect(SCREEN_HEIGHT * 0.435 + i * 200, SCREEN_HEIGHT * 0.4);
        gCharacter[i].SetRect(SCREEN_HEIGHT * 0.435 + i * 200, SCREEN_HEIGHT * 0.4);
        gCharDes[i].SetRect(SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.69);
        gCharDesFrame[i].SetRect(SCREEN_WIDTH * 0.25, SCREEN_HEIGHT * 0.69);
    }

    int time = 0;
    int x = 0;
    int y = 0;
    SDL_Event event;

    bool selected[MAIN_OBJECT_NUM] = { false };
    bool haveSelected = false;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                for (int i = 0; i < MAIN_OBJECT_NUM; i++)
                {
                    gCharacterFrame[i].Free();
                    gCharacter[i].Free();
                    gCharDes[i].Free();
                    textDescript[i].Free();
                }
                textObjectConfirm.Free();
                textObjectBack.Free();
                gBackgroundSelectMainObject.Free();
                return SDLCommonFunc::EXIT;
                break;

            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                if (x >= textObjectConfirm.GetRect().x && x <= textObjectConfirm.GetRect().x + textObjectConfirm.GetWidth() && y >= textObjectConfirm.GetRect().y && y <= textObjectConfirm.GetRect().y + textObjectConfirm.GetHeight())
                {
                    textObjectConfirm.Free();
                    textObjectConfirm.SetColorType(TextObject::YELLOW_TEXT);
                    textObjectConfirm.LoadFromRenderedText(font, screen);
                }
                else
                {
                    textObjectConfirm.Free();
                    textObjectConfirm.SetColorType(TextObject::WHITE_TEXT);
                    textObjectConfirm.LoadFromRenderedText(font, screen);

                }
                if (x >= textObjectBack.GetRect().x && x <= textObjectBack.GetRect().x + textObjectBack.GetWidth() && y >= textObjectBack.GetRect().y && y <= textObjectBack.GetRect().y + textObjectBack.GetHeight())
                {
                    textObjectBack.Free();
                    textObjectBack.SetColorType(TextObject::YELLOW_TEXT);
                    textObjectBack.LoadFromRenderedText(font, screen);
                }
                else
                {
                    textObjectBack.Free();
                    textObjectBack.SetColorType(TextObject::WHITE_TEXT);
                    textObjectBack.LoadFromRenderedText(font, screen);

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < MAIN_OBJECT_NUM; i++)
                {
                    if (x >= gCharacterFrame[i].GetRect().x && x <= gCharacterFrame[i].GetRect().x + gCharacterFrame[i].GetRect().w && y >= gCharacterFrame[i].GetRect().y && y <= gCharacterFrame[i].GetRect().y + gCharacterFrame[i].GetRect().h)
                    {
                        Mix_PlayChannel(-1, sSelect1, 0);
                        for (int j = 0; j < MAIN_OBJECT_NUM; j++)
                        {
                            selected[j] = false;
                            gCharacterFrame[j].Free();
                            gCharacterFrame[j].LoadImg(gFrameMainObject, screen);
                        }
                        gCharacterFrame[i].Free();
                        gCharacterFrame[i].LoadImg(gHoldFrameMainObject, screen);
                        selected[i] = true;
                        mainObject = i;
                        haveSelected = true;
                    }
                }
                if (x >= textObjectConfirm.GetRect().x && x <= textObjectConfirm.GetRect().x + textObjectConfirm.GetWidth() && y >= textObjectConfirm.GetRect().y && y <= textObjectConfirm.GetRect().y + textObjectConfirm.GetHeight() && haveSelected == true)
                {
                    Mix_PlayChannel(-1, sButton, 0);
                    for (int i = 0; i < MAIN_OBJECT_NUM; i++)
                    {
                        gCharacterFrame[i].Free();
                        gCharacter[i].Free();
                        gCharDes[i].Free();
                        textDescript[i].Free();
                    }
                    textObjectConfirm.Free();
                    textObjectBack.Free();
                    gBackgroundSelectMainObject.Free();
                    return SDLCommonFunc::SELECTMAP;
                }
                if (x >= textObjectBack.GetRect().x && x <= textObjectBack.GetRect().x + textObjectBack.GetWidth() && y >= textObjectBack.GetRect().y && y <= textObjectBack.GetRect().y + textObjectBack.GetHeight())
                {
                    Mix_PlayChannel(-1, sButton, 0);
                    for (int i = 0; i < MAIN_OBJECT_NUM; i++)
                    {
                        gCharacterFrame[i].Free();
                        gCharacter[i].Free();
                        gCharDes[i].Free();
                        textDescript[i].Free();
                    }
                    textObjectConfirm.Free();
                    textObjectBack.Free();
                    gBackgroundSelectMainObject.Free();
                    return SDLCommonFunc::BACK;
                }
                break;
            }
        }
        // Render
        gBackgroundSelectMainObject.Render(screen, NULL);
        for (int i = 0; i < MAIN_OBJECT_NUM; ++i)
        {
            gCharacterFrame[i].Render(screen, NULL);
            gCharacter[i].Render(screen, NULL);
            if (selected[i] == true)
            {
                gCharDesFrame[i].Render(screen);
                gCharDes[i].Render(screen);
                textDescript[i].RenderText(screen, textDescript[i].GetRect().x, textDescript[i].GetRect().y);
            }
        }
        textObjectConfirm.RenderText(screen, textObjectConfirm.GetRect().x, textObjectConfirm.GetRect().y);
        textObjectBack.RenderText(screen, textObjectBack.GetRect().x, textObjectBack.GetRect().y);

        SDL_RenderPresent(screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
    return SDLCommonFunc::NONE;
}
int SDLCommonFunc::ShowMapMenu(SDL_Renderer* screen, TTF_Font* font, const string& fileName, int& map, Mix_Chunk* sButton, Mix_Chunk* sSelect1)
{
    BaseObject gBackgroundSelectMap;
    bool ret = gBackgroundSelectMap.LoadImg(fileName, screen);


    BaseObject gMap[MAP_NUM];
    string mapName = "asset/img/menu/map_selection/";
    string mapHold = "asset/img/menu/map_selection/hold/";

    TextObject text_object;
    text_object.SetText("CONFIRM");
    TextObject textObjectBack;
    textObjectBack.SetText("BACK");

    text_object.SetRect(SCREEN_WIDTH * 0.6269, SCREEN_HEIGHT * 0.032);
    text_object.SetColorType(TextObject::WHITE_TEXT);
    text_object.LoadFromRenderedText(font, screen);

    textObjectBack.SetRect(SCREEN_WIDTH * 0.294, SCREEN_HEIGHT * 0.032);
    textObjectBack.SetColorType(TextObject::WHITE_TEXT);
    textObjectBack.LoadFromRenderedText(font, screen);

    for (int i = 0; i < MAP_NUM; i++)
    {
        string str = "";
        int tmp = i;
        if (tmp == 0)
            str = "0";
        else
        {
            while (tmp > 0)
            {
                str = char(tmp % 10 + 48) + str;
                tmp = tmp / 10;
            }
        }
        str += ".png";
        gMap[i].LoadImg(mapName + str, screen);
        str.clear();
        gMap[i].SetRect(SCREEN_WIDTH*0.255,SCREEN_HEIGHT*0.4 + i*200);
        
    }

    int time = 0;
    int x = 0;
    int y = 0;

    SDL_Event event;
    bool haveSelected = false;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                for (int i = 0; i < MAP_NUM; i++)
                {
                    gMap[i].Free();
                }
                text_object.Free();
                textObjectBack.Free();
                gBackgroundSelectMap.Free();
                return EXIT;
                break;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                if (x >= text_object.GetRect().x && x <= text_object.GetRect().x + text_object.GetWidth() && y >= text_object.GetRect().y && y <= text_object.GetRect().y + text_object.GetHeight())
                {
                    text_object.Free();
                    text_object.SetColorType(TextObject::YELLOW_TEXT);
                    text_object.LoadFromRenderedText(font, screen);
                }
                else
                {
                    text_object.Free();
                    text_object.SetColorType(TextObject::WHITE_TEXT);
                    text_object.LoadFromRenderedText(font, screen);

                }
                if (x >= textObjectBack.GetRect().x && x <= textObjectBack.GetRect().x + textObjectBack.GetWidth() && y >= textObjectBack.GetRect().y && y <= textObjectBack.GetRect().y + textObjectBack.GetHeight())
                {
                    textObjectBack.Free();
                    textObjectBack.SetColorType(TextObject::YELLOW_TEXT);
                    textObjectBack.LoadFromRenderedText(font, screen);
                }
                else
                {
                    textObjectBack.Free();
                    textObjectBack.SetColorType(TextObject::WHITE_TEXT);
                    textObjectBack.LoadFromRenderedText(font, screen);

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                for (int i = 0; i < MAP_NUM; ++i)
                {
                    if (x >= gMap[i].GetRect().x && x <= gMap[i].GetRect().x + gMap[i].GetRect().w && y >= gMap[i].GetRect().y && y <= gMap[i].GetRect().y + gMap[i].GetRect().h)
                    {
                        Mix_PlayChannel(-1, sSelect1, 0);
                        for (int j = 0; j < MAP_NUM; j++)
                        {
                            gMap[j].Free();
                            string str = "";
                            int tmp = j;
                            if (tmp == 0)
                                str = "0";
                            else
                            {
                                while (tmp > 0)
                                {
                                    str = char(tmp % 10 + 48) + str;
                                    tmp = tmp / 10;
                                }
                            }
                            str += ".png";
                            gMap[j].LoadImg(mapName + str, screen);
                            str.clear();
                        }
                        string str = "";
                        int tmp = i;
                        if (tmp == 0)
                            str = "0";
                        else
                        {
                            while (tmp > 0)
                            {
                                str = char(tmp % 10 + 48) + str;
                                tmp = tmp / 10;
                            }
                        }
                        str += ".png";
                        gMap[i].LoadImg(mapHold+str, screen);
                        map = i;
                        str.clear();
                        haveSelected = true;
                    }
                }
                if (x >= text_object.GetRect().x && x <= text_object.GetRect().x + text_object.GetWidth() && y >= text_object.GetRect().y && y <= text_object.GetRect().y + text_object.GetHeight() && haveSelected == true)
                {
                    Mix_PlayChannel(-1, sButton, 0);
                    for (int i = 0; i < MAP_NUM; i++)
                    {
                        gMap[i].Free();
                    }
                    text_object.Free();
                    textObjectBack.Free();
                    gBackgroundSelectMap.Free();
                    return INTOGAME;
                }
                if (x >= textObjectBack.GetRect().x && x <= textObjectBack.GetRect().x + textObjectBack.GetWidth() && y >= textObjectBack.GetRect().y && y <= textObjectBack.GetRect().y + textObjectBack.GetHeight())
                {
                    Mix_PlayChannel(-1, sButton, 0);
                    for (int i = 0; i < MAP_NUM; i++)
                    {
                        gMap[i].Free();
                    }
                    text_object.Free();
                    textObjectBack.Free();
                    gBackgroundSelectMap.Free();
                    return BACK;
                }
                break;
            }
        }
        gBackgroundSelectMap.Render(screen, NULL);
        for (int i = 0; i < MAP_NUM; ++i)
        {
            gMap[i].Render(screen, NULL);
            text_object.RenderText(screen, text_object.GetRect().x, text_object.GetRect().y);
            textObjectBack.RenderText(screen, textObjectBack.GetRect().x, textObjectBack.GetRect().y);
        }

        SDL_RenderPresent(screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
    return PLAYGAME;
}

int SDLCommonFunc::ShowSetting(SDL_Renderer* screen, TTF_Font* font, const string& back, const string& fileName, int& widthSlider1, int& widthSlider2, int& gameMode, Mix_Chunk* sButton)
{
    BaseObject gBackgroundSetting;
    bool ret = gBackgroundSetting.LoadImg(fileName, screen);

    TextObject textObjectBack;
    textObjectBack.SetText("BACK");

    textObjectBack.SetRect(SCREEN_WIDTH * 0.294, SCREEN_HEIGHT * 0.032);
    textObjectBack.SetColorType(TextObject::WHITE_TEXT);
    textObjectBack.LoadFromRenderedText(font, screen);


    BaseObject slider[2];
    BaseObject slider2[2];
    BaseObject button[2];
    BaseObject option[3];


    for (int i = 0; i < 2; i++)
    {
        slider[i].LoadImg(gSlider, screen);
        slider[i].SetRect(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.392 + i * 160);
        slider2[i].LoadImg(gSlider2, screen);
        slider2[i].SetRect(SCREEN_WIDTH * 0.5, SCREEN_HEIGHT * 0.392 + i * 160);
        button[i].LoadImg(gButton, screen);
    }
    slider2[0].SetWidth(widthSlider1);
    button[0].SetRect(SCREEN_WIDTH * 0.5 + widthSlider1 - button[1].GetRect().w / 2, SCREEN_HEIGHT * 0.375 + 0 * 160);
    slider2[1].SetWidth(widthSlider2);
    button[1].SetRect(SCREEN_WIDTH * 0.5 + widthSlider2 - button[1].GetRect().w / 2, SCREEN_HEIGHT * 0.375 + 1 * 160);

    for (int i = 0; i < 3; i++)
    {
        option[i].LoadImg(gOption, screen);
        if (i == gameMode)
            option[i].LoadImg(gOption2, screen);
        option[i].SetRect(SCREEN_WIDTH * 0.4845 + i * 167, SCREEN_HEIGHT * 0.675);
    }


    int time = 0;
    int x = 0;
    int y = 0;

    SDL_Event event;
    while (1)
    {
        int volume = 0;
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                textObjectBack.Free();
                gBackgroundSetting.Free();
                return EXIT;
                break;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                if (x >= textObjectBack.GetRect().x && x <= textObjectBack.GetRect().x + textObjectBack.GetWidth() && y >= textObjectBack.GetRect().y && y <= textObjectBack.GetRect().y + textObjectBack.GetHeight())
                {
                    textObjectBack.Free();
                    textObjectBack.SetColorType(TextObject::YELLOW_TEXT);
                    textObjectBack.LoadFromRenderedText(font, screen);
                }
                else
                {
                    textObjectBack.Free();
                    textObjectBack.SetColorType(TextObject::WHITE_TEXT);
                    textObjectBack.LoadFromRenderedText(font, screen);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                if (x >= textObjectBack.GetRect().x && x <= textObjectBack.GetRect().x + textObjectBack.GetWidth() && y >= textObjectBack.GetRect().y && y <= textObjectBack.GetRect().y + textObjectBack.GetHeight())
                {
                    Mix_PlayChannel(-1, sButton, 0);
                    return BACK;
                }
                for (int i = 0; i < 3; i++)
                {
                    if (x >= option[i].GetRect().x && x <= option[i].GetRect().x + option[i].GetRect().w && y >= option[i].GetRect().y && y <= option[i].GetRect().y + option[i].GetRect().h)
                    {
                        Mix_PlayChannel(-1, sButton, 0);
                        for (int j = 0; j < 3; j++)
                        {
                            option[j].LoadImg(gOption, screen);
                        }
                        option[i].LoadImg(gOption2, screen);
                        gameMode = i;
                        break;
                    }
                }
                if (x >= slider[0].GetRect().x && x <= slider[0].GetRect().x + slider[0].GetRect().w && y >= slider[0].GetRect().y && y <= slider[0].GetRect().y + slider[0].GetRect().h)
                {
                    Mix_PlayChannel(-1, sButton, 0);
                    button[0].SetRect(x - button[0].GetRect().w / 2, button[0].GetRect().y);
                    slider2[0].SetWidth(x - slider[0].GetRect().x);
                    widthSlider1 = x - slider[0].GetRect().x;
                    volume = (x - slider[0].GetRect().x) * MAX_VOLUME / slider[0].GetRect().w;
                    Mix_VolumeChunk(sSelect1, volume);
                    Mix_VolumeChunk(sButton, volume);

                }
                else if (x >= slider[1].GetRect().x && x <= slider[1].GetRect().x + slider[1].GetRect().w && y >= slider[1].GetRect().y && y <= slider[1].GetRect().y + slider[1].GetRect().h)
                {
                    Mix_PlayChannel(-1, sButton, 0);
                    button[1].SetRect(x - button[1].GetRect().w / 2, button[1].GetRect().y);
                    slider2[1].SetWidth(x - slider[1].GetRect().x);
                    volume = (x - slider[1].GetRect().x) * MAX_VOLUME / slider[1].GetRect().w;
                    widthSlider2 = x - slider[1].GetRect().x;
                    Mix_VolumeMusic(volume);
                }
                break;
            }
        }
        gBackgroundSetting.Render(screen, NULL);
        textObjectBack.RenderText(screen, textObjectBack.GetRect().x, textObjectBack.GetRect().y);
        for (int i = 0; i < 2; i++)
        {
            slider[i].Render(screen, NULL);
            slider2[i].Render(screen, NULL);
            button[i].Render(screen, NULL);
        }
        for (int i = 0; i < 3; i++)
        {
            option[i].Render(screen, NULL);
        }
        SDL_RenderPresent(screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
    return NONE;
}
int SDLCommonFunc::ShowTutorial(SDL_Renderer* screen, TTF_Font* font, const string& back, const string& fileName, Mix_Chunk* sButton)
{
    BaseObject gBackgroundSetting;
    bool ret = gBackgroundSetting.LoadImg(fileName, screen);

    TextObject textObjectBack;
    textObjectBack.SetText("BACK");

    textObjectBack.SetRect(SCREEN_WIDTH * 0.294, SCREEN_HEIGHT * 0.032);
    textObjectBack.SetColorType(TextObject::WHITE_TEXT);
    textObjectBack.LoadFromRenderedText(font, screen);

    int time = 0;
    int x = 0;
    int y = 0;

    SDL_Event event;
    while (1)
    {
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                textObjectBack.Free();
                gBackgroundSetting.Free();
                return EXIT;
                break;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                if (x >= textObjectBack.GetRect().x && x <= textObjectBack.GetRect().x + textObjectBack.GetWidth() && y >= textObjectBack.GetRect().y && y <= textObjectBack.GetRect().y + textObjectBack.GetHeight())
                {
                    textObjectBack.Free();
                    textObjectBack.SetColorType(TextObject::YELLOW_TEXT);
                    textObjectBack.LoadFromRenderedText(font, screen);
                }
                else
                {
                    textObjectBack.Free();
                    textObjectBack.SetColorType(TextObject::WHITE_TEXT);
                    textObjectBack.LoadFromRenderedText(font, screen);

                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                if (x >= textObjectBack.GetRect().x && x <= textObjectBack.GetRect().x + textObjectBack.GetWidth() && y >= textObjectBack.GetRect().y && y <= textObjectBack.GetRect().y + textObjectBack.GetHeight())
                {
                    Mix_PlayChannel(-1, sButton, 0);
                    return BACK;
                }
                break;
            }
        }
        gBackgroundSetting.Render(screen, NULL);

        for (int i = 0; i < MAP_NUM; ++i)
        {
            textObjectBack.RenderText(screen, textObjectBack.GetRect().x, textObjectBack.GetRect().y);
        }

        SDL_RenderPresent(screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
    return NONE;
}
int SDLCommonFunc::ShowEnd(SDL_Renderer* screen, TTF_Font* font, const string& win, const string& lose, int status, Mix_Chunk* sButton)
{


    BaseObject gWin;
    BaseObject gLose;
    bool tret = gWin.LoadImg(win, screen);
    bool xret = gLose.LoadImg(lose, screen);

    TextObject textObjectExit;
    textObjectExit.SetText("HOME");

    textObjectExit.SetRect(SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT - 170);
    textObjectExit.SetColorType(TextObject::WHITE_TEXT);
    textObjectExit.LoadFromRenderedText(font, screen);



    int time = 0;
    int x = 0;
    int y = 0;

    SDL_Event event;
    while (1)
    {
        int volume = 0;
        time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                textObjectExit.Free();
                gWin.Free();
                gLose.Free();
                return EXIT;
                break;
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
                if (x >= textObjectExit.GetRect().x && x <= textObjectExit.GetRect().x + textObjectExit.GetWidth() && y >= textObjectExit.GetRect().y && y <= textObjectExit.GetRect().y + textObjectExit.GetHeight())
                {
                    textObjectExit.Free();
                    textObjectExit.SetColorType(TextObject::YELLOW_TEXT);
                    textObjectExit.LoadFromRenderedText(font, screen);
                }
                else
                {
                    textObjectExit.Free();
                    textObjectExit.SetColorType(TextObject::WHITE_TEXT);
                    textObjectExit.LoadFromRenderedText(font, screen);
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                x = event.button.x;
                y = event.button.y;
                if (x >= textObjectExit.GetRect().x && x <= textObjectExit.GetRect().x + textObjectExit.GetWidth() && y >= textObjectExit.GetRect().y && y <= textObjectExit.GetRect().y + textObjectExit.GetHeight())
                {
                    Mix_PlayChannel(-1, sButton, 0);
                    return PLAYGAME;
                }
                break;
            }
        }
        if (status == true)
            gWin.Render(screen);
        else
            gLose.Render(screen);
        textObjectExit.RenderText(screen, textObjectExit.GetRect().x, textObjectExit.GetRect().y);
        SDL_RenderPresent(screen);
        if (1000 / 30 > (SDL_GetTicks() - time))
            SDL_Delay(1000 / 30 - (SDL_GetTicks() - time));
    }
    return NONE;
}
