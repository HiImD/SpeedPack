/*
	Về Class ScoreBoard: 
		- Kế thừa AutoComponent_Vertical
		- Có chức năng xử lí với điểm:
				+ Cập nhật điểm
				+ Hiện điểm (khi đang chơi và khi gameover)
				+ Lưu điểm (có thể bổ sung sau)
				+ Hiện danh sách HighScore (bổ sung sau)
*/
#pragma once
#include "AutoComponent_Vertical.h"
#include <iomanip>

class ScoreBoard: public AutoComponent_Vertical {
private:
	short score = 0; //Điểm 
	bool update = true; //Update pTexture ?

	std::stringstream ss; //stringstream của score_texture

	MyTexture score_texture, added_score_texture; //Texture điểm và điểm được cộng thêm khi trả lời đúng
	
	bool added_score_texture_show; //Render added_score_texture ?
	std::string added_score_str; // text của added_score_texture
	int added_score_time_show; // Số Frame hiển thị added_score_texture
protected:
public:
	ScoreBoard();
	~ScoreBoard();

	void StartOver(); //Bắt đầu tính điểm lại

	//Thêm điểm
	void AddPoint(const short& added_point);
	//Xem điểm
	short GetScore();
	
	//Thay đổi kích thước của component theo margin , kích thước của score_texture, added_score_texture.
	void Resize();
	//Render text cho score_texture, added_score_texture
	void Render(SDL_Renderer* renderer = nullptr, const double angle = 0, SDL_Point* center = nullptr, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Hiển thị score_texture, added_score_texture
	void ShowBoard();
	//Chuẩn bị texture hiện khi gameover
	void PreparResult();

};

