// include header files
#include "CommonFunc.h"
#include "BaseObject.h"
#include "GameMap.h"
#include "MainObject.h"
#include "ImpTimer.h"
#include "ThreatObject.h"
#include "Explosion.h"
#include "TextObject.h"
#include "Geometric.h"
#include "MainObjectInfo.h"
#include "GameStat.h"
#include "SupportItem.h"

// Game Map initalize
GameMap game_map;
// Main Object initalize
MainObject p_player;

// Font initalize
TTF_Font* fontIngame = NULL;
TTF_Font* fontMenu = NULL;
TTF_Font* fontSetting = NULL;
int MAX_THREAT_PER_KIND = 80;

bool Init();
std::vector <ThreatObject*> MakeThreatList();
std::vector <SupportItem* > MakeManaList();

void Close();

int main(int argc, char* argv[])
{
	if (Init() == false)
		return -1;
	int status = 2;
	int mainObject = 0;
	int map = 0;
	int gameMode = EASY;

	int maxTime = 600;
	int playerGun = 0;

	int maxExpPerLevel = 10;

	int lossHP = 0;
	int money = 0;
	int level = 0;
	int markValue = 0;
	int exp = 0;

	int volume = MAX_VOLUME;
	int currentHP = maxHP;
	int widthSlider1 = 370;
	int widthSlider2 = 370;
again_label:
	status = 2;

	maxExpPerLevel = 20;

	lossHP = 0;
	money = 0;
	level = 0;
	markValue = 0;
	exp = 0;

	currentHP = maxHP;


	bool quit = false;

	// Show game menu
	// Mix_FreeMusic(sMenuMusic);
	bool intogame = false;
	bool musicIsPlayed = false;
	
	fontIngame = TTF_OpenFont("asset/font/dlxfont.ttf", 12);
	fontMenu = TTF_OpenFont("asset/font/UTM Neutra.ttf", 40);
	fontSetting = TTF_OpenFont("asset/font/UTMThanchientranh.ttf", 30);

	sMenuMusic = Mix_LoadMUS("asset/sound/menuMusic.wav");
	gIngame = Mix_LoadMUS("asset/sound/ingameMusic.wav");
	sGunSound[0] = Mix_LoadWAV("asset/sound/gunSound.wav");
	sButton = Mix_LoadWAV("asset/sound/selectButton.wav");
	sSelect1 = Mix_LoadWAV("asset/sound/selectChar.wav");
	sMana = Mix_LoadWAV("asset/sound/mana.wav");
	enemy = Mix_LoadWAV("asset/sound/enemy.wav");
	loss = Mix_LoadWAV("asset/sound/sxf_loss.wav");
	over = Mix_LoadMUS("asset/sound/over.wav");
	emptyGun = Mix_LoadWAV("asset/sound/emptyGun.wav");
	if (emptyGun == NULL)
		return -1;
	Mix_PlayMusic(sMenuMusic, -1);
	//Mix_Volume(-1, volume);
	while (!intogame)
	{

		//cout << volume << endl;
		int ret_select = SDLCommonFunc::ShowMenu(gScreen, fontMenu, "PLAY GAME", "TUTORIAL", "SETTING", "EXIT", gBackgroundMenu, sButton);
		while (ret_select == SDLCommonFunc::PLAYGAME)
		{
			bool selectChar = false;
			while (selectChar == false)
			{
				if (intogame == true)
					break;

				ret_select = SDLCommonFunc::ShowMainObjectMenu(gScreen, fontSetting, gBackgroundSelectMainObject, mainObject, sButton, sSelect1);
				if (ret_select == SDLCommonFunc::BACK)
					break;
				while (ret_select == SDLCommonFunc::SELECTMAP)
				{
					bool selectMap = false;
					while (selectMap == false)
					{
						if (intogame == true)
							break;

						ret_select = SDLCommonFunc::ShowMapMenu(gScreen, fontSetting, gBackgroundSelectMap, map, sButton, sSelect1);

						if (ret_select == SDLCommonFunc::BACK)
						{
							break;
						}
						if (ret_select == SDLCommonFunc::INTOGAME)
						{
							intogame = true;
							break;
						}

						if (ret_select == SDLCommonFunc::EXIT)
						{
							//quit = true;
							break;
						}
					}
				}

				if (ret_select == SDLCommonFunc::EXIT)
				{
					//quit = true;
					break;
				}
			}

		}
		if (ret_select == SDLCommonFunc::TUTORIAL)
		{
			ret_select = SDLCommonFunc::ShowTutorial(gScreen, fontSetting, "BACK", gBackgroundTutorial, sButton);
		}
		if (ret_select == SDLCommonFunc::SETTING)
		{
			ret_select = SDLCommonFunc::ShowSetting(gScreen, fontSetting, "BACK", gBackgroundSetting, widthSlider1, widthSlider2, gameMode, sButton);
		}
		if (ret_select == SDLCommonFunc::EXIT)
		{
			quit = true;
			break;
		}
	}
	Uint32 timeVal = 0;
	Mix_FreeMusic(sMenuMusic);
	if (gameMode == EASY)
	{
		maxTime = 200;
	}
	if (gameMode == MEDIUM)
	{
		maxTime = 400;
	}
	if (gameMode == HARD)
	{
		maxTime = 600;
	}
	p_player.Reset();
	BaseObject moneyDisplay;
	moneyDisplay.LoadImg("asset/img/100.png", gScreen);
	// Load Map 
	gGameMap[10] = char(map + 48);
	game_map.LoadMap(gGameMap);
	game_map.LoadMapTiles(gScreen, map);

	// Loa Player
	p_player.LoadImg(gMainObject, gScreen, mainObject);
	p_player.SetClips();
	// Create Threats
	std::vector <ThreatObject*> threatList = MakeThreatList();
	std::vector <SupportItem*> manaList = MakeManaList();

	// Animation after threat dead
	ExplosionObject exp_threat;
	bool tRet = exp_threat.LoadImg("asset/img/exp3.png", gScreen);
	if (tRet == 0)
		return -1;
	exp_threat.SetClips();
	int lossEnergy = 0;



	// game 
	Mix_PlayMusic(gIngame, -1);
	Uint32 startTick = SDL_GetTicks();
	while (!quit)
	{
		ImpTimer fps;
		fps.Start();
		while (SDL_PollEvent(&gEvent) != 0)
		{
			//User requests quit
			if (gEvent.type == SDL_QUIT)
			{
				quit = true;
			}
			p_player.HandleInputAction(gEvent, gScreen, lossEnergy, sGunSound, emptyGun);
		}

		SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(gScreen);


		Map gMap = game_map.GetMap();

		p_player.SetMapXY(gMap.startX_, gMap.startY_);
		p_player.DoPlayer(gMap);
		game_map.SetMap(gMap);

		// Show Map
		game_map.DrawMap(gScreen);
		p_player.HandleBullet(gScreen);
		// Show Player
		p_player.Show(gScreen, mainObject);
		//cout << manaList.size() << endl;
		for (int i = 0; i < manaList.size(); i++)
		{
			SupportItem* p_mana = manaList.at(i);
			bool bCol3 = false;
			if (p_mana != NULL)
			{
				p_mana->SetMapXY(gMap.startX_, gMap.startY_);
				//p_threat->MakeBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
				SDL_Rect rectMana = p_mana->GetRectFrame();
				p_mana->Show(gScreen);

				//check collision between Player and threats bullet
				SDL_Rect rectPlayer = p_player.GetRectFrame();

				bCol3 = SDLCommonFunc::CheckCollision(rectPlayer, rectMana);
				if (bCol3 == 1)
				{
					//cout << "No" << endl;
					//cout << i << endl;
					manaList.erase(manaList.begin() + i);
					p_mana->Free();
					//break;
					//break;
					lossEnergy -= 30;
					//break;
					// else //if (MessageBox(NULL, L("GAME OVER"), MB_OK | MB_ICONSTOP) == IDOK)

				}

			}
			if (bCol3 == true)
				Mix_PlayChannel(-1, sMana, 0);
		}
		for (int i = 0; i < timeVal; i++)
		{
			ThreatObject* p_threat = threatList.at(i);
			bool bCol2 = false;
			if (p_threat != NULL)
			{
				p_threat->SetMapXY(gMap.startX_, gMap.startY_);
				p_threat->DoPlayer(gMap, p_player.GetXPos(), p_player.GetYPos(), threatList);
				//p_threat->MakeBullet(gScreen, SCREEN_WIDTH, SCREEN_HEIGHT);
				SDL_Rect rectThreat = p_threat->GetRectFrame();
				p_threat->Show(gScreen);

				//check collision between Player and threats bullet
				SDL_Rect rectPlayer = p_player.GetRectFrame();

				bCol2 = SDLCommonFunc::CheckCollision(rectPlayer, rectThreat);
				if (bCol2 == 1)
				{
					lossHP += 10;
					//break;
					// else //if (MessageBox(NULL, L("GAME OVER"), MB_OK | MB_ICONSTOP) == IDOK)
				}

			}
			if (bCol2 == true)
				Mix_PlayChannel(-1, loss, 0);
		}

	
		int frameExpWidth = exp_threat.GetFrameWidth();
		int frameExpHeight = exp_threat.GetFrameHeight();


		// threats die
		std::vector<BulletObject*> bulletArr = p_player.GetBulletList();
		for (int r = 0; r < bulletArr.size(); r++)
		{
			BulletObject* p_bullet = bulletArr.at(r);
			if (p_bullet != NULL)
			{
				for (int t = 0; t < threatList.size(); t++)
				{
					ThreatObject* objThreat = threatList.at(t);
					bool bCol = false;
					if (objThreat != NULL)
					{
						SDL_Rect tRect;
						tRect.x = objThreat->GetRect().x;
						tRect.y = objThreat->GetRect().y;
						tRect.w = objThreat->GetWidthFrame();
						tRect.h = objThreat->GetHeightFrame();

						SDL_Rect bRect = p_bullet->GetRect();

						bCol = SDLCommonFunc::CheckCollision(bRect, tRect);
						if (bCol)
						{
							markValue++;
							money += 10;
							//lossEnergy -= 20;
							exp += 2;
							//for (int ex = 0; ex < EXPLOSION_FRAMES; ex++)
							//{
							//	int xPos = p_bullet->GetRect().x - frameExpWidth * 0.5;
							//	int yPos = p_bullet->GetRect().y - frameExpHeight * 0.5;
							//	exp_threat.SetFrame(ex);
							//	exp_threat.SetRect(xPos, yPos);
							//	exp_threat.Show(gScreen);
							//}
							moneyDisplay.SetRect(p_bullet->GetRect().x, p_bullet->GetRect().y);
							moneyDisplay.Render(gScreen);
							p_player.RemoveBullet(r);
							objThreat->Free();
							threatList.erase(threatList.begin() + t);
						}
					}
					if (bCol == true)
					{
						Mix_PlayChannel(-1, enemy, 0);
					}
				}
			}

		}
		// show game Stat;
		BaseObject gameStat;
		BaseObject playerThumb;
		bool ret = gameStat.LoadImg(gGameStat, gScreen);
		gameStat.SetRect(SCREEN_WIDTH / 2 - gameStat.GetRect().w / 2, SCREEN_HEIGHT - gameStat.GetRect().h);
		if (ret == true)
			gameStat.Render(gScreen, NULL);
		gThum[28] = char(mainObject + 48);
		bool thumret = playerThumb.LoadImg(gThum, gScreen);
		playerThumb.SetRect(550, 845);
		if (thumret == true)
			playerThumb.Render(gScreen, NULL);


		// Text Object
		TextObject timeGame;
		timeGame.SetColorType(TextObject::WHITE_TEXT);

		TextObject markGame;
		markGame.SetColorType(TextObject::WHITE_TEXT);

		TextObject moneyCount;
		moneyCount.SetColorType(TextObject::WHITE_TEXT);

		TextObject levelCount;
		levelCount.SetColorType(TextObject::WHITE_TEXT);

		// Show energy
		if (exp == maxExpPerLevel)
		{
			level++;
			maxExpPerLevel += 2;
			exp = 0;
		}
		if (lossEnergy <= 0)
			lossEnergy = 0;
		if (lossEnergy >= maxEnergy)
			lossEnergy = maxEnergy;

		MainObjectInfo::ShowHPWithMain(gScreen, p_player.GetRectFrame(), maxHP / 10, lossHP / 10);
		MainObjectInfo::ShowEnergyInGameStat(gScreen, 645, 920, maxEnergy, 12, lossEnergy);
		MainObjectInfo::ShowHPInGameStat(gScreen, 645, 935, maxHP / 4, 12, lossHP / 4);

		// if Hp = 0;
		if (lossHP >= maxHP)
		{
			status = 0;
		}


		// Game Stat
		// Show time 
		string strTime = "TIME: ";
		timeVal = (SDL_GetTicks() - startTick) / 1000;
		Uint32 valTime = maxTime - timeVal;
		if (valTime <= 0)
		{
			status = 1;
		}
		else
		{
			std::string strVal = std::to_string(valTime);
			strTime += strVal;
			timeGame.SetText(strTime);
			timeGame.LoadFromRenderedText(fontIngame, gScreen);
			timeGame.RenderText(gScreen, 905, 900);
		}



		// mark of player
		std::string valStringMark = std::to_string(markValue);
		std::string strMark("KILL: ");
		strMark += valStringMark;
		markGame.SetText(strMark);
		markGame.LoadFromRenderedText(fontIngame, gScreen);
		markGame.RenderText(gScreen, 905, 917);



		// Money
		std::string valMoney = std::to_string(money);
		std::string strMoney("POINT: ");
		strMoney += valMoney;
		moneyCount.SetText(strMoney);
		moneyCount.LoadFromRenderedText(fontIngame, gScreen);
		moneyCount.RenderText(gScreen, 905, 934);

		// Level
		std::string stringLevel = std::to_string(level);
		levelCount.SetText(stringLevel);
		levelCount.LoadFromRenderedText(fontIngame, gScreen);
		levelCount.RenderText(gScreen, 618, 925);

		if (status != 2)
		{
			Mix_FreeMusic(gIngame);
			Mix_PlayMusic(over, 0);
			int ret = SDLCommonFunc::ShowEnd(gScreen, fontMenu, gWin, gLose, status, sButton);
			if (ret == SDLCommonFunc::EXIT)
			{
				quit = true;
				break;
			}
			if (ret == SDLCommonFunc::PLAYGAME)
			{
				//Delete full threatList
				for (int i = 0; i < threatList.size(); i++)
				{
					ThreatObject* p_threat = threatList.at(i);
					{
						if (p_threat)
						{
							p_threat->Free();
							p_threat = NULL;
						}

					}
				}
				for (int i = 0; i < manaList.size(); i++)
				{
					SupportItem* pMana = manaList.at(i);
					{
						if (pMana)
						{
							pMana->Free();
							pMana = NULL;
						}
					}
				}
				goto again_label;
			}
		}
		SDL_RenderPresent(gScreen);
		int imp_time = fps.GetTicks();
		int time_for_one_frame = 1000 / FRAME_PER_SECOND;
		if (imp_time < time_for_one_frame)
		{
			SDL_Delay(time_for_one_frame - imp_time);
		}
	}
	//Delete full threatList
	for (int i = 0; i < threatList.size(); i++)
	{
		ThreatObject* p_threat = threatList.at(i);
		{
			if (p_threat)
			{
				p_threat->Free();
				p_threat = NULL;
			}

		}
	}
	for (int i = 0; i < manaList.size(); i++)
	{
		SupportItem* pMana = manaList.at(i);
		{
			if (pMana)
			{
				pMana->Free();
				pMana = NULL;
			}
		}
	}
	Mix_CloseAudio();
	Close();
	return 0;
}
bool Init()
{
	bool success = true;
	int ret = SDL_Init(SDL_INIT_VIDEO);
	if (ret < 0)
		return false;
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	// create Window
	gWindow = SDL_CreateWindow("Advanture Time - Space Survivors", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == NULL)
		success = false;
	else
	{
		
		iconSurface = SDL_LoadBMP("asset/icon/icon.bmp");
		if (iconSurface == NULL)
			return false;
		SDL_SetWindowIcon(gWindow, iconSurface);
		gScreen = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (gScreen == NULL)
			success = false;
		else
		{
			SDL_SetRenderDrawColor(gScreen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int imgFlag = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlag) && imgFlag))
				success = false;
		}
		if (TTF_Init() == -1)
			success = false;
		else
		{
			if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
				return false;

		}

	}
	return success;
}

