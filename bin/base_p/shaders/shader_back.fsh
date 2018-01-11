precision mediump float;

uniform float time;
uniform vec2 resolution;

void main( void ) {

	vec2 position = ( gl_FragCoord.xy / resolution.xy );

	float color0 = (sin(position.x + time )) ;
	float color1 = (cos(position.y * time * 10.0 )) ;
	
	float res = clamp(color0 + color1, 0.0, 1.0);
	
	gl_FragColor = (vec4(86.0 / 255.0, 0, 234.0 / 255.0, 0.3)) * res;

}
