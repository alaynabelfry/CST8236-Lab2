#pragma once
#include <SFML\OpenGL.hpp>

class Cube
{
public:
	Cube(GLuint textureID);

	float _verticalAngle;

	void Update(float dt, bool isRotating, int rotateDir);
	void Draw(GLenum mode);

private:
	float _horizontalAngle;
	GLuint _textureID;

	float _textureOffset;
	bool isRotating;
	int rotateDir;
	float scrollDir;
};