void Close()
{
	//g_background.Free();
	SDL_DestroyRenderer(gScreen);
	gScreen = NULL;
	SDL_FreeSurface(iconSurface);

	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	IMG_Quit();
	SDL_Quit();
}

std::vector <ThreatObject*> MakeThreatList()
{
	srand(time(0));
	std::vector<ThreatObject*> threats;

	ThreatObject* ThreatObjs0 = new ThreatObject[100];
	for (int i = 0; i < 100; i++)
	{
		ThreatObject* p_threat = (ThreatObjs0 + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("asset/img/threat/0/left.png", gScreen);
			p_threat->SetClip();
			int y = rand() % ((MAX_MAP_Y - 2) * TILE_SIZE) + TILE_SIZE;
			int x = rand() % ((MAX_MAP_X - 2) * TILE_SIZE) + TILE_SIZE;
			p_threat->SetXPos(x);
			p_threat->SetYPos(y);
			threats.push_back(p_threat);
		}
	}
	srand(time(0));
	ThreatObject* ThreatObjs1 = new ThreatObject[100];
	for (int i = 0; i < 100; i++)
	{
		ThreatObject* p_threat = (ThreatObjs1 + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("asset/img/threat/1/left.png", gScreen);
			p_threat->SetClip();
			int y = rand() % ((MAX_MAP_Y - 2) * TILE_SIZE) + TILE_SIZE;
			int x = rand() % ((MAX_MAP_X - 2) * TILE_SIZE) + TILE_SIZE;

			p_threat->SetXPos(x);
			p_threat->SetYPos(y);
			//BulletObject* p_bullet = new BulletObject();
			//p_threat->InitBullet(p_bullet, g_screen);
			threats.push_back(p_threat);
		}
	}
	srand(time(0));
	ThreatObject* ThreatObjs2 = new ThreatObject[150];
	for (int i = 0; i < 150; i++)
	{
		ThreatObject* p_threat = (ThreatObjs2 + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("asset/img/threat/2/left.png", gScreen);
			p_threat->SetClip();
			int y = rand() % ((MAX_MAP_Y - 2) * TILE_SIZE) + TILE_SIZE;
			int x = rand() % ((MAX_MAP_X - 2) * TILE_SIZE) + TILE_SIZE;
			p_threat->SetXPos(x);
			p_threat->SetYPos(y);
			//BulletObject* p_bullet = new BulletObject();
			//p_threat->InitBullet(p_bullet, g_screen);
			threats.push_back(p_threat);
		}
	}
	ThreatObject* ThreatObjs3 = new ThreatObject[150];
	for (int i = 0; i < 150; i++)
	{
		ThreatObject* p_threat = (ThreatObjs3 + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("asset/img/threat/3/left.png", gScreen);
			p_threat->SetClip();
			int y = rand() % ((MAX_MAP_Y - 2) * TILE_SIZE) + TILE_SIZE;
			int x = rand() % ((MAX_MAP_X - 2) * TILE_SIZE) + TILE_SIZE;
			p_threat->SetXPos(x);
			p_threat->SetYPos(y);
			//BulletObject* p_bullet = new BulletObject();
			//p_threat->InitBullet(p_bullet, g_screen);
			threats.push_back(p_threat);
		}
	}
	srand(time(0));
	ThreatObject* ThreatObjs4 = new ThreatObject[200];
	for (int i = 0; i < 200; i++)
	{
		ThreatObject* p_threat = (ThreatObjs4 + i);
		if (p_threat != NULL)
		{
			p_threat->LoadImg("asset/img/threat/4/left.png", gScreen);
			p_threat->SetClip();
			int y = rand() % ((MAX_MAP_Y - 2) * TILE_SIZE) + TILE_SIZE;
			int x = rand() % ((MAX_MAP_X - 2) * TILE_SIZE) + TILE_SIZE;
			p_threat->SetXPos(x);
			p_threat->SetYPos(y);
			//BulletObject* p_bullet = new BulletObject();
			//p_threat->InitBullet(p_bullet, g_screen);
			threats.push_back(p_threat);
		}
	}
	return threats;
}

std::vector <SupportItem*> MakeManaList()
{
	srand(time(0));
	std::vector<SupportItem*> mana;

	SupportItem* mana1 = new SupportItem[80];
	for (int i = 0; i < 80; i++)
	{
		SupportItem* p_mana = (mana1 + i);
		if (p_mana != NULL)
		{
			p_mana->Free();
			p_mana->LoadImg("asset/img/mana.png", gScreen);
			p_mana->SetXPos(rand() % ((MAX_MAP_X - 2) * TILE_SIZE) + TILE_SIZE);
			p_mana->SetYPos(rand() % ((MAX_MAP_X - 2) * TILE_SIZE) + TILE_SIZE);
			mana.push_back(p_mana);
		}
	}
	return mana;
}