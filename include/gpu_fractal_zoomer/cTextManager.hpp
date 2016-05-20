// -------------------------------------------------------------------
// Manages all text and font objects
// -------------------------------------------------------------------

#ifndef _CTEXTMANAGER_HPP_
#define _CTEXTMANAGER_HPP_

// -------------------------------------------------------------------
// include files
#include <string>

namespace sf {
	class RenderWindow;
	class Font;
}

namespace GPUFractalZoomer {

class cTextManager
{
public:

	// constructor, destructor
	cTextManager( void );
	~cTextManager( void );

	// loads resources
	void load( void );

	// draws text to a window
	void printText( float x, float y, std::string text, sf::RenderWindow* window );


private:

	// font
	sf::Font* m_pFont;

};

} // namespace GPUFractalZoomer

#endif // _CTEXTMANAGER_HPP_
