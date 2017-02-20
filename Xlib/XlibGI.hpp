//
// XlibGI.hpp for nibbler in /home/royer_q/nibbler/Xlib
// 
// Made by Quentin ROYER
// Login   <royer_q@epitech.net>
// 
// Started on  Thu Mar 13 17:48:09 2014 Quentin ROYER
// Last update Sun Apr  6 22:23:18 2014 Quentin ROYER
//

#ifndef XLIBGI_HPP_
# define XLIBGI_HPP_

# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include <unistd.h>
# include <string>
# include <map>
# include <vector>
# include "../IGraphicalInterface.hpp"

class					XlibGI : public IGraphicalInterface
{
public:
  XlibGI(const Vector2i &,
	 const Vector2i &,
	 const std::string &,
	 bool);
  ~XlibGI();
  const Vector2i		       	getWindowSize() const;
  bool			       		isRunning() const;
  bool		       			isKeyDown(const std::string &);
  void	       				close();
  void 					display();
  void		       			processEvents();
  int	       				createSprite(const std::string &);
  int					createImage(const Vector2i &);
  void					drawSpriteToImage(const Vector2f &,
							  int,
							  int);
  void					drawImageToWindow(const Vector2f &,
							  int);
  void					drawSpriteToWindow(const Vector2f &,
							   int);
  void					drawText(const Vector2f &,
						 const std::string &);
  void					resetKeyboard();
private:
  std::map<std::string, KeyCode>       	_keyMap;
  std::map<KeyCode, bool>		_keyboard;
  std::vector<Pixmap>			_images;
  std::vector<GC>			_imageGCs;
  std::vector<Vector2i>			_imageSizes;
  Window		       		_window;
  Display	       			*_display;
  bool	       				_isRunning;
  GC   					_gc;
  GC					_textGC;
  XFontStruct				*_font;
};

extern "C"
{
  IGraphicalInterface		       	*construct_gi(const Vector2i &,
						      const Vector2i &,
						      const std::string &,
						      bool);
  void			       		destroy_gi(IGraphicalInterface *);
}

#endif /* !XLIBGI_HPP_ */
