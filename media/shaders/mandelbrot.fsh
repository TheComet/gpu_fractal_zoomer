// ------------------------------------------------------------------
// Mandelbrot
// ------------------------------------------------------------------
// by Alex Murray (TheComet)
// ------------------------------------------------------------------

#define POWER 2

// ------------------------------------------------------------------
// Uniforms
// ------------------------------------------------------------------

uniform float minX;
uniform float maxX;
uniform float minY;
uniform float maxY;
uniform float maxIterations;

// ------------------------------------------------------------------
// Shared
// ------------------------------------------------------------------

// gets the colour in proportion to the number of iterations
vec4 getColour( float i );

void main(void)
{

	// final colour will be stored here
	vec4 colour = vec4(0.0,0.0,0.0,1.0);

	// calculate width and height of window and set complex constant c
	float dx = maxX - minX;
	float dy = maxY - minY;
	float c_real = minX + dx * gl_TexCoord[0].x;
	float c_imag = minY + dy * gl_TexCoord[0].y;

	// reset
	float z_real = 0.0;
	float z_imag = 0.0;
	float z_real_raised = 0.0;
	float z_imag_raised = 0.0;

	// run mandelbrot algorithm
	float i;
	for( i = 0.0; i < maxIterations; i=i+1.0 )
	{
#if POWER == 2
		z_imag = 2.0*z_real*z_imag + c_imag;
		z_real = z_real_raised - z_imag_raised + c_real;
		z_real_raised = z_real*z_real;
		z_imag_raised = z_imag*z_imag;
#endif
#if POWER == 3
		float temp = 3.0*z_real*z_real*z_imag - z_imag_raised + c_imag;
		z_real = z_real_raised - 3.0*z_real*z_imag*z_imag + c_real;
		z_imag = temp;
		z_real_raised = z_real*z_real*z_real;
		z_imag_raised = z_imag*z_imag*z_imag;
#endif

		if( z_real_raised+z_imag_raised > 4.0 ) break;
	}

	// successful
	if( i < maxIterations )
	{

		// smooth colouring
		//a = (i - (log(log(sqrt(a*a+b*b)))))/0.3010299/maxIterations;

		// get colour
		colour = getColour(i);

	}

	// output colour
	gl_FragColor = colour;
}

vec4 getColour( float i )
{
	int r=0,g=0,b=0;
	int state = 0;
	for( float j=0.0; j < i; j=j+1.0 )
	{
		if( state == 0 ){ r++; if(r>25){ r=25; state=1; }}
		if( state == 1 ){ g--; if(g<0  ){ g=0;	state=2; }}
		if( state == 2 ){ b++; if(b>25){ b=25; state=3; }}
		if( state == 3 ){ r--; if(r<0  ){ r=0;	state=4; }}
		if( state == 4 ){ g++; if(g>25){ g=25; state=5; }}
		if( state == 5 ){ b--; if(b<0  ){ b=0;	state=0; }}
	}
	vec4 ret = vec4(r,g,b,25.0)/25.0;
	return ret;
}
