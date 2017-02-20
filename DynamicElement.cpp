//
// DynamicElement.cpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Wed Mar 26 01:52:58 2014 Quentin ROYER
// Last update Sun Apr  6 21:45:21 2014 Quentin ROYER
//

#include "DynamicElement.hpp"

DynamicElement::DynamicElement(int id, const Vector2f &position,
			       const std::vector<int> &spriteIds,
			       unsigned int blockSize,
			       int direction) :
  Element(spriteIds, position, blockSize), _id(id)
{
  _movementPtr[0] = &DynamicElement::moveUp;
  _movementPtr[1] = &DynamicElement::moveRight;
  _movementPtr[2] = &DynamicElement::moveDown;
  _movementPtr[3] = &DynamicElement::moveLeft;
  _direction.push_back(direction);
  _directionCount.push_back((id + 1) * 20);
}

DynamicElement::~DynamicElement()
{
}

const std::vector<int>	&DynamicElement::getDirection() const
{
  return (_direction);
}

const std::vector<int>	&DynamicElement::getDirectionCount() const
{
  return (_directionCount);
}

void			DynamicElement::setDirection(const std::vector<int> &direction,
						     const std::vector<int> &directionCount)
{
  _direction = direction;
  _directionCount = directionCount;
}

void			DynamicElement::dynamicMove(float elapsedTime)
{
  if (_direction[0] != 5)
    (this->*_movementPtr[_direction[0]])(elapsedTime);
  ++_directionCount[_direction.size() - 1];
  --_directionCount[0];
  if (_directionCount[0] == 0)
    {
      _directionCount.erase(_directionCount.begin());
      _direction.erase(_direction.begin());
    }
}

void	       	       	DynamicElement::turn(int direction)
{
  _direction.push_back(direction);
  _directionCount.push_back(0);
}

void   	       		DynamicElement::moveUp(float elapsedTime)
{
  _position.y -= elapsedTime * _blockSize;
}

void   	       		DynamicElement::moveRight(float elapsedTime)
{
  _position.x += elapsedTime * _blockSize;
}

void   		       	DynamicElement::moveDown(float elapsedTime)
{
  _position.y += elapsedTime * _blockSize;
}

void   		       	DynamicElement::moveLeft(float elapsedTime)
{
  _position.x -= elapsedTime * _blockSize;
}
