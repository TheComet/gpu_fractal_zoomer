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

	// render fractal to window
	void render( sf::RenderWindow* window );

private:

	// use a quad to render the fractal
	sf::VertexArray* m_pQuad;

	// fragment program of the current fractal
	sf::Shader* m_pShader;

	// fractal parameters to be passed to the shader
	float minX;
	float maxX;
	float minY;
	float maxY;
	float maxIterations;
};

} // namespace GPUFractalZoomer

#endif // _CFRACTALFRAME_HPP_