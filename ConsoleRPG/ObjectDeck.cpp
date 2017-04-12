#include "ObjectDeck.h"
#include "ObjectCard.h"
#include "Vector2.h"
#include <algorithm>

#include <list>

// @ Construction
ObjectDeck::ObjectDeck(const Vector2& position, float placementOffset) 
	: Object(position)
{
	for (int i = 0; i < SUIT_AMOUNT; i++)
	{
		for (int j = 0; j < NUMBER_AMOUNT; j++)
		{
			int startIndex = j + 1;
			ObjectCard* card = new ObjectCard(position, startIndex, (eCardSuit)i);
			card->Hide();
			mDeck.push(card);
		}
	}
	Shuffle();

	mEmptyDeck = new ObjectCard(position, 'V');

	mPlacementPos = new Vector2(position.x - placementOffset, position.y);
}
ObjectDeck::ObjectDeck(const ObjectDeck& cpy) : Object(cpy)
{
	mDeck = cpy.mDeck;
	mPutoutDeck = cpy.mPutoutDeck;
	mPlacementPos = new Vector2(*cpy.mPlacementPos);
	mEmptyDeck = new ObjectCard(*cpy.mPosition, 'V');
}
ObjectDeck::~ObjectDeck()
{
	while (mDeck.size() > 0)
	{
		delete mDeck.front();
		mDeck.front() = nullptr;
		mDeck.pop();
	}

	while (mPutoutDeck.size() > 0)
	{
		delete mPutoutDeck.top();
		mPutoutDeck.top() = nullptr;
		mPutoutDeck.pop();
	}

	delete mEmptyDeck;
	mEmptyDeck = nullptr;

	delete mPlacementPos;
	mPlacementPos = nullptr;
}

// @ Overload
void ObjectDeck::Render(View& window)
{
	if (HasHiddenCardsLeft())
		mDeck.front()->Render(window);
	else
		mEmptyDeck->Render(window);

	if(HasShownCardsLeft())
		mPutoutDeck.top()->Render(window);
}

// @ Actions
void ObjectDeck::Select()
{
	if (HasShownCardsLeft())
		mPutoutDeck.top()->Select();
}
void ObjectDeck::Deselect()
{
	if (HasShownCardsLeft())
		mPutoutDeck.top()->Deselect();
}

void ObjectDeck::PlaceCard()
{
	if (!HasHiddenCardsLeft())
		return;

	ObjectCard* card = mDeck.front();
	card->SetPosition(*mPlacementPos);
	card->Show();

	mPutoutDeck.push(card);
	mDeck.pop();
}

ObjectCard* ObjectDeck::Fetch()
{
	if (!HasShownCardsLeft())
		return nullptr;

	ObjectCard* card = mPutoutDeck.top();
	mPutoutDeck.pop();
	return card;
}

ObjectCard* ObjectDeck::FetchDirect()
{
	ObjectCard* card = mDeck.front();
	mDeck.pop();
	return card;
}

void ObjectDeck::Shuffle()
{
	/// Store all the cards in a temporary vector
	std::vector<ObjectCard*> tempDeck;
	const int deckSize = mDeck.size();

	tempDeck.reserve(deckSize);
	for (int i = 0; i < deckSize; i++)
	{
		tempDeck.push_back(mDeck.front());
		mDeck.pop();
	}
	/// shuffle the vector
	std::random_shuffle(tempDeck.begin(), tempDeck.end());

	/// but the cards back
	for (ObjectCard* card : tempDeck)
		mDeck.push(card);
}

void ObjectDeck::PutBack(ObjectCard* card)
{
	mPutoutDeck.push(card);
}

void ObjectDeck::Reset()
{
	// To make sure that the stack is added the right way around
	/// The original top value needs to be placed again
	/*std::list<ObjectCard*> shownCardPile;
	while (HasShownCardsLeft())
	{
		ObjectCard* card = mPutoutDeck.top();
		card->SetPosition(*mPosition);
		card->Hide();

		shownCardPile.push_front(card);
		mPutoutDeck.pop();
	}*/

	while (HasShownCardsLeft())
	{
		ObjectCard* card = mPutoutDeck.top();
		card->SetPosition(*mPosition);
		card->Hide();

		mDeck.push(card);
		//shownCardPile.push_front(card);
		mPutoutDeck.pop();
	}
}

// @ Getter
bool ObjectDeck::HasHiddenCardsLeft() const
{
	return mDeck.size() > 0;
}

bool ObjectDeck::HasShownCardsLeft() const
{
	return mPutoutDeck.size() > 0;
}

ObjectCard* ObjectDeck::PeekAtTopCardInOpenDeck() const
{
	return mPutoutDeck.top();
}