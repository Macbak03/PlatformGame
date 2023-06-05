#include "Node.h"

Node::Node(Node* parentNode)
{
    if (parentNode != nullptr)
    {
        (parentNode->children).push_back(this);
    }
    this->parentNode = parentNode;
}

Node::~Node()
{
    if (parentNode != nullptr) 
    {
        auto iterator = std::find(parentNode->children.begin(), parentNode->children.end(), this);
        if (iterator != parentNode->children.end())
        {
            parentNode->children.erase(iterator);
        }
    }
    
}


void Node::draw(sf::RenderTarget& target, const sf::Transform& parentTransform) const
{
    {
        sf::Transform combinedTransform = parentTransform * transformable.getTransform();

        onDraw(target, combinedTransform);

        for (std::size_t i = 0; i < children.size(); ++i)
            children[i]->draw(target, combinedTransform);
    }
}

sf::Transform Node::getGlobalTransform()
{
    if (parentNode != nullptr)
    {
        sf::Transform globalTransform = parentNode->getGlobalTransform() * transformable.getTransform();
        return globalTransform;
    }
    return transformable.getTransform();
}

void Node::move(sf::Vector2f& offset)
{
    transformable.move(offset);
}

void Node::move(float x, float y)
{
    transformable.move(x, y);
}

void Node::scale(sf::Vector2f& factors)
{
    transformable.scale(factors);
}

void Node::flipX()
{
    auto factors = sf::Vector2f(-1.f, 1.f);
    scale(factors);
}

void Node::setLocalPosition(sf::Vector2f& position)
{
    transformable.setPosition(position);
}

void Node::setLocalPosition(float x, float y)
{
    transformable.setPosition(x, y);
}

void Node::setOrigin(float x, float y)
{
    transformable.setOrigin(x, y);
}

void Node::setOrigin(sf::Vector2f origin)
{
    transformable.setOrigin(origin);
}

sf::Vector2f Node::getGlobalPosition()
{
    sf::Vector2f globalPosition = parentNode->getGlobalTransform().transformPoint(transformable.getPosition());
    return globalPosition;
}

sf::Vector2f Node::getLocalPosition()
{
    return transformable.getPosition();
}
