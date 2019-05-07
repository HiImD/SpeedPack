/*
	Về Class AutoComponent_Vertical:
		- Kế thừ từ class Component, có thêm chức năng tự động sắp xếp các texture được thêm vào theo hàng dọc,
		theo format được cài đặt trong biến margin.
*/

#pragma once
#include "Component.h"

class AutoComponent_Vertical : public Component {
private:
	int comp_h;
protected:
	
	std::vector<MyTexture*> pMyTexture_arr; //Mảng lưu con trỏ của các MyTexture được đưa vào AutoComponent_Vertical
	struct Margin {
		int top, bottom, left, right, between;
		Margin(const int& _top = 0, const int& _bottom = 0, const int& _left = 0, const int& _right = 0, const int& _between = 0) {
			top = _top;
			bottom = _bottom;
			left = _left;
			right = _right;
			between = _between;
		} 
		/*
			top: khoảng cách từ đỉnh trên của pTexture đến Texture đầu tiên
			bottom: khoảng cách từ đỉnh dưới của pTexture đến Texture cuối cùng
			left: lề trái
			right: lề phải
			between: Khoảng cách giữa các Texture
		*/
	};
public:
	Margin margin;

	AutoComponent_Vertical(SDL_Color color = {0, 0, 0, 0});
	~AutoComponent_Vertical();

	//Overide MyObj.h
	OBJTYPE type() const;
	const char* toString() const;

	//Các hàm thêm và xóa Texture
	void PushBack(MyTexture* mT);
	void PopBack();
	void InsertMyTexture(const int& id, MyTexture* added_MyTexture);
	void EraseMyTexture(const int& id, const bool& destroy = false);
	//Trả về con trỏ của MyTexture tại vị trí id
	MyTexture* GetMyTexturePointer(const int& id);

	//Hàm sắp xếp các Texture, virtual_comp = true nếu không dán nên pTexture, chỉ sử dụng Rect của Component để định vị các Texture 
	void AutoSort(bool virtual_comp = false);
	//Dán tất cả các Texture lên pTexture
	void ParseAllToComp();

	
};