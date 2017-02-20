//
// Clock.hpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Fri Apr  4 23:09:56 2014 Quentin ROYER
// Last update Fri Apr  4 23:36:32 2014 Quentin ROYER
//

#ifndef CLOCK_HPP_
# define CLOCK_HPP_

# include <time.h>

class				Clock
{
public:
  Clock();
  ~Clock();
  void				restartTimer();
  int				getElapsedTime() const;
private:
  int				_startTime;
};

# endif /* !CLOCK_HPP_ */
