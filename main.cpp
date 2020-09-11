#include <windows.h> 
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>

#include "OSMReader.h"
#include "RoadReader.h"
#include "camera.h"
#define PI	3.1415926
int height = 0.5f;
int length = 640, width = 480;
bool mouseIn = false;
unsigned char key = 0;
int mx, my;
float X = 0.0, Y = 1.0, Z = 0.0;
float camYaw = 0.0, camPitch = 0.0;
const std::string OSM_File_Name = "map/st.osm";
OSMReader read;
RoadReader roadReader;

void readfile()
{
	read.readfile(OSM_File_Name); 
	if (read.id_list.empty())
	{
		cout << "node id list is empty" << endl;
	}
	read.recomputeBound();

	roadReader.readRoad(read);

}

void drawtest(void)
{

	//glColor3f(0, 1, 0);
	//glTranslated(1, 0.5, 1);
	//glutSolidCube(1);

}

void drawCircle(glm::vec3 centerPoint)
{
	double R = RoadWidth, pi = 3.1415926;
	int n = 20;
	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex3f(R*cos(2 * pi / n * i) + centerPoint.x, 0.1, R*sin(2 * pi / n * i) + centerPoint.z);
	}
	glEnd();

	glBegin(GL_POLYGON);
	for (int i = 0; i < n; i++)
	{
		glVertex3f(R * cos(2 * pi / n * i) + centerPoint.x, 0.1+height, R * sin(2 * pi / n * i) + centerPoint.z);
	}
	glEnd();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();

	CameraControllor(1, 0.1, key, mx, my);
	updateCamera();

	glBegin(GL_QUADS);
	glColor3f(0.3f, 0.3f, 0.3f);
	glVertex3f(-200.0f, 0.0f, -200.0f);
	glVertex3f(-200.0f, 0.0f, 200.0f);
	glVertex3f(200.0f, 0.0f, 200.0f);
	glVertex3f(200.0f, 0.0f, -200.0f);
	glEnd();
	
	//draw();

	for (int i = 0; i < roadReader.roads.size(); i++)
	{
		const Road& road = roadReader.roads[i];

		 
		//glVertex3d(read.lat_list[i], 0, read.lon_list[i]);
		for (int p_i = 0 ; p_i < road.points.size() ; p_i += 5)
		{
			glm::vec3 centerPoint = road.points[p_i];
			glColor3f(1, 0, 0);
			drawCircle(centerPoint);

			glColor3f(1, 0, 0);
			glBegin(GL_QUADS);
			for (int quad_i = 1 ; quad_i < 5 ; ++quad_i)
			{
				const glm::vec3& point = road.points[p_i + quad_i];
				glVertex3f(point.x, point.y, point.z);
			}
			glEnd();

			glColor3f(1, 0, 0);
			glBegin(GL_QUADS);
			for (int quad_i = 1; quad_i < 5; ++quad_i)
			{
				const glm::vec3& point = road.points[p_i + quad_i];
				glVertex3f(point.x, point.y+ height, point.z);
			}
			glEnd();

			glColor3f(1, 0, 0);
			glBegin(GL_QUADS);
			for (int quad_i = 1; quad_i < 3; quad_i = quad_i+1)
			{
				const glm::vec3& point = road.points[p_i + quad_i];
				glVertex3f(point.x, point.y, point.z);
				glVertex3f(point.x, point.y+ height, point.z);
			}
			glEnd();

			glColor3f(1, 0, 0);
			glBegin(GL_QUADS);
			for (int quad_i = 3; quad_i < 5; quad_i = quad_i + 1)
			{
				const glm::vec3& point = road.points[p_i + quad_i];
				glVertex3f(point.x, point.y, point.z);
				glVertex3f(point.x, point.y + height, point.z);
			}
			glEnd();

			glColor3f(1, 0, 0);
			glBegin(GL_QUADS);
			for (int quad_i = 2; quad_i < 4; quad_i = quad_i + 1)
			{
				const glm::vec3& point = road.points[p_i + quad_i];
				glVertex3f(point.x, point.y, point.z);
				glVertex3f(point.x, point.y + height, point.z);
			}
			glEnd();

			glColor3f(1, 0, 0);
			glBegin(GL_QUADS);
			for (int quad_i = 1; quad_i < 5; quad_i = quad_i + 3)
			{
				const glm::vec3& point = road.points[p_i + quad_i];
				glVertex3f(point.x, point.y, point.z);
				glVertex3f(point.x, point.y + height, point.z);
			}
			glEnd();



		}
		//cout << read.lat_list[i]<< " " << " " << " " << read.lon_list[i] << endl;
	}

	glFlush();
	glutSwapBuffers();

	key = 0;
}

void CameraControllor(float moveVelo, float mouseVelo, unsigned char key, int mX, int mY)
{
	int midX = length / 2;
	int midY = width / 2;

	glutSetCursor(GLUT_CURSOR_NONE);

	camYaw += mouseVelo * (midX - mX);
	camPitch += mouseVelo * (midY - mY);

	lockCameraDir();

	glutWarpPointer(midX, midY);

	switch (key)
	{
	case 'w':
		if (camPitch != 90.0 && camPitch != -90.0)
			CameraXZ(moveVelo, 0.0);

		CameraY(moveVelo, 0.0);
		break;

	case 's':
		if (camPitch != 90.0 && camPitch != -90.0)
			CameraXZ(moveVelo, 180.0);

		CameraY(moveVelo, 180.0);
		break;

	case 'a':
		CameraXZ(moveVelo, 90.0);
		break;

	case 'd':
		CameraXZ(moveVelo, 270.0);
		break;
	}

	glRotatef(-camPitch, 1.0, 0.0, 0.0);
	glRotatef(-camYaw, 0.0, 1.0, 0.0);
}

void lockCameraDir(void)
{

	if (camPitch > 90.0)
		camPitch = 90.0;

	if (camPitch < -90.0)
		camPitch = -90.0;

	if (Y < 1.0)
		Y = 1;

	if (camYaw > 360.0)
		camYaw -= 360;
}

void CameraXZ(float Velo, float dir)
{
	float r = (camYaw + dir) * PI / 180.0;

	X -= sin(r) * Velo;
	Z -= cos(r) * Velo;
}

void CameraY(float Velo, float dir)
{
	float r = (camPitch + dir) * PI / 180.0;

	Y += sin(r) * Velo;
}


void updateCamera(void)
{
	glTranslatef(-X, -Y, -Z);
}


void processNormalKeys(unsigned char pressedKey, int x, int y)
{
	if (pressedKey == 27)
		exit(0);

	if (pressedKey == 'w' || pressedKey == 'a' || pressedKey == 's' || pressedKey == 'd')
		key = pressedKey;
}


void mouseMove(int xx, int yy)
{
	mx = xx;
	my = yy;
}

void reshape(int w, int h)
{
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);

	gluPerspective(45, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(length, width);
	glutCreateWindow("Project");
	readfile();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(display);

	glutKeyboardFunc(processNormalKeys);

	//glutMouseFunc(mouseButton);
	glutPassiveMotionFunc(mouseMove);

	glEnable(GL_DEPTH_TEST);
	//cout << glGetString(GL_VERSION) << endl;
	glutMainLoop();

	return EXIT_SUCCESS;
}