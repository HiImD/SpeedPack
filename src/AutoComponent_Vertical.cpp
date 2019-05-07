#include "AutoComponent_Vertical.h"

AutoComponent_Vertical::AutoComponent_Vertical(SDL_Color color) : Component(color), margin(), comp_h(0) {
}

AutoComponent_Vertical::~AutoComponent_Vertical() {

}

OBJTYPE AutoComponent_Vertical::type() const {
	return OBJTYPE::PACK3_3x2;
}

const char* AutoComponent_Vertical::toString() const {
	return "AutoComponent_Vertical";
}

void AutoComponent_Vertical::PushBack(MyTexture* mT) {
	pMyTexture_arr.push_back(mT);
}

void AutoComponent_Vertical::PopBack() {
	pMyTexture_arr.pop_back();

}

void AutoComponent_Vertical::InsertMyTexture(const int& id, MyTexture* added_MyTexture ) {
	if (id >= pMyTexture_arr.size()) {
		SDL_Log("Invalid id when InsertMyTexture");
	}
	else {
		pMyTexture_arr.insert(pMyTexture_arr.begin() + id,  added_MyTexture);
	}
}

void AutoComponent_Vertical::EraseMyTexture(const int& id, const bool& destroy) {
	if (destroy) {
		delete pMyTexture_arr[id];
		pMyTexture_arr[id] = nullptr;
	}
	pMyTexture_arr.erase(pMyTexture_arr.begin() + id);
}

void AutoComponent_Vertical::AutoSort(bool virtual_comp) {
	comp_h = margin.top;
	for (MyTexture* pM : pMyTexture_arr) {
		pM->getRectPointer()->x = margin.left ;
		pM->getRectPointer()->y = comp_h ;
		if (virtual_comp) {
			pM->getRectPointer()->x += GetComponentXPos();
			pM->getRectPointer()->y += GetComponentYPos();
		}
		comp_h += pM->getRectPointer()->h + margin.between;
	}
	if (pMyTexture_arr.size() > 0)
		comp_h -= margin.between;
	comp_h += margin.bottom;
}

void AutoComponent_Vertical::ParseAllToComp() {  //can toi uu hon
	pTexture->getRectPointer()->h = comp_h;
	int  h;
	SDL_QueryTexture(pTexture->getTexture(),nullptr, nullptr,  nullptr, &h);
	if (h != comp_h) {
		pTexture->createTransparentTexture(SDL_PIXELFORMAT_ABGR8888, pTexture->getRectPointer()->w, comp_h, true, bgColor);
	}
	else {
		ClearComponent();
	}
	
	
	for (MyTexture* pM : pMyTexture_arr) {
		pTexture->parseTexture(pM->getTexture(), nullptr, pM->getRectPointer());
	}
}

MyTexture* AutoComponent_Vertical::GetMyTexturePointer(const int& id) {
	return pMyTexture_arr[id];
}