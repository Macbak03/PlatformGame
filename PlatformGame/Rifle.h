#pragma once
#include "Weapon.h"
class Rifle : public Weapon
{
private:
	void loadTexture() override;
	void initTexture() override;
public:
	Rifle(Node* parentNode, Bullets& bullets);
};

