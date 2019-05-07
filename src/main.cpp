#include "GameSpeedPack.h"
#include "AutoComponent_Vertical.h"
#include "Menu.h"

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* gTexture = NULL;
TTF_Font* gFont = nullptr;
SDL_Event events;
int SCREEN_HEIGHT = 1000;
int SCREEN_WIDTH = 1000;




int main(int args, char* argc[]) {
	Func::init();
	gFont = TTF_OpenFont(FONTPATH, 30);
	
	Menu menu(gFont, { 255 , 255, 255, 255 }, {255, 100, 100, 255 });
	menu.AddButton("st", "START");
	menu.AddButton("op", "OPTION");
	menu.AddButton("qu", "QUIT");
	menu.margin = { 10, 10, 10, 10, 10 };
	menu.SetComponentSize(1000, 100);
	menu.AutoSort();
	menu.ParseAllToComp();
	menu.SetComponentPos(0, 100);
	std::string id = "";
	while (!ChangeProgramState::CheckProgramQuit()) {
		while (SDL_PollEvent(&events)) {
			if (events.type == SDL_QUIT) {
				ChangeProgramState::program_quit = true;
			}
			id = menu.HandleInputEvents(events);
			if (id == "st") {
				GameSpeedPack game;
				game.Start();
				}
			else if (id == "qu") {
				ChangeProgramState::program_quit = true;
			}
			
		}
		SDL_RenderClear(gRenderer);
		menu.Show();
		SDL_RenderPresent(gRenderer);
	}	
 	Func::Close();
	return 0;
}