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
	cException( void );
	cException( const char* message );
	~cException( void );

	// override standard what method
	virtual const char* what() const throw();

private:

	const char* m_pMessage;

};

#endif // _CEXCEPTION_HPP_