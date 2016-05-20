// -------------------------------------------------------------------
// Text class
// -------------------------------------------------------------------

#ifndef _CTEXT_HPP_
#define _CTEXT_HPP_

// -------------------------------------------------------------------
// include files

#include <SFML/Graphics.hpp>

namespace GPUFractalZoomer {

class cText : public sf::Text
{
public:

	// constructor, destructor
	cText( void );
	~cText( void );

	// get and set the life for the text
	void setLife( unsigned int& life );
	unsigned int& getLife( void );

	// update internal values
	void update( void );

private:

	// how many loops text should remain active
	unsigned int m_pLife;

};

} // namespace GPUFractalZoomer

#endif // _CTEXT_HPP_