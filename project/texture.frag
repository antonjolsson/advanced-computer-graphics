#version 420

// required by GLSL spec Sect 4.5.3 (though nvidia does not, amd does)
precision highp float;

layout(binding = 0) uniform sampler2D inputTexture;

layout(location = 0) out vec4 fragmentColor;

vec4 textureRect(in sampler2D tex, vec2 rectangleCoord)
{
	return texture(tex, rectangleCoord / textureSize(tex, 0));
}

void main()
{
	fragmentColor = textureRect(inputTexture, gl_FragCoord.xy);

}