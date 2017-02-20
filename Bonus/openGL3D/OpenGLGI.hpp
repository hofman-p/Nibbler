//
// OpenGLGI.hpp for nibbler in /home/royer_q/depots/cpp_nibbler/openGL
//
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
//
// Started on  Fri Mar 14 14:12:07 2014 Quentin ROYER
// Last update Sun Apr  6 22:26:10 2014 Quentin ROYER
//

#ifndef OPENGLGI_HPP_
# define OPENGLGI_HPP_

# include <GL/gl.h>
# include <GL/glut.h>
# include <GL/freeglut.h>
# include <GL/freeglut_ext.h>
# include <GLFW/glfw3.h>
# include <string>
# include <vector>
# include <map>
# include "../../IGraphicalInterface.hpp"
# include "PNGLoader.hpp"

std::map<unsigned char, bool>		_keyboard;

class					OpenGLGI : public IGraphicalInterface
{
public:
  OpenGLGI(const Vector2i &, const Vector2i &, const std::string &, bool);
  ~OpenGLGI();
  const Vector2i			getWindowSize() const;
  bool					isRunning() const;
  bool					isKeyDown(const std::string &);
  void					close();
  void					display();
  void					processEvents();
  int					createSprite(const std::string &);
  int					createImage(const Vector2i &);
  void					drawSpriteToImage(const Vector2f &,
							  int,
							  int);
  void					drawImageToWindow(const Vector2f &,
							  int);
  void					drawSpriteToWindow(const Vector2f &,
							   int);
  void					drawText(const Vector2f &,
						 const std::string &);
  Vector2d				getWorldCoordsFromScreenCoords(float,
								       float);
  void					drawCube(const Vector2f &,
						 const Vector2f &,
						 int);
  void					drawPlan(const Vector2f &,
						 const Vector2f &,
						 int);
  void					selectPos(unsigned,
						  const Vector2f &,
						  const Vector2f &,
						  int);
  void					resetKeyboard();
private:
  std::map<std::string, int>		_keyMap;
  GLFWwindow				*_window;
  bool					_isRunning;
  std::vector<GLuint>			_sprites;
  Vector2i				_mapImageSize;
  int					_groundId;
  int					_wallId;
  bool					_isFirst;
  bool					_is3D;
};

extern "C"
{
  void					keyboardFunc(GLFWwindow *,
						     int,
						     int,
						     int,
						     int);
  IGraphicalInterface			*construct_gi(const Vector2i &,
						      const Vector2i &,
						      const std::string &,
						      bool);
  void					destroy_gi(IGraphicalInterface *);
}

#endif /* !OPENGLGI_HPP_ */
