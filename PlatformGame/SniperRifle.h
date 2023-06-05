#pragma once
#include "Weapon.h"
class SniperRifle : public Weapon
{
private:
	void loadTexture() override;
	void initTexture() override;
public:
	SniperRifle(Node* parentNode, Bullets& bullets);
};

