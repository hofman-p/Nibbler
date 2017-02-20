//
// Element.cpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Wed Mar 26 01:40:16 2014 Quentin ROYER
// Last update Sun Apr  6 21:30:22 2014 Quentin ROYER
//

#include "Element.hpp"

Element::Element(const std::vector<int> &spriteIds,
		 const Vector2f &position,
		 unsigned int blockSize) :
  _spriteIds(spriteIds),
  _currentSpriteId(spriteIds[0]),
  _position(position),
  _blockSize(blockSize),
  _cycle(0.0f)
{
}

Element::~Element()
{
}

const std::vector<int>	&Element::getSpriteIds() const
{
  return (_spriteIds);
}

int	       		Element::getCurrentSpriteId() const
{
  return (_currentSpriteId);
}

const Vector2f		&Element::getPosition() const
{
  return (_position);
}

bool	       		Element::isColliding(const Element &element) const
{
  Vector2f		selfCenter;
  Vector2f		targetPosition(element.getPosition());
  
  selfCenter.x = _position.x + _blockSize / 2.0f;
  selfCenter.y = _position.y + _blockSize / 2.0f;
  if (selfCenter.x > targetPosition.x && selfCenter.x < targetPosition.x + _blockSize &&
      selfCenter.y > targetPosition.y && selfCenter.y < targetPosition.y + _blockSize)
    return (true);
  return (false);
}

void	       		Element::setPosition(const Vector2f &position)
{
  _position = position;
}

void	       		Element::draw(IGraphicalInterface *gi)
{
  gi->drawSpriteToWindow(_position, _currentSpriteId);
}

void	       		Element::move(const Vector2f &movement)
{
  _position.x += movement.x;
  _position.y += movement.y;
}

void	     	       	Element::animate(float elapsedTime)
{
  _cycle = _cycle + elapsedTime > _blockSize ? 0.0f : _cycle + elapsedTime;
  if (_cycle < _blockSize * 0.25f)
    _currentSpriteId = _spriteIds[0];
  else if (_cycle < _blockSize * 0.5f)
    _currentSpriteId = _spriteIds[1];
  else if (_cycle < _blockSize * 0.75f)
    _currentSpriteId = _spriteIds[2];
  else
    _currentSpriteId = _spriteIds[3];
}
