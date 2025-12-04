#pragma once
#include "Mechanism/Pawn.h"

class Enemy : public Mechanism::Pawn
{

public:

	void EnemyUpdate(float deltaTime);

private:

	float velocity;

};

