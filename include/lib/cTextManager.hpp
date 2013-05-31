// -------------------------------------------------------------------
// Manages all text and font objects
// -------------------------------------------------------------------

#ifndef _CTEXTMANAGER_HPP_
#define _CTEXTMANAGER_HPP_

// -------------------------------------------------------------------
// include files

#include <vector>
#include <cException.hpp>
#include <cText.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GPUFractalZoomer {

class cTextManager
{
public:

	// constructor, destructor
	cTextManager( void );
	~cTextManager( void );

	// loads resources
	void load( void );

	// updates internal values - expected to be called at 60 fps
	void update( void );

	// renders everything to a window
	void render( sf::RenderWindow* window );

	// methods for managing text objects
	cText* createText( const char* text, unsigned int life );		// returns pointer to created object
	void destroyAll( void );
	

private:

	// list of text objects
	std::vector<cText*>* m_pTextList;

	// font
	sf::Font* m_pFont;

};

} // namespace GPUFractalZoomer

#endif // _CTEXTMANAGER_HPP_