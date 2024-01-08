#pragma once

#include <map>

#include <glad\glad.h>
#include <glm\glm.hpp>

#include "Shader.h"

struct Character
{
	unsigned int TextureId;
	glm::ivec2 Size;
	glm::ivec2 Bearing;
	unsigned int Advance;
};

class TextRenderer 
{
public:

	std::map<char, Character> Characters;

	Shader TextShader;

	TextRenderer(unsigned int width, unsigned int height);

	void Load(std::string font, unsigned int fontSize);

	void RenderText(std::string text, float x, float y, float scale, glm::vec3 color = glm::vec3(1.0f));

private:
	unsigned int VBO, VAO;
};
