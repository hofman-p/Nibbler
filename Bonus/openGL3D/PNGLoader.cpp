//
// PNGLoader.cpp for nibbler in /home/royer_q/depots/cpp_nibbler
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Mon Mar 31 12:47:54 2014 Quentin ROYER
// Last update Tue Apr  1 18:56:25 2014 Quentin ROYER
//

#include "PNGLoader.hpp"

PNGLoader::PNGLoader() : _image(NULL)
{
}

PNGLoader::~PNGLoader()
{
  delete [] _image;
}

PNGLoader			&PNGLoader::instance()
{
  static PNGLoader		instance;

  return (instance);
}

const Vector2u			&PNGLoader::getSize() const
{
  return (_size);
}

unsigned char			*PNGLoader::getImage() const
{
  return (_image);
}

bool				PNGLoader::loadImage(const char *filename)
{
  int				color_type;
  int				interlace_type;
  int				bit_depth;
  int				row_bytes;
  png_bytepp			row_pointers;
  png_uint_32			width;
  png_uint_32			height;
  unsigned int			i;

  if (_image)
    delete [] _image;
  if (!this->initPNG(filename))
    return (false);
  png_init_io(_png_ptr, _fp);
  png_set_sig_bytes(_png_ptr, 0);
  png_read_png(_png_ptr, _info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING
               | PNG_TRANSFORM_EXPAND, NULL);
  png_get_IHDR(_png_ptr, _info_ptr, &width, &height, &bit_depth, &color_type,
	       &interlace_type, NULL, NULL);
  _size.x = width;
  _size.y = height;
  row_bytes = png_get_rowbytes(_png_ptr, _info_ptr);
  _image = new unsigned char[row_bytes * _size.y];
  row_pointers = png_get_rows(_png_ptr, _info_ptr);
  for (i = 0 ; i < _size.y ; ++i)
    memcpy(_image + (row_bytes * (_size.y - 1 - i)), row_pointers[i], row_bytes);
  png_destroy_read_struct(&_png_ptr, &_info_ptr, NULL);
  fclose(_fp);
  return (true);
}

bool			PNGLoader::initPNG(const char *filename)
{
  if ((_fp = fopen(filename, "rb")) == NULL)
    return (false);
  if ((_png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)) == NULL)
    {
      fclose(_fp);
      return (false);
    }
  if ((_info_ptr = png_create_info_struct(_png_ptr)) == NULL)
    {
      fclose(_fp);
      png_destroy_read_struct(&_png_ptr, NULL, NULL);
      return (false);
    }
  if (setjmp(png_jmpbuf(_png_ptr)))
    {
      fclose(_fp);
      png_destroy_read_struct(&_png_ptr, &_info_ptr, NULL);
      return (false);
    }
  return (true);
}
