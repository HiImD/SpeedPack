#include "ChangeProgramState.h"

bool ChangeProgramState::program_quit = false;

ChangeProgramState::ChangeProgramState() {

}

bool ChangeProgramState::CheckProgramQuit() {
	return program_quit;
}

void ChangeProgramState::Quit() {
	program_quit = true;
}