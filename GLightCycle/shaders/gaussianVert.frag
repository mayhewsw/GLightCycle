uniform sampler2D RTBlurH; // this should hold the texture rendered by the horizontal blur pass
uniform int texSize;
  
void main(void)
{
	float blurSize = 1.0/texSize;
   vec4 sum = vec4(0.0);
 
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   sum += texture2D(RTBlurH, vec2(gl_TexCoord[0].s, gl_TexCoord[0].t - 4.0*blurSize)) * 0.05;
   sum += texture2D(RTBlurH, vec2(gl_TexCoord[0].s, gl_TexCoord[0].t - 3.0*blurSize)) * 0.09;
   sum += texture2D(RTBlurH, vec2(gl_TexCoord[0].s, gl_TexCoord[0].t - 2.0*blurSize)) * 0.12;
   sum += texture2D(RTBlurH, vec2(gl_TexCoord[0].s, gl_TexCoord[0].t - blurSize)) * 0.15;
   sum += texture2D(RTBlurH, vec2(gl_TexCoord[0].s, gl_TexCoord[0].t)) * 0.16;
   sum += texture2D(RTBlurH, vec2(gl_TexCoord[0].s, gl_TexCoord[0].t + blurSize)) * 0.15;
   sum += texture2D(RTBlurH, vec2(gl_TexCoord[0].s, gl_TexCoord[0].t + 2.0*blurSize)) * 0.12;
   sum += texture2D(RTBlurH, vec2(gl_TexCoord[0].s, gl_TexCoord[0].t + 3.0*blurSize)) * 0.09;
   sum += texture2D(RTBlurH, vec2(gl_TexCoord[0].s, gl_TexCoord[0].t + 4.0*blurSize)) * 0.05;
 
   gl_FragColor = sum;
}
