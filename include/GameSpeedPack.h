/*
	Về Class GameSpeedPack:
	- Là một Logic game hoàn chỉnh.
	- Điều khiển và xử lí các trạng thái của game
*/
#pragma once
#include "Func.h"
#include "BackGround.h"
#include "MyTexture.h"
#include "Pack2x4_2.h"
#include "Pack3_3x2.h"
#include "TimerComponent.h"
#include "ButtonComponent.h"
#include "Menu.h"
#include "ChangeProgramState.h"
#include "ScoreBoard.h"
#include <time.h>

class GameSpeedPack : public MyObj, public ChangeProgramState {
private:
	Menu menu; 

	enum STATE {
		HAVENOTINIT,
		INIT,
		START,
		RUNNING,
		PAUSE,
		RESUMING,
		GAMEOVER,
		RESTART,
		STOP
	} state; //Biến lưu trạng thái của game

	short bonus_point; //Biến lưu điểm được cộng thêm của người chơi
	short chain_pack_complete; //Biến lưu dãy các Pack đúng liên tiếp của người chơi
	Pack* pack; //Con trỏ của Pack

	MyTimer timer; //Đồng hồ đếm giờ

	ScoreBoard scoreBoard; //Bảng điểm của người chơi
	BackGround background; //Background Game

	//Hàm tạo mới một pack nếu pack == nullptr
	//Nếu compulsory == true, tạo mới một Pack kể cả khi pack != nullptr
	void CreateNewPack(bool compulsory = false);

	//Vòng lặp điều khiển dòng logic game
	void GameLoop();

	//Các hàm tương ứng với state game tương ứng
	void Init();
	void Run();
	void Pause();
	void Resume();
	void Restart();
	void GameOver();

protected:
public:
	GameSpeedPack();
	~GameSpeedPack();

	//Overide MyObj.h
	OBJTYPE type() const;
	const char* toString() const;

	
	void Start();
	void Stop();



};