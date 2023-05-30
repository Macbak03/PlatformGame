#include "Collider.h"


bool Collider::xCausesCollision(sf::Vector2f thisGlobalPosition, sf::Vector2f otherGlobalPosition, Collider& otherCollider, float speedX)
{
    bool hasCollision = this->intersects(thisGlobalPosition, otherGlobalPosition, otherCollider);
    thisGlobalPosition.x -= speedX;
    bool hadCollision = this->intersects(thisGlobalPosition, otherGlobalPosition, otherCollider);
    return hasCollision && !hadCollision;
}

bool Collider::yCausesCollision(sf::Vector2f thisGlobalPosition, sf::Vector2f otherGlobalPosition, Collider& otherCollider, float speedY)
{
    bool hasCollision = this->intersects(thisGlobalPosition, otherGlobalPosition, otherCollider);
    thisGlobalPosition.y -= speedY;
    bool hadCollision = this->intersects(thisGlobalPosition, otherGlobalPosition, otherCollider);
    return hasCollision && !hadCollision;
}

bool Collider::intersects(sf::Vector2f thisGlobalPosition, sf::Vector2f otherGlobalPosition, Collider& otherCollider)
{
    float thisColliderTop = thisGlobalPosition.y + this->offset.y;
    float thisColliderBottom = thisColliderTop + this->size.y;
    float thisColliderLeft = thisGlobalPosition.x + this->offset.x;
    float thisColliderRight = thisColliderLeft + this->size.x;

    float otherColliderTop = otherGlobalPosition.y + otherCollider.offset.y;
    float otherColliderBottom = otherColliderTop + otherCollider.size.y;
    float otherColliderLeft = otherGlobalPosition.x + otherCollider.offset.x;
    float otherColliderRight = otherColliderLeft + otherCollider.size.x;

    if (thisColliderTop > otherColliderBottom)
    {
        return false;
    }
    if (thisColliderBottom < otherColliderTop)
    {
        return false;
    }
    if (thisColliderLeft > otherColliderRight)
    {
        return false;
    }
    if (thisColliderRight < otherColliderLeft)
    {
        return false;
    }
    return true;
}
