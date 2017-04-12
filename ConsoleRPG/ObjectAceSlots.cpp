#include "ObjectAceSlots.h"
#include "ObjectCard.h"
#include "Vector2.h"

// @ Construction
ObjectAceSlots::ObjectAceSlots(const Vector2& startPos, int horizontalPadding, int verticalPadding) : Object(startPos)
{
	mAcePiles.reserve(ACE_PILE_COUNT);
	mPilePositions.reserve(ACE_PILE_COUNT);

	Vector2 pos = GetPosition();
	pos.y += verticalPadding;

	for (int i = 0; i < ACE_PILE_COUNT; i++)
	{
		std::stack<ObjectCard*> newPile;
		mAcePiles.push_back(newPile);

		mPilePositions.push_back(new Vector2(pos));
		pos.x += (ObjectCard::CARD_WIDTH + horizontalPadding) / 2;
	}
}
ObjectAceSlots::ObjectAceSlots(const ObjectAceSlots& cpy) : Object(cpy)
{
	mAcePiles = cpy.mAcePiles;
	mPilePositions = cpy.mPilePositions;
}
ObjectAceSlots::~ObjectAceSlots()
{
	for (std::stack<ObjectCard*> acePile : mAcePiles)
	{
		while (acePile.size() > 0)
		{
			ObjectCard* card = acePile.top();
			acePile.pop();

			delete card;
			card = nullptr;
		}
	}

	for (Vector2* pos : mPilePositions)
	{
		delete pos;
		pos = nullptr;
	}
}


// @ Virtual Methods
void ObjectAceSlots::Render(View& window)
{
	for (std::stack<ObjectCard*>& acePile : mAcePiles)
	{
		if(!acePile.empty())
			acePile.top()->Render(window);
	}
}

// @ Actions
bool ObjectAceSlots::AttemptToAddCard(ObjectCard* card)
{
	const int index = (int)card->GetSuit();
	std::stack<ObjectCard*>& acePile = mAcePiles[index];

	const int cardNumber = card->GetNumber();
	
	// if the pile is empty and the cardnumber is an ace
	if (acePile.empty())
	{
		if (cardNumber == 1)
		{
			acePile.push(card);
			card->SetPosition(*mPilePositions[index]);
			return true;
		}
	}
	// if the pile is not empty
	else if (cardNumber - 1 == acePile.top()->GetNumber())
	{
		acePile.push(card);
		card->SetPosition(*mPilePositions[index]);
		return true;
	}

	return false;
}

bool ObjectAceSlots::HasWon(int winAmount)
{
	for (std::stack<ObjectCard*>& pile : mAcePiles)
	{
		if (pile.size() < (size_t)winAmount)
			return false;
	}

	return true;
}