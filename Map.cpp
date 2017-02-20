//
// Map.cpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Tue Mar 18 01:44:42 2014 Quentin ROYER
// Last update Sun Apr  6 22:46:11 2014 Quentin ROYER
//

#include "Map.hpp"
#include <iostream>

Map::Map(const Vector2i &size,
	 unsigned int blockSize) :
  _size(size),
  _blockSize(blockSize),
  _id(-1),
  _wallTexture(""),
  _groundTexture("")
{
  if (size.x < 4 || size.y < 3)
    throw ("Invalid map dimensions : cannot place snake.");
  else if (size.x + size.y > 200)
    throw ("Invalid map dimensions : map is too big !");
}

Map::~Map()
{
}

const Vector2i	       	&Map::getSize() const
{
  return (_size);
}

const Vector2f		&Map::getPosition() const
{
  return (_position);
}

void		       	Map::setTextures(const std::string &wallTexture,
					 const std::string &groundTexture)
{
  _wallTexture = wallTexture;
  _groundTexture = groundTexture;
}

void		       	Map::generate(IGraphicalInterface *gi)
{
  int	       		x;
  int	       		y;
  int	       		groundSpriteId;
  int	       		wallSpriteId;

  _id = gi->createImage(Vector2i(_size.x * _blockSize, _size.y * _blockSize));
  groundSpriteId = gi->createSprite(_groundTexture);
  wallSpriteId = gi->createSprite(_wallTexture);
  for (x = 0 ; x != _size.x ; ++x)
    for (y = 0 ; y != _size.y ; ++y)
      {
        gi->drawSpriteToImage(Vector2f(x * _blockSize, y * _blockSize), groundSpriteId, _id);
        if (x == 0 || x == _size.x - 1 || y == 0 || y == _size.y - 1)
          gi->drawSpriteToImage(Vector2f(x * _blockSize, y * _blockSize), wallSpriteId, _id);
      }
  _position.x = gi->getWindowSize().x / 2.0f - _size.x * _blockSize / 2.0f;
  _position.y = gi->getWindowSize().y / 2.0f - _size.y * _blockSize / 2.0f;
  
}

void	      	       	Map::draw(IGraphicalInterface *gi)
{
  gi->drawImageToWindow(_position, _id);
}

void	       		Map::move(const Vector2f &movement)
{
  _position.x += movement.x;
  _position.y += movement.y;
}
