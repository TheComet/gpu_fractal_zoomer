// -------------------------------------------------------------------
// Handles drawing of the fractal
// -------------------------------------------------------------------

// -------------------------------------------------------------------
// include files
#include "gpu_fractal_zoomer/cFractalFrame.hpp"
#include "gpu_fractal_zoomer/cException.hpp"
#include <iostream>

namespace GPUFractalZoomer {

// -------------------------------------------------------------------
// constructor
cFractalFrame::cFractalFrame( sf::RenderWindow* window ) :
	m_pQuad( NULL ),
	m_pShader( NULL ),
	m_pZoomTarget( 0.0, 0.0 ),
	m_pZoomSpeed( 0.0 ),
	m_pWindowSizeX( static_cast<float>(window->getSize().x) ),
	m_pWindowSizeY( static_cast<float>(window->getSize().y) )
{
	// debug
	std::cout << "constructed cFractalFrame" << std::endl;

	// set up vertex array
	this->m_pQuad = new sf::VertexArray( sf::Quads, 4 );

	// define quad to fill entire screen
	(*this->m_pQuad)[0].position = sf::Vector2f( 0.0, 0.0 );
	(*this->m_pQuad)[1].position = sf::Vector2f( static_cast<float>(window->getSize().x), 0.0 );
	(*this->m_pQuad)[2].position = sf::Vector2f( static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y) );
	(*this->m_pQuad)[3].position = sf::Vector2f( 0.0, static_cast<float>(window->getSize().y) );

	// set texture coordinates
	(*this->m_pQuad)[0].texCoords = sf::Vector2f( 0.0, 0.0 );
	(*this->m_pQuad)[1].texCoords = sf::Vector2f( 1.0, 0.0 );
	(*this->m_pQuad)[2].texCoords = sf::Vector2f( 1.0, 1.0 );
	(*this->m_pQuad)[3].texCoords = sf::Vector2f( 0.0, 1.0 );

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
			if( !this->m_pShader->loadFromFile( "media/shaders/commonVertexShader.vsh", "media/shaders/mandelbrot.fsh" ) )
			{
				throw cException();
			}

			// set default zoom values
			this->minX = -2.0f;
			this->maxX = 1.0f;
			this->minY = -1.2f;
			this->maxY = 1.2f;
			this->maxIterations = 500.0;
			this->m_pAspectRatio.x = (maxX-minX)/(maxY-minY);
			this->m_pAspectRatio.y = 1.0f;

			// debug
			std::cout << "loaded mandelbrot fractal" << std::endl;

			break;

		default :
			break;
	}
}

// -------------------------------------------------------------------
// set zoom speed
void cFractalFrame::setZoomSpeed( float speed )
{
	this->m_pZoomSpeed = speed;
}

// -------------------------------------------------------------------
// sets the target to zoom into
void cFractalFrame::setZoomTarget( sf::Vector2f target )
{
	// convert from pixel coordinates to fractal space coordinates
	sf::Vector2f fractalTarget;
	fractalTarget.x = (maxX-minX) * target.x / this->m_pWindowSizeX + minX;
	fractalTarget.y = (maxY-minY) * target.y / this->m_pWindowSizeY + minY;
	this->m_pZoomTarget = fractalTarget;
}

// -------------------------------------------------------------------
// sets number of iterations
void cFractalFrame::setIterations( float iterations )
{

	// limit between 1 and 10'000
	if( iterations < 1.0f ) iterations = 1.0f;
	if( iterations > 10000.0f ) iterations = 10000.0f;
	this->maxIterations = iterations;
	std::cout << "Iterations: " << this->maxIterations << std::endl;
}

// -------------------------------------------------------------------
// gets number of iterations
float cFractalFrame::getIterations( void )
{
	return this->maxIterations;
}

// -------------------------------------------------------------------
// update
void cFractalFrame::update( void )
{

	// calculate new maxX and minX values, weighted by where the mouse is positioned
	float gap = maxX-minX;
	float reduce = gap * 0.01f * this->m_pZoomSpeed;
	float weight = (maxX-this->m_pZoomTarget.x) / gap;
	maxX = maxX - (reduce * weight);
	minX = minX + (reduce * (1.0f - weight));

	// calculate new maxY and minY values, weighted by where the mouse is positioned
	gap = maxY-minY;
	reduce = gap * 0.01f * this->m_pZoomSpeed;
	weight = (maxY-this->m_pZoomTarget.y) / gap;
	maxY = maxY - (reduce * weight);
	minY = minY + (reduce * (1.0f - weight));

	// retain aspect ratio (need to do this due to floating point inprecision)
	maxX = (maxY-minY) * this->m_pAspectRatio.x / this->m_pAspectRatio.y + minX;

}

// -------------------------------------------------------------------
// render fractal to window
void cFractalFrame::render( sf::RenderWindow* window )
{

	// set shader uniforms
	this->m_pShader->setParameter( "maxX", maxX );
	this->m_pShader->setParameter( "maxY", maxY );
	this->m_pShader->setParameter( "minX", minX );
	this->m_pShader->setParameter( "minY", minY );
	this->m_pShader->setParameter( "maxIterations", maxIterations );

	// render to window
	window->draw( *this->m_pQuad, this->m_pShader );
}

} // namespace GPUFractalZoomer
