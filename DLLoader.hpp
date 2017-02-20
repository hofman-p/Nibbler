//
// DLLoader.hpp for nibbler in /home/royer_q/nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Wed Mar 12 11:16:49 2014 Quentin ROYER
// Last update Fri Apr  4 14:43:36 2014 Quentin ROYER
//

#ifndef DLLOADER_HPP_
# define DLLOADER_HPP_

# include <iostream>
# include <dlfcn.h>

class				DLLoader
{
public:
  DLLoader();
  ~DLLoader();
  void				loadLibrary(const char *dynlib_name);
  template <typename function_pointer>
  void				loadSymbol(const std::string &name, function_pointer *ptr)
  {
    *ptr = reinterpret_cast<function_pointer>(dlsym(_handle, name.c_str()));
    if (*ptr == NULL)
      throw (dlerror());
  }
private:
  void				*_handle;
};

#endif /* !DLLOADER_HPP_ */
