#include "main_game.h"
#include <GL\GLU.h>
#include <math.h>
#include "extendedGL.h"
#include "fileIO.h"

#define M_PI       3.14159265358979323846

void main_game::initializeGraphics()
{
	main_game_state::initializeGraphics();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->playerWorldRotation.x = 0.0f;
	this->playerWorldRotation.y = 0.0f;
	this->playerWorldRotation.z = 0.0f;

	glEnable(GL_MULTISAMPLE);
	glEnable(GL_POLYGON_SMOOTH);

	loadFile("credits.tga", &creditsTextureData);

	glGenTextures(1, &creditsTextureHandle);
	glBindTexture(GL_TEXTURE_2D, creditsTextureHandle);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 1024, 1024, GL_RGBA, GL_UNSIGNED_BYTE, creditsTextureData);
	// Check if anisotropic is supported.
	if(strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic"))
	{
		// Create a float to hold the max texture anisotropy.
		GLfloat fLargest;
		// Get the GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT paramater (0x84FF).
		glGetFloatv(0x84FF, &fLargest);
		// Set the texture parameter GL_TEXTURE_MAX_ANISOTROPY_EXT (0x84FE).
		glTexParameterf(GL_TEXTURE_2D, 0x84FE, fLargest);

		// Set the minimum distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// Set the magnifying distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		// Set the minimum distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// Set the magnifying distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	loadFile("moon.tga", &moonTextureData);

	glGenTextures(1, &moonTextureHandle);
	glBindTexture(GL_TEXTURE_2D, moonTextureHandle);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 1024, 1024, GL_RGB, GL_UNSIGNED_BYTE, moonTextureData);
	// Check if anisotropic is supported.
	if(strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic"))
	{
		// Create a float to hold the max texture anisotropy.
		GLfloat fLargest;
		// Get the GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT paramater (0x84FF).
		glGetFloatv(0x84FF, &fLargest);
		// Set the texture parameter GL_TEXTURE_MAX_ANISOTROPY_EXT (0x84FE).
		glTexParameterf(GL_TEXTURE_2D, 0x84FE, fLargest);

		// Set the minimum distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// Set the magnifying distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		// Set the minimum distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// Set the magnifying distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	loadFile("stars.tga", &starsTextureData);

	glGenTextures(1, &starsTextureHandle);
	glBindTexture(GL_TEXTURE_2D, starsTextureHandle);
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 1024, 1024, GL_RGBA, GL_UNSIGNED_BYTE, starsTextureData);
	// Check if anisotropic is supported.
	if(strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic"))
	{
		// Create a float to hold the max texture anisotropy.
		GLfloat fLargest;
		// Get the GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT paramater (0x84FF).
		glGetFloatv(0x84FF, &fLargest);
		// Set the texture parameter GL_TEXTURE_MAX_ANISOTROPY_EXT (0x84FE).
		glTexParameterf(GL_TEXTURE_2D, 0x84FE, fLargest);

		// Set the minimum distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		// Set the magnifying distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
	else
	{
		// Set the minimum distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		// Set the magnifying distance filter to be linear.
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}

	if(loadFile("earth.tga", &earthTextureData) > 0)
	{
		glGenTextures(1, &earthTextureHandle);
		glBindTexture(GL_TEXTURE_2D, earthTextureHandle);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 1000, 500, GL_RGB, GL_UNSIGNED_BYTE, earthTextureData);
		// Check if anisotropic is supported.
		if(strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic"))
		{
			// Create a float to hold the max texture anisotropy.
			GLfloat fLargest;
			// Get the GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT paramater (0x84FF).
			glGetFloatv(0x84FF, &fLargest);
			// Set the texture parameter GL_TEXTURE_MAX_ANISOTROPY_EXT (0x84FE).
			glTexParameterf(GL_TEXTURE_2D, 0x84FE, fLargest);

			// Set the minimum distance filter to be linear.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			// Set the magnifying distance filter to be linear.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			// Set the minimum distance filter to be linear.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// Set the magnifying distance filter to be linear.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}

	this->earthRotation = 0.0f;

	if(loadFile("sun.tga", &sunTextureData) > 0)
	{
		glGenTextures(1, &sunTextureHandle);
		glBindTexture(GL_TEXTURE_2D, sunTextureHandle);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, 1024, 512, GL_RGB, GL_UNSIGNED_BYTE, sunTextureData);
		// Check if anisotropic is supported.
		if(strstr((char*)glGetString(GL_EXTENSIONS), "GL_EXT_texture_filter_anisotropic"))
		{
			// Create a float to hold the max texture anisotropy.
			GLfloat fLargest;
			// Get the GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT paramater (0x84FF).
			glGetFloatv(0x84FF, &fLargest);
			// Set the texture parameter GL_TEXTURE_MAX_ANISOTROPY_EXT (0x84FE).
			glTexParameterf(GL_TEXTURE_2D, 0x84FE, fLargest);

			// Set the minimum distance filter to be linear.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			// Set the magnifying distance filter to be linear.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		}
		else
		{
			// Set the minimum distance filter to be linear.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			// Set the magnifying distance filter to be linear.
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
	}

	for(int i = 0;i < 640 * 480 * 4;i += 1)
	{
		this->feedbackDisplayData[i] = 255;
	}

	glGenTextures(1, &this->feedbackDisplayHandle);
	glBindTexture(GL_TEXTURE_2D, this->feedbackDisplayHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 640, 480, 0, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)this->feedbackDisplayData);
	glBindTexture(GL_TEXTURE_2D, 0);

	glShadeModel(GL_SMOOTH);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

	mroModel = new wavefrontObject();
	mroModel->loadGraphics("MRO.obj");
	this->mroRotation = 0;

	MKIIIModel = new wavefrontObject();
	MKIIIModel->loadGraphics("MKIII.obj");

	tardisModel = new wavefrontObject();
	tardisModel->loadGraphics("tardis.obj");

	this->kinect = new Kinect();

	this->camera.Position.y = -1.0f;

	printf("main game-initializeGraphics\n");
}

void main_game::initializeLogic()
{
	printf("main game-initializeLogic\n");
}
void main_game::initializeSound()
{
	printf("main game-initializeSound\n");
}

GLfloat lightPosition[] = {0.0f, 1000.0f, 3000.0f, 0.0f};
GLfloat spot_direction[] = {0.0f, 0.0f, 1.0f};

bool main_game::draw()
{
	glEnable(GL_LIGHTING);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	glPushMatrix();
	{
		glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
		//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	}
	glPopMatrix();

	glBindTexture(GL_TEXTURE_2D, 0);

	glDisable(GL_LIGHTING);
	// Draw a quad
	glPushMatrix();
	{
		GLUquadric *moon = gluNewQuadric();
		gluQuadricTexture(moon,GL_TRUE);
		gluQuadricNormals(moon, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, moonTextureHandle);
		glTranslatef(0.0f, -1001.0f, 0.0f);
		glColor4f(1, 1, 1, 1);

		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glScalef(1000.0f, 1000.0f, 1000.0f);
		glMatrixMode(GL_MODELVIEW);

		gluSphere(moon, 1000.0, 100, 100);

		glMatrixMode(GL_TEXTURE);
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
	}
	glPopMatrix();

	glPushMatrix();
	{
		GLUquadric *qobj = gluNewQuadric();
		gluQuadricTexture(qobj,GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, starsTextureHandle);
		glTranslated(4.0, 0.5, -4.0);
		glRotatef(90.0f, 1, 0, 0);
		glColor4f(1, 1, 1, 1);

		gluSphere(qobj, 100000000.0, 1000, 1000);
	}
	glPopMatrix();

	glPushMatrix();
	{
		GLUquadric *qobj = gluNewQuadric();
		gluQuadricTexture(qobj, GL_TRUE);
		gluQuadricNormals(qobj, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, sunTextureHandle);
		glRotatef(-this->earthRotation * 0.5f, 0, 1, 0);
		glTranslatef(0.0f, 1000.0f, 2800.0f);
		glColor4f(1, 1, 1, 1);
		gluSphere(qobj, 1000.0, 100, 100);
	}
	glPopMatrix();

	glEnable(GL_LIGHTING);

	glPushMatrix();
	{
		GLUquadric *qobj = gluNewQuadric();
		gluQuadricTexture(qobj, GL_TRUE);
		gluQuadricNormals(qobj, GL_TRUE);
		glBindTexture(GL_TEXTURE_2D, earthTextureHandle);
		glRotatef(this->earthRotation, 0, 1, 0);
		glTranslatef(0.0f, 500.0f, -1500.0f);
		glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
		glColor4f(1, 1, 1, 1);
		gluSphere(qobj, 500.0, 100, 100);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, creditsTextureHandle);

		glTranslatef(0.0f, 0.0f, 5.0f);

		glBegin(GL_QUADS);
		{
			glVertex3f(-1.0f, -1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f);

			glVertex3f(1.0f, -1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);

			glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 1.0f);

			glVertex3f(-1.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 1.0f);
		}
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, 0);

		glTranslatef(0.0f, 75.0f, -100.0f);
		glRotatef(this->mroRotation, 0, 0, 1);
		glColor3f(1.0f, 0.0f, 0.0f);
		this->mroModel->draw();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, 0);

		glTranslatef(5.0f, 0.75f, 2.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);
		this->MKIIIModel->draw();
	}
	glPopMatrix();

	glDisable(GL_LIGHTING);
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, 0);

		glScalef(0.01f, 0.01f, 0.01f);
		glTranslatef(0.0f, 1.0f, 2.0f);
		glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
		glColor3f(1.0f, 1.0f, 1.0f);

		//this->tardisModel->draw();
	}
	glPopMatrix();

	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, 0);
		glTranslatef(0.0f, 75.0f, 100.0f);
		glScalef(0.01f, 0.01f, 0.01f);
		glColor3f(1.0f, 1.0f, 1.0f);
		//this->deathStarModel->draw();
	}
	glPopMatrix();

	if(this->kinect->active)
	{
		float size = 0.1f;
		// Left hand
		glPushMatrix();
		{
			GLUquadric *qobj = gluNewQuadric();
			gluQuadricNormals(qobj, GL_TRUE);

			glBindTexture(GL_TEXTURE_2D, 0);

			glTranslatef(this->leftHand.position.x, this->leftHand.position.y, this->leftHand.position.z);
			//glRotatef(this->leftHand.rotation.rotationAngle, -this->leftHand.rotation.axis.x, this->leftHand.rotation.axis.y, -this->leftHand.rotation.axis.z);
			glColor3f(1, 0, 0);

			gluSphere(qobj, size, 10, 10);
		}
		glPopMatrix();

		// Right hand
		glPushMatrix();
		{
			GLUquadric *qobj = gluNewQuadric();
			gluQuadricNormals(qobj, GL_TRUE);

			glBindTexture(GL_TEXTURE_2D, 0);

			glTranslatef(this->rightHand.x, this->rightHand.y, this->rightHand.z);
			glColor3f(0, 0.5f, 0);

			gluSphere(qobj, size, 10, 10);
		}
		glPopMatrix();

		// Left foot
		glPushMatrix();
		{
			GLUquadric *qobj = gluNewQuadric();
			gluQuadricNormals(qobj, GL_TRUE);

			glBindTexture(GL_TEXTURE_2D, 0);

			glTranslatef(this->leftFoot.x, this->leftFoot.y, this->leftFoot.z);
			glColor3f(1, 0, 1);

			gluSphere(qobj, size, 10, 10);
		}
		glPopMatrix();

		// Right foot
		glPushMatrix();
		{
			GLUquadric *qobj = gluNewQuadric();
			gluQuadricNormals(qobj, GL_TRUE);

			glBindTexture(GL_TEXTURE_2D, 0);

			glTranslatef(this->rightFoot.x, this->rightFoot.y, this->rightFoot.z);
			glColor3f(0, 0, 1);

			gluSphere(qobj, size, 10, 10);
		}
		glPopMatrix();
	}

	glDisable(GL_LIGHTING);
	return true;
}

