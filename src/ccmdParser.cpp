// -------------------------------------------------------------------
// Command Line Parser
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// Include files
#include "gpu_fractal_zoomer/ccmdParser.hpp"
#include <string.h>

// -------------------------------------------------------------------
// constructor
ccmdParser::ccmdParser( void ) :
	m_pIsReadyToLaunch( false ),
	m_pWidth( 800 ),
	m_pHeight( 600 ),
	m_pDepth( 32 ),
	m_pIsFullscreen( false ),
	m_pUseVsync( false )
{
	std::cout << "constructed ccmdParser" << std::endl;
}

// -------------------------------------------------------------------
// destructor
ccmdParser::~ccmdParser( void )
{
	std::cout << "destructed ccmdParser" << std::endl;
}

// -------------------------------------------------------------------
// ready to launch
bool ccmdParser::isReadyToLaunch( void )
{
	return this->m_pIsReadyToLaunch;
}

// -------------------------------------------------------------------
// gets the width
int ccmdParser::getWidth( void )
{
	return this->m_pWidth;
}

// -------------------------------------------------------------------
// gets the height
int ccmdParser::getHeight( void )
{
	return this->m_pHeight;
}

// -------------------------------------------------------------------
// gets the depth
int ccmdParser::getDepth( void )
{
	return this->m_pDepth;
}

// -------------------------------------------------------------------
// returns true if fullscreen was requested
bool ccmdParser::isFullscreen( void )
{
	return this->m_pIsFullscreen;
}

// -------------------------------------------------------------------
// returns true if vsync should be enabled
bool ccmdParser::useVsync( void )
{
	return this->m_pUseVsync;
}

// -------------------------------------------------------------------
// parses command line
void ccmdParser::parse( int argc, char** argv )
{
	int state = 0;
	for( int i = 0; i != argc; i++ )
	{
		for(;;)
		{

			// help
			if( strcmp( "--help", argv[i] ) == 0 )
			{
				std::cout << std::endl;
				std::cout << "==============================" << std::endl;
				std::cout << "\"Eight Bit Challenge\" - Help" << std::endl;
				std::cout << "==============================" << std::endl << std::endl;
				std::cout << "Arguments" << std::endl;
				std::cout << "	-w                - Sets the width of the screen" << std::endl;
				std::cout << "	-h                - Sets the height of the screen" << std::endl;
				std::cout << "	-d                - Sets the depth of the screen" << std::endl;
				std::cout << "	--fullscreen      - Sets the screen to fullscreen" << std::endl;
				std::cout << "	                    default is windowed" << std::endl;
				std::cout << "	--vsync           - Enable vertical sync" << std::endl;
				std::cout << "	                    default is disabled" << std::endl;
				break;
			}

			// set width
			if( strcmp( "-w", argv[i] ) == 0 )
			{
				state = 1;
				break;
			}
			if( state == 1 )
			{
				this->m_pWidth = atoi( argv[i] );
				state = 0;
				std::cout << "Width: " << this->m_pWidth << std::endl;
				break;
			}

			// set height
			if( strcmp( "-h", argv[i] ) == 0 )
			{
				state = 2;
				break;
			}
			if( state == 2 )
			{
				this->m_pHeight = atoi( argv[i] );
				state = 0;
				std::cout << "Height: " << this->m_pHeight << std::endl;
				break;
			}

			// set depth
			if( strcmp( "-d", argv[i] ) == 0 )
			{
				state = 3;
				break;
			}
			if( state == 3 )
			{
				this->m_pDepth = atoi( argv[i] );
				state = 0;
				std::cout << "Depth: " << this->m_pDepth << std::endl;
				break;
			}

			// set to fullscreen
			if( strcmp( "--fullscreen", argv[i] ) == 0 )
			{
				m_pIsFullscreen = true;
				std::cout << "Fullscreen enabled" << std::endl;
			}

			// enable vertical sync
			if( strcmp( "--vsync", argv[i] ) == 0 )
			{
				m_pUseVsync = true;
				std::cout << "Vertical sync enabled" << std::endl;
			}

			// nothing to do
			break;
		}
	}

	// check if enough information has been supplied to launch
	if( this->m_pWidth != 0 &&
		this->m_pHeight != 0 &&
		this->m_pDepth != 0 )
	{
		this->m_pIsReadyToLaunch = true;
	}
}
