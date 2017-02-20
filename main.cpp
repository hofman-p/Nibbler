//
// main.cpp for nibbler in /home/royer_q/nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Tue Mar 11 14:52:13 2014 Quentin ROYER
// Last update Sun Apr  6 21:46:01 2014 Quentin ROYER
//

#include <time.h>
#include "Launcher.hpp"

int		       	main(int argc, char **argv)
{
  Launcher     		*launcher;
  std::string	       	currentEnv;
  std::string	       	displayName(":0.0");

  try
    {
      if (argc != 4)
	throw ("Usage : ./nibbler [width] [height] [library]");
      srand(time(NULL));
      if (getenv("DISPLAY") != NULL)
	currentEnv = getenv("DISPLAY");
      if (currentEnv.compare(displayName) != 0)
	throw ("Display environment variable is unknown.");
      launcher = new Launcher(argv[1], argv[2], argv[3]);
      launcher->start();
      launcher->loop();
      delete (launcher);
    }
  catch (const char *error_msg)
    {
      std::cerr << error_msg << std::endl;
    }
  return (0);
}