bool main_game::updateGraphics()
{
	main_game_state::updateGraphics();
	return true;
}

bool main_game::updateSound()
{
	return true;
}

float distanceFromCenterOfPlanet(vertex_t point)
{
	float distance = 0.0f;

	distance = ((point.x - 0.0f) * (point.x - 0.0f));
	distance += ((point.y - 1000.0f) * (point.y - 1000.0f));
	distance += ((point.z - 0.0f) * (point.z - 0.0f));
	distance = sqrt(distance);

	return distance;
}

bool main_game::updateLogic()
{
	main_game_state::updateLogic();
	if(this->mroRotation >= 360)
	{
		this->mroRotation = 0;
	}
	else
	{
		this->mroRotation += 1;
	}

	if(this->earthRotation < 360.0f)
	{
		this->earthRotation += 0.1f;
	}
	else
	{
		this->earthRotation = 0.0f;
	}

	vertex_t position = {this->camera.Position.x, this->camera.Position.y, this->camera.Position.z};
	/*
	while(distanceFromCenterOfPlanet(position) > 1000.0f)
	{
		this->camera.Position.y += 0.0001f;

		position.y = this->camera.Position.y;
	}
	while(distanceFromCenterOfPlanet(position) < 1000.0f)
	{
		this->camera.Position.y -= 0.0001f;

		position.y = this->camera.Position.y;
	}*/

	if(this->kinect->active)
	{
		const NUI_SKELETON_DATA skeleton = this->kinect->getMainPerson(0);
		NUI_SKELETON_BONE_ORIENTATION boneOrientations[NUI_SKELETON_POSITION_COUNT];
		NuiSkeletonCalculateBoneOrientations(&skeleton, boneOrientations);

		if(skeleton.eTrackingState == NUI_SKELETON_POSITION_TRACKED)
		{
			this->camera.Position.x = skeleton.Position.x * 2.0f;
			this->camera.Position.y = -skeleton.Position.y - 0.5f;
			this->camera.Position.z = skeleton.Position.z * 2.0f;
		}

		if(skeleton.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_LEFT] == NUI_SKELETON_POSITION_TRACKED ||
			skeleton.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_LEFT] == NUI_SKELETON_POSITION_INFERRED)
		{
			this->leftHand.position.x = -skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].x * 2.0f;
			this->leftHand.position.y = skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].y;
			this->leftHand.position.z = -skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_LEFT].z * 2.0f;
			/*
			if(skeleton.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_LEFT] == NUI_SKELETON_POSITION_TRACKED)
			{
				this->leftHand.rotation.rotationAngle = acos(boneOrientations[NUI_SKELETON_POSITION_HAND_LEFT].absoluteRotation.rotationQuaternion.w) * 2;
				this->leftHand.rotation.axis.x = boneOrientations[NUI_SKELETON_POSITION_HAND_LEFT].absoluteRotation.rotationQuaternion.x / sin(this->leftHand.rotation.rotationAngle / 2);
				this->leftHand.rotation.axis.y = boneOrientations[NUI_SKELETON_POSITION_HAND_LEFT].absoluteRotation.rotationQuaternion.y / sin(this->leftHand.rotation.rotationAngle / 2);
				this->leftHand.rotation.axis.z = boneOrientations[NUI_SKELETON_POSITION_HAND_LEFT].absoluteRotation.rotationQuaternion.z / sin(this->leftHand.rotation.rotationAngle / 2);
				this->leftHand.rotation.rotationAngle = 180.0f / M_PI * this->leftHand.rotation.rotationAngle;
			}*/
		}
		if(skeleton.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_RIGHT] == NUI_SKELETON_POSITION_TRACKED ||
			skeleton.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_HAND_RIGHT] == NUI_SKELETON_POSITION_INFERRED)
		{
			this->rightHand.x = -skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].x * 2.0f;
			this->rightHand.y = skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].y;
			this->rightHand.z = -skeleton.SkeletonPositions[NUI_SKELETON_POSITION_HAND_RIGHT].z * 2.0f;
		}

		if(skeleton.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_FOOT_LEFT] == NUI_SKELETON_POSITION_TRACKED ||
			skeleton.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_FOOT_LEFT] == NUI_SKELETON_POSITION_INFERRED)
		{
			this->leftFoot.x = -skeleton.SkeletonPositions[NUI_SKELETON_POSITION_FOOT_LEFT].x * 2.0f;
			this->leftFoot.y = skeleton.SkeletonPositions[NUI_SKELETON_POSITION_FOOT_LEFT].y;
			this->leftFoot.z = -skeleton.SkeletonPositions[NUI_SKELETON_POSITION_FOOT_LEFT].z * 2.0f;
		}
		if(skeleton.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_FOOT_RIGHT] == NUI_SKELETON_POSITION_TRACKED ||
			skeleton.eSkeletonPositionTrackingState[NUI_SKELETON_POSITION_FOOT_RIGHT] == NUI_SKELETON_POSITION_INFERRED)
		{
			this->rightFoot.x = -skeleton.SkeletonPositions[NUI_SKELETON_POSITION_FOOT_RIGHT].x * 2.0f;
			this->rightFoot.y = skeleton.SkeletonPositions[NUI_SKELETON_POSITION_FOOT_RIGHT].y;
			this->rightFoot.z = -skeleton.SkeletonPositions[NUI_SKELETON_POSITION_FOOT_RIGHT].z * 2.0f;
		}
	}

	return true;
}

