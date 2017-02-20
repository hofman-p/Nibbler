//
// XlibGI.cpp for nibbler in /home/royer_q/nibbler/Xlib
//
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
//
// Started on  Thu Mar 13 17:54:04 2014 Quentin ROYER
// Last update Sun Apr  6 22:24:17 2014 Quentin ROYER
//

#include "XlibGI.hpp"

XlibGI::XlibGI(const Vector2i &size,
	       const Vector2i &position,
	       const std::string &title,
	       bool isFirst) :
  _display(NULL),
  _isRunning(true)
{
  int					screen_nbr;
  Screen				*screen;
  Window				rootWindow;
  Atom					closeWindowProtocol;
  XGCValues				gcValues;

  if ((_display = XOpenDisplay(NULL)) == NULL)
    throw ("X11 : Cannot connect to default display.");
  screen_nbr = XDefaultScreen(_display);
  screen = XScreenOfDisplay(_display, screen_nbr);
  rootWindow = XRootWindow(_display, screen_nbr);
  if (size.x == 0 || size.y == 0)
    _window = XCreateSimpleWindow(_display, rootWindow, 0, 0, XWidthOfScreen(screen),
				  XHeightOfScreen(screen), 0, 0, 0);
  else
    _window = XCreateSimpleWindow(_display, rootWindow, 0, 0, size.x, size.y, 0, 0, 0);
  closeWindowProtocol = XInternAtom(_display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(_display, _window, &closeWindowProtocol, 1);
  XSelectInput(_display, _window, ExposureMask | KeyPressMask | KeyReleaseMask);
  _gc = XDefaultGC(_display, screen_nbr);
  _font = XLoadQueryFont(_display, "-misc-fixed-medium-r-normal--15-140-75-75-c-90-iso10646-1");
  if (_font == NULL)
    throw ("Xlib : Cannot load font.");
  gcValues.font = _font->fid;
  _textGC = XCreateGC(_display, _window, GCFont, &gcValues);
  XSetBackground(_display, _textGC, 0x00ff00);
  XSetForeground(_display, _textGC, 0x00ff00);
  XStoreName(_display, _window, title.c_str());
  XMapWindow(_display, _window);
  XMoveWindow(_display, _window, position.x, position.y);
  XSetWindowBackground(_display, _window, 0x000000);
  XClearArea(_display, _window, 0, 0, 0, 0, True);
  _keyMap["ESCAPE"] = XKeysymToKeycode(_display, XK_Escape);
  _keyMap["LEFT"] = XKeysymToKeycode(_display, XK_Left);
  _keyMap["RIGHT"] = XKeysymToKeycode(_display, XK_Right);
  _keyMap["DOWN"] = XKeysymToKeycode(_display, XK_Down);
  _keyMap["UP"] = XKeysymToKeycode(_display, XK_Up);
  _keyboard[_keyMap["ESCAPE"]] = false;
  _keyboard[_keyMap["LEFT"]] = false;
  _keyboard[_keyMap["RIGHT"]] = false;
  _keyboard[_keyMap["UP"]] = false;
  _keyboard[_keyMap["DOWN"]] = false;
}

XlibGI::~XlibGI()
{
  unsigned int				i;

  for (i = 0 ; i != _images.size() ; ++i)
    XFreePixmap(_display, _images[i]);
  XDestroyWindow(_display, _window);
  if (_display)
    XCloseDisplay(_display);
}

const Vector2i				XlibGI::getWindowSize() const
{
  Vector2i				size;
  XWindowAttributes			attr;

  XGetWindowAttributes(_display, _window, &attr);
  size.x = attr.width;
  size.y = attr.height;
  return (size);
}

bool					XlibGI::isRunning() const
{
  return (_isRunning);
}

bool					XlibGI::isKeyDown(const std::string &keyName)
{
  return (_keyboard[_keyMap[keyName]]);
}

void					XlibGI::close()
{
  _isRunning = false;
}

void					XlibGI::display()
{
  XFlush(_display);
}

void					XlibGI::processEvents()
{
  XEvent				event;

  while (XPending(_display))
    {
      XNextEvent(_display, &event);
      if (event.type == ClientMessage)
	this->close();
      else if (event.type == KeyPress)
	_keyboard[event.xkey.keycode] = true;
      else if (event.type == KeyRelease)
	_keyboard[event.xkey.keycode] = false;
    }
  usleep(16000);
  XClearArea(_display, _window, 0, 0, 0, 0, True);
}

int					XlibGI::createSprite(const std::string &name)
{
  int					imageId;
  Vector2i				size(64, 64);
  std::string				textureName;

  imageId = this->createImage(size);
  textureName = name.substr(name.find_last_of("/") + 1, name.length() - name.find_last_of("/") - 6);
  if (textureName.compare("ground") == 0)
    XSetForeground(_display, _imageGCs[imageId], 0xffdead);
  else if (textureName.compare("wall") == 0)
    XSetForeground(_display, _imageGCs[imageId], 0xc7d0e1);
  else if (textureName.compare("head") == 0)
    XSetForeground(_display, _imageGCs[imageId], 0x6b8e23);
  else if (textureName.compare("body") == 0)
    XSetForeground(_display, _imageGCs[imageId], 0x9ab973);
  else if (textureName.compare("food") == 0)
    XSetForeground(_display, _imageGCs[imageId], 0x993333);
  XFillRectangle(_display, _images[imageId], _imageGCs[imageId], 0, 0, size.x, size.y);
  return (imageId);
}

int					XlibGI::createImage(const Vector2i &size)
{
  Pixmap				image;
  int					screen_nbr = XDefaultScreen(_display);
  GC					gc = XDefaultGC(_display, screen_nbr);
  int					depth = XDefaultDepth(_display, screen_nbr);

  if ((image = XCreatePixmap(_display, _window, size.x, size.y, depth)) == -1)
    throw("Xlib : Cannot create pixmap.");
  _images.push_back(image);
  _imageGCs.push_back(gc);
  _imageSizes.push_back(size);
  return (_images.size() - 1);
}

void					XlibGI::drawSpriteToImage(const Vector2f &position,
								  int spriteId,
								  int imageId)
{
  Pixmap				sprite = _images[spriteId];
  Pixmap				image = _images[imageId];
  Vector2i				size = _imageSizes[spriteId];

  XCopyArea(_display, sprite, image, _imageGCs[spriteId], 0, 0, size.x, size.y, position.x, position.y);
}

void					XlibGI::drawImageToWindow(const Vector2f &position,
								  int id)
{
  Pixmap				image = _images[id];
  Vector2i				size = _imageSizes[id];

  XCopyArea(_display, image, _window, _imageGCs[id], 0, 0, size.x, size.y, position.x, position.y);
}

void					XlibGI::drawSpriteToWindow(const Vector2f &position,
								   int id)
{
  this->drawImageToWindow(position, id);
}

void					XlibGI::drawText(const Vector2f &position,
							 const std::string &text)
{
  XDrawString(_display, _window, _textGC, position.x, position.y, text.c_str(), text.size());
}

void					XlibGI::resetKeyboard()
{
  _keyboard[_keyMap["UP"]] = false;
  _keyboard[_keyMap["DOWN"]] = false;
  _keyboard[_keyMap["LEFT"]] = false;
  _keyboard[_keyMap["RIGHT"]] = false;
  _keyboard[_keyMap["ESCAPE"]] = false;
}

IGraphicalInterface			*construct_gi(const Vector2i &size,
						      const Vector2i &position,
						      const std::string &title,
						      bool isFirst)
{
  return (new XlibGI(size, position, title, isFirst));
}

void					destroy_gi(IGraphicalInterface *gi)
{
  if (gi)
    delete (gi);
}
