#include "ObjectCardRow.h"
#include "ObjectDeck.h"
#include "ObjectCard.h"
#include "Vector2.h"
#include "uMaths.h"

#include <iterator>

ObjectCardRow::ObjectCardRow(const Vector2& position, ObjectDeck& deck, int rowCount, int cardOffset) 
	: Object(position), mCardOffset(cardOffset)
{
	Vector2 pos(position);
	for (int i = 0; i < rowCount; i++)
	{
		ObjectCard* card = deck.FetchDirect();
		card->SetPosition(pos);
		mRow.push_back(card);

		pos.y += mCardOffset;
	}
	mRow.back()->Show();

	mEmptyRow = new ObjectCard(position, ' ');
}
ObjectCardRow::ObjectCardRow(const ObjectCardRow& cpy) : Object(cpy)
{
	mRow = cpy.mRow;
	mEmptyRow = new ObjectCard(*cpy.mEmptyRow);
	mCardOffset = cpy.mCardOffset;
}
ObjectCardRow::~ObjectCardRow()
{
	if (HasCardsLeft())
	{
		for (ObjectCard* card : mRow)
		{
			delete card;
			card = nullptr;
		}
	}

	delete mEmptyRow;
	mEmptyRow = nullptr;
}

// @ Virtual
void ObjectCardRow::Render(View& window)
{
	if (HasCardsLeft())
	{
		for (ObjectCard* card : mRow)
			card->Render(window);
	}
	else
		mEmptyRow->Render(window);
}

// @ Action
ObjectCardRow* ObjectCardRow::Select(int indexFrom)
{
	if (!HasCardsLeft())
		return nullptr;

	std::list<ObjectCard*> listOfCards;
	GetListOfCards(listOfCards, indexFrom);
	for (ObjectCard* card : listOfCards)
		card->Select();

	return this;
}
ObjectCardRow* ObjectCardRow::Deselect(int indexFrom)
{
	if (!HasCardsLeft())
		return nullptr;

	std::list<ObjectCard*> listOfCards;
	GetListOfCards(listOfCards, indexFrom);
	for (ObjectCard* card : listOfCards)
		card->Deselect();


	return nullptr;
}

std::list<ObjectCard*> ObjectCardRow::Fetch(int indexFrom)
{
	std::list<ObjectCard*> collectList;
	if (!HasCardsLeft())
		return collectList;

	for (int i = GetTopIndex(); i >= indexFrom; i--)
	{
		ObjectCard* card = mRow.back();
		if (card->IsHidden())
			break;

		card->Deselect();
		collectList.push_front(card);

		mRow.pop_back();
	}

	if(mRow.size() >= 1)
		mRow.back()->Show();

	return collectList;
}
ObjectCard* ObjectCardRow::Fetch()
{
	ObjectCard* card = mRow.back();
	mRow.pop_back();

	if(mRow.size() >= 1)
		mRow.back()->Show();

	card->Deselect();

	return card;
}

void ObjectCardRow::PutBack(const std::list<ObjectCard*>& cards)
{
	if (cards.size() < 1) return;

	Vector2 pos;
	for (ObjectCard* card : cards)
	{
		if (mRow.size() > 0)
		{
			ObjectCard* prevCard = mRow.back();
			pos = prevCard->GetPosition();
			pos.y += mCardOffset;
		}
		else
			pos = *mPosition;

		card->SetPosition(pos);
		mRow.push_back(card);
	}
}
void ObjectCardRow::PutBack(ObjectCard* card)
{
	if (!card) return;

	Vector2 pos;
	if (mRow.size() >= 1)
	{
		ObjectCard* prevCard = mRow.back();
		pos = prevCard->GetPosition();
		pos.y += mCardOffset;
	}
	else
		pos = *mPosition;

	card->SetPosition(pos);
	mRow.push_back(card);
}


int ObjectCardRow::Hover(int indexFrom)
{
	if (!HasCardsLeft())
	{
		mEmptyRow->Hover();
		return indexFrom;
	}

	std::list<ObjectCard*> listOfCards;
	GetListOfCards(listOfCards, indexFrom);
	for (ObjectCard* card : listOfCards)
		card->Hover();

	return indexFrom;
}
void ObjectCardRow::HoverTop()
{
	if (!HasCardsLeft())
	{
		mEmptyRow->Hover();
		return;
	}
	
	mRow.back()->Hover();
}

int ObjectCardRow::UnHover(int indexFrom)
{
	if (!HasCardsLeft())
	{
		mEmptyRow->UnHover();
		return indexFrom;
	}

	util::Clamp(indexFrom, mRow.size() - 1);

	std::list<ObjectCard*> listOfCards;
	GetListOfCards(listOfCards, indexFrom);
	for (ObjectCard* card : listOfCards)
		card->UnHover();

	return indexFrom;
}
void ObjectCardRow::UnHoverTop()
{
	if (!HasCardsLeft())
	{
		mEmptyRow->UnHover();
		return;
	}

	mRow.back()->UnHover();
}

// @ Getter
bool ObjectCardRow::HasCardsLeft() const
{
	return mRow.size() > 0;
}

int ObjectCardRow::GetTopIndex() const
{
	return mRow.size() - 1;
}

void ObjectCardRow::GetListOfCards(std::list<ObjectCard*>& cards, int& sIndex)
{
	cards.clear();
	util::Clamp(sIndex, mRow.size() - 1);

	/*if (sIndex == GetTopIndex())
	{
		cards.push_back(mRow.back());
		return;
	}*/

	auto top = mRow.begin();
	for (unsigned i = sIndex; i < mRow.size(); i++)
	{
		ObjectCard* card = (*std::next(top, i));
		if (card->IsHidden())
		{
			sIndex++;
			break;
		}
		cards.push_back(card);
	}
}

ObjectCard* ObjectCardRow::PeekAtCard(int index) const
{
	util::Clamp(index, mRow.size() - 1);
	ObjectCard* card = (*std::next(mRow.begin(), index));

	return card;
}

ObjectCard* ObjectCardRow::PeekAtTopCard() const
{
	return mRow.back();
}