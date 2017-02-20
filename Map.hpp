//
// Map.hpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Tue Mar 18 01:39:11 2014 Quentin ROYER
// Last update Sun Apr  6 21:48:37 2014 Quentin ROYER
//

#ifndef MAP_HPP_
# define MAP_HPP_

# include <string>
# include "Vector2.hpp"
# include "IGraphicalInterface.hpp"

class				Map
{
public:
  Map(const Vector2i &, unsigned int);
  ~Map();
  const Vector2i	       	&getSize() const;
  const Vector2f       		&getPosition() const;
  void		       		setTextures(const std::string &, const std::string &);
  void	       			generate(IGraphicalInterface *);
  void	       			draw(IGraphicalInterface *);
  void	       			move(const Vector2f &);
private:
  Vector2i       		_size;
  Vector2f		       	_position;
  unsigned int			_blockSize;
  int			       	_id;
  std::string		       	_wallTexture;
  std::string		       	_groundTexture;
};

#endif /* !MAP_HPP_ */
