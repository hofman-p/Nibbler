//
// OpenGLGI.cpp for nibbler in /home/royer_q/depots/cpp_nibbler/openGL
//
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
//
// Started on  Fri Mar 14 14:18:14 2014 Quentin ROYER
// Last update Sun Apr  6 22:28:16 2014 Quentin ROYER
//

#include "OpenGLGI.hpp"

OpenGLGI::OpenGLGI(const Vector2i &size,
		   const Vector2i &position,
		   const std::string &title,
		   bool isFirst) :
  _isRunning(true),
  _isFirst(isFirst)
{
  int					ac = 0;
  const GLFWvidmode			*videoMode;

  if (_isFirst)
    glutInit(&ac, NULL);
  if (_isFirst && !glfwInit())
    throw ("OpenGl : Cannot init glfw.");
  videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
  if (size.x == 0 || size.y == 0)
    _window = glfwCreateWindow(videoMode->width, videoMode->height, title.c_str(), NULL, NULL);
  else
    _window = glfwCreateWindow(size.x, size.y, title.c_str(), NULL, NULL);
  if (_window == NULL)
    throw ("OpenGL : Cannot create window");
  glfwSetWindowPos(_window, videoMode->width / 2 - size.x / 2, videoMode->height / 2 - size.y / 2);
  glfwMakeContextCurrent(_window);
  glfwSetKeyCallback(_window, &keyboardFunc);
  _keyMap["LEFT"] = GLFW_KEY_LEFT;
  _keyMap["RIGHT"] = GLFW_KEY_RIGHT;
  _keyMap["UP"] = GLFW_KEY_UP;
  _keyMap["DOWN"] = GLFW_KEY_DOWN;
  _keyMap["ESCAPE"] = GLFW_KEY_ESCAPE;
  _keyboard[_keyMap["UP"]] = false;
  _keyboard[_keyMap["DOWN"]] = false;
  _keyboard[_keyMap["RIGHT"]] = false;
  _keyboard[_keyMap["LEFT"]] = false;
  _keyboard[_keyMap["ESCAPE"]] = false;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(67, videoMode->width / videoMode->height, 1, 1000);
  gluLookAt(30, 20, 30, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glEnable(GL_TEXTURE_2D);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

OpenGLGI::~OpenGLGI()
{
  glfwDestroyWindow(_window);
  if (_isFirst)
    glfwTerminate();
}

const Vector2i				OpenGLGI::getWindowSize() const
{
  Vector2i				size;

  size.x = glutGet(GLUT_WINDOW_WIDTH);
  size.y = glutGet(GLUT_WINDOW_HEIGHT);
  return (size);
}

bool					OpenGLGI::isRunning() const
{
  return (_isRunning);
}

bool					OpenGLGI::isKeyDown(const std::string &keyName)
{
  return (_keyboard[_keyMap[keyName]]);
}

void					OpenGLGI::close()
{
  _isRunning = false;
}

void					OpenGLGI::display()
{
  glFlush();
  glfwSwapBuffers(_window);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void					OpenGLGI::processEvents()
{
  glfwPollEvents();
}

int					OpenGLGI::createSprite(const std::string &textureName)
{
  GLuint				id;
  GLubyte				*sprite;
  Vector2u				size;
  std::string				name;

  if ((PNGLoader::instance().loadImage(textureName.c_str())) == false)
    throw ("OpenGL : Cannot create image.");
  size = PNGLoader::instance().getSize();
  sprite = PNGLoader::instance().getImage();
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA,
	       GL_UNSIGNED_BYTE, sprite);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  name = textureName.substr(textureName.find_last_of("/") + 1,
			    textureName.length() - textureName.find_last_of("/") - 6);
  if (name.compare("ground") == 0)
    _groundId = id;
  else if (name.compare("wall") == 0)
    _wallId = id;
  _sprites.push_back(id);
  return (_sprites.size() - 1);
}

int					OpenGLGI::createImage(const Vector2i &size)
{
  unsigned int				x;
  unsigned int				y;
  Vector2i				blockSize(64, 64);

  _mapImageSize.x = size.x / blockSize.x;
  _mapImageSize.y = size.y / blockSize.y;
}

void					OpenGLGI::drawSpriteToImage(const Vector2f &position,
								    int spriteId,
								    int imageId)
{
}

void					OpenGLGI::drawImageToWindow(const Vector2f &position,
								    int id)
{
  unsigned int				x;
  unsigned int				y;
  float					blockSize = 64.0f;
  Vector2f				screenPos;
  Vector2f				groundSize(_mapImageSize.x * blockSize,
						   _mapImageSize.y * blockSize);
  Vector2f				wallSize(blockSize, _mapImageSize.y * blockSize);

  this->drawPlan(position, groundSize, _groundId);
  for (unsigned int i = 0; i < 4; ++i)
    this->selectPos(i, position, wallSize, _wallId);
}

void					OpenGLGI::selectPos(unsigned my_status,
							    const Vector2f &position,
							    const Vector2f &wallSize,
							    int id)
{
  glPushMatrix();
  glRotated(45, 0, 1, 0);
  glRotated(25, 1, 0, 0);
  if (my_status == 0)
    glTranslated(-wallSize.x / 64.0f, 1 , wallSize.y / 64.0f);
  if (my_status == 1)
    glTranslated(wallSize.x / 64.0f, 1 , -wallSize.y / 64.0f);
  if (my_status == 2)
    {
      glRotated(90, 0, 1, 0);
      glTranslated(-wallSize.x / 64.0f, 1 , wallSize.y / 64.0f);
    }
  if (my_status == 3)
    {
      glRotated(90, 0, 1, 0);
      glTranslated(wallSize.x / 64.0f, 1 , -wallSize.y / 64.0f);
    }
  this->drawCube(position, wallSize, _wallId);
  glPopMatrix();
}

void					OpenGLGI::drawSpriteToWindow(const Vector2f &position,
								     int id)
{
  glPushMatrix();
  glRotated(45, 0, 1, 0);
  glRotated(25, 1, 0, 0);
  glTranslated(0, 1, 0);
  glTranslated(position.x / 86.0f, 0, position.y / 86.0f);
  this->drawCube(position, Vector2f(64.0f, 64.0f), _sprites[id]);
  glPopMatrix();
}

void                                    OpenGLGI::drawText(const Vector2f &position,
							   const std::string &text)
{
  Vector2d                              worldPos;
  unsigned int                          i;
  const char                            *cStr = text.c_str();

  worldPos = this->getWorldCoordsFromScreenCoords(position.x, position.y);
  glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
  glRasterPos2f(worldPos.x, worldPos.y);
  for (i = 0 ; i != text.size() ; ++i)
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, cStr[i]);
  glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void					OpenGLGI::drawPlan(const Vector2f &position,
							   const Vector2f &size,
							   int id)
{
  glPushMatrix();
  glBindTexture(GL_TEXTURE_2D, id);
  glRotated(45, 0, 1, 0);
  glRotated(25, 1, 0, 0);
  glBegin(GL_QUADS);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-1 * (size.x / 64.0f) , 0, -1 * (size.y / 64.0f));
  glTexCoord2f(0.0, 1.0 * (size.y / 64.0f));
  glVertex3f(1 * size.x / 64.0f, 0, -1 * size.y / 64.0f);
  glTexCoord2f(1.0 * size.x / 64.0f, 1.0 * size.y / 64.0f);
  glVertex3f(1 * size.x / 64.0f, 0, 1 * size.y / 64.0f);
  glTexCoord2f(1.0 * size.x / 64.0f, 0.0);
  glVertex3f(-1 * size.x / 64.0f, 0, 1 * size.y / 64.0f);

  glEnd();
  glBindTexture(GL_TEXTURE_2D, 0);
  glDisable(GL_BLEND);
  glPopMatrix();
}

void					OpenGLGI::drawCube(const Vector2f &pos,
							   const Vector2f &size,
							   int id)
{
  glBindTexture(GL_TEXTURE_2D, id);
  glBegin(GL_QUADS);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(size.y / 64.0f, 1, 1);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(size.y / 64.0f, 1, -1);
  glTexCoord2f(size.y / 64.0f , 1.0);
  glVertex3f(-size.y / 64.0f, 1, -1);
  glTexCoord2f(size.y / 64.0f, 0.0);
  glVertex3f(-size.y / 64.0f, 1, 1);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(size.y / 64.0f, -1, 1);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(size.y / 64.0f, -1, -1);
  glTexCoord2f(size.y / 64.0f, 1.0);
  glVertex3f(size.y / 64.0f, 1, -1);
  glTexCoord2f(size.y / 64.0f, 0.0);
  glVertex3f(size.y / 64.0f, 1, 1);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-size.y / 64.0f, -1, 1);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-size.y / 64.0f, -1, -1);
  glTexCoord2f(size.y / 64.0f, 1.0);
  glVertex3f(size.y / 64.0f, -1, -1);
  glTexCoord2f(size.y / 64.0f, 0.0);
  glVertex3f(size.y / 64.0f, -1, 1);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(-size.y / 64.0f, 1, 1);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(-size.y / 64.0f, 1, -1);
  glTexCoord2f(size.y / 64.0f, 1.0);
  glVertex3f(-size.y / 64.0f, -1, -1);
  glTexCoord2f(size.y / 64.0f, 0.0);
  glVertex3f(-size.y / 64.0f, -1, 1);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(size.y / 64.0f, 1, -1);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(size.y / 64.0f, -1, -1);
  glTexCoord2f(size.y / 64.0f, 1.0);
  glVertex3f(-size.y / 64.0f, -1, -1);
  glTexCoord2f(size.y / 64.0f, 0.0);
  glVertex3f(-size.y / 64.0f , 1, -1);

  glTexCoord2f(0.0, 0.0);
  glVertex3f(size.y / 64.0f, -1, 1);
  glTexCoord2f(0.0, 1.0);
  glVertex3f(size.y / 64.0f, 1, 1);
  glTexCoord2f(size.y / 64.0f, 1.0);
  glVertex3f(-size.y / 64.0f, 1, 1);
  glTexCoord2f(size.y / 64.0f, 0.0);
  glVertex3f(-size.y / 64.0f, -1, 1);
  glEnd();
}

