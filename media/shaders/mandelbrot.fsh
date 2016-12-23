// ------------------------------------------------------------------
// Mandelbrot
// ------------------------------------------------------------------
// by Alex Murray (TheComet)
// ------------------------------------------------------------------

// Can be 2 or 3
#define POWER 2

// Set to 1 to enable. Set to 0 to disable
#define SMOOTH_COLOURING 1

// How fine-grained the colour palette should be
#define RESOLUTION 200

// ------------------------------------------------------------------
// Uniforms
// ------------------------------------------------------------------

uniform float minX;
uniform float maxX;
uniform float minY;
uniform float maxY;
uniform float maxIterations;
uniform float counter;

// ------------------------------------------------------------------
// Shared
// ------------------------------------------------------------------

// gets the colour in proportion to the number of iterations
vec4 getColour( float i, float resolution );

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
#if SMOOTH_COLOURING == 1
		i = (i - (log(log(sqrt(z_real_raised+z_imag_raised)))))/0.3010299;
#endif

		// get colour
		colour = getColour(i, RESOLUTION);

	}

	// output colour
	gl_FragColor = colour;
}

float wrap( float value, float wrap_to )
{
    while( value > wrap_to )
        value -= wrap_to;
    return value;
}

vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}

vec4 getColour( float i, float resolution )
{
	i = wrap ( i + wrap(counter/2, resolution), resolution ) / resolution;
	return vec4(hsv2rgb(vec3(i, 0.8, 1)), 1);
}

