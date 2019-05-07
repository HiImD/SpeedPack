/*
	Về Class Pack (Va li):
		- Là một lớp trừu tượng, chứa các hàm chức năng cơ bản mà các class kế thừa từ nó cần có. 
*/

#pragma once


#include "Component.h"
#include "PickableBlock.h"
#include "FixedBlock.h"
#include "MyArray.h"
#include "TheCamera.h"

class Pack: public Component{
private:

protected:
	const int row, col; //Kích thước của Pack
	int point = 0; // Điểm của Pack
	int close_stage = 0; // Trạng thái của Pack
	int theta = 0; // Biến chức năng biểu diễn góc quay của Pack khi gập lại và được sử dụng lại để lưu thời gian

	MyTexture* parts; //Con trỏ đến một mảng các Texture của Pack
	const int number_of_parts; //Biến đếm số cánh của Pack

	Func::Vector* O;          //toa do goc tren ben trai cua bang block ung voi moi part
	
	MyArray<PickableBlock*> piBl; //Mảng lưu con trỏ của các PickableBlock
	MyArray<FixedBlock*> fiBl;  //Mảng lưu con trỏ của các FixedBlock
	
	Func::Vector mouseOnBlock; //Biến lưu tọa độ con trỏ chuột so với Pack
							   //Có giá trị (i, j) với  -1 <= i <= row và  -1 <= j <= col 
							   //      i == -1 || j == -1 có nghĩa con trỏ chuột không trỏ tới bất kì block nào của Pack
	
	TheCamera camera;

	// Cac ham
	//
	/*    
	       i
		+------> 
	  j	|
		|
		v

		___________________
		|		 |		   |
		|	0,0	 |	 0,1   |
	 ---|________|_________|
	 |	|		 |		   |
	 | 	|	1,0	 |	 1,1   |
	 ---|________|_________|
		|		 |		   |
	*/
	
	//Kiem tra vi tri cua con tro chuot
	//Cap nhan gia tri vao bien mouseOnBlock theo format tren
	// mouseOnBlock nhan gia tri (-1, -1) neu con tro chuot khong nam tren Block nao
	void checkMouse(const int& x0, const int& y0, const int& size_of_block);  
	
	//Ham kiem tra con tro chuot hien co dang o tren mot PickableBlock hop le
	//Neu dung set visible cua block do thanh false tra ve true
	//Neu khong tra ve false
	bool checkMouseOver();

	//Tao mot PickableBlock tai o (i,j) la dap an dung(answer == true) hoac sai (answer == false) xuat hien tai parts[id_part]
	bool CreateNewPickeableBlock(const int& id_part, const int& i, const int& j, const bool& answer);

	//Tao mot FixedBlock tai o (i,j) (voi i,j theo toa do cua part chua PickableBlock)
	bool CreateNewFixedBlock(const int& i, const int& j, const int& id);

	//Dan FixedBlock tai o (i,j) (voi i,j theo toa do cua part chua PickableBlock) len parts[id_part] su dung phep chieu qua guong flip
	bool ParseBlock(const int& id_part, const int& i, const int& j, const SDL_RendererFlip& flip);

	//Dan Texture cua Camera len o (i,j) (voi i,j theo toa do cua part chua PickableBlock) 
	//id_part nen la part chua PickableBlock
	bool ParseCamera(const int& id_part, const int& i, const int& j);


	/*
				|\
				| \
				|  \
				|   \
	            |   /\
				|  /  \
				| /    \
				+------
				   
	*/
	//Dung de tinh gia tri cua w, h cua Texture theo phep chieu khi quay Texture quanh truc mot goc theta (mot bien cua Pack)
	void caculNewSizeTrazoid(const int& norm_a, const int& norm_b, int& a, int& b);

public:
    Pack(const int& w, const int& h, const int& comp_x0, const int& comp_y0, const int& _row, const int& _col, const int& number_of_parts);
    virtual ~Pack();
    virtual OBJTYPE type() const;
    virtual const char* toString() const;

	//Ham khoi tao
	virtual void init() = 0;
	
	//Ham render cac thanh phan cua Pack nen Texture cua Component
	virtual void render() = 0;

	//Ham xu li su kien
	virtual void HandleInputEvents(SDL_Event& events) = 0;
	
	//Ham tra ve diem cua Pack
	virtual int getPoint() const = 0;

	//Ham kiem tra vong doi cua Pack
	virtual bool DoneWithPack() const = 0;


	int getCloseStage();
	

};

