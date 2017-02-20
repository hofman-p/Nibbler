//
// IGraphicalInterface.hpp for nibbler in /home/royer_q/nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Wed Mar 12 08:58:40 2014 Quentin ROYER
// Last update Sun Apr  6 22:14:25 2014 Quentin ROYER
//

#ifndef IGRAPHICALINTERFACE_HPP_
# define IGRAPHICALINTERFACE_HPP_

# include <string>
# include "Vector2.hpp"

class				IGraphicalInterface
{
public:
  virtual ~IGraphicalInterface() {}
  virtual const Vector2i 	getWindowSize() const = 0;
  virtual bool			isRunning() const = 0;
  virtual bool			isKeyDown(const std::string &) = 0;
  virtual void			close() = 0;
  virtual void			display() = 0;
  virtual void			processEvents() = 0;
  virtual int			createSprite(const std::string &) = 0;
  virtual int			createImage(const Vector2i &) = 0;
  virtual void			drawSpriteToImage(const Vector2f &,
						  int,
						  int) = 0;
  virtual void			drawImageToWindow(const Vector2f &,
						  int) = 0;
  virtual void			drawSpriteToWindow(const Vector2f &,
						   int) = 0;
  virtual void			drawText(const Vector2f &, const std::string &) = 0;
  virtual void			resetKeyboard() = 0;
};

#endif /* !IGRAPHICALINTERFACE_HPP_ */
