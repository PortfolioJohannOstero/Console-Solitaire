#pragma once
#include "Object.h"
#include <queue>
#include <stack>

class ObjectCard;
class View;
class ObjectDeck : public Object
{
public:
	const static int NUMBER_AMOUNT = 13;
	const static int SUIT_AMOUNT = 4;

	// @ Construction
	ObjectDeck(const Vector2& position, float placementOffset);
	ObjectDeck(const ObjectDeck& cpy);
	~ObjectDeck();

	// @ Overload
	void Render(View& window) override;

	// @ Actions
	void Select();
	void Deselect();

	void PlaceCard();
	ObjectCard* Fetch();
	void PutBack(ObjectCard* card);
	void Reset();

	ObjectCard* FetchDirect();

	void Shuffle();

	// @ Getter
	bool HasHiddenCardsLeft() const;
	bool HasShownCardsLeft() const;
	/// Gets a const pointer to look at; It will NOT remove the card
	ObjectCard* PeekAtTopCardInOpenDeck() const;

private:

	std::queue<ObjectCard*> mDeck;

	std::stack<ObjectCard*> mPutoutDeck;
	Vector2* mPlacementPos;

	ObjectCard* mEmptyDeck = nullptr;
};

