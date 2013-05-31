// -------------------------------------------------------------------
// Command Line Parser
// -------------------------------------------------------------------

#ifndef _CCMDPARSER_HPP_
#define _CCMDPARSER_HPP_ 

// -------------------------------------------------------------------
// Include files
#include <iostream>
#include <stdlib.h>

// -------------------------------------------------------------------
// cmdParser class
class ccmdParser
{
public:

	// constructor, destructor
	ccmdParser( void  );
	~ccmdParser( void );

	// parses command line arguments
	void parse( int argc, char** argv );

	// gets arguments
	int getWidth( void );
	int getHeight( void );
	int getDepth( void );
	bool isFullscreen( void );
	bool useVsync( void );

	// ready to launch
	bool isReadyToLaunch( void );

private:

	// set to true when application has enough information to launch
	bool m_pIsReadyToLaunch;

	// screen properties
	int m_pWidth;
	int m_pHeight;
	int m_pDepth;
	bool m_pIsFullscreen;
	bool m_pUseVsync;
};

#endif // _CCMDPARSER_HPP_