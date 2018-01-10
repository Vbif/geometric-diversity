attribute vec4 a_vertex; attribute vec4 a_color; attribute vec2 a_texcoord;  
uniform mat4 u_modelview;  
varying vec4 vColor; varying vec2 vTexCoord; 

void main() 
{
	vColor = a_color; 
	vTexCoord = a_texcoord;  
	gl_Position = u_modelview * a_vertex; 
}  