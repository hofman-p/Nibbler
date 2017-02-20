//
// GI.cpp for GI in /home/royer_q/nibbler/SFML
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Tue Mar 11 13:44:49 2014 Quentin ROYER
// Last update Sun Apr  6 22:18:03 2014 Quentin ROYER
//

#include "SFMLGI.hpp"

SFMLGI::SFMLGI(const Vector2i &size,
	       const Vector2i &position,
	       const std::string &title,
	       bool isFirst) :
  _app(NULL)
{
  sf::VideoMode			mode;

  if (size.x == 0 || size.y == 0)
    mode = sf::VideoMode::getDesktopMode();
  else
    mode = sf::VideoMode(size.x, size.y);
  if ((_app = new sf::RenderWindow(mode, title)) == NULL)
    throw ("SFML : Cannot create window.");
  _app->setPosition(sf::Vector2i(position.x, position.y));
  _app->clear(sf::Color::Black);
  if (!_font.loadFromFile("/usr/share/fonts/truetype/DroidSerif-Regular.ttf"))
    throw ("SFML : Cannot load font.");
  _keyMap["ESCAPE"] = sf::Keyboard::Escape;
  _keyMap["LEFT"] = sf::Keyboard::Left;
  _keyMap["RIGHT"] = sf::Keyboard::Right;
  _keyMap["UP"] = sf::Keyboard::Up;
  _keyMap["DOWN"] = sf::Keyboard::Down;
  _keyboard[_keyMap["ESCAPE"]] = false;
  _keyboard[_keyMap["UP"]] = false;
  _keyboard[_keyMap["DOWN"]] = false;
  _keyboard[_keyMap["LEFT"]] = false;
  _keyboard[_keyMap["RIGHT"]] = false;
}

SFMLGI::~SFMLGI()
{
  unsigned int			i;

  for (i = 0 ; i != _images.size() ; ++i)
    delete (_images[i]);
  for (i = 0 ; i != _sprites.size() ; ++i)
    delete (_sprites[i]);
  if (_app)
    delete (_app);
}

const Vector2i			SFMLGI::getWindowSize() const
{
  Vector2i			size(_app->getSize().x, _app->getSize().y);

  return (size);
}

bool				SFMLGI::isRunning() const
{
  return (_app->isOpen());
}

bool				SFMLGI::isKeyDown(const std::string &keyName)
{
  return (_keyboard[_keyMap[keyName]]);
} 

void				SFMLGI::close()
{
  _app->close();
}

void				SFMLGI::display()
{
  _app->display();
}

void				SFMLGI::processEvents()
{
  sf::Event			event;

  while (_app->pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	_app->close();
      else if (event.type == sf::Event::KeyPressed)
	_keyboard[event.key.code] = true;
      else if (event.type == sf::Event::KeyReleased)
	_keyboard[event.key.code] = false;
    }
  _app->clear();
}

int				SFMLGI::createSprite(const std::string &textureName)
{
  sf::Texture			*texture;
  sf::Sprite			*sprite;

  sprite = new sf::Sprite();
  texture = new sf::Texture();
  if (!texture->loadFromFile(textureName))
    throw ("SFML : Cannot load texture file.");
  sprite->setTexture(*texture);
  _sprites.push_back(sprite);
  return (_sprites.size() - 1);
}

int				SFMLGI::createImage(const Vector2i &size)
{
  sf::RenderTexture		*image;
  sf::Sprite			*sprite;

  image = new sf::RenderTexture();
  sprite = new sf::Sprite();
  if (!image->create(size.x, size.y))
    throw ("SFML : Cannot create image.");
  image->clear(sf::Color::Black);
  sprite->setTexture(image->getTexture());
  _images.push_back(image);
  _sprites.push_back(sprite);
  return (_images.size() - 1);
}

void				SFMLGI::drawSpriteToImage(const Vector2f &position,
							  int spriteId,
							  int imageId)
{
  unsigned int			i;

  _sprites[spriteId]->setPosition(position.x, position.y);
  _images[imageId]->draw(*_sprites[spriteId]);
  _images[imageId]->display();
}

void				SFMLGI::drawImageToWindow(const Vector2f &position,
							  int id)
{
  unsigned int			i;

  for (i = 0 ; i != _sprites.size() ; ++i)
    {
      if (_sprites[i]->getTexture() == &_images[id]->getTexture())
	break;
    }
  _sprites[i]->setPosition(position.x, position.y);
  _app->draw(*_sprites[i]);
}

void				SFMLGI::drawSpriteToWindow(const Vector2f &position,
							   int id)
{
  _sprites[id]->setPosition(position.x, position.y);
  _app->draw(*_sprites[id]);
}

void				SFMLGI::drawText(const Vector2f &position,
						 const std::string &text)
{
  sf::Text			sfText(text, _font);

  sfText.setCharacterSize(15);
  sfText.setColor(sf::Color::Green);
  sfText.setPosition(position.x, position.y);
  _app->draw(sfText);
}

void				SFMLGI::resetKeyboard()
{
  _keyboard[_keyMap["ESCAPE"]] = false;
  _keyboard[_keyMap["UP"]] = false;
  _keyboard[_keyMap["DOWN"]] = false;
  _keyboard[_keyMap["LEFT"]] = false;
  _keyboard[_keyMap["RIGHT"]] = false;
}

IGraphicalInterface		*construct_gi(const Vector2i&size,
					      const Vector2i &position,
					      const std::string &title,
					      bool isFirst)
{
  return (new SFMLGI(size, position, title, isFirst));
}

void				destroy_gi(IGraphicalInterface *gi)
{
  if (gi)
    delete (gi);
}
