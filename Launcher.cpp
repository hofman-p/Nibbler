//
// Launcher.cpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Wed Apr  2 16:58:21 2014 Quentin ROYER
// Last update Sun Apr  6 23:34:45 2014 Quentin ROYER
//

#include "Launcher.hpp"

Launcher::Launcher(const char *width,
		   const char *height,
		   const char *dynlibName) :
  _gi(NULL),
  _size(Vector2i(800, 600)),
  _selected(0),
  _currentMenu(0),
  _dynlibName(std::string(dynlibName)),
  _width(std::string(width)),
  _height(std::string(height))
{
  if (_dynlibName.compare("lib/lib_nibbler_openGL3D.so") == 0)
    _dynlibName = "lib/lib_nibbler_openGL.so";
}

Launcher::~Launcher()
{
}

const std::vector<std::string>	Launcher::getLibNames() const
{
  DIR				*dirp;
  struct dirent			*dent;
  std::vector<std::string>	libNames;
  std::string			fileName;
  std::string			fileExtension;
  std::string			fileConvention;

  if ((dirp = opendir("lib")) == NULL)
    throw ("Cannot open lib directory.");
  while ((dent = readdir(dirp)) != NULL)
    {
      fileName = std::string(dent->d_name);
      fileExtension = fileName.substr(fileName.find_last_of("."),
				      fileName.length() - fileName.find_last_of("."));
      fileConvention = fileName.substr(0, fileName.find_last_of("_") + 1);
      if (fileExtension.compare(".so") == 0 && fileConvention.compare("lib_nibbler_") == 0)
	libNames.push_back(fileName);
    }
  closedir(dirp);
  return (libNames);
}

const std::vector<std::string>	Launcher::getTexturePackNames() const
{
  DIR				*dirp;
  struct dirent			*dent;
  std::vector<std::string>	texturePackNames;
  std::string			fileName;
  std::string			fileExtension;

  if ((dirp = opendir("media")) == NULL)
    throw ("Cannot open media directory.");
  while ((dent = readdir(dirp)) != NULL)
    {
      fileName = std::string(dent->d_name);
      if (fileName.compare(".") == 0 || fileName.compare("..") == 0 ||
	  fileName.find_last_of("_") == std::string::npos)
	continue;
      fileExtension = fileName.substr(fileName.find_last_of("_"),
				      fileName.length() - fileName.find_last_of("_"));
      if (fileExtension.compare("_pack") == 0)
	texturePackNames.push_back(fileName);
    }
  closedir(dirp);
  return (texturePackNames);
}

void				Launcher::start()
{
  Vector2i			centerPosition;

  _loader.loadLibrary(_dynlibName.c_str());
  _loader.loadSymbol("construct_gi", &_giConstructor);
  centerPosition.x = 1920 / 2 - _size.x / 2;
  centerPosition.y = 1080 / 2 - _size.y / 2;
  _menuPtr[0] = &Launcher::drawLibMenu;
  _menuPtr[1] = &Launcher::drawTextureMenu;
  _menuPtr[2] = &Launcher::drawEndMenu;
  _currentMenu = 0;
  _selected = 0;
  _gi = _giConstructor(Vector2i(_size.x, _size.y), centerPosition, "Nibbler Launcher", true);
}

void				Launcher::loop()
{
  while (_gi->isRunning())
    {
      _gi->processEvents();
      if (_gi->isKeyDown("ESCAPE"))
	_gi->close();
      (this->*_menuPtr[_currentMenu])();
      _gi->display();
    }
}

int				Launcher::navigate(unsigned int maxIndex)
{
  if (_clock.getElapsedTime() > 5000)
    {
      if (_gi->isKeyDown("UP"))
	{
	  _selected = _selected == 0 ? maxIndex : _selected - 1;
	  _clock.restartTimer();
	}
      else if (_gi->isKeyDown("DOWN"))
	{
	  _selected = _selected == maxIndex ? 0 : _selected + 1;
	  _clock.restartTimer();
	}
      if (_gi->isKeyDown("RIGHT"))
	{
	  _clock.restartTimer();
	  return (1);
	}
      else if (_gi->isKeyDown("LEFT"))
	{
	  _clock.restartTimer();
	  return (-1);
	}
    }
  return (0);
}

