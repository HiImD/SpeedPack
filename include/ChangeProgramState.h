/*
	Về Class ChangeProgramState:
		- Chỉ được dùng để làm lớp cha cho các class có khả năng tắt chương trình này
*/
#pragma once
class ChangeProgramState {
private:
	static bool program_quit;
protected:
	
	void Quit();
public :
	ChangeProgramState();

	static bool CheckProgramQuit();
	friend int main(int args, char* argc[]);
};