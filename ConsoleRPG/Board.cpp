#include <Windows.h>
#include <time.h>
#include <iostream>

#include "Board.h"
#include "Vector2.h"
#include "ObjectDeck.h"
#include "ObjectCardRow.h"
#include "ObjectCard.h"
#include "ObjectAceSlots.h"
#include "View.h"
#include "Bounds.h"
#include "AsciiTexture.h"

#include "ObjectPopup.h"
#include "UIText.h"
#include "KeyInput.h"

Board::Board() {}

Board::~Board()
{
	delete mDeck;
	mDeck = nullptr;

	for (ObjectCardRow* row : mRows)
	{
		delete row;
		row = nullptr;
	}
	mRows.clear();

	delete mAceSlots;
	mAceSlots = nullptr;

	/// UI
	delete mHelpWindow;
	mHelpWindow = nullptr;
}

bool Board::CanPlace(const ObjectCard* cardToPlace)
{
	/// Check to see if the row slot is empty
	if (!mRows[rowIndex]->HasCardsLeft())
		return cardToPlace->GetNumber() == ObjectDeck::NUMBER_AMOUNT;

	const ObjectCard* cardInRow = mRows[rowIndex]->PeekAtTopCard();

	/// Check if the suits match
	if (cardToPlace->SuitMatch(cardInRow))
		return false;

	/// Check if the number is valid
	return cardInRow->GetNumber() - 1 == cardToPlace->GetNumber();
}

void Board::ConstructBoard()
{
	Vector2 slotPos((float)((PRIMARY_SLOT_COUNT - 1) * (ObjectCard::CARD_WIDTH + mHorizontalPadding) / 2), (float)mSpecialVerticalPadding);
	mDeck = new ObjectDeck(slotPos, ObjectCard::CARD_WIDTH/2 + 1);

	// Setup Rows
	slotPos = Vector2(0.0f, (float)mPrimaryVerticalPadding);
	int stackAmount = 1;
	mRows.resize(PRIMARY_SLOT_COUNT);
	for (int i = 0; i < PRIMARY_SLOT_COUNT; i++)
	{
		mRows[i] = new ObjectCardRow(slotPos, *mDeck, stackAmount, 1);
		slotPos.x += (ObjectCard::CARD_WIDTH + mHorizontalPadding) / 2; // increment x position
		stackAmount++; // increase stack amount per slot
	}

	/// Setup Ace Slots
	mAceSlots = new ObjectAceSlots(Vector2(0.0f, 0.0f), mHorizontalPadding, mSpecialVerticalPadding);
	ConstructEmptySlots(6);
}

void Board::Play(View& window)
{
	ConstructUI(window);

	//clock_t worldTime = clock();
	//clock_t lastTime = worldTime;
	//clock_t sleepTime = 100;

	bool quit = false;
	while (!quit)
	{
		//std::wcout << worldTime - lastTime;
		//if (worldTime - lastTime > sleepTime)
		//{
			/// EXIT GAME
			quit = mAceSlots->HasWon(ObjectDeck::NUMBER_AMOUNT) ||
				KeyInput::KeyUp('B');

			// Over all controls
			/// Display Help Window
			if (KeyInput::KeyUp('H'))
			{
				const bool flip = !mHelpWindow->GetIsActive();
				mHelpWindow->SetActive(flip);
			}

			if (!mHelpWindow->GetIsActive())
				GameLogic();

			//lastTime = worldTime;
		//}

		// @ Render
		window.Clear();
		/// Empty Slots
		for (auto& emptySlots : mEmptyBoardSlots)
			emptySlots->Render(window);
		/// Deck
		mDeck->Render(window);
		/// Rows
		for (auto& row : mRows)
			row->Render(window);
		/// Ace Slots
		mAceSlots->Render(window);
		/// UI
		mHelpWindow->Render(window);
		mBottomNavLabel->Render(window);

		window.SwapBuffers();

		//worldTime = clock();
	}

	int i = 0;
}

