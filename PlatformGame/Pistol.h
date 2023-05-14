#pragma once
#include "Weapon.h"
class Pistol : public Weapon
{
private:
	void loadTexture() override;
	void initTexture() override;
public:
	Pistol();
};

