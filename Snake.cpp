//
// Snake.cpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Fri Mar 21 21:36:49 2014 Quentin ROYER
// Last update Sun Apr  6 22:05:48 2014 Quentin ROYER
//

#include "Snake.hpp"

Snake::Snake(const unsigned int &blockSize) :
  _blockSize(blockSize),
  _direction(1)
{
}

Snake::~Snake()
{
}

const std::vector<DynamicElement>	&Snake::getElements() const
{
  return (_elements);
}

bool					Snake::mapCollision(const Map &map,
							    unsigned int blockSize) const
{
  Vector2f				offset(map.getPosition());
  Vector2f				elementPosition(_elements[0].getPosition());

  if (elementPosition.x < offset.x + blockSize / 2.0f ||
      elementPosition.y < offset.y + blockSize / 2.0f ||
      elementPosition.x > offset.x + map.getSize().x * blockSize - blockSize * 1.5f ||
      elementPosition.y > offset.y + map.getSize().y * blockSize - blockSize * 1.5f)
    return (true);
  return (false);
}

bool					Snake::foodCollision(const Element &food) const
{
  if (food.isColliding(_elements[0]))
    return (true);
  return (false);
}

bool					Snake::selfCollision() const
{
  unsigned int				i;
  Vector2f				selfCenter;
  Vector2f				elementPosition;

  selfCenter.x = _elements[0].getPosition().x + _blockSize / 2.0f;
  selfCenter.y = _elements[0].getPosition().y + _blockSize / 2.0f;
  for (i = 4 ; i != _elements.size() ; ++i)
    {
      elementPosition = _elements[i].getPosition();
      if (selfCenter.x > elementPosition.x && selfCenter.x < elementPosition.x + _blockSize &&
	  selfCenter.y > elementPosition.y && selfCenter.y < elementPosition.y + _blockSize)
	return (true);
    }
  return (false);
}

void					Snake::setTextures(const std::string &texturePack)
{
  unsigned int				i;
  std::string				headTexture;
  std::string				bodyTexture;

  for (i = 0 ; i != 4 ; ++i)
    {
      headTexture = texturePack + "/head";
      headTexture += i + '0';
      headTexture += ".png";
      bodyTexture = texturePack + "/body";
      bodyTexture += i + '0';
      bodyTexture += ".png";
      _headTexture[i] = headTexture;
      _bodyTexture[i] = bodyTexture;
    }
}

void					Snake::generate(IGraphicalInterface *gi,
							const Vector2f &mapPosition,
							const Vector2i &mapSize)
{
  unsigned int				i;
  Vector2f				spawnPosition;
  Vector2f				position;
  std::vector<int>			headSpriteId;
  std::vector<int>			bodySpriteId;

  for (i = 0 ; i != 4 ; ++i)
    {
      headSpriteId.push_back(gi->createSprite(_headTexture[i]));
      bodySpriteId.push_back(gi->createSprite(_bodyTexture[i]));
    }
  spawnPosition.x = mapPosition.x + (mapSize.x / 2 * _blockSize) + _blockSize;
  spawnPosition.y = mapPosition.y + (mapSize.y / 2 * _blockSize);
  _position = spawnPosition;
  for (i = 0 ; i != 4 ; ++i)
    {
      position.x = spawnPosition.x - i * _blockSize;
      position.y = spawnPosition.y;
      if (i == 0)
	_elements.push_back(DynamicElement(i, position, headSpriteId, _blockSize, 1));
      else
	_elements.push_back(DynamicElement(i, position, bodySpriteId, _blockSize, 1));
    }
}

void					Snake::addElement()
{
  unsigned int				i;
  std::vector<int>			spriteIds;
  std::vector<int>			direction;
  std::vector<int>			directionCount;
  Vector2f				position;

  i = _elements.size();
  spriteIds = _elements[i - 1].getSpriteIds();
  direction = _elements[i - 1].getDirection();
  directionCount = _elements[i - 1].getDirectionCount();
  position = _elements[i - 1].getPosition();
  direction.insert(direction.begin(), 5);
  directionCount.insert(directionCount.begin(), 20);
  _elements.push_back(DynamicElement(i, position, spriteIds, _blockSize, 0));
  _elements[i].setDirection(direction, directionCount);
}

void					Snake::draw(IGraphicalInterface *gi)
{
  unsigned int				i;

  for (i = 0 ; i != _elements.size() ; ++i)
    _elements[i].draw(gi);
}

const Vector2f				Snake::dynamicMove(float elapsedTime)
{
  Vector2f				movement(_elements[0].getPosition());
  unsigned int				i;

  for (i = 0 ; i != _elements.size() ; ++i)
    _elements[i].dynamicMove(elapsedTime);
  movement.x -= _elements[0].getPosition().x;
  movement.y -= _elements[0].getPosition().y;
  return (movement);
}

void					Snake::move(const Vector2f &movement)
{
  unsigned int				i;

  for (i = 0 ; i != _elements.size() ; ++i)
    _elements[i].move(movement);
}

void					Snake::turn(int direction)
{
  unsigned int				i;

  _direction += direction;
  if (_direction < 0)
    _direction = 3;
  else if (_direction > 3)
    _direction = 0;
  for (i = 0 ; i != _elements.size() ; ++i)
    _elements[i].turn(_direction);
}

void					Snake::animate(float elapsedTime)
{
  unsigned int				i;

  for (i = 0 ; i != _elements.size() ; ++i)
    _elements[i].animate(elapsedTime);
}
