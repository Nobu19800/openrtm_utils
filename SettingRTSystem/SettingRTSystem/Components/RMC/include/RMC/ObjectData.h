#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include <vector>
#include <QtGui>
#include <QMainWindow>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QPen>

#include "RMC.h"

QT_BEGIN_NAMESPACE
class QFocusEvent;
class QGraphicsItem;
class QGraphicsScene;
class QPolygonF;
class QTimeLine;
class QAction;
class QActionGroup;
class QLabel;
class QMenu;
QT_END_NAMESPACE


enum ObjectType { BodyObj, JointObj, SensorObj, CameraObj};
enum GeomType { Body_Box, Body_Sphere, Body_Cylinder, Body_Cone, Body_Polygon };
enum JointType { Hinge, Slider, Fix};
enum SensorType { Force, Gyro, Range, Acceleration, Torque};
enum CameraType { Camera };
enum CameraDataType { COLOR, DEPTH, COLOR_DEPTH, NONE};	//カメラの取得する情報の種類
enum BTType { BTFree, BTFix};
enum SourceType{ Source_NONE, Source_COLOR, Source_POINT, Source_COORD, Source_DEF, Source_TYPE, Source_TRANS, Source_ROTATION, Source_CIT };
enum Control_Mode { InsertItem, InsertLine, InsertText, MoveItem, MoveLink, CreateLink, CreateSensor, CreateCamera};


class JointData;


class ItemDataBase
{
public:
	ItemDataBase();
	int obj_type;
	JointData *m_joint1;
	JointData *m_joint2;
};

class MeshData
{
public:
	MeshData();
	void setColor(float r, float g, float b);
	int num;
	float color[3];
	std::vector<float> point;
	std::vector<std::vector<int>> coordIndex;
	
};

class colorFlag
{
public:
	colorFlag(float r, float g, float b, QString name);
	float color[3];
	QString m_name;
};

class PolygonData
{
public:
	PolygonData();
	QString NAME;
	std::vector<colorFlag> colorList;
	std::vector<MeshData> Data;
	void loadFile(const QString &fileName, QWidget *parent);
	QStringList::iterator setDiffuseColor(QStringList::iterator f, MeshData *md, QString name);
	QStringList::iterator setCoordinate(QStringList::iterator f, MeshData *md);
	QStringList::iterator setPoint(QStringList::iterator f, MeshData *md);
	QStringList::iterator setCoordIndex(QStringList::iterator f, MeshData *md);
	QStringList::iterator setDEF(QStringList::iterator f, MeshData *md);
	QStringList::iterator setShape(QStringList::iterator f, MeshData *md);
	QStringList::iterator setColor(QStringList::iterator f, MeshData *md);
};

class ObjectParamBase
{
public:
	virtual void setPosition(double px, double py, double pz);
	int NUM;
	QString NAME;
	double m_px;
	double m_py;
	double m_pz;
};

class BodyParam : public ObjectParamBase
{
public:
	BodyParam();
	void setSize(double length, double width, double height);
	void setDirection(double slx, double sly, double slz);
	void setColor(double red, double green, double blue);
	double m_length;
	double m_width;
	double m_height;
	double m_slx;
	double m_sly;
	double m_slz;
	double m_mass;
	double m_red;
	double m_green;
	double m_blue;
	double m_axis;
	double m_rad;
	double I[9];
	int axis;
	PolygonData m_pd;
	int m_type;
	
};

class BodyData : public ItemDataBase
{
public:
	BodyData(BodyParam param);
	void remove(JointData *jd);
	bool tip;
	BodyParam m_param;
	int m_mode;
	float ROT[12];
};

class JointParam : public ObjectParamBase
{
public:
	JointParam();
	void setAxis(double axisx, double axisy, double axisz);
	void setULimit(double h, double l);
	void setUVLimit(double h, double l);
	double m_axisx;
	double m_axisy;
	double m_axisz;
	double ulimitH;
	double ulimitL;
	double uvlimitH;
	double uvlimitL;
	double rotorInertia;
	double rotorResistor;
	double torqueConst;
	double encoder;
	int JointType;
	int m_type;
	int m_mode;
};

class JointData : public ItemDataBase
{
public:
	JointData(BodyData *item1, BodyData *item2, JointParam param);
	void setBody(BodyData *item1, BodyData *item2);
	void remove(BodyData *item1);
	double angle;
	float ROT[12];
	BodyData *m_item1;
	BodyData *m_item2;
	JointParam m_param;
};

class SensorParam : public ObjectParamBase
{
public:
	SensorParam();
	void setSize(double length, double width, double height);
	void setDirection(double slx, double sly, double slz);
	double m_length;
	double m_width;
	double m_height;
	double m_slx;
	double m_sly;
	double m_slz;
	int m_type;
	int ID;
};
class SensorData : public ItemDataBase
{
public:
	SensorData(BodyData *body, SensorParam param);
	void delPort();
	void setType(int type);
	void update();
	BodyData *m_body;
	SensorParam m_param;
	SensorDataPort *m_port;
	std::vector<float> value;
};


class CameraParam : public ObjectParamBase
{
public:
	CameraParam();
	void setSize(double width, double height);
	void setDirection(double slx, double sly, double slz);
	double m_length;
	double m_width;
	double m_height;
	double m_slx;
	double m_sly;
	double m_slz;
	double fieldOfView;
	double frontClipDistance;
	double backClipDistance;
	int m_type;	//カメラの取得する情報の種類
	int ID;
};

class CameraData : public ItemDataBase
{
public:
	CameraData(JointData *joint, CameraParam param);
	//int JointNUM;
	CameraParam m_param;
};






#endif 