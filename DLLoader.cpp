//
// DLLoader.cpp for nibbler in /home/royer_q/nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Wed Mar 12 11:46:31 2014 Quentin ROYER
// Last update Fri Apr  4 14:43:58 2014 Quentin ROYER
//

#include "DLLoader.hpp"

DLLoader::DLLoader() : _handle(NULL)
{
}

DLLoader::~DLLoader()
{
  if (_handle)
    dlclose(_handle);
}

void					DLLoader::loadLibrary(const char *dynlib_name)
{
  if (_handle)
    dlclose(_handle);
  if ((_handle = dlopen(dynlib_name, RTLD_NOW)) == NULL)
    throw (dlerror());
}
