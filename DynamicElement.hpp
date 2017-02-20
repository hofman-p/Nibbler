//
// DynamicElement.hpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Wed Mar 26 01:52:04 2014 Quentin ROYER
// Last update Sun Apr  6 20:49:52 2014 Quentin ROYER
//

#ifndef DYNAMICELEMENT_HPP_
# define DYNAMICELEMENT_HPP_

# include <vector>
# include "Element.hpp"

class				DynamicElement : public Element
{
public:
  DynamicElement(int, const Vector2f &, const std::vector<int> &, unsigned int, int);
  ~DynamicElement();
  const std::vector<int>	&getDirection() const;
  const std::vector<int>	&getDirectionCount() const;
  void				setDirection(const std::vector<int> &, const std::vector<int> &); 
  void				dynamicMove(float);
  void				turn(int);
  void				moveUp(float);
  void				moveRight(float);
  void				moveDown(float);
  void				moveLeft(float);
private:
  int				_id;
  std::vector<int>		_direction;
  std::vector<int>		_directionCount;
  void				(DynamicElement::*_movementPtr[4])(float);
};

#endif /* !DYNAMICELEMENT_HPP_ */
