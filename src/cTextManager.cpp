// -------------------------------------------------------------------
// Manages all text and font objects
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// include files
#include "gpu_fractal_zoomer/cTextManager.hpp"
#include "gpu_fractal_zoomer/cException.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>

namespace GPUFractalZoomer {

// -------------------------------------------------------------------
// constructor
cTextManager::cTextManager( void ) :
	m_pFont( NULL)
{
	// debug
	std::cout << "constructed cTextManager" << std::endl;

	this->m_pFont = new sf::Font();
}

// -------------------------------------------------------------------
// destructor
cTextManager::~cTextManager( void )
{
	// debug
	std::cout << "destructed cTextManager" << std::endl;

	delete this->m_pFont;
}

// -------------------------------------------------------------------
// load resources
void cTextManager::load( void )
{

	// load font
	if( !this->m_pFont->loadFromFile( "media/fonts/8_bit_party.ttf" ) )
	{
		throw cException();
	}

}

// -------------------------------------------------------------------
// create a new text object
void cTextManager::printText( float x, float y, std::string text, sf::RenderWindow* window )
{
	sf::Text newText;
	newText.setString( text );
	newText.setFont( *this->m_pFont );
	newText.setCharacterSize( 18 );
	newText.setColor( sf::Color::White );
	newText.setPosition( x, y );
	window->draw( newText );
}

} // namespace GPUFractalZoomer
