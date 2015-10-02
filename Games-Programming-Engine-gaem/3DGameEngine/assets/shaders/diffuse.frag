#version 430
// Uniform
uniform sampler2D tex;
uniform vec2 uvTile; // how many times should texture tile?


// Subroutine for getting tex colour so we can return plain white if no texture
//subroutine vec4 getTexColour();
//subroutine uniform getTexColour texColour;

// In values from vertex shader
in vec2 texCoord;
in vec4 colour;

// Just used for shader without subroutines - int used like a bool
uniform int hasTex;

layout (location=0) out vec4 FragColour;

void main()
{	
	// Without subroutines
	if(hasTex == 0) // false
	{
		FragColour =  colour;
	}
	else
	{
		FragColour =  texture(tex, texCoord * uvTile) * colour;
	}
	
	// With subroutines	
	//FragColour =  texColour() * colour;
}

// Possible sub routines for getting tex colour
/*
subroutine(getTexColour)
vec4 noTex()
{
	return vec4(1.0, 1.0, 1.0, 1.0);
}

subroutine(getTexColour)
vec4 sampleTex()
{
	return texture(tex, texCoord * uvTile);
}
* */
