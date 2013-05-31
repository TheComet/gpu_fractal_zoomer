void main( void )
{
	vec4 colour = vec4(gl_TexCoord[0].xy, 0.4f, 1.0);
	gl_FragColor = colour;
}