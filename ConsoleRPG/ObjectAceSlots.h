#pragma once
#include "Object.h"

#include <vector>
#include <stack>

class Vector2;
class ObjectCard;
class ObjectAceSlots : public Object
{
public:
	ObjectAceSlots(const Vector2& startPos, int horizontalPadding, int verticalPadding);
	ObjectAceSlots(const ObjectAceSlots& cpy);
	virtual ~ObjectAceSlots();

	// @ Virtual method
	void Render(View& window) override;

	// @ Actions
	bool AttemptToAddCard(ObjectCard* card);
	bool HasWon(int winAmount);

private:
	std::vector<std::stack<ObjectCard*>> mAcePiles;
	std::vector<Vector2*> mPilePositions;


	const static int ACE_PILE_COUNT = 4;
};

