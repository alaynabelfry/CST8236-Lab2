#include <SFML/Graphics.hpp>
#include <SFML\OpenGL.hpp>

int main(int argc, char *argv)
{
	sf::RenderWindow window(sf::VideoMode(400, 400), "Template", sf::Style::Titlebar | sf::Style::Close);

	sf::Image castleImage;
	castleImage.loadFromFile("res/castle.jpg");

	sf::Texture treeTexture;
	treeTexture.loadFromFile("res/tree.jpg");

	glEnable(GL_TEXTURE_2D);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glFrontFace(GL_CW);

	GLuint castleTextureID;
	glGenTextures(1, &castleTextureID);

	glBindTexture(GL_TEXTURE_2D, castleTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, castleImage.getSize().x, castleImage.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE,
		castleImage.getPixelsPtr()
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

		float offset = 0.25f;
		angle += 90.0f * deltaTime;

		//draw stuff
		GLfloat position[] = { positionZ, -0.1, positionZ, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, position);

		glPushMatrix();
		glRotatef(angle, 0.0f, 1.0f, 0.0f); // y axis rotate
		if (isRotating) {
			glRotatef(angle, 1.0f*rotateDir, 0.0f, 0.0f); //x axis rotate
		}

		glBegin(mode);

		float leftS = 0.3f;
		float rightS = 0.7f;
		float topT = 0.25f;
		float bottomT = 0.75f;

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

		// Right
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

		// Left
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

		// Back
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

		// Top
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

		// Bottom
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

		// End our drawing block.
		glEnd();

		glPopMatrix();

		window.display();
	}

	return 0;
}