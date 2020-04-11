#ifndef OBJ_H
#define OBJ_H

#include <SFML/Graphics.hpp>

class Obj : public sf::CircleShape
{
   public:
      sf::Vector2f velocity;
      float bound;
      float mass;

      /** Default constructor */
      Obj(float,float = 10,unsigned int = 30);

      void setMass(float);
      float getMass();
      void addVelocity(sf::Vector2f);
      void makeMove();
      void setBound();
      void setVelocity(sf::Vector2f);
      sf::Vector2f getVelocity();



   protected:
   private:
};
#endif // OBJ_H
