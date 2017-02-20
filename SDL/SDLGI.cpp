//
// SDLGI.cpp for nibbler in /home/royer_q/depots/cpp_nibbler/SDL
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Sun Apr  6 14:50:34 2014 Quentin ROYER
// Last update Sun Apr  6 22:13:45 2014 Quentin ROYER
//

#include "SDLGI.hpp"

SDLGI::SDLGI(const Vector2i &size,
	     const Vector2i &position,
	     const std::string &title,
	     bool isFirst) :
  _isRunning(true),
  _isFirst(isFirst)
{
  if (_isFirst && SDL_Init(SDL_INIT_VIDEO) < 0)
    throw ("Error: Init SDL.");
  if (size.x == 0 || size.y == 0)
    _screen = SDL_SetVideoMode(0, 0, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  else
    _screen = SDL_SetVideoMode(size.x, size.y, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
  if (_screen == NULL)
    throw ("Error: SetVideoMode.");
  SDL_WM_SetCaption(title.c_str(), NULL);
  SDL_FillRect(_screen, NULL, SDL_MapRGB(_screen->format, 0, 0, 0));
  _keyMap["ESCAPE"] = SDLK_ESCAPE;
  _keyMap["UP"] = SDLK_UP;
  _keyMap["DOWN"] = SDLK_DOWN;
  _keyMap["LEFT"] = SDLK_LEFT;
  _keyMap["RIGHT"] = SDLK_RIGHT;
  _keyboard[_keyMap["ESCAPE"]] = false;
  _keyboard[_keyMap["LEFT"]] = false;
  _keyboard[_keyMap["RIGHT"]] = false;
  _keyboard[_keyMap["UP"]] = false;
  _keyboard[_keyMap["DOWN"]] = false;
  if (_isFirst && TTF_Init() == -1)
    throw ("Can't init font.");
  if ((_font = TTF_OpenFont("/usr/share/fonts/truetype/DroidSerif-Regular.ttf", 15)) == NULL)
    throw ("Can't find font.");
}

SDLGI::~SDLGI()
{
  unsigned int		i;
  
  for (i = 0 ; i != _sprites.size() ; ++i)
    SDL_FreeSurface(_sprites[i]);
  TTF_CloseFont(_font);
  SDL_FreeSurface(_screen);
  if (_isFirst)
    SDL_Quit();
}

void			SDLGI::resetKeyboard()
{
  _keyboard[_keyMap["ESCAPE"]] = false;
  _keyboard[_keyMap["LEFT"]] = false;
  _keyboard[_keyMap["RIGHT"]] = false;
  _keyboard[_keyMap["UP"]] = false;
  _keyboard[_keyMap["DOWN"]] = false;
}

void			SDLGI::drawText(const Vector2f &position,
					const std::string &text)
{
  SDL_Surface		*surface;
  SDL_Rect		posTTF;
  SDL_Color		background = { 0, 0, 0 };
  SDL_Color		foreground = { 0, 255, 0 };

  posTTF.x = position.x;
  posTTF.y = position.y;
  if ((surface = TTF_RenderText_Shaded(_font, text.c_str(), foreground, background)) == NULL)
    throw("Can't create text");
  SDL_BlitSurface(surface, NULL, _screen, &posTTF);
  SDL_FreeSurface(surface);
}

const Vector2i		SDLGI::getWindowSize() const
{
  Vector2i		size(_screen->w, _screen->h);

  return (size);
}

bool			SDLGI::isRunning() const
{
  return (_isRunning);
}

bool			SDLGI::isKeyDown(const std::string &keyName)
{
  return (_keyboard[_keyMap[keyName]]);
}

void			SDLGI::close()
{
  _isRunning = false;
}

void			SDLGI::display()
{
  SDL_Flip(_screen);
  SDL_FillRect(_screen, NULL, SDL_MapRGB(_screen->format, 0, 0, 0));
}

void			SDLGI::processEvents()
{
  SDL_Event		event;

  while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
	this->close();
      else if (event.type == SDL_KEYDOWN)
	_keyboard[event.key.keysym.sym] = true;
      else if (event.type == SDL_KEYUP)
	_keyboard[event.key.keysym.sym] = false;
    }
  SDL_Delay(10);
}

int			SDLGI::createSprite(const std::string &textureName)
{
  SDL_Surface		*surface;

  if ((surface = IMG_Load(textureName.c_str())) == NULL)
    throw("Error: Can't load image");
  _sprites.push_back(surface);
  return (_sprites.size() - 1);
}

int			SDLGI::createImage(const Vector2i &size)
{
  SDL_Surface		*surface;

  surface = SDL_CreateRGBSurface(SDL_SWSURFACE, size.x, size.y, 32, 0, 0, 0, 0);
  _sprites.push_back(surface);
  return (_sprites.size() - 1);
}

void			SDLGI::drawSpriteToImage(const Vector2f &position,
						 int spriteId,
						 int imageId)
{
  SDL_Surface		*sprite = _sprites[spriteId];
  SDL_Surface		*image = _sprites[imageId];
  SDL_Rect		rect;

  rect.x = position.x;
  rect.y = position.y;
  SDL_BlitSurface(sprite, NULL, image, &rect);
}

void			SDLGI::drawImageToWindow(const Vector2f &position,
						 int id)
{
  SDL_Surface		*image = _sprites[id];
  SDL_Rect		rect;

  rect.x = position.x;
  rect.y = position.y;
  SDL_BlitSurface(image, NULL, _screen, &rect);
}

void			SDLGI::drawSpriteToWindow(const Vector2f &position,
						  int id)
{
  this->drawImageToWindow(position, id);
}

IGraphicalInterface    	*construct_gi(const Vector2i &size,
				      const Vector2i &position,
				      const std::string &title,
				      bool isFirst)
{
  return (new SDLGI(size, position, title, isFirst));
}

void			destroy_gi(IGraphicalInterface *gi)
{
  if (gi)
    delete (gi);
}
