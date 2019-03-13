#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec3 color;
attribute float lines;

varying vec2 v_texcoord;
varying vec3 colr;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * a_position;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
    //v_texcoord = a_texcoord;
    if (lines > 0.5) {
        colr = color;
    }
    else {
        vec3 cl = vec3(min(abs(a_position.x) * 100.0, 100.0)/100.0, min(abs(a_position.y) * 100.0, 100.0)/100.0, min(abs(a_position.z) * 100.0, 100.0)/100.0);
        colr = cl;
    }
}
