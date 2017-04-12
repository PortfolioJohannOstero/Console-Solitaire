#pragma once
#include "Object.h"
#include <list>

class ObjectCard;
class ObjectDeck;
class ObjectCardRow : public Object
{
public:
	ObjectCardRow(const Vector2& position, ObjectDeck& deck, int rowCount, int cardOffset);
	ObjectCardRow(const ObjectCardRow& cpy);
	~ObjectCardRow();

	// @ Virtual
	void Render(View& window) override;

	// @ Action
	ObjectCardRow* Select(int indexFrom);
	ObjectCardRow* Deselect(int indexFrom);
	std::list<ObjectCard*> Fetch(int indexFrom);
	ObjectCard* Fetch();

	void PutBack(const std::list<ObjectCard*>& card);
	void PutBack(ObjectCard* card);

	int Hover(int indexFrom);
	void HoverTop();

	int UnHover(int indexFrom);
	void UnHoverTop();

	// @ Getter
	bool HasCardsLeft() const;
	/// Gets the size of the row - 1 (the index)
	int GetTopIndex() const;
	/// Gets a const pointer to look at; It will NOT remove the card
	ObjectCard* PeekAtTopCard() const;
	ObjectCard* PeekAtCard(int index) const;


private:
	// @ Helper Methods
	void GetListOfCards(std::list<ObjectCard*>& cards, int& sIndex);

	std::list<ObjectCard*> mRow;
	ObjectCard* mEmptyRow = nullptr;

	int mCardOffset;
};

