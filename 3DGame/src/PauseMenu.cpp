#include "PauseMenu.h"
#include "DialogBox.h"
#include "Game.h"
#include <SDL/SDL.h>

PauseMenu::PauseMenu(Game* game) : UIScreen(game) {
	mGame->SetState(Game::EGameState::EPaused);
	SetRelativeMouseMode(false);
	SetTitle("PauseTitle");
	AddButton("ResumeButton", [this]() { Close(); });
	AddButton("QuitButton", [this]() {
		new DialogBox(mGame, "QuitText",
			[this]() { mGame->SetState(Game::EGameState::EQuit); });
		});
}

PauseMenu::~PauseMenu() {
	SetRelativeMouseMode(true);
	mGame->SetState(Game::EGameState::EGameplay);
}

void PauseMenu::HandleKeyPress(int key) {
	UIScreen::HandleKeyPress(key);

	if (key == SDLK_ESCAPE) {
		Close();
	}
}