void				Launcher::drawLibMenu()
{
  std::vector<std::string>	libNames;
  std::string			shortName;
  std::string			emptyMessage;
  float				offset = 75.0f;
  unsigned int			i;

  emptyMessage = "The lib/ directory is empty. Put the libraries inside.";
  libNames = this->getLibNames();
  if (this->navigate(libNames.size() - 1) == 1)
    {
      if (libNames.size() > _selected)
	{
	  _chosenLibrary = "lib/" + libNames[_selected];
	  _selected = 0;
	  _currentMenu = 1;
	}
    }
  _gi->drawText(Vector2f(_size.x * 0.37f, _size.y * 0.1f), "Choose a graphic library");
  _gi->drawText(Vector2f(_size.x * 0.6f, _size.y * 0.95f), "Press Right Arrow to continue");
  if (libNames.size() == 0)
    _gi->drawText(Vector2f(_size.x * 0.1f, _size.y * 0.5f), emptyMessage);
  for (i = 0 ; i != libNames.size() ; ++i)
    {
      shortName = libNames[i];
      shortName = shortName.substr(shortName.find_last_of("_") + 1,
				   shortName.find_first_of(".") - 1 - shortName.find_last_of("_"));
      if (i == _selected)
	_gi->drawText(Vector2f(_size.x * 0.55f, _size.y * 0.3f + offset * i), shortName);
      else
	_gi->drawText(Vector2f(_size.x * 0.45f, _size.y * 0.3f + offset * i), shortName);
    }
}

void				Launcher::drawTextureMenu()
{
  std::vector<std::string>	texturePackNames;
  std::string			shortName;
  std::string			emptyMessage;
  float				offset = 75.0f;
  unsigned int			i;
  int				ret;

  emptyMessage = "The media/ directory is empty. Put the texture packs inside.";
  texturePackNames = this->getTexturePackNames();
  if ((ret = this->navigate(texturePackNames.size() - 1)) == 1)
    {
      if (texturePackNames.size() > _selected)
	{
	  _chosenTexturePack = "media/" + texturePackNames[_selected];
	  boost::thread		thread(&Launcher::launchNibbler, this);
	  thread.join();
	  _gi->resetKeyboard();
	  _currentMenu = 2;
	  _selected = 0;
	}
    }
  else if (ret == -1)
    _currentMenu = 0;
  _gi->drawText(Vector2f(_size.x * 0.37f, _size.y * 0.1f), "Choose a texture pack");
  _gi->drawText(Vector2f(_size.x * 0.6f, _size.y * 0.95f), "Press Right Arrow to start");
  _gi->drawText(Vector2f(_size.x * 0.1f, _size.y * 0.95f), "Press Left Arrow to go back");
  if (texturePackNames.size() == 0)
    _gi->drawText(Vector2f(_size.x * 0.1f, _size.y * 0.5f), emptyMessage);
  for (i = 0 ; i != texturePackNames.size() ; ++i)
    {
      shortName = texturePackNames[i];
      shortName = shortName.substr(0, shortName.find_first_of("_"));
      if (i == _selected)
	_gi->drawText(Vector2f(_size.x * 0.55f, _size.y * 0.3f + offset * i), shortName);
      else
	_gi->drawText(Vector2f(_size.x * 0.45f, _size.y * 0.3f + offset * i), shortName);
    }
}

void				Launcher::drawEndMenu()
{
  std::ostringstream		oss;
  std::string			result;
  int				ret;

  oss << _score;
  result = "Your score is : " + oss.str() + " !";
  _gi->drawText(Vector2f(_size.x * 0.38f, _size.y * 0.45f), result);
  _gi->drawText(Vector2f(_size.x * 0.6f, _size.y * 0.95f), "Press Right Arrow to try again");
  _gi->drawText(Vector2f(_size.x * 0.1f, _size.y * 0.95f), "Press Left Arrow to go back");
  if ((ret = this->navigate(1)) == 1)
    { 
      boost::thread		thread(&Launcher::launchNibbler, this);
      thread.join();
      _gi->resetKeyboard();
      _currentMenu = 2;
      _selected = 0;
    }
  else if (ret == -1)
    _currentMenu = 0;
}

void				Launcher::launchNibbler()
{
  Nibbler			*nibbler;
  bool				isFirst;

  try
    {
      isFirst = _chosenLibrary.compare(_dynlibName) == 0 ? false : true;
      if (_chosenLibrary.compare("lib/lib_nibbler_openGL3D.so") == 0 &&
	  _dynlibName.compare("lib/lib_nibbler_openGL.so") == 0)
	isFirst = false;
      nibbler = new Nibbler(_width.c_str(), _height.c_str(), _chosenLibrary, _chosenTexturePack);
      nibbler->start(isFirst);
      nibbler->loop();
      _score = nibbler->end();
      delete (nibbler);
    }
  catch (const char *msg)
    {
      std::cout << msg << std::endl;
    }
}
