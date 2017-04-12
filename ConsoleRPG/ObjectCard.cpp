#include <Windows.h>
#include <string.h>

#include "ObjectCard.h"
#include "AsciiTexture.h"
#include "View.h"
#include "Vector2.h"

#include <iostream>

const rchar ObjectCard::TEXTURE_PIECES[]{ L"┌─────┐│ 5♥  ││  ♥  ││  ♥5 │└─────┘" };
const rchar ObjectCard::TEXTURE_HIDDEN[]{ L"┌─────┐│█████││█████││█████│└─────┘" };
const rchar ObjectCard::TEXTURE_EMPTY[] { L"┌─────┐│     ││     ││     │└─────┘" };
const rchar ObjectCard::TEXTURE_SUITS[]{ L"♥♦♣♠" };
const int ObjectCard::INDEX_SUITS[]{ 10, 24 };

// @ Construction
ObjectCard::ObjectCard(const Vector2& position, rchar centreSymbol)
	: Object(position), mNumber(-1), mSuit(eCardSuit::HEART)
{
	mTexture = new AsciiTexture(CARD_WIDTH, CARD_HEIGHT, TEXTURE_EMPTY);
	rchar* texture = mTexture->GetTexture();
	texture[INDEX_CENTRE_SUIT] = centreSymbol;
}
ObjectCard::ObjectCard(const Vector2& position, int cardNumber, eCardSuit suitType, bool hide)
	: Object(position), mNumber(cardNumber), mSuit(suitType)
{
	mTexture = new AsciiTexture(CARD_WIDTH, CARD_HEIGHT, TEXTURE_PIECES);
	if (hide)
		Hide();
	else
		Show();
}
ObjectCard::ObjectCard(const ObjectCard& cpy) : Object(cpy)
{
	int mNumber = cpy.GetNumber();
	eCardSuit mSuit = cpy.GetSuit();
	mTexture = new AsciiTexture(*cpy.mTexture);
}
ObjectCard::~ObjectCard()
{
	delete mTexture;
	mTexture = nullptr;
}


// @ Actions
void ObjectCard::Show()
{
	rchar* texture = mTexture->GetTexture();
	memcpy(texture, TEXTURE_PIECES, TEXTURE_PIECE_COUNT * sizeof(rchar));
	
	int suitOffset[2]{ 0,0 };

	if (mNumber != 10)
	{
		rchar numToChar = 'A';
		if (mNumber > 1)
		{
			switch (mNumber)
			{
			case 11: numToChar = 'J'; break;
			case 12: numToChar = 'Q'; break;
			case 13: numToChar = 'K'; break;
			default:
				numToChar = mNumber + '0';
				break;
			}
		}

		texture[INDEX_NUMBER_ONE] = numToChar;
		texture[INDEX_NUMBER_TWO] = numToChar;
	}
	/// If the number is 10, meaning double digits
	else
	{
		const rchar ten_one = '1';
		const rchar ten_zero = '0';

		texture[INDEX_NUMBER_ONE] = ten_one;
		texture[INDEX_NUMBER_ONE + 1] = ten_zero;
		suitOffset[0]++;

		texture[INDEX_NUMBER_TWO - 1] = ten_one;
		texture[INDEX_NUMBER_TWO] = ten_zero;
		suitOffset[1]--;
	}

	int suitIndicies = sizeof(INDEX_SUITS) / sizeof(INDEX_SUITS[0]);
	for (int i = 0; i < suitIndicies; i++)
		texture[INDEX_SUITS[i] + suitOffset[i]] = TEXTURE_SUITS[(int)mSuit];

	texture[INDEX_CENTRE_SUIT] = TEXTURE_SUITS[(int)mSuit];

	mIsHidden = false;
}
void ObjectCard::Hide()
{
	rchar* texture = mTexture->GetTexture();
	memcpy(texture, TEXTURE_HIDDEN, TEXTURE_PIECE_COUNT * sizeof(rchar));
	mIsHidden = true;
}

void ObjectCard::Select()
{
	rchar* texture = mTexture->GetTexture();
	texture[INDEX_SELECT] = TEXTURE_SELECT;
}
void ObjectCard::Deselect()
{
	rchar* texture = mTexture->GetTexture();
	texture[INDEX_SELECT] = TEXTURE_PIECES[INDEX_SELECT];
}

void ObjectCard::Hover()
{
	rchar* texture = mTexture->GetTexture();
	
	if(texture[INDEX_SELECT] != TEXTURE_SELECT)
		texture[INDEX_SELECT] = TEXTURE_HOVER;
}
void ObjectCard::UnHover()
{
	if (mTexture->GetTexture()[INDEX_SELECT] != TEXTURE_SELECT)
		Deselect();
}

bool ObjectCard::SuitMatch(const ObjectCard const* other) const
{
	const eCardSuit otherSuit = other->GetSuit();
	const eCardSuit centreSuit = eCardSuit::DIAMOND;

	return (mSuit <= centreSuit && otherSuit <= centreSuit) ||
		   (mSuit  > centreSuit && otherSuit  > centreSuit);
}

// @ Virtual
void ObjectCard::Render(View& window)
{
	window.FillBuffer(*mPosition, *mTexture);
}

// @ Getters
int ObjectCard::GetNumber() const
{
	return mNumber;
}
eCardSuit ObjectCard::GetSuit() const
{
	return mSuit;
}

bool ObjectCard::IsHidden() const
{
	return mIsHidden;
}