bool main_game::processWindow(HWND winHandle, UINT message, WPARAM windowParam, LPARAM messageParam)
{
	if(GetKeyState(VK_ESCAPE) & 0x8000)
	{
		exit(0);
	}
	if(GetKeyState(VK_LEFT) & 0x8000)
	{
		this->camera.Rotation.y -= 1.0f;
	}
	if(GetKeyState(VK_RIGHT) & 0x8000)
	{
		this->camera.Rotation.y += 1.0f;
	}
	short space = GetAsyncKeyState(VK_SPACE);
	if(space & 0x8000)
	{
		this->camera.Rotation.y += 180.0f;
	}
	if(GetKeyState(VK_UP) & 0x8000)
	{
		this->camera.Position.x += sin(M_PI / 180.0 * this->camera.Rotation.y);
		this->camera.Position.y += sin(M_PI / 180.0 * this->camera.Rotation.x);
		this->camera.Position.z -= cos(M_PI / 180.0 * this->camera.Rotation.y);

		//this->camera.Rotation.x -= sin(M_PI / 180.0 * this->camera.Rotation.y) * (1.0f / 2000.0f) * 360.0f;
		//this->camera.Rotation.z += cos(M_PI / 180.0 * this->camera.Rotation.y) * (1.0f / 4000.0f) *360.0f;
	}
	if(GetKeyState(VK_DOWN) & 0x8000)
	{
		this->camera.Position.x -= sin(M_PI / 180.0 * this->camera.Rotation.y);
		this->camera.Position.y -= sin(M_PI / 180.0 * this->camera.Rotation.x);
		this->camera.Position.z += cos(M_PI / 180.0 * this->camera.Rotation.y);

		//this->camera.Rotation.x += sin(M_PI / 180.0 * this->camera.Rotation.y) * (1.0f / 2000.0f) * 360.0f;
		//this->camera.Rotation.z -= cos(M_PI / 180.0 * this->camera.Rotation.y) * (1.0f / 4000.0f) *360.0f;
	}
	return true;
}