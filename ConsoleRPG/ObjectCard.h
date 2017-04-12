#pragma once

#include "Object.h"
#include "Precision.h"
enum class eCardSuit
{
	HEART = 0, 
	DIAMOND,
	CLOVER,
	SPADES,
};

class AsciiTexture;
class Vector2;
class ObjectCard : public Object
{
public:
	const static int CARD_WIDTH  = 7;
	const static int CARD_HEIGHT = 5;

	// @ Construction
	ObjectCard(const Vector2& position, rchar centreSymbol);
	ObjectCard(const Vector2& position, int cardNumber, eCardSuit suitType, bool hide = false);
	ObjectCard(const ObjectCard& cpy);
	~ObjectCard();

	// @ Action
	void Show();
	void Hide();

	void Select();
	void Deselect();
	void Hover();
	void UnHover();

	bool SuitMatch(const ObjectCard* other) const;

	// @ Virtual
	void Render(View& window) override;

	// @ Getters
	int GetNumber() const;
	eCardSuit GetSuit() const;
	bool IsHidden() const;


private:
	const static rchar TEXTURE_PIECES[];
	const static rchar TEXTURE_HIDDEN[];
	const static rchar TEXTURE_EMPTY[];
	const static int TEXTURE_PIECE_COUNT = 35;
	
	const static rchar TEXTURE_SUITS[];
	const static rchar TEXTURE_SELECT = '#';
	const static rchar TEXTURE_HOVER = '%';
	const static int INDEX_NUMBER_ONE = 9;
	const static int INDEX_CENTRE_SUIT = 17;
	const static int INDEX_SUITS[];
	const static int INDEX_NUMBER_TWO = 25;
	const static int INDEX_SELECT = 6;

	int mNumber;
	eCardSuit mSuit;
	AsciiTexture* mTexture = nullptr;
	bool mIsHidden = true;

};

