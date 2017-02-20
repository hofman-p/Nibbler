//
// GI.hpp for GI in /home/royer_q/nibbler/SFML
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Tue Mar 11 13:45:11 2014 Quentin ROYER
// Last update Sun Apr  6 22:15:48 2014 Quentin ROYER
//

#ifndef SFMLGI_HPP_
# define SFMLGI_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include <SFML/Window.hpp>
# include <string>
# include <map>
# include "../IGraphicalInterface.hpp"

class						SFMLGI : public IGraphicalInterface
{
public:
  SFMLGI(const Vector2i &,
	 const Vector2i &,
	 const std::string &,
	 bool);
  ~SFMLGI();
  const Vector2i				getWindowSize() const;
  bool						isRunning() const;
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
  void						drawText(const Vector2f &,
							 const std::string &);
  void						resetKeyboard();
private:
  sf::RenderWindow				*_app;
  std::vector<sf::Sprite *>			_sprites;
  std::vector<sf::RenderTexture *>		_images;
  std::map<std::string, sf::Keyboard::Key>	_keyMap;
  std::map<sf::Keyboard::Key, bool>		_keyboard;
  sf::Font					_font;
};

extern "C"
{
  IGraphicalInterface				*construct_gi(const Vector2i &,
							      const Vector2i &,
							      const std::string &,
							      bool);
  void						destroy_gi(IGraphicalInterface *);
}

#endif /* !SFMLGI_HPP_ */
