
#ifndef GLBOX_H
#define GLBOX_H

#include <QtOpenGL>
#include <GL/gl.h>
#include <GL/glu.h>
#include "ObjectData.h"






/*3D描画*/

class GLBox : public QGLWidget
{
    Q_OBJECT

public:


    GLBox( QWidget* parent, const char* name = 0 );
    ~GLBox();

    
	void setBody(BodyData *bd, int num=-1);
	void setBodyParam(BodyParam *bp, int num = -1);
	void setJoint(JointData *jd, int num=-1);
	void setSensor(SensorData *sd, int num=-1);
	void setCamera(CameraData *cd, int num=-1);
	void clearBody();
	void clearJoint();
	void clearSensor();
	void clearCamera();
	void DrawPolygon(PolygonData P1, const float pos[3], const float R[12], bool SEL);
	float m_ANGLE[12];
	void moveBody(std::vector<float> ANGLE);
	std::vector<JointData*> getJoint(BodyData* bd);
	void setBodyPosition(JointData *jd);
	void calcJointRot(JointData *jd);
	std::vector<float> ANGLE;
	void timerEvent(QTimerEvent *);
	bool CHECK;
	int RotNum;
	int GeoNum;
	int SSNum;
	int CCNum;
	std::vector<BodyData*> m_Body;
	float BCL;
	int BorT;

public slots:

    void		setXRotation( int degrees );
    void		setYRotation( int degrees );
    void		setZRotation( int degrees );
	void        animate(qreal val);
	void        animFinished();
	void		setRotation(int rot);
	void		setJointScale(int rot);
	void		setSensorScale(int rot);
	void		setAccArrowScale(int rot);
	void		setGyroArrowScale(int rot);
	void		setForceArrowScale(int rot);
	void		setTorqueArrowScale(int rot);
	void		setRangeArrowScale(int rot);

protected:

    void		initializeGL();
    void		paintGL();
    void		resizeGL( int w, int h );


    virtual GLuint 	makeObject();
	void mouseMoveEvent(QMouseEvent *);
	void mousePressEvent(QMouseEvent *); 


private:

    GLuint object;
	QPoint anchor;
    double xRot, yRot, zRot, scale;
	double xWe, yWe;
	int bodynum;
	int jointnum;
	int sensornum;
	int cameranum;
	std::vector<JointData*> m_Joint;
	std::vector<SensorData*> m_Sensor;
	std::vector<CameraData*> m_Vision;
	
	float testANGLE[6];
	bool MoveFlag;
	QTimeLine *anim;
	float JScale;
	float SScale;
	float AScale;
	float GScale;
	float TScale;
	float RScale;
	float FScale;
	


};

#endif 
