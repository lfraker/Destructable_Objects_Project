#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;

varying vec2 v_texcoord;
varying float colr;

void main()
{
    // Set fragment color from texture
    //gl_FragColor = texture2D(texture, v_texcoord);
    gl_FragColor = vec4(colr, colr, colr, 1.0);
}
