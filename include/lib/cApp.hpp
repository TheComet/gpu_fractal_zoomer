#ifndef _CAPP_HPP_
#define _CAPP_HPP_

// -------------------------------------------------------------------
// include files

#include <SFML/Window.hpp>
#include <cTextManager.hpp>
#include <cFractalFrame.hpp>

namespace GPUFractalZoomer {

class cApp
{
public:

	// constructor, destructor
	cApp( int width, int height, int depth, bool isFullscreen, bool useVsync );
	~cApp( void );

	// loads everything
	void load( void );

	// starts the game
	void go( void );

	// updates the game loop
	void updateGame( void );
	
	// renders everything
	void renderGame( void );

private:

	// sfml window
	sf::RenderWindow* m_pMainWindow;

	// clock for timing the main loop
	sf::Clock* m_pClock;

	// for event handling
	sf::Event* m_pEvent;

	// manages all fonts and text
	cTextManager* m_pTextManager;

	// fractal frame, a class to handle the fractal
	cFractalFrame* m_pFractalFrame;

	// counts how many game loops have passed
	unsigned long m_pLoopCounter;

};

} // namespace GPUFractalZoomer

#endif // _CAPP_HPP: