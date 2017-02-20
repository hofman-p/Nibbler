//
// Launcher.hpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Wed Apr  2 16:51:30 2014 Quentin ROYER
// Last update Sun Apr  6 21:31:54 2014 Quentin ROYER
//

#ifndef LAUNCHER_HPP_
# define LAUNCHER_HPP_

# include <unistd.h>
# include <dirent.h>
# include <boost/thread.hpp>
# include <vector>
# include <string>
# include "IGraphicalInterface.hpp"
# include "DLLoader.hpp"
# include "Nibbler.hpp"
# include "Clock.hpp"

class					Launcher
{
public:
  Launcher(const char *, const char *, const char *);
  ~Launcher();
  const std::vector<std::string>	getLibNames() const;
  const std::vector<std::string>	getTexturePackNames() const;
  void					start();
  void					loop();
  int					navigate(unsigned int);
  void					drawLibMenu();
  void					drawTextureMenu();
  void					drawEndMenu();
  void					launchNibbler();
private:
  IGraphicalInterface			*_gi;
  Vector2i				_size;
  unsigned int				_selected;
  int					_currentMenu;
  std::string				_dynlibName;
  std::string				_width;
  std::string				_height;
  DLLoader				_loader;
  std::string				_chosenLibrary;
  std::string				_chosenTexturePack;
  Clock					_clock;
  int					_score;
  void					(Launcher::*_menuPtr[3])();
  IGraphicalInterface			*(*_giConstructor)(const Vector2i &, const Vector2i &,
							   const std::string &, bool);
};

# endif /* !LAUNCHER_HPP_ */
