#pragma once

#include <vector>
#include <stack>
#include "GameState.h"

class UIText;
class ObjectPopup;
class ObjectAceSlots;
class ObjectDeck;
class ObjectCardRow;
class ObjectCard;
class View;
class Board
{
public:
	Board();
	~Board();

	void ConstructBoard();
	void Play(View& window);

private:
	void GameLogic();

	/// Checks to see if the card is placeable, i.e; do the suits the numbers and obey the rules?
	bool CanPlace(const ObjectCard* cardToPlace);

	void ConstructEmptySlots(int slotCount);
	void ConstructUI(View& window);

	// Empty board 
	std::vector<ObjectCard*> mEmptyBoardSlots;

	// Deck data
	ObjectDeck* mDeck;
	bool mDeckCardSelected = false;

	ObjectAceSlots* mAceSlots;

	// Row Specific data
	std::vector<ObjectCardRow*> mRows;
	int rowIndex = 0;
	int mColIndex = 0;
	int mFetchedColIndex = 0;
	ObjectCardRow* mCurrentRow = nullptr;
	bool mRowCardsSelected = false;

	/// UI
	ObjectPopup* mHelpWindow = nullptr;
	UIText* mBottomNavLabel = nullptr;

	int mHorizontalPadding = 1;
	int mPrimaryVerticalPadding = 3;
	int mSpecialVerticalPadding = 0;

	const static int PRIMARY_SLOT_COUNT = 7;
};

