//
// Element.hpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Wed Mar 26 01:37:23 2014 Quentin ROYER
// Last update Sun Apr  6 21:18:46 2014 Quentin ROYER
//

#ifndef ELEMENT_HPP_
# define ELEMENT_HPP_

# include <vector>
# include "Vector2.hpp"
# include "IGraphicalInterface.hpp"

class				Element
{
public:
  Element(const std::vector<int> &, const Vector2f &, unsigned int);
  ~Element();
  const std::vector<int>	&getSpriteIds() const;
  int				getCurrentSpriteId() const;
  const Vector2f		&getPosition() const;
  bool				isColliding(const Element &) const;
  void				setPosition(const Vector2f &);
  void				draw(IGraphicalInterface *);
  void				move(const Vector2f &);
  void				animate(float);
protected:
  std::vector<int>	       	_spriteIds;
  int				_currentSpriteId;
  Vector2f			_position;
  unsigned int			_blockSize;
  float				_cycle;
};

#endif /* !ELEMENT_HPP_ */
