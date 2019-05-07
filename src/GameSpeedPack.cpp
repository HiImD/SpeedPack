#include "GameSpeedPack.h"
//Private
//Vong lap game 
void GameSpeedPack::GameLoop() {
	while (state != STOP) {
		switch (state)
		{
		case GameSpeedPack::HAVENOTINIT:
			break;
		case GameSpeedPack::INIT:
			Init();
			break;
		case GameSpeedPack::START:
			Start();
			break;
		case GameSpeedPack::RUNNING:
			Run();
			break;
		case GameSpeedPack::PAUSE:
			Pause();
			break;
		case GameSpeedPack::RESUMING:
			Resume();
			break;
		case GameSpeedPack::GAMEOVER:
			GameOver();
			break;
		case GameSpeedPack::RESTART:
			Restart();
			break;
		case GameSpeedPack::STOP:
			break;
		default:
			break;
		}
	}
}
//Public


OBJTYPE GameSpeedPack::type() const{
	return OBJTYPE::GAMESPEEDPACK;
}

const char* GameSpeedPack::toString() const {
	return "GameSpeedPack";
}

GameSpeedPack::GameSpeedPack(): timer(gRenderer, nullptr), scoreBoard(), bonus_point(0), pack(nullptr), state(STATE::HAVENOTINIT), menu(gFont, { 255 , 255, 255, 255 }, { 255, 100, 100, 255 }) {
	if (gWindow == nullptr) {
		SDL_Log("gWindow == nullptr");
		state = STATE::STOP;
		return;
	}
	if (gRenderer == nullptr) {
		SDL_Log("gRenderer == nullptr");
		state = STATE::STOP;
		return;
	}
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	background.LoadBackgroundImg(IMGPATH::BACKGROUNG);
	state = STATE::INIT;
	Init();
	srand(time(nullptr));

	timer.getRectPointer()->x = 0;
	timer.getRectPointer()->y = 0;
	scoreBoard.SetComponentPos(900, 0);

	menu.AddButton("res", "RESUME");
	menu.AddButton("rep", "REPLAY");
	menu.AddButton("op", "OPTION");
	menu.AddButton("qu", "EXIT TO MENU");
	menu.margin = { 10, 10, 10, 10, 10 };
	menu.SetComponentSize(250, 100);
	menu.setBGColor({ 100, 100, 100, 100 });
	menu.AutoSort();
	menu.ParseAllToComp();

	state = START;
	GameLoop();				//Bat dau vong lap game
}

GameSpeedPack::~GameSpeedPack() {
	if (pack != nullptr) {
		delete pack;
		pack = nullptr;
	}
}

void GameSpeedPack::Init() {
	scoreBoard.SetComponentPos(900, 0);
	scoreBoard.margin = { 10, 10, 10, 10, 10 };
	scoreBoard.Resize();
	scoreBoard.AutoSort(true);

}

void GameSpeedPack::Start() {
	chain_pack_complete = 0;
	state = RUNNING;		//Cai game state ve RUNNING  
	timer.StartCount(120);  //Cai dat lai dong ho dem gio
}

void GameSpeedPack::Run() {
	SDL_Log("Game Run");
	bool score_updated = false;
	if (timer.IsPausing())
		timer.Pause_Resume();
	while (state == RUNNING) {

		//Sinh them Pack neu pack == nullptr
		CreateNewPack();

		//Kiem tra neu da het thoi gian
		if (timer.CheckTimeOut()) {
			SDL_Log("TimeOut");
			state = GAMEOVER;
			break;
		}

		//Neu Close Stage == 2, nguoi choi da co dap an va diem cua Pack do se duoc cap nhat
		if (pack->getCloseStage() == 2 && !score_updated) {
			if (pack->getPoint()) {
				chain_pack_complete++;
			}
			else {
				chain_pack_complete = 0;
			}
			bonus_point = (chain_pack_complete / 5) * 10;
			scoreBoard.AddPoint(pack->getPoint() + bonus_point); // pack->getPoint() must be positive
			score_updated = true;
		}

		//Kiem tra neu Pack da hoan thanh vong doi
		else if (pack->DoneWithPack()) {
			CreateNewPack(true);
			score_updated = false;
		}

		//Vong lap xu li xu kien input
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) {
				state = STOP;
				Quit();
				break;
			}
			pack->HandleInputEvents(events);
			if (events.type == SDL_KEYDOWN) {
				if (events.key.keysym.sym == SDLK_ESCAPE) {
					timer.Pause_Resume();
					state = PAUSE;
				}
			}
		}

		pack->render();
		if (SDL_GetRenderTarget(gRenderer) != nullptr) {
			SDL_SetRenderTarget(gRenderer, nullptr);
		}
		SDL_RenderClear(gRenderer);
		background.render();
		timer.Render();
		pack->Show();
		scoreBoard.ShowBoard();
		SDL_RenderPresent(gRenderer);
	}
}

