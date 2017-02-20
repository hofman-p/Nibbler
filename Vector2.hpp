//
// Vector2.hpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Fri Mar 21 23:49:05 2014 Quentin ROYER
// Last update Sun Apr  6 22:06:03 2014 Quentin ROYER
//

#ifndef VECTOR2_HPP_
# define VECTOR2_HPP_

template <typename T>
class					Vector2
{
public:
  Vector2(T _x = 0, T _y = 0) : x(_x), y(_y) {}
  ~Vector2() {}
  T					x;
  T					y;
};

typedef Vector2<int>			Vector2i;
typedef Vector2<float>			Vector2f;
typedef Vector2<double>			Vector2d;
typedef Vector2<unsigned int>		Vector2u;

#endif /* !VECTOR2_HPP_ */
