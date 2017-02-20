//
// Nibbler.hpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Sat Mar 15 14:13:33 2014 Quentin ROYER
// Last update Sun Apr  6 22:47:31 2014 Quentin ROYER
//

#ifndef NIBBLER_HPP_
# define NIBBLER_HPP_

# include <sstream>
# include <unistd.h>
# include <stdlib.h>
# include "IGraphicalInterface.hpp"
# include "DLLoader.hpp"
# include "Map.hpp"
# include "Snake.hpp"

class				Nibbler
{
public:
  Nibbler(const char *,
	  const char *,
	  const std::string &,
	  const std::string &);
  ~Nibbler();
  void			       	start(bool);
  int			       	end();
  void			       	loop();
  void			       	drawAll();
  void			       	manageEvents();
  void			       	manageCollisions();
  void			       	manageCycle();
  void			      	manageScrolling(Vector2f &);
  void			       	spawnFood();
private:
  int		       		_blockSize;
  int		       		_score;
  int		       		_lastEvent;
  unsigned int	       		_cycle;
  float		       		_speed;
  std::string	       		_texturePack;
  IGraphicalInterface  		*_gi;
  Map		       		*_map;
  Snake		       		*_snake;
  Element	       		*_food;
  Vector2i	       		_size;
  DLLoader	       		_loader;
  IGraphicalInterface	       	*(*_giConstructor)(const Vector2i &,
						   const Vector2i &,
						   const std::string &,
						   bool);
  void			       	(*_giDestructor)(IGraphicalInterface *);
};

#endif /* !NIBBLER_HPP_ */
