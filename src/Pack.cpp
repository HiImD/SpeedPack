#include "Pack.h"

Pack::Pack(const int& w, const int& h, const int& comp_x0, const int& comp_y0, const int& _row, const int& _col, const int& _number_of_parts) :Component(w, h), row(_row), col(_col), number_of_parts(_number_of_parts), mouseOnBlock(-1, -1), piBl(_row, _col, nullptr), fiBl(_row, _col, nullptr), camera(mRenderer, pTexture->getTexture()) {
	SetComponentPos(comp_x0, comp_y0);
	try {
		parts = new MyTexture[number_of_parts];
		O = new Func::Vector[number_of_parts];
	}
	catch (std::bad_alloc & ba) {
		SDL_Log(std::string("From: %s", toString()).c_str());
		SDL_Log(std::string(" -- bad_alloc caught: %s", ba.what()).c_str());
	}
	for (int i = 0; i < number_of_parts; i++) {
		parts[i].init(mRenderer, pTexture->getTexture());
	}
	
	
}

Pack::~Pack(){
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			if ((*piBl.at(i, j)) != nullptr) {
				delete (*piBl.at(i, j));
			}
			if ((*fiBl.at(i, j)) != nullptr) {
				delete (*fiBl.at(i, j));
			}
		}
	}
	if (parts != nullptr) {
		delete[] parts;
		parts = nullptr;
	}
	if (O != nullptr) {
		delete[] O;
		O = nullptr;
	}
}

OBJTYPE Pack::type() const{
    return OBJTYPE::PACK;
}

const char* Pack::toString() const{
    return "Pack";
}

bool Pack::CreateNewFixedBlock(const int& i, const int& j, const int& id) {
	if (i < 0 || i >= row || j < 0 || j >= col) {
		return false;
	}
	if ((*fiBl.at(i, j)) != nullptr) {
		SDL_Log(std::string("Fail to creat new Block at %d %d", i, j).c_str());
		return false;
	}
	(*fiBl.at(i, j)) = new FixedBlock(mRenderer, pTexture->getTexture(), id);
	return true;
}

bool Pack::CreateNewPickeableBlock(const int& id_part, const int& i, const int& j, const bool& answer) {
	if (i < 0 || i >= row || j < 0 || j >= col) {
		return false;
	}
	if ((*piBl.at(i, j)) != nullptr) {
		return false;
	}
	(*piBl.at(i, j)) = new PickableBlock(mRenderer, pTexture->getTexture(), answer);
	(*piBl.at(i, j))->setPos(parts[id_part].getRectPointer()->x + O[id_part].x + j * 93, parts[id_part].getRectPointer()->y + O[id_part].y + i * 93);
	return true;
}

bool Pack::ParseBlock(const int& id_part, const int& i, const int& j, const SDL_RendererFlip& flip) {
	if (id_part >= number_of_parts || id_part < 0) {
		SDL_Log("Out of range of parts");
		return false;
	}
	if ((*fiBl.at(i, j)) != nullptr) {
		if (flip == SDL_FLIP_NONE) {
			(*fiBl.at(i, j))->setPos(O[id_part].x + j * 93, O[id_part].y + i * 93);
		}
		else if (flip == SDL_FLIP_HORIZONTAL) {
			(*fiBl.at(i, j))->setPos(O[id_part].x + (col - (*fiBl.at(i, j))->getCol() - j) * 93, O[id_part].y + i * 93);
		}
		else if (flip == SDL_FLIP_VERTICAL) {
			(*fiBl.at(i, j))->setPos(O[id_part].x + j * 93, O[id_part].y + (row - (*fiBl.at(i, j))->getRow() - i) * 93);
		}
		parts[id_part].parseTexture((*fiBl.at(i, j))->getTexture(), nullptr, (*fiBl.at(i, j))->getRectPointer(), 0, nullptr, flip);
	}
	return true;
}
bool Pack::ParseCamera(const int& id_part, const int& i, const int& j) {
	if (id_part >= number_of_parts || id_part < 0) {
		SDL_Log("Out of range of parts");
		return false;
	}
	SDL_Rect cam_rect_on_part = { O[id_part].x + j * 93, O[id_part].y + i * 93 , camera.getRectPointer()->w, camera.getRectPointer()->h };
	parts[id_part].parseTexture(camera.getTexture(), nullptr, &cam_rect_on_part);
	return true;
}


// a la canh song song voi truc quay
// b la canh vuong goc voi truc quay
void Pack::caculNewSizeTrazoid(const int& norm_a, const int& norm_b, int& a, int& b) {
	double h1 = pow(pow(13, 2) - 120 * sin(theta * PI * 1.0 / 180), 0.5) * 100;
	h1 = round(h1);
	a = round((norm_a * 1.0 / 5) * 6500 / h1);    //do dai cua canh song song voi truc quay

	double newH = 100 * (12 * 5 * abs(cos(theta * PI / 180))) / (12 - 5 * sin(theta * PI / 180));
	b = round(norm_b * newH * 1.0 / 500);         //do dai cua canh vuong goc voi truc quay
}

void Pack::checkMouse(const int &x0, const int& y0, const int& size_of_block) {
	mouseOnBlock.set(-1, -1);
	int x, y;
	SDL_GetMouseState(&x, &y);
	{
		int x_component, y_component;
		GetComponentPos(x_component, y_component);
		x -= (x_component + x0);
		y -= (y_component + y0);
	}
	if (Func::inRange(x, 0, col*size_of_block + col - 1) && Func::inRange(y, 0, row*size_of_block + row - 1)) {
		if ((x == (x / size_of_block) * (size_of_block + 1)) || (y == (y / size_of_block) * (size_of_block + 1)))
			return;
		int j = x / (size_of_block + 1), i = y / (size_of_block + 1); 
		if (*piBl.at(i, j) != nullptr) {
			mouseOnBlock.set(i, j);
		}
	}
}

bool Pack::checkMouseOver() {
	if (mouseOnBlock.x != -1 && mouseOnBlock.y != -1) {
		if (*piBl.at(mouseOnBlock.x, mouseOnBlock.y) != NULL) {
			(*piBl.at(mouseOnBlock.x, mouseOnBlock.y))->setVisible(false);
			camera.SlideTo(mouseOnBlock.x, mouseOnBlock.y);
			return true;
		}
	}
	return false;
}

int Pack::getCloseStage() {
	return close_stage;
}