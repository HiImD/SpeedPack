/*
	Về Class MyObj:
		- Yêu cầu các class kế thừa nó overide type() và toString() là các hàm cung cấp thông tin của class đó
*/

#pragma once
#include "gVar.h"

class MyObj {
protected:
public:
	//Trả về OBJTYPE (enum trong gVar.h)
	virtual OBJTYPE type() const = 0;
	//Trả về const char* miêu tả bản thân class
	virtual const char* toString() const = 0;
};
