// -------------------------------------------------------------------
// Include files
#include <cApp.hpp>
#include <iostream>
#include <sstream>
#include <cException.hpp>

namespace GPUFractalZoomer {

// -------------------------------------------------------------------
// Constructor
cApp::cApp( int width, int height, int depth, bool isFullscreen, bool useVsync ) :
	m_pMainWindow( NULL ),
	m_pClock( NULL ),
	m_pEvent( NULL ),
	m_pTextManager( NULL ),
	m_pFractalFrame( NULL ),
	m_pLoopCounter( 0 )
{

	// debug
	std::cout << "constructed cApp" << std::endl;

	// setup window
	if( isFullscreen )
	{
		this->m_pMainWindow = new sf::RenderWindow( sf::VideoMode( width, height ), "GPU Fractal Zoomer", sf::Style::Fullscreen );
	}else{
		this->m_pMainWindow = new sf::RenderWindow( sf::VideoMode( width, height ), "GPU Fractal Zoomer", sf::Style::Close | sf::Style::Titlebar );
	}
	this->m_pMainWindow->setVerticalSyncEnabled( useVsync );

	this->m_pClock = new sf::Clock();
	this->m_pEvent = new sf::Event();
	this->m_pTextManager = new cTextManager();
	this->m_pFractalFrame = new cFractalFrame( this->m_pMainWindow );
}

// -------------------------------------------------------------------
// Destructor
cApp::~cApp( void )
{
	// debug
	std::cout << "destructed cApp" << std::endl;

	if( this->m_pMainWindow ) delete this->m_pMainWindow;
	if( this->m_pClock ) delete this->m_pClock;
	if( this->m_pEvent ) delete this->m_pEvent;
	if( this->m_pTextManager ) delete this->m_pTextManager;
	if( this->m_pFractalFrame ) delete this->m_pFractalFrame;
}

// -------------------------------------------------------------------
// loads all resources
void cApp::load( void )
{
	this->m_pTextManager->load();
	this->m_pFractalFrame->load( cFractalFrame::Mandelbrot );
}

// -------------------------------------------------------------------
// main entry point of the application
void cApp::go( void )
{

	// restart clock
	this->m_pClock->restart();

	// application runs as long as the window is open
	while( this->m_pMainWindow->isOpen() )
	{

		// calculate how many loops should have theoretically passed
		sf::Time totalTimePassed = this->m_pClock->getElapsedTime();
		unsigned long targetLoopCount = totalTimePassed.asMilliseconds()/17;

		// process game loop until target loop count has been reached
		while( this->m_pLoopCounter < targetLoopCount )
		{
			this->updateGame();
			m_pLoopCounter++;
		}

		// render game
		this->renderGame();

		// poll window events
		while( this->m_pMainWindow->pollEvent( *this->m_pEvent ) )
		{
			switch( this->m_pEvent->type )
			{

				// mouse moved
				case sf::Event::MouseMoved :
					this->m_pFractalFrame->setZoomTarget( sf::Vector2f(
						static_cast<float>(this->m_pEvent->mouseMove.x),
						static_cast<float>(this->m_pEvent->mouseMove.y) ) );
					break;

				// mouse clicked
				case sf::Event::MouseButtonPressed :

					// zoom in or out
					if( this->m_pEvent->mouseButton.button == sf::Mouse::Left )
						this->m_pFractalFrame->setZoomSpeed( 1.0 );
					if( this->m_pEvent->mouseButton.button == sf::Mouse::Right )
						this->m_pFractalFrame->setZoomSpeed( -1.0 );

					break;

				// mouse scroll
				case sf::Event::MouseWheelMoved :

					// change maximum iterations
					this->m_pFractalFrame->setIterations(
						static_cast<float>(
							this->m_pFractalFrame->getIterations()+
							( this->m_pFractalFrame->getIterations()*0.1*
							this->m_pEvent->mouseWheel.delta)));
					break;

				// mouse released
				case sf::Event::MouseButtonReleased :
					this->m_pFractalFrame->setZoomSpeed( 0.0 );
					break;

				// keyboard input
				case sf::Event::KeyPressed :
					if( this->m_pEvent->key.code == sf::Keyboard::Escape )
						this->m_pMainWindow->close();
					break;

				// close window was requested
				case sf::Event::Closed :
					this->m_pMainWindow->close();
					break;

				// not interested in this event
				default :
					break;

			}
		}
	}
}

// -------------------------------------------------------------------
// updates game loop
void cApp::updateGame( void )
{
	this->m_pFractalFrame->update();
}

// -------------------------------------------------------------------
// renders game
void cApp::renderGame( void )
{

	// clear window
	this->m_pMainWindow->clear( sf::Color::Black );

	// render things
	this->m_pFractalFrame->render( this->m_pMainWindow );

	// print number of iterations to screen
	std::stringstream stream;
	stream << "Iterations: ";
	stream << static_cast<int>(this->m_pFractalFrame->getIterations());
	std::string string = stream.str();
	// this->m_pTextManager->printText( 2.0f, 2.0f, string, this->m_pMainWindow );
	// The above is not working currently for some reason

	// update
	this->m_pMainWindow->display();
}

} // namespace GPUFractalZoomer
