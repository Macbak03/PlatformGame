#pragma once
#include "Weapon.h"
class Shotgun : public Weapon
{
private:
	void loadTexture() override;
	void initTexture() override;
public:
	Shotgun(Node* parentNode, Bullets& bullets);
};

