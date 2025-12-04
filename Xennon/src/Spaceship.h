#pragma once
#include "Mechanism/Pawn.h"

class Spaceship : public Mechanism::Pawn
{
public:

	void PlayerUpdate(float deltaTime);

private:

	float velocity;

};

