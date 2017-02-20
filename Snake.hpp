//
// Snake.hpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Fri Mar 21 21:35:06 2014 Quentin ROYER
// Last update Sun Apr  6 22:03:21 2014 Quentin ROYER
//

#ifndef SNAKE_HPP_
# define SNAKE_HPP_

# include <string>
# include "Map.hpp"
# include "DynamicElement.hpp"

class					Snake
{
public:
  Snake(const unsigned int &);
  ~Snake();
  const std::vector<DynamicElement>	&getElements() const;
  bool					mapCollision(const Map &,
						     unsigned int) const;
  bool					foodCollision(const Element &) const;
  bool					selfCollision() const;
  void					setTextures(const std::string &);
  void					generate(IGraphicalInterface *,
						 const Vector2f &,
						 const Vector2i &);
  void					addElement();
  void					draw(IGraphicalInterface *);
  const Vector2f			dynamicMove(float);
  void					move(const Vector2f &);
  void					turn(int);
  void					animate(float);
private:
  unsigned int				_blockSize;
  int					_direction;
  Vector2f				_position;
  std::vector<DynamicElement>		_elements;
  std::string				_headTexture[4];
  std::string				_bodyTexture[4];
};

#endif /* !SNAKE_HPP_ */
