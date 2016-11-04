#include <SFML/Graphics.hpp>
#include <SFML\OpenGL.hpp>

#include "cube.h"

int main(int argc, char *argv)
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Template", sf::Style::Titlebar | sf::Style::Close);

	sf::Image cubeImage;
	cubeImage.loadFromFile("res/walltexture.jpg");

	sf::Image bgImage;
	bgImage.loadFromFile("res/skyrs.jpg");

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glFrontFace(GL_CW);

	GLuint cubeTextureID;
	glGenTextures(1, &cubeTextureID);


	glBindTexture(GL_TEXTURE_2D, cubeTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cubeImage.getSize().x, cubeImage.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		cubeImage.getPixelsPtr()
	);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	GLuint bgTextureID;
	glGenTextures(1, &bgTextureID);
	glBindTexture(GL_TEXTURE_2D, bgTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bgImage.getSize().x, bgImage.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		bgImage.getPixelsPtr()
	);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	float positionZ = 0.5f;
	float angle = 0.0f;
	GLenum mode = GL_TRIANGLES;
	int rotateDir = 1;//changes to -1 to reverse x axis rotation
	bool isRotating = false;
	sf::Event evt;
	sf::Clock appTimer;
	Cube cube = Cube(cubeTextureID);
	while (window.isOpen()) {

		float deltaTime = appTimer.restart().asSeconds();

		while (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				window.close();
			}
			if (evt.type == sf::Event::KeyPressed) {
				if (evt.key.code == sf::Keyboard::Num1) {
					mode = GL_TRIANGLES;
				}
				else if (evt.key.code == sf::Keyboard::Num2) {
					mode = GL_TRIANGLE_FAN;
				}
				else if (evt.key.code == sf::Keyboard::Num3) {
					mode = GL_TRIANGLE_STRIP;
				}
				else if (evt.key.code == sf::Keyboard::Num4) {
					mode = GL_QUADS;
				}
				else if (evt.key.code == sf::Keyboard::Num5) {
					mode = GL_TRIANGLE_FAN;
				}
				else if (evt.key.code == sf::Keyboard::Up) {
					isRotating = true;
				}
				else if (evt.key.code == sf::Keyboard::Down) {
					isRotating = true;
					rotateDir = -1;
				}
			}
			else if (evt.type == sf::Event::KeyReleased) {
				if (evt.key.code == sf::Keyboard::Up || evt.key.code == sf::Keyboard::Down) {
					isRotating = false;
				}
			}
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		GLenum error = glGetError();

		//float offset = 0.25f;
		float offset = 1.0f;
		angle += 90.0f * deltaTime;

		//draw stuff
		GLfloat position[] = { positionZ, -0.1, positionZ, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		//draw background
		glBindTexture(GL_TEXTURE_2D, bgTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, bgImage.getSize().x, bgImage.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			bgImage.getPixelsPtr()
		);
		glPushMatrix();

		glBegin(GL_QUADS);

		float leftS = 0.0f;
		float rightS = 1.0f;
		float topT = 0.0f;
		float bottomT = 1.0f;

		// Front
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

		glEnd();

		glPushMatrix();
		//draw cube
		glBindTexture(GL_TEXTURE_2D, cubeTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, cubeImage.getSize().x, cubeImage.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			cubeImage.getPixelsPtr()
		);
		cube.Update(deltaTime, isRotating, rotateDir);
		cube.Draw(mode);



		window.display();
	}

	return 0;
}