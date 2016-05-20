// ------------------------------------------------------------------
// Mandelbrot
// ------------------------------------------------------------------
// by Alex Murray (TheComet)
// ------------------------------------------------------------------

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
   
   // calculate width
   float dx = maxX - minX;
   float dy = maxY - minY;
   
   // reset
   float ca = minX + dx*gl_TexCoord[0].x;
   float cbi = minY + dy*gl_TexCoord[0].y;
   float a = 0.0;
   float b = 0.0;
   float old_a;
/*
   // check if inside centre of mandelbrot
   // if we are inside, no need to run algorithm
   float q = pow((ca - 0.25), 2.0) + pow(cbi, 2.0);
   if( pow( cbi, 2.0 ) * 0.25 < q * ( q + ( ca - 0.25 ) ) )
   {
      if( pow((ca+1.0), 2.0) + pow(cbi, 2.0) > 0.0625 )
      {
*/
         // run mandelbrot algorithm
         float i;
         for( i = 0.0; i < maxIterations; i=i+1.0 )
         {

            old_a = a;
            a = a * (a*a - b*b) + ca;
            b = b * (2*old_a*old_a + old_a*old_a*old_a - b*b) + cbi;
            if( a*a + b*b > 4.0 ) break;
         }
         
         // successful
         if( i < maxIterations )
         {
         
            // smooth colouring
            //a = (i - (log(log(sqrt(a*a+b*b)))))/0.3010299;
            
            // get colour
            colour = getColour(i);

         }
/*
      }
   }
*/
   // output colour
   gl_FragColor = colour;
}

vec4 getColour( float i )
{
   float r=255.0f,g=0.0f,b=0.0f;
   float state = 2.0f;
   for( float j=0.0; j < i; j=j+1.0f )
   {
      if( state == 0.0f ){ ++r; if(r==255.0f){ state=1.0f; }}
      if( state == 1.0f ){ --b; if(b==0.0f  ){ state=2.0f; }}
      if( state == 2.0f ){ ++g; if(g==255.0f){ state=3.0f; }}
      if( state == 3.0f ){ --r; if(r==0.0f  ){ state=4.0f; }}
      if( state == 4.0f ){ ++b; if(b==255.0f){ state=5.0f; }}
      if( state == 5.0f ){ --g; if(g==0.0f  ){ state=0.0f; }}
   }
   vec4 ret = vec4(r,g,b,255.0f)/255.0f;
   return ret;
}
