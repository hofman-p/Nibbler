//
// Nibbler.cpp for nibbler in /home/royer_q/depots/cpp_nibbler
//
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
//
// Started on  Sat Mar 15 14:16:20 2014 Quentin ROYER
// Last update Sun Apr  6 23:00:19 2014 Quentin ROYER
//

#include "Nibbler.hpp"

Nibbler::Nibbler(const char *width,
		 const char *height,
		 const std::string &dynlibName,
		 const std::string &texturePack) :
  _blockSize(64),
  _score(0),
  _lastEvent(0),
  _cycle(0),
  _speed(0.0f),
  _texturePack(texturePack),
  _gi(NULL),
  _map(NULL),
  _snake(NULL),
  _food(NULL)
{
  std::istringstream		iss_width(width);
  std::istringstream	       	iss_height(height);

  _loader.loadLibrary(dynlibName.c_str());
  _loader.loadSymbol("construct_gi", &_giConstructor);
  _loader.loadSymbol("destroy_gi", &_giDestructor);
  iss_width >> _size.x;
  iss_height >> _size.y;
  _map = new Map(_size, _blockSize);
  _snake = new Snake(_blockSize);
}

Nibbler::~Nibbler()
{
  if (_map)
    delete (_map);
  if (_snake)
    delete (_snake);
  if (_food)
    delete (_food);
}

void		       		Nibbler::start(bool isFirst)
{
  _gi = _giConstructor(Vector2i(0, 0), Vector2i(0, 0), "Nibbler", isFirst);
  _map->setTextures(std::string(_texturePack + "/wall0.png"),
		    std::string(_texturePack + "/ground0.png"));
  _snake->setTextures(_texturePack);
  _map->generate(_gi);
  _snake->generate(_gi, _map->getPosition(), _map->getSize());
  this->spawnFood();
}

int	       			Nibbler::end()
{
  _giDestructor(_gi);
  return (_score);
}

void			       	Nibbler::loop()
{
  while (_gi->isRunning())
    {
      _gi->processEvents();
      this->manageEvents();
      this->manageCollisions();
      this->manageCycle();
      this->drawAll();
      _gi->display();
    }
}

void		       		Nibbler::drawAll()
{
  _map->draw(_gi);
  _snake->draw(_gi);
  _food->draw(_gi);
}

void	       			Nibbler::manageEvents()
{
  if (_gi->isKeyDown("ESCAPE"))
    _gi->close();
  if (_gi->isKeyDown("LEFT"))
    _lastEvent = -1;
  else if (_gi->isKeyDown("RIGHT"))
    _lastEvent = 1;
}

void	       			Nibbler::manageCollisions()
{
  if (_snake->mapCollision(*_map, _blockSize) || _snake->selfCollision())
    _gi->close();
  if (_snake->foodCollision(*_food))
    {
      _snake->addElement();
      this->spawnFood();
      _score += 10;
    }
}

void	       			Nibbler::manageCycle()
{
  Vector2f     			movement;

  if (_cycle == 20)
    {
      _cycle = 0;
      _snake->turn(_lastEvent);
      _lastEvent = 0;
      _gi->resetKeyboard();
    }
  movement = _snake->dynamicMove(0.05f);
  _map->move(movement);
  _snake->move(movement);
  _food->move(movement);
  this->manageScrolling(movement);
  _snake->animate(2.0f);
  _food->animate(2.0f);
  ++_cycle;
}

void	       			Nibbler::manageScrolling(Vector2f &movement)
{
  Vector2i	       		mapSize(_map->getSize());
  Vector2f	       		mapPos(_map->getPosition());
  Vector2i	       		screenSize(_gi->getWindowSize());
  Vector2f	       		snakePos(_snake->getElements().at(0).getPosition());

  mapSize.x *= _blockSize;
  mapSize.y *= _blockSize;
  if ((mapPos.x > 0 ||
       (snakePos.x < screenSize.x / 2.0f && movement.x < 0)) ||
      (mapPos.x + mapSize.x < screenSize.x ||
       (snakePos.x > screenSize.x / 2.0f && movement.x > 0)))
    {
      movement.x = -movement.x;
      _map->move(Vector2f(movement.x, 0.0f));
      _snake->move(Vector2f(movement.x, 0.0f));
      _food->move(Vector2f(movement.x, 0.0f));
    }
  if ((mapPos.y > 0 ||
       (snakePos.y < screenSize.y / 2.0f && movement.y < 0)) ||
      (mapPos.y + mapSize.y < screenSize.y ||
       (snakePos.y > screenSize.y / 2.0f && movement.y > 0)))
    {
      movement.y = -movement.y;
      _map->move(Vector2f(0.0f, movement.y));
      _snake->move(Vector2f(0.0f, movement.y));
      _food->move(Vector2f(0.0f, movement.y));
    }
}

void	       			Nibbler::spawnFood()
{
  Vector2f		       	position;
  std::vector<int>	       	spriteIds;
  bool			       	isOk = false;
  std::string		       	spriteName;
  unsigned int		       	i;

  if (_food)
    {
      spriteIds = _food->getSpriteIds();
      delete (_food);
    }
  else
    for (i = 0 ; i != 4 ; ++i)
      {
	spriteName = std::string(_texturePack + "/food");
	spriteName += i + '0';
	spriteName += ".png";
	spriteIds.push_back(_gi->createSprite(spriteName));
      }
  _food = new Element(spriteIds, Vector2f(0, 0), _blockSize);
  while (!isOk)
    {
      isOk = true;
      position.x = (rand() % (_map->getSize().x - 2) + 1) * _blockSize + _map->getPosition().x;
      position.y = (rand() % (_map->getSize().y - 2) + 1) * _blockSize + _map->getPosition().y;
      _food->setPosition(position);
      for (i = 0 ; i != _snake->getElements().size() ; ++i)
	{
	  if (_food->isColliding(_snake->getElements().at(i)))
	    isOk = false;
	  if (i != 0 && _food->isColliding(_snake->getElements().at(i - 1)))
	    isOk = false;
	  if (i != _snake->getElements().size() - 1 &&
	      _food->isColliding(_snake->getElements().at(i + 1)))
	    isOk = false;
	}
    }
}
