// -------------------------------------------------------------------
// Manages all text and font objects
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// include files
#include <cTextManager.hpp>
#include <iostream>
#include <cException.hpp>

namespace GPUFractalZoomer {

// -------------------------------------------------------------------
// constructor
cTextManager::cTextManager( void ) :
	m_pTextList( NULL ),
	m_pFont( NULL)
{
	// debug
	std::cout << "constructed cTextManager" << std::endl;

	this->m_pTextList = new std::vector<cText*>();
	this->m_pFont = new sf::Font();
}

// -------------------------------------------------------------------
// destructor
cTextManager::~cTextManager( void )
{
	// debug
	std::cout << "destructed cTextManager" << std::endl;

	// clean up any active text objects
	this->destroyAll();

	delete this->m_pFont;
	delete this->m_pTextList;
}

// -------------------------------------------------------------------
// load resources
void cTextManager::load( void )
{

	// load font
	if( !this->m_pFont->loadFromFile( "media/fonts/Znikomit.otf" ) )
	{
		throw cException();
	}

}

// -------------------------------------------------------------------
// update loop
void cTextManager::update( void )
{
	std::vector<cText*>::iterator it = this->m_pTextList->begin();
	while( it != this->m_pTextList->end() )
	{

		// update internal values of each object
		(*it)->update();

		// if life has reached 1, destroy text
		if( (*it)->getLife() == 1 )
		{
			delete (*it);
			it = this->m_pTextList->erase(it);

		// text doesn't need to be destroyed? Move on to next
		}else{
			it++;
		}
	}
}

// -------------------------------------------------------------------
// render all text to a window
void cTextManager::render( sf::RenderWindow* window )
{
	for( std::vector<cText*>::iterator it = this->m_pTextList->begin(); it != this->m_pTextList->end(); it++ )
	{
		window->draw( **it );
	}
}

// -------------------------------------------------------------------
// create a new text object
cText* cTextManager::createText( const char* text, unsigned int life )
{
	cText* newText = new cText();
	newText->setLife( life );
	newText->setString( text );
	newText->setFont( *this->m_pFont );
	newText->setCharacterSize( 14 );
	this->m_pTextList->push_back( newText );
	return newText;
}

// -------------------------------------------------------------------
// destroys all existing text objects
void cTextManager::destroyAll( void )
{
	std::vector<cText*>::iterator it = this->m_pTextList->begin();
	while( it != this->m_pTextList->end() )
	{
		delete (*it);
		it = this->m_pTextList->erase(it);
	}
}

} // namespace GPUFractalZoomer