#pragma once
#include <SFML/Graphics.hpp>
class Node
{
private:
    virtual void onDraw(sf::RenderTarget& target, const sf::Transform& transform) const = 0;
    Node* parentNode;
    sf::Transformable transformable;
    std::vector<Node*> children;
    sf::Transform getGlobalTransform();
protected:
    void draw(sf::RenderTarget& target, const sf::Transform& parentTransformable) const;
public:
    Node(Node* parentNode);
    ~Node();
    void move(sf::Vector2f& offset);
    void move(float x, float y);
    void scale(sf::Vector2f& factors);
    void flipX();
    void setLocalPosition(sf::Vector2f& position);
    void setLocalPosition(float x, float y);
    void setOrigin(float x, float y);
    void setOrigin(sf::Vector2f origin);
    sf::Vector2f getGlobalPosition();
    sf::Vector2f getLocalPosition();
   

};


