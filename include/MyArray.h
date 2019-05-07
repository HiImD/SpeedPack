/*
	Về Class MyArray:
		- Chỉ như một mảng để chứa các đối tượng
*/

#pragma once
#include <stdlib.h>
#include <cstring>
#include "PickableBlock.h"

template<class T>
class MyArray {
	int r = 0, c = 0;
	T* arr = nullptr;
public:
	MyArray() {
	}

	
	MyArray(const int& r, const int& c,const T& init_value) {
		init(r, c, init_value);
	}
	~MyArray() {
		free(arr);
	}

	//Khởi tạo không tường minh
	//Yêu cầu cấp phát bộ nhớ và sao giá trị init_value vào từng vị trí
	void init(const int& r,const int& c, const T& init_value) {
		this->r = r;
		this->c = c;
		arr = (T*)calloc(r * c + 1, sizeof(T));
		if (arr != nullptr) {
			for (int i = 0; i < r * c; i++) {
				memcpy(arr + i, &init_value, sizeof(T));
			}
		}
		else {
			SDL_Log("Allocate memory fail!");
		}
	}

	//Trả về con trỏ của đối tượng tại vị trí i, j
	//(Trả về con trỏ do có yêu cầu thay đổi giá trị của phần tử tại i, j)
	T* at(const int& i,const int& j) {
		if (i >= 0 && i < r && j >= 0 && j < c) {
			return &arr[i * c + j];
		}
		else
		{
			SDL_Log("Out of range!!!");
			//throw "Out of range!!!";
			return nullptr;
		}
	}

};
