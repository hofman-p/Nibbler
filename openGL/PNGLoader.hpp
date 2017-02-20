//
// PNGLoader.hpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Mon Mar 31 12:45:57 2014 Quentin ROYER
// Last update Tue Apr  1 17:28:24 2014 Quentin ROYER
//

#ifndef _PNGLOADER_HPP_
# define _PNGLOADER_HPP_

# include <string>
# include <unistd.h>
# include <png.h>
# include <stdio.h>
# include <string.h>
# include "../Vector2.hpp"

class			PNGLoader
{
public:
  ~PNGLoader();
  static PNGLoader	&instance();
  const Vector2u	&getSize() const;
  unsigned char  	*getImage() const;
  bool			loadImage(const char *);
  bool			initPNG(const char *);
private:
  PNGLoader();
  unsigned char		*_image;
  char			*_filename;
  png_FILE_p		_fp;
  png_structp		_png_ptr;
  png_infop		_info_ptr;
  Vector2u		_size;
};

#endif /* !_PNGLOADER_HPP_ */
