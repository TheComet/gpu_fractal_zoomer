// -------------------------------------------------------------------
// Exception thrower
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// include files
#include <cException.hpp>

// -------------------------------------------------------------------
// constructor
cException::cException( void ) throw()
{
	this->m_pMessage = "An error occured and the program must be terminated.";
}
cException::cException( const char* message ) throw()
{
	this->m_pMessage = message;
}

// -------------------------------------------------------------------
// destructor
cException::~cException( void ) throw()
{
}

// -------------------------------------------------------------------
// get message
const char* cException::what() const throw()
{
	return m_pMessage;
}
