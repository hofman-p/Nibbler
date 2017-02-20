//
// SDLGI.hpp for nibbler in /home/royer_q/depots/cpp_nibbler/SDL
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Sun Apr  6 14:50:21 2014 Quentin ROYER
// Last update Sun Apr  6 22:08:57 2014 Quentin ROYER
//

#ifndef SDLGI_HPP_
# define SDLGI_HPP_

# include <SDL/SDL.h>
# include <SDL/SDL_image.h>
# include <SDL/SDL_ttf.h>
# include <string>
# include <map>
# include <vector>
# include <unistd.h>
# include "../IGraphicalInterface.hpp"

class SDLGI : public IGraphicalInterface
{
 public:
  SDLGI(const Vector2i &,
	const Vector2i &,
	const std::string &,
	bool);
  ~SDLGI();
  bool						isRunning() const;
  const Vector2i				getWindowSize() const;
  bool						isKeyDown(const std::string &);
  void						close();
  void						display();
  void						processEvents();
  int						createSprite(const std::string &);
  int						createImage(const Vector2i &);
  void						drawSpriteToImage(const Vector2f &,
								  int,
								  int);
  void						drawImageToWindow(const Vector2f &,
								  int);
  void						drawSpriteToWindow(const Vector2f &,
								   int);
  void						resetKeyboard();
  void						drawText(const Vector2f &, const std::string &);
private:
  std::map<std::string, SDLKey>			_keyMap;
  std::map<SDLKey, bool>			_keyboard;
  std::vector<SDL_Surface *>			_sprites;
  SDL_Surface					*_screen;
  TTF_Font					*_font;
  bool						_isRunning;
  bool						_isFirst;
};

extern "C"
{
  IGraphicalInterface				*construct_gi(const Vector2i &,
							      const Vector2i &,
							      const std::string &,
							      bool);
  void						destroy_gi(IGraphicalInterface *);
}

#endif /* !SDLGI_HPP_ */