void Board::GameLogic()
{
	/* CARD ROWS: HORIZONTAL */
	if (KeyInput::KeyUp(VK_LEFT))
	{
		mRows[rowIndex]->UnHover(mColIndex);
		rowIndex = std::max<int>(--rowIndex, 0);
		mRows[rowIndex]->HoverTop();

		mColIndex = mRows[rowIndex]->GetTopIndex();
	}
	else if (KeyInput::KeyUp(VK_RIGHT))
	{
		mRows[rowIndex]->UnHover(mColIndex);
		rowIndex = std::min<int>(++rowIndex, mRows.size() - 1);
		mRows[rowIndex]->HoverTop();

		mColIndex = mRows[rowIndex]->GetTopIndex();
	}

	/* CARD ROWS: VERTICAL */
	if (KeyInput::KeyUp(VK_UP))
	{
		/// If a row is already selected, then deselect everything that is currently selected
		if (mCurrentRow)
			mCurrentRow->Deselect(mColIndex);

		/// move "up" the card row and set the cards to hover
		mColIndex = std::max<int>(--mColIndex, 0);
		mColIndex = mRows[rowIndex]->Hover(mColIndex);
	}
	else if (KeyInput::KeyUp(VK_DOWN))
	{
		/// If a row is already selected, then deselect everything that is currently selected
		if (mCurrentRow)
			mCurrentRow->Deselect(mColIndex);

		/// move "down" the card row and set the cards to hover
		const int topIndex = mRows[rowIndex]->GetTopIndex();
		mColIndex = std::min<int>(++mColIndex, topIndex);

		/// If there is only one card to pick between, don't bother updating
		if (mColIndex < topIndex)
			mColIndex = mRows[rowIndex]->UnHover(mColIndex);
	}

	/* CARD ROWS: SELECT / PLACE */
	if (KeyInput::KeyUp(VK_SPACE))
	{
		/// if a card deck is selected
		if (mDeckCardSelected)
		{
			/// Will take a peek at the deck to see if the card will be placed in a valid spot
			if (CanPlace(mDeck->PeekAtTopCardInOpenDeck()))
			{
				/// Fetches the top most available card in the visible card pile (in the deck)
				ObjectCard* card = mDeck->Fetch();
				card->Deselect();
				mRows[rowIndex]->UnHoverTop();
				mRows[rowIndex]->PutBack(card);
				mRows[rowIndex]->HoverTop();
				/// Reset the column index
				mColIndex = mRows[rowIndex]->GetTopIndex();

				/// Card has been placed; set card selected to false
				mDeckCardSelected = false;
				mRowCardsSelected = !mRowCardsSelected;
			}
		}
		/// if a deck card is not selected; check if the current row is selected 
		else if (mRowCardsSelected)
		{
			/// if a row is selected (from the horizontal controls)
			if (mCurrentRow)
			{
				if (CanPlace(mCurrentRow->PeekAtCard(mFetchedColIndex)))
				{
					/// Fetch the amount of cards specified (in the vertical controls)
					std::list<ObjectCard*> card = mCurrentRow->Fetch(mFetchedColIndex);
					mRows[rowIndex]->UnHover(mColIndex);
					mRows[rowIndex]->PutBack(card);
					mRows[rowIndex]->HoverTop();
					mColIndex = mRows[rowIndex]->GetTopIndex();

					/// reset the current row and the currently fetched column index
					mCurrentRow = nullptr;
					mFetchedColIndex = mColIndex;
				}
				/// If the placement fails, deselect all
				else if (mCurrentRow)
				{
					mCurrentRow->Deselect(mFetchedColIndex);
					mCurrentRow->UnHover(mFetchedColIndex);
					mDeckCardSelected = false;
					mCurrentRow = nullptr;
					mFetchedColIndex = mColIndex;

					mRows[rowIndex]->HoverTop();
				}
			}
			mDeckCardSelected = false;
		}
		/// if a card has not been previously selected
		else
		{
			/// store the currently set column index, to know 
			/// how much of the currentRow needs to be moved
			mFetchedColIndex = mColIndex;
			/// Sets the row to move from
			if (!mCurrentRow)
				mCurrentRow = mRows[rowIndex]->Select(mFetchedColIndex);
		}

		if (mRows[rowIndex]->HasCardsLeft())
			mRowCardsSelected = !mRowCardsSelected;
	}

	/* DECK : SELECT AND RESET  */
	if (KeyInput::KeyUp('W'))
	{
		mDeck->Deselect();
		mDeckCardSelected = false;

		/// if no cards are left on the table, reset the deck
		/// else, place a card from the deck
		if (!mDeck->HasHiddenCardsLeft())
			mDeck->Reset();
		else
			mDeck->PlaceCard();
	}

	/* DECK: SELECT CARD */
	else if (KeyInput::KeyUp('E'))
	{
		if (mDeckCardSelected)
			mDeck->Deselect();
		else
		{
			/// if a card in a row has already been selected;
			/// Deselect and set the top card in that row to hover
			if (mCurrentRow)
			{
				mCurrentRow->Deselect(mFetchedColIndex);
				mCurrentRow->HoverTop();
				mRowCardsSelected = false;
			}
			mDeck->Select();
		}
		mDeckCardSelected = !mDeckCardSelected;
	}

	/* ACE SLOT: SEND */
	if (KeyInput::KeyUp('X'))
	{
		/// If the deck card is selected
		/// Ignore the current row, and attempt to add the top deck card to a ace slot
		if (mDeckCardSelected)
		{
			ObjectCard* revealedCard = mDeck->PeekAtTopCardInOpenDeck();
			if (mAceSlots->AttemptToAddCard(revealedCard))
			{
				mDeck->Fetch();
				revealedCard->Deselect();
				mDeckCardSelected = false;
				
			}
		}
		/// if no cards are present in the row, then do nothing
		else if (mRows[rowIndex]->HasCardsLeft())
		{
			ObjectCard* topCardInRow = mRows[rowIndex]->PeekAtTopCard();
			if (mAceSlots->AttemptToAddCard(topCardInRow))
			{
				mRows[rowIndex]->Fetch();
				mRows[rowIndex]->HoverTop();	
			}
		}
	}
}

