// -------------------------------------------------------------------
// GPU Fractal Zoomer
// -------------------------------------------------------------------
// author		: TheComet (Alex Murray)
// date started	: 31.05.2013
// date ended	: ?
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// Include files
#include <iostream>
#include <cException.hpp>
#include <ccmdParser.hpp>
#include <cApp.hpp>

// -------------------------------------------------------------------
// Main entry point
int main( int argc, char* argv[] )
{

	// declare application
	GPUFractalZoomer::cApp* theApp = NULL;

	try
	{

	#ifdef NDEBUG

		// -------------------------------------------------------------------
		// parse command line arguments
		ccmdParser parser;
		parser.parse( argc, argv );

		// check if app can be launched
		if( parser.isReadyToLaunch() == false ){
			std::cout << "Not enough arguments were passed to the application to start" << std::endl;
			std::cout << "Try using \"--help\" for more information" << std::endl;
			std::cin.ignore();
			return 0;
		}

		// construct app
		theApp = new GPUFractalZoomer::cApp(
			parser.getWidth(),
			parser.getHeight(),
			parser.getDepth(),
			parser.isFullscreen(),
			parser.useVsync()
		);

	#endif
	#ifdef _DEBUG

		// construct app with hard coded parameters
		theApp = new GPUFractalZoomer::cApp( 800, 600, 32, false, true );

	#endif

		// run the game
		theApp->load();
		theApp->go();

		// destroy app
		delete theApp;

	}
	catch( std::exception& e )
	{
		std::cerr << e.what() << std::endl << std::endl;
		if( theApp ) delete theApp;
		std::cout << "...Press any key to quit" << std::endl;
		std::cin.ignore();
	}

	// exit process
	return 0;
}