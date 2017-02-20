//
// Clock.cpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Fri Apr  4 23:13:03 2014 Quentin ROYER
// Last update Fri Apr  4 23:40:34 2014 Quentin ROYER
//

#include "Clock.hpp"

Clock::Clock()
{
}

Clock::~Clock()
{
}

void				Clock::restartTimer()
{
  _startTime = clock();
}

int				Clock::getElapsedTime() const
{
  return (clock() - _startTime);
}
