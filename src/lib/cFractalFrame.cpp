// -------------------------------------------------------------------
// Handles drawing of the fractal
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// include files
#include <cFractalFrame.hpp>
#include <cException.hpp>
#include <iostream>

namespace GPUFractalZoomer {

// -------------------------------------------------------------------
// constructor
cFractalFrame::cFractalFrame( sf::RenderWindow* window ) :
	m_pQuad( NULL ),
	m_pShader( NULL )
{
	// debug
	std::cout << "constructed cFractalFrame" << std::endl;

	// set up vertex array
	this->m_pQuad = new sf::VertexArray( sf::Triangles, 3 );
	(*this->m_pQuad)[0].position = sf::Vector2f( 0, 0 );
	(*this->m_pQuad)[1].position = sf::Vector2f( static_cast<float>(window->getSize().x), 0.0 );
	(*this->m_pQuad)[2].position = sf::Vector2f( static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y) );
	//(*this->m_pQuad)[3].position = sf::Vector2f( 0.0, static_cast<float>(window->getSize().y) );

	// create shader
	this->m_pShader = new sf::Shader();
}

// -------------------------------------------------------------------
// destructor
cFractalFrame::~cFractalFrame( void )
{
	// debug
	std::cout << "destructed cFractalFrame" << std::endl;

	delete this->m_pShader;
	delete this->m_pQuad;
}

// -------------------------------------------------------------------
// load a fractal
void cFractalFrame::load( FractalType type )
{
	switch( type )
	{

		// mandelbrot
		case Mandelbrot :

			// attempt to load shader
			if( !this->m_pShader->loadFromFile( "media/shaders/commonVertexShader.vsh", "media/shaders/simpletest.fsh" ) )
			{
				throw cException();
			}

			// set default zoom values
			minX = -2.0f;
			maxX = 1.0f;
			minY = -1.2f;
			maxY = 1.2f;
			maxIterations = 10.0;

			break;

		default :
			break;
	}
}

// -------------------------------------------------------------------
// render fractal to window
void cFractalFrame::render( sf::RenderWindow* window )
{

	// set shader uniforms
	/*
	this->m_pShader->setParameter( "maxX", maxX );
	this->m_pShader->setParameter( "maxY", maxY );
	this->m_pShader->setParameter( "minX", minX );
	this->m_pShader->setParameter( "minY", minY );
	this->m_pShader->setParameter( "maxIterations", maxIterations );
	*/

	// render to window
	window->draw( *this->m_pQuad, this->m_pShader );
}

} // namespace GPUFractalZoomer