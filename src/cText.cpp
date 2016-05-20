// -------------------------------------------------------------------
// Manages all text and font objects
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// include files
#include "gpu_fractal_zoomer/cText.hpp"
#include <iostream>

namespace GPUFractalZoomer {

// -------------------------------------------------------------------
// constructor
cText::cText( void )
{
	// debug
	std::cout << "constructed cText" << std::endl;
}

// -------------------------------------------------------------------
// destructor
cText::~cText( void )
{
	// debug
	std::cout << "destructed cText" << std::endl;
}

// -------------------------------------------------------------------
// set life
void cText::setLife( unsigned int& life )
{
	this->m_pLife = life;
}

// -------------------------------------------------------------------
// get life
unsigned int& cText::getLife( void )
{
	return this->m_pLife;
}

// -------------------------------------------------------------------
// update
void cText::update( void )
{

	// decrement life
	if( this->m_pLife > 1 ) (this->m_pLife)--;

}

} // namespace GPUFractalZoomer
