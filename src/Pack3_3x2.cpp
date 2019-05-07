#include "Pack3_3x2.h"

Pack3_3x2::Pack3_3x2():Pack(597,830, -597, 152, 3, 2, 5) {
	if (parts != nullptr && O != nullptr) {
		parts[0].loadImg(IMGPATH::PACK::PACK3_3X2::UPLEFT);
		parts[0].setRect(94, 35, 218, 349);
		O[0].set(15,37 + 18);
		parts[1].loadImg(IMGPATH::PACK::PACK3_3X2::BOTTOMLEFT);
		parts[1].setRect(57, 384, 257, 312);
		O[1].set(37 + 15, 18);
		parts[2].loadImg(IMGPATH::PACK::PACK3_3X2::BOTTOMRIGHT);
		parts[2].setRect(314, 384, 257, 312);
		O[2].set(15, 18);
		parts[3].loadImg(IMGPATH::PACK::PACK3_3X2::UPLEFT_CLOSE);
		parts[3].setRect(314, 349, 257, 312);
		O[3].set(15, 18);
		parts[4].loadImg(IMGPATH::PACK::PACK3_3X2::BOTTOMRIGHT_CLOSE);
		parts[4].setRect(314, 349, 257, 312);
		O[4].set( 37 + 15, 18);
		theta = 3;
		update = false;
	}
	else {
		SDL_Log("Khoi tao Pack2_3x2 that bai");
	}
	backup_texture = nullptr;
}


Pack3_3x2::~Pack3_3x2() {
	SDL_DestroyTexture(backup_texture);
}

OBJTYPE Pack3_3x2::type() const {
	return OBJTYPE::PACK3_3x2;
}

const char* Pack3_3x2::toString() const {
	return "Pack3_3x2";
}


