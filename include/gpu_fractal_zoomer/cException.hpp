// -------------------------------------------------------------------
// Exception thrower
// -------------------------------------------------------------------

#ifndef _CEXCEPTION_HPP_
#define _CEXCEPTION_HPP_

// -------------------------------------------------------------------
// include files
#include <exception>

class cException : public std::exception
{
public:

	// error messages can be passed to constructor
	cException( void ) throw();
	cException( const char* message ) throw();
	~cException( void ) throw();

	// override standard what method
	virtual const char* what() const throw();

private:

	const char* m_pMessage;

};

#endif // _CEXCEPTION_HPP_
