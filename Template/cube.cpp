#include "Cube.h"

Cube::Cube(GLuint textureID) : _horizontalAngle(0), _verticalAngle(0), _textureID(textureID), isRotating(false), rotateDir(1)
{
	_textureOffset = 0.0f;
}


void Cube::Update(float dt, bool isRotating, int rotateDir)
{
	_horizontalAngle += 90.0f * dt;
	_textureOffset += 0.1f * dt;
	//if (_textureOffset > 1.0f) {
	if(_textureOffset > 0.6f){
		//_textureOffset -= 1.0f;
		_textureOffset -= 0.6f;
	}
	if (isRotating) {
		_verticalAngle += 90.0f*dt;
	}
}

void Cube::Draw(GLenum mode)
{
	float offset = 0.25f;

	float leftS = _textureOffset;
	float rightS = leftS + 0.4f;
	float topT = 0.25f;
	float bottomT = 0.75f;

	//glBindTexture(GL_TEXTURE_2D, _textureID);
	GLenum error = glGetError();

	glPushMatrix();
	error = glGetError();
	{
		glRotatef(_horizontalAngle, 0.0f, 1.0f, 0.0f); // y axis rotate
		if (isRotating) {
			glRotatef(_verticalAngle, 1.0f*rotateDir, 0.0f, 0.0f); //x axis rotate
		}

		glBegin(mode);

		glColor3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-offset, -offset, offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(offset, offset, offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(0.0f, 0.0f, 1.0f);
		glVertex3f(offset, -offset, offset);

		glColor3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, -offset, offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, offset, offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(1.0f, 0.0f, 0.0f);
		glVertex3f(offset, -offset, -offset);

		glColor3f(0.0f, 0.0f, 1.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, -offset, -offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(-1.0f, 0.0f, 0.0f);
		glVertex3f(-offset, -offset, offset);

		glColor3f(0.0f, 1.0f, 1.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(offset, -offset, -offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(0.0f, 0.0f, -1.0f);
		glVertex3f(-offset, -offset, -offset);

		glColor3f(1.0f, 0.0f, 1.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-offset, offset, offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-offset, offset, -offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(offset, offset, -offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(0.0f, 1.0f, 0.0f);
		glVertex3f(offset, offset, offset);

		glColor3f(1.0f, 1.0f, 1.0f);
		glTexCoord2f(leftS, bottomT);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-offset, -offset, -offset);

		glTexCoord2f(leftS, topT);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(-offset, -offset, offset);

		glTexCoord2f(rightS, topT);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(offset, -offset, offset);

		glTexCoord2f(rightS, bottomT);
		glNormal3f(0.0f, -1.0f, 0.0f);
		glVertex3f(offset, -offset, -offset);

		glEnd();
	}
	glPopMatrix();
}