#include "Obj.h"
#include <iostream>

Obj::Obj(float a, float m, unsigned int b):CircleShape(a,b)
{
   velocity = sf::Vector2f(0,0);
   bound = 0.5;
   mass = m;
   this->setOrigin(a,a);
}

void Obj::setMass(float m)
{
   mass = m;
}

float Obj::getMass()
{
   return mass;
}

void Obj::addVelocity(sf::Vector2f v)
{
   velocity += v;
}

void Obj::makeMove()
{
   this->setPosition(this->getPosition() + velocity);
}

void Obj::setBound()
{
   velocity.x=-velocity.x+velocity.x*bound;
   velocity.y=-velocity.y+velocity.y*bound;
}

void Obj::setVelocity(sf::Vector2f v)
{
   velocity = v;
}
sf::Vector2f Obj::getVelocity()
{
   return velocity;
}

/*
 sf::Vector2f Obj::gravity()
{
   sf::Vector2f pozus = this->getPosition();
   sf::Vector2f poz = o->getPosition();
   float f;
   f =
   sf::Vector2f result((poz.x-pozus.x)*f,(poz.y-pozus.y)*f);
}
*/
