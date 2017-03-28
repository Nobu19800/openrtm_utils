#include <fstream>
#include "DrawThread.h"

//std::ofstream ofs( "test.txt" );

#ifdef dDOUBLE
#define dsDrawCapsule dsDrawCapsuleD
#define dsDrawBox     dsDrawBoxD
#define dsDrawLine    dsDrawLineD
#define dsDrawTriangle    dsDrawTriangleD
#endif

DrawThread *obj = NULL;


/**
*@brief �V�~�����[�V�����̕`�������X���b�h�̃R���X�g���N�^
*/
DrawThread::DrawThread(SimulatorObj *so)
{
	m_so = so;
	

	setDrawStuff();

	obj = this;
}

/**
*@brief �V�~�����[�V�������[�v
* @param pause ���g�p
*/
void simLoop(int pause)
{
	if(obj)
	{
		obj->drawRobot();
	}
}



/**
*@brief �V�~�����[�V����������
*/
void start()
{
  //float xyz[3] = {  .0f,  1.0f, 3.0f};  
  float xyz[3] = {  0.5f,  -0.0f, 0.25f}; 
  float hpr[3] = {180.0f, -10.0f, 0.0f};  
  //float hpr[3] = {0.0f, -90.0f, 90.0f}; 
  //float xyz[3] = {  5.0f,  -5.0f, 3.0f};
  //float hpr[3] = {180.0f, -10.0f, 0.0f};
  dsSetViewpoint(xyz,hpr);                
  dsSetSphereQuality(3);
  dsSetCapsuleQuality(6);


  
  
}

/**
*@brief �X���b�h���s�֐�
* @return
*/
int DrawThread::svc()
{
	int argc = 0;
	char *argv[] = {""};

	dsSimulationLoop(argc,argv,800,480,&fn);

	return 0;
}


/**
*@brief DrawStuff������
*/
void DrawThread::setDrawStuff()
{
	fn.version = DS_VERSION;
  fn.start   = &start;
  fn.step    = &simLoop;
  fn.command = NULL;
  fn.path_to_textures = "drawstuff/textures";
}

/**
*@brief �����̕`��
* @param body �{�f�B�I�u�W�F�N�g
*/
void DrawThread::drawBox(MyLink *body)
{
	const double sides[3] = {body->lx, body->ly, body->lz};
	dsSetColorAlpha(body->red,body->green,body->blue,1.0);
	dsDrawBoxD(dBodyGetPosition(body->body),
						dBodyGetRotation(body->body),sides);
}

/**
*@brief �~���`��
* @param body �{�f�B�I�u�W�F�N�g
*/
void DrawThread::drawCylinder(MyLink *body)
{
	dsSetColorAlpha(body->red,body->green,body->blue,1.0);
	dsDrawCylinderD(dBodyGetPosition(body->body),
						dBodyGetRotation(body->body),body->lz,body->lx);
}

/**
*@brief �S�{�f�B�`��
*/
void DrawThread::drawRobot()
{
	if(m_so->pause)
	{
		m_so->mu.lock();

		drawBox(&m_so->link0);
		drawBox(&m_so->link1);
		drawBox(&m_so->link2);
		drawBox(&m_so->link3);
	
		drawCylinder(&m_so->linkh);
	

		drawBox(&m_so->linkf[0]);
		drawBox(&m_so->linkf[1]);

		m_so->mu.unlock();
	}
}