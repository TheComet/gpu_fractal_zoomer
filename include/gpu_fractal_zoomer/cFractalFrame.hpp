// -------------------------------------------------------------------
// Handles drawing of the fractal
// -------------------------------------------------------------------

#ifndef _CFRACTALFRAME_HPP_
#define _CFRACTALFRAME_HPP_

// -------------------------------------------------------------------
// include files
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

namespace GPUFractalZoomer {

class cFractalFrame
{
public:

	// factal types
	enum FractalType
	{
		Mandelbrot
	};

	// constructor, destructor
	cFractalFrame( sf::RenderWindow* window );
	~cFractalFrame( void );

	// load a fractal
	void load( FractalType type );

	// manipulate view of fractal
	void setZoomSpeed( float speed );
	void setZoomTarget( sf::Vector2f target );
	void setIterations( float iterations );
	float getIterations( void );

	// updates internal values
	void update( void );

	// render fractal to window
	void render( sf::RenderWindow* window );

private:

	// use a quad to render the fractal
	sf::VertexArray* m_pQuad;

	// fragment program of the current fractal
	sf::Shader* m_pShader;

	// zoom controls
	sf::Vector2f m_pZoomTarget;
	float m_pZoomSpeed;

	// holds the window dimensions
	float m_pWindowSizeX;
	float m_pWindowSizeY;

	// fractal parameters to be passed to the shader
	sf::Vector2f m_pAspectRatio;
	float minX;
	float maxX;
	float minY;
	float maxY;
	float maxIterations;
};

} // namespace GPUFractalZoomer

#endif // _CFRACTALFRAME_HPP_