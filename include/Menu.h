/*
	Về Class Menu:
		- Kế thừa AutoComponent_Vertical
		- Chứa các Button (các Text Texture) và xử lí sự kiện chuột, bàn phím với các Button 
*/

#pragma once
#include "AutoComponent_Vertical.h"
#include <map>
#include <set>
#include "Button.h"

class Menu : public AutoComponent_Vertical {
private:
	TTF_Font* font; //Font chữ được dùng cho cac Button
	SDL_Color fg_text, bg_text; //fg_text: màu chữ
					  //bg_text: màu nền khi shaded text

	int mouseOnButton;

	std::set<std::string> button_id; //Lưu id (duy nhất) của các button
	std::vector<std::string> button_down;//Lưu id của các button được nhấn, sử dụng cấu trúc hàng đợi
	int h_button_size; //Lưu kích h của button
protected:
public:
	bool done = false; //Menu đã sử dụng xong ?
	Menu(TTF_Font* font, SDL_Color fg, SDL_Color bg);
	~Menu();
	
	//Overide MyObj.h
	virtual OBJTYPE type() const;
	virtual const char* toString() const;

	//Thêm và xóa button
	void AddButton( const std::string& id, const std::string& text, const int& index = -1);  //id != ""
	void EraseButton(const int& index);
	
	//Kiểm tra vị trí chuột
	void CheckMouse();

	//Xử lí xự kiện
	//Trả về id của button được nhấn
	//trả về "" nếu không có button được nhấn
	std::string HandleInputEvents(SDL_Event& events);

	//Render Menu lên màn hình
	void Show(SDL_Rect* srcRect = NULL, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
};