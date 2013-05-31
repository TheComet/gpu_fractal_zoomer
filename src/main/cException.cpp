// -------------------------------------------------------------------
// Exception thrower
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// include files
#include <cException.hpp>

// -------------------------------------------------------------------
// constructor
cException::cException( void )
{
	this->m_pMessage = "An error occured and the program must be terminated.";
}
cException::cException( const char* message )
{
	this->m_pMessage = message;
}

// -------------------------------------------------------------------
// destructor
cException::~cException( void )
{
}

// -------------------------------------------------------------------
// get message
const char* cException::what() const throw()
{
	return m_pMessage;
}