void Pack3_3x2::init() {
	std::vector<std::vector<int>> init_table = Func::randUnion(3, 2);
	{
		int n_fixed = init_table[3][0];
		SDL_Log(std::to_string(n_fixed).c_str());
		int i0;
		int j0;
		for (int i = 0; i < n_fixed / 3; i++) {
			i0 = rand() % 3;
			j0 = rand() % 2;
			if (init_table[i0][j0] != 0 && init_table[i0][j0] != -1 && init_table[i0][j0] != -3) {
				if (CreateNewFixedBlock(i0, j0, init_table[i0][j0])) {
					(*fiBl.at(i0, j0))->onPart = 0;
					ParseBlock(0, i0, j0, SDL_FLIP_VERTICAL);
					ParseBlock(3, i0, j0, SDL_FLIP_NONE);
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

		for (int i = 0; i < n_fixed / 3; i++) {
			i0 = rand() % 3;
			j0 = rand() % 2;
			if (init_table[i0][j0] != 0 && init_table[i0][j0] != -1 && init_table[i0][j0] != -3) {
				if (CreateNewFixedBlock(i0, j0, init_table[i0][j0])) {
					(*fiBl.at(i0, j0))->onPart = 2;
					ParseBlock(2, i0, j0, SDL_FLIP_HORIZONTAL);
					ParseBlock(4, i0, j0, SDL_FLIP_NONE);
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
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			if (init_table[i][j] == 0) {
				CreateNewPickeableBlock(1, i, j, true);
			}
			else if (init_table[i][j] == -3) {
				CreateNewPickeableBlock(1, i, j, false);
			}
			else if (init_table[i][j] != -1) {
				if (CreateNewFixedBlock(i, j, init_table[i][j])) {
					(*fiBl.at(i, j))->onPart = 1;
					ParseBlock(1, i, j, SDL_FLIP_NONE);

				}

			}
		}
	}

	camera.setOPos(109, 402);
	camera.setRect(298, 738, SIZE::BLOCK::UNIT_SIZE, SIZE::BLOCK::UNIT_SIZE);
}


void Pack3_3x2::Close() {
	int newW ;
	int newH ;
	
	if(close_stage == 2){
        caculNewSizeTrazoid(218, 349, newW, newH);
        if (theta < 90) {
            if (theta == 3) {
				backup_texture = parts[0].getTexture();
                parts[0].setTexture(Func::resizeTextureWithTrapeZoidShape(backup_texture, newW, 1, -1), false);
            }
            else
                parts[0].setTexture(Func::resizeTextureWithTrapeZoidShape(backup_texture, newW, 1, -1), true);
            parts[0].setRect(94 - (newW - 218) / 2, 35 + (349 - newH), newW, newH);
            theta += 9;
        }
        else if (theta <= 180) {
            parts[0].setTexture(Func::resizeTextureWithTrapeZoidShape(parts[3].getTexture(), newW, 1, 1), true);
            parts[0].setRect(94 - (newW - 218) / 2, 384, newW, newH);
            theta += 5;
        }
        else {
			
			parts[1].loadImg(IMGPATH::PACK::PACK3_3X2::BOTTOMRIGHT_CLOSE);
			ParseCamera(1, mouseOnBlock.x, mouseOnBlock.y);
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 2; j++) {
					if ((*fiBl.at(i, j)) != nullptr &&( (*fiBl.at(i, j))->onPart == 0 || (*fiBl.at(i, j))->onPart == 1)) {
						ParseBlock(1, i, j, SDL_FLIP_NONE);
					}
				}
			}
            theta = 0;
            close_stage++;
			
			camera.ShowAnswer((*piBl.at(mouseOnBlock.x, mouseOnBlock.y))->getAnswer());
        }
    }
	else {
        caculNewSizeTrazoid(312, 257, newH, newW);
        if (theta < 90) {
            if (theta == 0) {
				backup_texture = parts[2].getTexture();
                parts[2].setTexture(Func::resizeTextureWithTrapeZoidShape(backup_texture, newH, 0, 1), false);
            }
            else
                parts[2].setTexture(Func::resizeTextureWithTrapeZoidShape(backup_texture, newH, 0, 1), true);

            parts[2].setRect(314, 384 - (newH - 312) / 2, newW, newH);
            theta += 9;
        }
        else if (theta <= 180) {
            parts[2].setTexture(Func::resizeTextureWithTrapeZoidShape(parts[4].getTexture(), newH, 0, -1), true);
            parts[2].setRect(314 - newW, 384 - (newH - 312) / 2, newW, newH);
            theta += 5;
        }
        else {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 2; j++) {
					if ((*fiBl.at(i, j)) != nullptr && (*fiBl.at(i, j))->onPart ==2 ) {
						ParseBlock(1, i, j, SDL_FLIP_NONE);
					}
				}
			}
			
            close_stage++;
			theta = 0;
        }
    }
}


void Pack3_3x2::HandleInputEvents(SDL_Event& event) {
	switch (events.type)
	{
	case SDL_MOUSEMOTION:
		if (close_stage == 1)
			checkMouse(109, 402, SIZE::BLOCK::UNIT_SIZE); // need more general
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

void Pack3_3x2::render(){
	switch (close_stage) {
	case 0:
		if (230 - GetComponentXPos() < 10) {
			Slide(230 - GetComponentXPos(), 1);
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
		Close();
		update = true;
		break;
	case 4:
		if (theta == 0) {
			theta = SDL_GetTicks();
			return;
		}
		else if (SDL_GetTicks() - theta < 300) {
			update = true;
			break;
		}
		update = true;
		Slide(20, 0);
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
		
		parts[1].Render();
		if (close_stage <= 2) {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 2; j++) {
					if ((*piBl.at(i, j)) != nullptr) {
						(*piBl.at(i, j))->render();
					}
				}
			}
			
			parts[2].Render();
			camera.render();
			parts[0].Render();
			
		}
		else if (close_stage == 3) {
			parts[2].Render();
		}
		else {
			if (theta != 0 && SDL_GetTicks() - theta >= 200) {
				camera.render();
			}
		}
	}
}




int Pack3_3x2::getPoint() const {
	return point;
}

bool Pack3_3x2::DoneWithPack() const {
	if (close_stage >= 5) {
		return true;
	}
	return false;
}