Vector2d				OpenGLGI::getWorldCoordsFromScreenCoords(float x,
										 float y)
{
  Vector2d				worldCoords;

  worldCoords.x = x * 2.0f / glutGet(GLUT_WINDOW_WIDTH) - 1.0f;
  worldCoords.y = y * -2.0f / glutGet(GLUT_WINDOW_HEIGHT) + 1.0f;
  return (worldCoords);
}

void					OpenGLGI::resetKeyboard()
{
  _keyboard[_keyMap["UP"]] = false;
  _keyboard[_keyMap["DOWN"]] = false;
  _keyboard[_keyMap["RIGHT"]] = false;
  _keyboard[_keyMap["LEFT"]] = false;
  _keyboard[_keyMap["ESCAPE"]] = false;
}

void					keyboardFunc(GLFWwindow *window,
						     int key,
						     int scancod,
						     int action,
						     int mods)
{
  if (action == GLFW_PRESS)
    _keyboard[key] = true;
  else if (action == GLFW_RELEASE)
    _keyboard[key] = false;
}

IGraphicalInterface			*construct_gi(const Vector2i &size,
						      const Vector2i &position,
						      const std::string &title,
						      bool isFirst)
{
  return (new OpenGLGI(size, position, title, isFirst));
}

void					destroy_gi(IGraphicalInterface *gi)
{
  if (gi)
    delete (gi);
}