void Board::ConstructEmptySlots(int slotOffset)
{
	const int specialSlots = 6;

	// Setup visual empty board slots
	mEmptyBoardSlots.reserve(specialSlots);
	
	Vector2 pos((float)((slotOffset - 1) * (ObjectCard::CARD_WIDTH + mHorizontalPadding) / 2), (float)mSpecialVerticalPadding);
	ObjectCard* cardBundle = new ObjectCard(pos, 'V');
	mEmptyBoardSlots.push_back(cardBundle);

	/// Setup Empty Ace Slots
	pos.x = 0.0f;
	for (int i = 0; i < specialSlots - 2; i++)
	{
		ObjectCard* aceSlot = new ObjectCard(pos, ' ');
		pos.x += (ObjectCard::CARD_WIDTH + mHorizontalPadding) / 2;
		mEmptyBoardSlots.push_back(aceSlot);
	}
}

void Board::ConstructUI(View& window)
{
	Bounds winBound = window.GetBoundary();
	int width = winBound.GetWidth() - 1;
	int height = winBound.GetHeight() - 1;

	Vector2 pos(2.0f, 2.0f);
	mHelpWindow = new ObjectPopup(pos, 40.0f, 20.0f, L"Controls");
	mHelpWindow->AddLine(L"╼╼╼╼╼╼╼╼╼╼╼╼╼╴");
	mHelpWindow->AddLine(L"← → : Move between the card rows");
	mHelpWindow->AddLine(L"↑ ↓ : Move up/down the card rows");
	mHelpWindow->AddLine(L"Space : (De)Select card");
	mHelpWindow->AddLine(L"W : Place card from deck");
	mHelpWindow->AddLine(L"E : Select card from deck");
	mHelpWindow->AddLine(L"X : Add card to Ace piles");
	mHelpWindow->SetActive(false);

	pos = Vector2(0.0f, 18.0f);
	mBottomNavLabel = new UIText(pos, L"[H]: Help | [B]: Back To Menu");
}