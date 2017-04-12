#include <Windows.h>

#include "Precision.h"

#include <iostream>
#include <io.h>
#include <fcntl.h>

#include <cstdlib>
#include <time.h>

// For quick and dirty main menu
#include "AsciiTexture.h"
#include "UIText.h"
#include "View.h"
#include "Vector2.h"
#include "Board.h"
#include "ObjectCard.h"
#include <vector>

void RunGame(View& window)
{
	AsciiTexture header(53, 9, L"╔════╗╔════╗╔═╗   ╔═══╗╔═════╗╔════╗╔═══╗╔════╗╔════╗║ ╔══╝║ ╔╗ ║║ ║   ╚╗ ╔╝╚═╗ ╔═╝║ ╔╗ ║╚╗ ╔╝║ ╔╗ ║║ ╔══╝║ ╚══╗║ ║║ ║║ ║    ║ ║   ║ ║  ║ ║║ ║ ║ ║ ║ ║║╔╝║ ╚═╗.╚══╗ ║║ ║║ ║║ ║    ║ ║   ║ ║  ║ ╚╝ ║ ║ ║ ║ ╚╝╚╗║ ╔═╝'╔══╝ ║║ ╚╝ ║║ ╚══╗╔╝ ╚╗  ║ ║  ║ ╔╗ ║╔╝ ╚╗║ ╔╗ ║║ ╚══╗╚════╝╚════╝╚════╝╚═══╝  ╚═╝  ╚═╝╚═╝╚═══╝╚═╝╚═╝╚════╝╔═══════════════════════════════════════════════════╗╚═══════════════════════════════════════════════════╝");
	UIText mInstructionLabel({ 8.0f, 7.0f }, L"[S]: Start | [ESC]: Quit");

	// Draw a set of cards
	Vector2 pos(0, 4);
	std::vector<ObjectCard*> pile;
	pile.reserve(13);
	for (int i = 0; i < 13; i++)
	{
		pile.push_back(new ObjectCard(pos, i+1, eCardSuit::HEART));
		pos.x += 2;
	}

	// Render Menu and handle game start
	bool quit = false;
	while (!quit)
	{
		quit = GetAsyncKeyState(VK_ESCAPE);

		if (GetAsyncKeyState('S'))
		{
			Board board;
			board.ConstructBoard();
			board.Play(window);
		}

		// @ Render Menu
		window.Clear();
		window.FillBuffer({ 1.0f, 0.0f }, header);
		mInstructionLabel.Render(window);

		for (ObjectCard* card : pile)
			card->Render(window);

		window.SwapBuffers();

	}
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	View window(70, 40, ' ');

	std::srand(time(0));

	RunGame(window);
	return 0;
}