void GameSpeedPack::Pause() {
	SDL_Log("Game Pause");
	menu.SetComponentPos(-SCREEN_WIDTH/2 + pack->GetComponentXPos() - menu.GetComponentWSize()/2, 100);
	
	while (state == PAUSE) {
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) {
				state = STOP;
				Quit();
				break;
			}
			if (events.type == SDL_KEYDOWN) {
				if (events.key.keysym.sym == SDLK_ESCAPE) {
					state = RESUMING;
				}
			}
			std::string id_down = menu.HandleInputEvents(events);
				if (id_down == "res") {
					state = RESUMING;
				}
				else if (id_down == "rep") {
					state = RESTART;
				}
				else if (id_down == "qu"){
					state = STOP;
				}
		}

		if (SDL_GetRenderTarget(gRenderer) != nullptr) {
			//SDL_Log("Target of gRenderer != nullptr");
			SDL_SetRenderTarget(gRenderer, nullptr);
		}
		//pack->render();
		SDL_RenderClear(gRenderer);
		
		background.render();
		if (pack != nullptr && !pack->SlideTo(SCREEN_WIDTH, -1, 20, 0)) {
			menu.Slide(20, 0);
			pack->Show();
			
		}
		timer.Render();
		scoreBoard.ShowBoard();
		menu.Show();
		SDL_RenderPresent(gRenderer);
	}
}

void GameSpeedPack::Resume() {
	SDL_Log("Game Resume");
	state = RESUMING;
	while (state == RESUMING) {
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) {
				state = STOP;
				Quit();
				break;
			}
			if (events.type == SDL_KEYDOWN) {
				if (events.key.keysym.sym == SDLK_ESCAPE) {
					state = PAUSE;
				}
			}
		}

		if (SDL_GetRenderTarget(gRenderer) != nullptr) {
			//SDL_Log("Target of gRenderer != nullptr");
			SDL_SetRenderTarget(gRenderer, nullptr);
		}
		//pack->render();
		SDL_RenderClear(gRenderer);

		background.render();
		if (pack == nullptr) {
			state = RUNNING;
		} 
		else if (pack->SlideTo(SCREEN_WIDTH / 2 - pack->GetComponentWSize() / 2, -1, 20, 0)) {
			state = RUNNING;
		}
		menu.Slide(-20, 0);
		pack->Show();
		timer.Render();
		scoreBoard.Show();
		menu.Show();
		SDL_RenderPresent(gRenderer);
	}
}

void GameSpeedPack::Restart() {
	if (pack != nullptr) {
		delete pack;
		pack = nullptr;
	}
	bonus_point = 0;
	scoreBoard.StartOver();
	Start();
}

void GameSpeedPack::GameOver() {
	short show_stage = 0;
	bool slided = false;
	bool menu_showed = false;
	scoreBoard.PreparResult();
	menu.EraseButton(0);
	menu.AutoSort();
	menu.ParseAllToComp();
	if(pack != nullptr && pack->getCloseStage() < 3)
		scoreBoard.SetComponentPos(-SCREEN_WIDTH / 2 + pack->GetComponentXPos() - scoreBoard.GetComponentWSize() / 2, (SCREEN_HEIGHT - scoreBoard.GetComponentHSize()) / 2);
	else
		scoreBoard.SetComponentPos(-scoreBoard.GetComponentWSize(), (SCREEN_HEIGHT - scoreBoard.GetComponentHSize()) / 2);
	while (state == GAMEOVER) {
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) {
				state = STOP;
				Quit();
				break;
			}
			if (menu_showed) {
				std::string id_down = menu.HandleInputEvents(events);
					if (id_down == "rep") {
						menu.AddButton("res", "RESUME", 0);
						menu.AutoSort();
						menu.ParseAllToComp();
						show_stage = 3;
						Init();
						state = RESTART;
					}
					else if (id_down == "qu") {
						state = STOP;
					}
			}
		}
		switch (show_stage) {
		case 0:
			if (pack != nullptr && !(pack->DoneWithPack() || pack->getCloseStage() < 2)) {
				pack->render();
			}
			SDL_SetRenderTarget(gRenderer, nullptr);
			background.render();
			if (pack != nullptr && (pack->DoneWithPack() || pack->getCloseStage() < 2) && !slided) {
				if (!pack->SlideTo(SCREEN_WIDTH, -1, 20, 0)) {
					
				}
			}
			if (((pack != nullptr && (pack->DoneWithPack() || pack->getCloseStage() < 2)) || pack == nullptr) && !slided) {
				if (scoreBoard.SlideTo((SCREEN_WIDTH - scoreBoard.GetComponentWSize()) / 2, -1, 20, 0)) {
					timer.StartCount(2);
					slided = true;
					menu.SetComponentPos(-SCREEN_WIDTH / 2 + scoreBoard.GetComponentXPos() - menu.GetComponentWSize() / 2, 100);
					show_stage = 1;
				}				
			}
			scoreBoard.Show();
			break;
		case 1:
			background.render();
			if (timer.CheckTimeOut()) {
				show_stage = 2;
			}
			scoreBoard.Show();
			break;
		case 2:
			background.render();
			if (!scoreBoard.SlideTo(SCREEN_WIDTH, -1, 20, 0)) {
				menu.Slide(20, 0);
				scoreBoard.Show();
			}
			menu_showed = true;
			menu.Show();
			break;
		default:
			break;
		}		
		pack->Show();
		SDL_RenderPresent(gRenderer);
	}
	
}

void GameSpeedPack::Stop() {
	state = STOP;
}

void GameSpeedPack::CreateNewPack(bool compulsory) {
	if (compulsory && pack != nullptr) {
		delete pack;
		pack = nullptr;
	}
	if (pack == nullptr) {
		if (rand() % 2 == 1) {
			pack = new Pack2x4_2();
		}
		else {
			pack = new Pack3_3x2;
		}
		pack->init();
	}
	
}