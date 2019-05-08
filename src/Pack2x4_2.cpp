#include "Pack2x4_2.h"

Pack2x4_2::Pack2x4_2() : Pack(743, 700, -743, 265, 2, 4, 3) {
	if (parts != nullptr) {
		parts[0].loadImg(IMGPATH::PACK::PACK2X4::UP);
		parts[0].setRect(172, 22, 400, 255);
		O[0].set(14, 52);
		parts[1].loadImg(IMGPATH::PACK::PACK2X4::DOWN);
		parts[1].setRect(172, 277, 400, 255);
		O[1].set(14, 18);
		parts[2].loadImg(IMGPATH::PACK::PACK2X4::CLOSE); 
		O[2].set(14, 18);
		theta = 3;
		update = true;
	}
	else {
		SDL_Log("Khoi tao Pack2_2x4 that bai");
	}
	backup_texture = nullptr;
}

Pack2x4_2::~Pack2x4_2() {
	SDL_DestroyTexture(backup_texture);
}

OBJTYPE Pack2x4_2::type() const {
	return OBJTYPE::PACK2X4_2;
}
const char* Pack2x4_2::toString() const {
	return "Pack2x4_2";
}


void Pack2x4_2::init() {
	std::vector<std::vector<int>> init_table = Func::randUnion(2, 4);
	{
		int n_fixed = init_table[2][0];
		int i0;
		int j0;
		for (int i = 0; i < n_fixed / 2; i++) {
			i0 = rand() % 2;
			j0 = rand() % 4;
			if (init_table[i0][j0] != 0 && init_table[i0][j0] != -1 && init_table[i0][j0] != -3) {
				if (CreateNewFixedBlock(i0, j0, init_table[i0][j0])) {
					ParseBlock(0, i0, j0, SDL_FLIP_VERTICAL);
					ParseBlock(2, i0, j0, SDL_FLIP_NONE);
					(*fiBl.at(i0, j0))->onPart = 0;
				}				
				if (init_table[i0][j0] == 2) {
					init_table[i0][j0 + 1] = -3;
				}
				else if (init_table[i0][j0] == -2) {
					init_table[i0 + 1][j0] = -3;
				}
				init_table[i0][j0] = -3;
			}
			else {
				i--;
			}
		}
		backup_texture = parts[0].getTexture();
	}
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 4; j++) {
			if (init_table[i][j] == 0) {
				CreateNewPickeableBlock(1, i, j, true);
			}
			else if (init_table[i][j] == -3) {
				CreateNewPickeableBlock(1, i, j, false);
			}
			else if (init_table[i][j] != -1) {
				if (CreateNewFixedBlock(i, j, init_table[i][j])) {
					ParseBlock(1, i, j, SDL_FLIP_NONE);
					(*fiBl.at(i, j))->onPart = 1;
				}
			}
		}
	}

	camera.setOPos(186, 295);
	camera.setRect(372, 573, SIZE::BLOCK::UNIT_SIZE, SIZE::BLOCK::UNIT_SIZE);
}


void Pack2x4_2::Close() {
	int newW;
	int newH;
	caculNewSizeTrazoid(400, 255, newW, newH);
	if (theta < 90) {
		if (theta == 3) {
			parts[0].setTexture(Func::resizeTextureWithTrapeZoidShape(backup_texture, newW, 1, -1), false);
		} else 
			parts[0].setTexture(Func::resizeTextureWithTrapeZoidShape(backup_texture, newW, 1, -1), true);

		parts[0].setRect(172 - (newW - 400) / 2, 22 + (255 - newH), newW, newH);
		theta+=9;
	}
	else if (theta <= 180) {
		parts[0].setTexture(Func::resizeTextureWithTrapeZoidShape(parts[2].getTexture(), newW, 1, 1), true);
		parts[0].setRect(172 - (newW - 400) / 2, 277, newW, newH);
		theta += 5;
	}
	else {
		Mix_PlayChannel(-1, CLOSE_VALI_SOUND, 0);
		parts[1].loadImg(IMGPATH::PACK::PACK2X4::CLOSE);
		ParseCamera(1, mouseOnBlock.x, mouseOnBlock.y);
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				if ((*fiBl.at(i, j)) != nullptr) {
					ParseBlock(1, i, j, SDL_FLIP_NONE);
				}
			}
		}
		theta = 0;
		if ((*piBl.at(mouseOnBlock.x, mouseOnBlock.y))->getAnswer()) {
			point = 10;
		}
		camera.ShowAnswer((*piBl.at(mouseOnBlock.x, mouseOnBlock.y))->getAnswer());
		close_stage++;
	}
}


void Pack2x4_2::HandleInputEvents(SDL_Event& event) {
	switch (events.type)
	{
	case SDL_MOUSEMOTION:
		if (close_stage == 1)
			checkMouse(186, 295, SIZE::BLOCK::UNIT_SIZE); // need more general
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (events.button.button == SDL_BUTTON_LEFT) {
			if (close_stage == 1 && mouseOnBlock.x != -1 && (*piBl.at(mouseOnBlock.x, mouseOnBlock.y)) != nullptr) {
				close_stage = 2;
				(*piBl.at(mouseOnBlock.x, mouseOnBlock.y))->Chosed();
				if ((*piBl.at(mouseOnBlock.x, mouseOnBlock.y))->getAnswer()) {
					point = 15;
				}
			}
			
		}
		break;

	default:
		break;
	}

}

void Pack2x4_2::render(){
	switch (close_stage) {
	case 0:
		if (128 - GetComponentXPos() < 10) {
			Slide(128 - GetComponentXPos(), 1);
			close_stage = 1;
		}
		else
			Slide(20, 0);
		update = true;
		break;
	case 1:
		checkMouseOver();
		if(camera.IsRunning())
			update = true;
		break;
	case 2:
		Close();
		update = true;
		break;
	case 3:
		if (theta == 0) {
			theta = SDL_GetTicks();
			return;
		} 
		else if (SDL_GetTicks() - theta < 300) {
			update = true;
			break;
		}
		Slide(20, 0);
		update = true;
		if (GetComponentXPos() > SCREEN_WIDTH) {
			close_stage++;
		}
		break;
	default:
		update = false;
		break;
	}
	
	if (update)
	{
		SDL_Log("Rendering...");
		update = false;
		ClearComponent();
		parts[1].render();
		if (close_stage <= 2) {
			for (int i = 0; i < row; i++) {
				for (int j = 0; j < col; j++) {
					if ((*piBl.at(i, j)) != nullptr) {
						(*piBl.at(i, j))->render();
					}
				}
			}
			camera.render();
			parts[0].Render();
		}
		else {
			if (theta != 0 && SDL_GetTicks() - theta >= 200) {
				camera.render();
			}

		}
	}
	
}

int Pack2x4_2::getPoint() const {
	return point;
}

bool Pack2x4_2::DoneWithPack() const {
	if (close_stage >= 4) {
		return true;
	}
	return false;
}