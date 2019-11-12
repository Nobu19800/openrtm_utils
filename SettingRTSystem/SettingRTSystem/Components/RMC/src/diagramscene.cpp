#include <QtWidgets>
#include <QtGui>

#include <iostream>

#include "diagramscene.h"


DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
        tc = QTextCodec::codecForLocale();

	myMode = MoveItem;
	int i;
	DoubleFlag = true;
	templine = new QGraphicsLineItem();
	templine2 = NULL;
	camlin = NULL;
	senlin = NULL;
	tempItem = NULL;
	tempItem2 = NULL;
	myLineColor = Qt::black;
	createActions();
	addItem(templine);

	RotNum = 100;
	GeoNum = 100;
	SSNum = 100;

	
}


void DiagramScene::createActions()
{
    cutAct = new QAction(tc->toUnicode("Cu&t"),this);
    cutAct->setShortcuts(QKeySequence::Cut);
    cutAct->setStatusTip(tc->toUnicode("Cut the current selection's contents to the "
                            "clipboard"));
}

void DiagramScene::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction(cutAct);
    menu.exec(event->globalPos());
}



void DiagramScene::setMode(Control_Mode mode)
{
    myMode = mode;
	if(myMode != MoveItem)RotNum = 100;
	emit setRotNum();
}


void DiagramScene::dropEvent(QGraphicsSceneDragDropEvent *mouseEvent)
{    
	if (myMode == CreateSensor){

	}
}


int DiagramScene::ReturnItemCount()
{
	/*int TempNum = -1;
	for(int i=0;i<item_count;i++){
		if( textItem[i]->NUM > TempNum)TempNum =  textItem[i]->NUM;
	}
	return TempNum + 1;*/
	return 	textItem.size();		
}



JointData* DiagramScene::ReturnactParam(int num)
{
	
	if(num < actItem.size())
		return actItem[num]->ReturnParam();
	else
		return NULL;
}

SensorData* DiagramScene::ReturnsenParam(int num)
{
	if(num < senItem.size())
		return senItem[num]->ReturnParam();
	else
		return NULL;
}

CameraData* DiagramScene::ReturncamParam(int num)
{
	if(num < camItem.size())
		return camItem[num]->ReturnParam();
	else
		return NULL;
}



int DiagramScene::ReturnactCount()
{
	/*int TempNum = -1;
	for(int i=0;i<line_count;i++){
		if(actItem[i]->NUM > TempNum)TempNum = actItem[i]->NUM;
	}
	return TempNum + 1;*/
	return 	actItem.size();
}


int DiagramScene::ReturnsenCount()
{
	/*int TempNum = -1;
	for(int i=0;i<sen_count;i++){
		if(senItem[i]->NUM > TempNum)TempNum = senItem[i]->NUM;
	}
	return TempNum + 1;*/
	return 	senItem.size();	
}



int DiagramScene::ReturncamCount()
{
	/*int TempNum = -1;
	for(int i=0;i<cam_count;i++){
		if(camItem[i]->NUM > TempNum)TempNum = senItem[i]->NUM;
	}
	return TempNum + 1;*/
	return 	camItem.size();	
}






BodyData* DiagramScene::ReturnParam(int num)
{
	if(num < textItem.size())
		return textItem[num]->ReturnParam();
	else
		return NULL;
	
}

int DiagramScene::CHECK()
{
	updateJoint();
	bool ENDFLAG = true;
	int ITEM_CO = textItem.size();
	bool FLAG;

	int NUMBER = 0;
	while(ENDFLAG){
		FLAG = false;
		for(int i=0;i < textItem.size();i++){
			if(textItem[i]->m_param->m_param.NUM == NUMBER)
			{
				
				NUMBER += 1;
				FLAG = true;
				if(ITEM_CO == NUMBER)ENDFLAG = false;
				
			}
		}
		if(!FLAG){
			return 1;
		}
		

	}
	
	ENDFLAG = true;
	NUMBER = 0;

	int LINE_CO = actItem.size();
	/*for(int i=0;i < line_count;i++)
	{
		if(!actItem[i]->FLAG)LINE_CO -= 1;
	}*/

		
		
	if (actItem.size() > 0)
	{
		while (ENDFLAG){
			FLAG = false;

			for (int i = 0; i < actItem.size(); i++){
				if (actItem[i]->m_param->m_param.NUM == NUMBER)
				{

					NUMBER += 1;
					FLAG = true;
					if (LINE_CO == NUMBER)ENDFLAG = false;

				}
			}
			if (!FLAG){
				return 2;
			}


		}
	}

	return 0;

}



int DiagramScene::returnActNum(int i)
{
	if (actItem.size() > i)return actItem[i]->m_param->m_param.NUM;
	
	return 0;
}
int DiagramScene::returnBodyNum(int i)
{
	if (textItem.size() > i)return textItem[i]->m_param->m_param.NUM;
	return 0;
}
int DiagramScene::returnSenNum(int i)
{
	if (senItem.size() > i)return senItem[i]->m_param->m_param.NUM;
	return 0;
}
int DiagramScene::returnCamNum(int i)
{
	if (camItem.size() > i)return camItem[i]->m_param->m_param.NUM;
	return 0;
}


void DiagramScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

	QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
		BodyDialog dialog;
		ActDialog dialog2;
		SensorDialog dialog3;
		CameraDialog dialog4;
			foreach (QGraphicsItem *item2, selectedItems()) {
				if (item2->type() == BodyItem::Type) {
					for(int j=0;j<textItem.size();j++){
						if(item2->pos() == textItem[j]->pos()){


						dialog.SetParam(textItem[j]->ReturnParam()->m_param);

						BType = dialog.BT;
						
							dialog.exec();
							if(dialog.ReturnFLAG()){
								BodyParam bp = dialog.returnParam();
								textItem[j]->setParam(bp);

								if(textItem[j]->m_param->m_param.NUM == 0)textItem[j]->SetTip(true);
								

								
								}
								/*int body1=0;
								int body2=0;
								int ANUM;
								bool AFRAG = false;
								for(int g=0;g<line_count;g++){
									if(lin1[g]->pos() == textItem[j]->pos()){
										if(j != actItem[g]->returnNUM1()){

										body1 = j;
										body2 = actItem[g]->returnNUM1();}
										ANUM = g;
										AFRAG = true;
									}
									if(lin2[g]->pos() == textItem[j]->pos()){
										if(j != actItem[g]->returnNUM1()){


										body1 = actItem[g]->returnNUM1();
										body2 = j;

										}
										ANUM = g;
										AFRAG = true;
									}
								}
								if(AFRAG){
									if(body2 != 0)
										textItem[body2]->SetTip(false);
									if(body1 != 0)
										textItem[body1]->SetTip(false);

									int FH = 0;
									
									for(int s=0;s<line_count;s++)
									{

										if(ANUM != s){
											if(body2 == actItem[s]->returnNUM2())
											{
												int temp;
												textItem[body2]->SetTip(true);
												temp = body1;
												body1 = body2;
												body2 = temp;
												QGraphicsItem *TEMPLIN;
												TEMPLIN = lin2[ANUM];
												lin2[ANUM] = lin1[ANUM];
												lin1[ANUM] = TEMPLIN;
											}
											else if(body1 == actItem[s]->returnNUM2())
											{
												textItem[body1]->SetTip(true);
											}
											if(body2 == actItem[s]->returnNUM1())
											{
												if(FH == 1)
												{
													textItem[body1]->SetTip(true);
													textItem[body2]->SetTip(true);

												}
												FH = 1;
												
											}
											if(body1 == actItem[s]->returnNUM2())
											{
												if(FH == 1)
												{
													textItem[body1]->SetTip(true);
													textItem[body2]->SetTip(true);

												}
												FH = 1;
											}
										}





									}
									if(body2 == 0)
									{
										int temp;
										temp = body1;
										body1 = body2;
										body2 = temp;
										QGraphicsItem *TEMPLIN;
										TEMPLIN = lin2[ANUM];
										lin2[ANUM] = lin1[ANUM];
										lin1[ANUM] = TEMPLIN;
									}
							



									actItem[ANUM]->setBody(body1, body2);
									emit actInserted(actItem[ANUM]);
									
								}*/
							}


									
						}
				}

	
			
				if (item2->type() == JointItem::Type) {
							for(int j=0;j<actItem.size();j++){
								if(item2->pos() == actItem[j]->pos()){
									
									dialog2.SetParam(actItem[j]->ReturnParam()->m_param);
									dialog2.exec();
									if(dialog2.ReturnFLAG()){
								JointParam jp = dialog2.returnParam();
								actItem[j]->setParam(jp);


									}
									}
						}

	
				}
				if (item2->type() == SensorItem::Type) {
							for(int j=0;j<senItem.size();j++){
								if(item2->pos() == senItem[j]->pos()){
									dialog3.SetParam(senItem[j]->ReturnParam()->m_param);
									dialog3.exec();
									if(dialog3.ReturnFLAG()){
										SensorParam sp = dialog3.returnParam();
										senItem[j]->setParam(sp) ;


									}
									}
						}

	
				}
				if (item2->type() == CameraItem::Type) {
							for(int j=0;j<camItem.size();j++){
								if(item2->pos() == camItem[j]->pos()){
									




									dialog4.SetParam(camItem[j]->ReturnParam()->m_param);
									dialog4.exec();
									if(dialog4.ReturnFLAG()){
										CameraParam cp = dialog4.returnParam();
										camItem[j]->setParam(cp) ;


									}
									}
						}

	
				}
							
							
							

		}

							

						
						
							
			
	emit renew();
}

double *DiagramScene::dot3X3(double *T1, double *T2)
{
	double *T3 = new double[12];
	T3[0] = T1[0]*T2[0]+T1[1]*T2[4]+T1[2]*T2[8];
	T3[1] = T1[0]*T2[1]+T1[1]*T2[5]+T1[2]*T2[9];
	T3[2] = T1[0]*T2[2]+T1[1]*T2[6]+T1[2]*T2[10];
	T3[3] = T1[0]*T2[3]+T1[1]*T2[7]+T1[2]*T2[11]+T1[3];
	T3[4] = T1[4]*T2[0]+T1[5]*T2[4]+T1[6]*T2[8];
	T3[5] = T1[4]*T2[1]+T1[5]*T2[5]+T1[6]*T2[9];
	T3[6] = T1[4]*T2[2]+T1[5]*T2[6]+T1[6]*T2[10];
	T3[7] = T1[4]*T2[3]+T1[5]*T2[7]+T1[6]*T2[11]+T1[7];
	T3[8] = T1[8]*T2[0]+T1[9]*T2[4]+T1[10]*T2[8];
	T3[9] = T1[8]*T2[1]+T1[9]*T2[5]+T1[10]*T2[9];
	T3[10] = T1[8]*T2[2]+T1[9]*T2[6]+T1[10]*T2[10];
	T3[11] = T1[8]*T2[3]+T1[9]*T2[7]+T1[10]*T2[11]+T1[11];


	return T3;
}






double *DiagramScene::Silde(double x, double y, double z, double *T1)
{
	double *T3 = new double[12];
	for(int i=0;i<12;i++)T3[i] = T1[i];
	T3[3] += x;
	T3[7] += y;
	T3[11] += z;



	return T3;
}

double *DiagramScene::RotX(double rad, double *T1)
{
	double T2[12] = {1.0, 0.0, 0.0, 0.0, 
					0.0, cos(rad), -sin(rad), 0.0,
					0.0, sin(rad), cos(rad), 0.0};
	double *T3;

	T3 = dot3X3(T2, T1);

	return T3;
}

double *DiagramScene::RotY(double rad, double *T1)
{
	double T2[12] = {cos(rad), 0.0, sin(rad), 0.0,
					0.0, 1.0, 0.0, 0.0,
					-sin(rad), 0.0, cos(rad), 0.0};
	double *T3;

	T3 = dot3X3(T2, T1);

	return T3;
}

double *DiagramScene::RotZ(double rad, double *T1)
{
	double T2[12] = {cos(rad), -sin(rad), 0.0, 0.0,
					sin(rad), cos(rad), 0.0, 0.0,
					0.0, 0.0, 1.0, 0.0};
	double *T3;

	T3 = dot3X3(T2, T1);

	return T3;
}



double *DiagramScene::RotTSL(double roll, double pitch, double yaw, double x, double y, double z, double *R)
{
	double RKK[12];
	double RKKK[12];
	double RKKKK[12];
	double *R2;
	double *R3;
	double *R4;
	double *R5;
	R2 = Silde(x,y,z,R);
	for(int i=0;i<12;i++)RKK[i] = R2[i];
	R3 = RotX(roll, RKK);
	for(int i=0;i<12;i++)RKKK[i] = R3[i];
	R4 = RotY(pitch, RKKK);
	for(int i=0;i<12;i++)RKKKK[i] = R4[i];
	R5 = RotZ(yaw, RKKKK);

	return R5;

}

void DiagramScene::loadFile(const QString &fileName, PolygonData *P1, double Tr[3], double Ro[3])
{
	

}


void DiagramScene::savePolygon(const QString &fileName, BodyData *bd)
{

	QStringList TXX3;
	TXX3 = fileName.split("/");
	QString fileName2 = "";

	for (int k = 0; k < TXX3.size() - 1; k++){

		if (TXX3[k] != ""){
			fileName2 += TXX3[k] + "/";
		}
	}
	fileName2 += bd->m_param.NAME;
	fileName2 += ".wrl";
	QFile file(fileName2);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {

	}

	QTextStream out(&file);

	out << "#VRML V2.0 utf8" << "\n";
	out << "Transform {" << "\n";
	out << "  children	[" << "\n";

	for (int i = 0; i < bd->m_param.m_pd.Data.size(); i++)
	{
		if (i == 0)
		{
			out << "    DEF " << bd->m_param.NAME << " Transform {" << "\n";
			out << "        children  [" << "\n";
			out << "    Shape {" << "\n";
		}
		else {
			out << " Transform {" << "\n";
			out << "      children	Shape {" << "\n";
		}



		out << "      appearance	Appearance {" << "\n";
		out << "	material	Material {" << "\n";
		out << "	  diffuseColor	" << bd->m_param.m_pd.Data[i].color[0] << " " << bd->m_param.m_pd.Data[i].color[1] << " " << bd->m_param.m_pd.Data[i].color[2] << " " << "\n";
		out << "	}" << "\n";
		out << "  }" << "\n";
		out << "geometry	DEF _" << i << " IndexedFaceSet {" << "\n";
		out << "            coord	Coordinate {" << "\n";
		out << "              point	[ " << "\n";
		for (int j = 0; j < bd->m_param.m_pd.Data[i].point.size(); j++)
		{
			out << bd->m_param.m_pd.Data[i].point[j] << " " << "\n";
			if ((j % 3) == 2)out << "\n";
		}
		out << "      ]" << "\n";
		out << "   }" << "\n";
		out << "            coordIndex	[ " << "\n";
		for (int j = 0; j < bd->m_param.m_pd.Data[i].coordIndex.size(); j++)
		{
			for (int k = 0; k < bd->m_param.m_pd.Data[i].coordIndex[j].size(); k++)
			{
				out << bd->m_param.m_pd.Data[i].coordIndex[j][k] << " ";
			}
			out << ",";
			out << "\n";
			//if((j % 3) == 2)out << "\n";
		}
		out << "     ]" << "\n";
		out << "    	    normalPerVertex	FALSE" << "\n";
		out << "    	    normalIndex	[  ]" << "\n";
		out << "    	    texCoordIndex	[  ]" << "\n";
		out << "     }" << "\n";
		out << "   }" << "\n";
		if (i == 0)
		{
			out << "]" << "\n";
			out << "      translation	0 0 0" << "\n";
			out << "      rotation	1 0 0 0" << "\n";
			out << "}" << "\n";
		}
		else
		{
			out << "}" << "\n";
		}


	}
	out << "]" << "\n";
	out << "}" << "\n";

}


void DiagramScene::writeJointData(const QString &fileName, QTextStream &out, JointData *jd, float *trans)
{
	out << "DEF " << jd->m_param.NAME << " Joint {" << "\n";
	if (jd->m_param.m_type == Hinge)out << "jointType \"rotate\"" << "\n";
	if (jd->m_param.m_type == Slider)out << "jointType \"slide\"" << "\n";
	if (jd->m_param.m_type == Fix)out << "jointType \"fixed\"" << "\n";
	out << "jointAxis " << jd->m_param.m_axisx << " " << jd->m_param.m_axisy << " " << jd->m_param.m_axisz << "\n";
	out << "translation " << jd->m_param.m_px - trans[0] << " " << jd->m_param.m_py - trans[1] << " " << jd->m_param.m_pz - trans[2] << "\n";
	trans[0] += jd->m_param.m_px - trans[0];
	trans[1] += jd->m_param.m_py - trans[1];
	trans[2] += jd->m_param.m_pz - trans[2];
	out << "rotation 0 0 1 0" << "\n";
	out << "jointId " << jd->m_param.NUM << "\n";
	out << "ulimit " << jd->m_param.ulimitH << "\n";
	out << "llimit " << jd->m_param.ulimitL << "\n";
	out << "lvlimit " << jd->m_param.uvlimitH << "\n";
	out << "uvlimit " << jd->m_param.uvlimitL << "\n";
	out << "rotorInertia " << jd->m_param.rotorInertia << "\n";
	out << "rotorResistor " << jd->m_param.rotorResistor << "\n";
	out << "torqueConst " << jd->m_param.torqueConst << "\n";
	out << "encoderPulse " << jd->m_param.encoder << "\n";

	out << "children [" << "\n";

	for (int j = 0; j < senItem.size(); j++)
	{
		senItem[j]->ReturnParam();
		if (senItem[j]->m_param->m_body == jd->m_item2)
		{
			out << "Transform {" << "\n";



			if (senItem[j]->m_param->m_param.m_slz == 0.0 && senItem[j]->m_param->m_param.m_slx == 0.0)
			{
				out << "children [" << "\n";

				out << "Transform {" << "\n";
				out << "      rotation 0 1 0 " << -1.57 << "\n";
				out << "children [" << "\n";
			}
			else if (senItem[j]->m_param->m_param.m_slz == 0.0 && senItem[j]->m_param->m_param.m_sly == 0.0)
			{
				out << "children [" << "\n";
				out << "Transform {" << "\n";
				out << "      rotation 1 0 0 " << -1.57 << "\n";
				out << "children [" << "\n";
			}
			else if (senItem[j]->m_param->m_param.m_slx == 0.0 && senItem[j]->m_param->m_param.m_sly == 0.0){
				out << "children [" << "\n";
				out << "Transform {" << "\n";
				out << "children [" << "\n";
			}
			else if (senItem[j]->m_param->m_param.m_slx != 0.0){
				float TEMPX = senItem[j]->m_param->m_param.m_slx;
				float TEMPY = senItem[j]->m_param->m_param.m_sly;
				float TEMPZ = senItem[j]->m_param->m_param.m_slz;
				float TEMPXY = sqrt(TEMPZ * TEMPZ + TEMPY * TEMPY);
				float TEMPRZ = atan2(TEMPY, TEMPZ);
				float TEMPRY = atan2(-TEMPX, TEMPXY);
				out << "      rotation 0 1 0 " << TEMPRY << "\n";
				out << "children [" << "\n";
				out << "Transform {" << "\n";
				out << "      rotation 1 0 0 " << TEMPRZ << "\n";
				out << "children [" << "\n";


			}
			if (senItem[j]->m_param->m_param.m_type == Force)out << "DEF " << senItem[j]->m_param->m_param.NAME << " ForceSensor {" << "\n";
			if (senItem[j]->m_param->m_param.m_type == Gyro)out << "DEF " << senItem[j]->m_param->m_param.NAME << " Gyro {" << "\n";
			if (senItem[j]->m_param->m_param.m_type == Range)out << "DEF " << senItem[j]->m_param->m_param.NAME << " RangeSensor {" << "\n";
			if (senItem[j]->m_param->m_param.m_type == Acceleration)out << "DEF " << senItem[j]->m_param->m_param.NAME << " AccelerationSensor {" << "\n";
			if (senItem[j]->m_param->m_param.m_type == Torque)out << "DEF " << senItem[j]->m_param->m_param.NAME << " ForceSensor {" << "\n";

			out << "      translation " << senItem[j]->m_param->m_param.m_px - trans[0] << " " << senItem[j]->m_param->m_param.m_py - trans[1] << " " << senItem[j]->m_param->m_param.m_pz - trans[2] << "\n";
			out << "sensorId " << senItem[j]->ReturnID() << "\n";

			out << "}" << "\n";
			out << "]" << "\n";
			out << "}" << "\n";
			out << "]" << "\n";
			out << "}" << "\n";


		}
	}
	BodyData *bd = jd->m_item2;
	out << "        DEF " << bd->m_param.NAME << " Segment {" << "\n";

	out << "	  mass " << bd->m_param.m_mass << "\n";
	out << "          centerOfMass 0 0 0" << "\n";
	out << "	  momentsOfInertia [";
	for (int j = 0; j < 9; j++)out << " " << bd->m_param.I[j];
	out << " ]" << "\n";
	out << "          children [" << "\n";

	out << "Transform {" << "\n";



	out << "      translation " << bd->m_param.m_px - trans[0] << " " << bd->m_param.m_py - trans[1] << " " << bd->m_param.m_pz - trans[2] << "\n";
	out << "      rotation 1 0 0 " << bd->m_param.m_slx << "\n";
	out << "          children [" << "\n";
	out << "Transform {" << "\n";

	out << "      rotation 0 1 0 " << bd->m_param.m_sly << "\n";
	out << "          children [" << "\n";
	out << "Transform {" << "\n";
	out << "      rotation 0 0 1 " << bd->m_param.m_slz << "\n";
	out << "          children [" << "\n";
	if (bd->m_param.m_type == Body_Box){
		out << "Shape {" << "\n";
		out << "appearance Appearance {" << "\n";
		out << "                material Material {" << "\n";
		out << "                diffuseColor  " << bd->m_param.m_red << " " << bd->m_param.m_green << " " << bd->m_param.m_blue << " " << "\n";
		out << "}" << "\n";
		out << "}" << "\n";
		out << "    geometry Box {" << "\n";
		out << "        size " << bd->m_param.m_length - trans[0] << " " << bd->m_param.m_width - trans[0] << " " << bd->m_param.m_height - trans[0] << "\n";
		out << "    }" << "\n";

		out << "    }" << "\n";

	}
	if (bd->m_param.m_type == Body_Sphere){
		out << "Shape {" << "\n";
		out << "appearance Appearance {" << "\n";
		out << "                material Material {" << "\n";
		out << "                diffuseColor  " << bd->m_param.m_red << " " << bd->m_param.m_green << " " << bd->m_param.m_blue << " " << "\n";
		out << "}" << "\n";
		out << "}" << "\n";
		out << "    geometry Sphere {" << "\n";
		out << "    radius " << bd->m_param.m_rad << "\n";
		out << "    }" << "\n";
		out << "    }" << "\n";
	}
	if (bd->m_param.m_type == Body_Cone){

		out << "Shape {" << "\n";
		out << "appearance Appearance {" << "\n";
		out << "                material Material {" << "\n";
		out << "                diffuseColor  " << bd->m_param.m_red << " " << bd->m_param.m_green << " " << bd->m_param.m_blue << " " << "\n";
		out << "}" << "\n";
		out << "}" << "\n";
		out << "    geometry Cone {" << "\n";
		out << "    bottomRadius " << bd->m_param.m_rad << "\n";
		out << "    height " << bd->m_param.m_length << "\n";
		out << "    }" << "\n";
		out << "    }" << "\n";
	}
	if (bd->m_param.m_type == Body_Cylinder){
		out << "Shape {" << "\n";
		out << "appearance Appearance {" << "\n";
		out << "                material Material {" << "\n";
		out << "                diffuseColor  " << bd->m_param.m_red << " " << bd->m_param.m_green << " " << bd->m_param.m_blue << " " << "\n";
		out << "}" << "\n";
		out << "}" << "\n";
		out << "    geometry Cylinder {" << "\n";
		out << "    radius " << bd->m_param.m_rad << "\n";
		out << "    height " << bd->m_param.m_length << "\n";
		out << "    }" << "\n";
		out << "    }" << "\n";
	}
	if (bd->m_param.m_type == Body_Polygon){
		savePolygon(fileName, bd);
		out << "Inline {" << "\n";
		out << "url " << "\"" << bd->m_param.NAME << ".wrl\"" << "\n";
		out << "    }" << "\n";
	}
	out << "]" << "\n";
	out << "}" << "\n";
	out << "]" << "\n";
	out << "}" << "\n";
	out << "]" << "\n";
	out << "}" << "\n";
	out << "]" << "\n";

	out << "}" << "\n";
	for (int j = 0; j < camItem.size(); j++)
	{
		{
			CameraData *cd = camItem[j]->m_param;
			if (cd->m_joint1 == jd)
			{
				out << "Transform {" << "\n";
				out << "translation  " << cd->m_param.m_px - trans[0] << " " << cd->m_param.m_py - trans[1] << " " << cd->m_param.m_pz - trans[2] << "\n";

				if (cd->m_param.m_slz == 0.0 && cd->m_param.m_sly == 0.0)
				{
					out << "      rotation 0 1 0 " << -1.57 << "\n";
					out << "children [" << "\n";
					out << "Transform {" << "\n";
					out << "children [" << "\n";
				}


				else if (cd->m_param.m_slz == 0.0 && cd->m_param.m_slx == 0.0)
				{
					out << "      rotation 1 0 0 " << -1.57 << "\n";
					out << "children [" << "\n";
					out << "Transform {" << "\n";
					out << "children [" << "\n";
				}
				else if (cd->m_param.m_slx == 0.0 && cd->m_param.m_sly == 0.0)
				{
					out << "children [" << "\n";
					out << "Transform {" << "\n";
					out << "children [" << "\n";
				}
				else if (cd->m_param.m_slx != 0.0){
					float TEMPX = cd->m_param.m_slx;
					float TEMPY = cd->m_param.m_sly;
					float TEMPZ = cd->m_param.m_slz;
					float TEMPXY = sqrt(TEMPZ * TEMPZ + TEMPY * TEMPY);
					float TEMPRZ = atan2(TEMPY, TEMPZ);
					float TEMPRY = atan2(-TEMPX, TEMPXY);
					out << "      rotation 1 0 0 " << TEMPRZ << "\n";
					out << "children [" << "\n";
					out << "Transform {" << "\n";
					out << "      rotation 0 1 0 " << TEMPRY << "\n";
					out << "children [" << "\n";

				}
				out << "DEF " << cd->m_param.NAME << " VisionSensor {" << "\n";

				out << "sensorId " << cd->m_param.ID << "\n";
				if (cd->m_param.m_type == COLOR)
					out << "type \"COLOR\"" << "\n";
				if (cd->m_param.m_type == DEPTH)
					out << "type \"DEPTH\"" << "\n";
				if (cd->m_param.m_type == COLOR_DEPTH)
					out << "type \"COLOR_DEPTH\"" << "\n";
				if (cd->m_param.m_type == NONE)
					out << "type \"NONE\"" << "\n";

				out << "fieldOfView " << cd->m_param.fieldOfView << "\n";
				out << "frontClipDistance " << cd->m_param.frontClipDistance << "\n";
				out << "backClipDistance " << cd->m_param.backClipDistance << "\n";


				out << "height " << (int)cd->m_param.m_height << "\n";
				out << "width " << (int)cd->m_param.m_length << "\n";

				out << "children [ " << "\n";
				out << "DEF CAMERA_SHAPE Transform { " << "\n";
				out << "children [ " << "\n";
				out << "Shape {" << "\n";
				out << "geometry Cylinder { " << "\n";
				out << "radius      0.02 " << "\n";
				out << " height      0.025" << "\n";
				out << "}" << "\n";
				out << "appearance Appearance {" << "\n";
				out << "material Material {" << "\n";
				out << "diffuseColor      1 0 0 " << "\n";
				out << "}" << "\n";
				out << "}" << "\n";
				out << "}" << "\n";
				out << "]" << "\n";
				out << "}" << "\n";
				out << "]" << "\n";
				out << "}" << "\n";
				out << "]" << "\n";





				out << "} " << "\n";
				out << "] " << "\n";
				out << "} " << "\n";






			}
		}
	}
	JointItem *ji = NULL;
	for (int i = 0; i < actItem.size(); i++)
	{
		if (actItem[i]->m_param->m_item1 == jd->m_item2)
		{
			ji = actItem[i];
		}
	}
	if (ji)
	{
		writeJointData(fileName, out, ji->m_param, trans);
	}
	out << "]" << "\n";
	out << "}" << "\n";
}

int DiagramScene::SaveFile(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly)) {

		return 2;
	}
	QDataStream out(&file);	out << (int)textItem.size();	for (std::vector<BodyItem*>::iterator it = textItem.begin(); it != textItem.end(); ++it)	{		out << (*it)->m_param->m_param.NAME;		out << (*it)->m_param->m_param.NUM;		out << (*it)->m_param->m_param.m_px;		out << (*it)->m_param->m_param.m_py;		out << (*it)->m_param->m_param.m_pz;		out << (*it)->m_param->m_param.m_length;		out << (*it)->m_param->m_param.m_width;		out << (*it)->m_param->m_param.m_height;		out << (*it)->m_param->m_param.m_slx;		out << (*it)->m_param->m_param.m_sly;		out << (*it)->m_param->m_param.m_slz;		out << (*it)->m_param->m_param.m_mass;		out << (*it)->m_param->m_param.m_red;		out << (*it)->m_param->m_param.m_green;		out << (*it)->m_param->m_param.m_blue;		out << (*it)->m_param->m_param.m_rad;		out << (*it)->m_param->m_param.axis;		out << (*it)->m_param->m_param.m_pd.NAME;		out << (*it)->m_param->m_param.m_type;		out << (float)(*it)->pos().x();		out << (float)(*it)->pos().y();	}		out << (int)actItem.size();	for (std::vector<JointItem*>::iterator it = actItem.begin(); it != actItem.end(); ++it)	{
		out << (*it)->m_param->m_param.NAME;		out << (*it)->m_param->m_param.NUM;		out << (*it)->m_param->m_param.m_px;		out << (*it)->m_param->m_param.m_py;		out << (*it)->m_param->m_param.m_pz;		out << (*it)->m_param->m_param.m_axisx;		out << (*it)->m_param->m_param.m_axisy;		out << (*it)->m_param->m_param.m_axisz;		out << (*it)->m_param->m_param.ulimitH;		out << (*it)->m_param->m_param.ulimitL;		out << (*it)->m_param->m_param.uvlimitH;		out << (*it)->m_param->m_param.uvlimitL;		out << (*it)->m_param->m_param.rotorInertia;		out << (*it)->m_param->m_param.rotorResistor;		out << (*it)->m_param->m_param.torqueConst;		out << (*it)->m_param->m_param.encoder;		out << (*it)->m_param->m_param.m_type;
		out << (*it)->m_param->m_item1->m_param.NUM;
		out << (*it)->m_param->m_item2->m_param.NUM;
	}

	out << (int)senItem.size();	for (std::vector<SensorItem*>::iterator it = senItem.begin(); it != senItem.end(); ++it)	{
		out << (*it)->m_param->m_param.NAME;		out << (*it)->m_param->m_param.NUM;		out << (*it)->m_param->m_param.m_px;		out << (*it)->m_param->m_param.m_py;		out << (*it)->m_param->m_param.m_pz;		out << (*it)->m_param->m_param.m_slx;		out << (*it)->m_param->m_param.m_sly;		out << (*it)->m_param->m_param.m_slz;		out << (*it)->m_param->m_param.m_type;
		out << (*it)->m_param->m_body->m_param.NUM;
		out << (float)(*it)->pos().x();		out << (float)(*it)->pos().y();
	}

	out << (int)camItem.size();	for (std::vector<CameraItem*>::iterator it = camItem.begin(); it != camItem.end(); ++it)	{
		out << (*it)->m_param->m_param.NAME;		out << (*it)->m_param->m_param.NUM;		out << (*it)->m_param->m_param.m_px;		out << (*it)->m_param->m_param.m_py;		out << (*it)->m_param->m_param.m_pz;		out << (*it)->m_param->m_param.m_width;		out << (*it)->m_param->m_param.m_height;		out << (*it)->m_param->m_param.m_slx;		out << (*it)->m_param->m_param.m_sly;		out << (*it)->m_param->m_param.m_slz;		out << (*it)->m_param->m_param.fieldOfView;		out << (*it)->m_param->m_param.frontClipDistance;		out << (*it)->m_param->m_param.backClipDistance;		out << (*it)->m_param->m_param.m_type;		out << (*it)->m_param->m_param.ID;
		out << (*it)->m_param->m_joint1->m_param.NUM;
		out << (float)(*it)->pos().x();		out << (float)(*it)->pos().y();
	}

	file.close();

	return 0;
}

int DiagramScene::SaveFileVRML(const QString &fileName)
{

	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {

		return 2;
	}

	QTextStream out(&file);
	//QApplication::setOverrideCursor(Qt::WaitCursor);
	out << "#VRML V2.0 utf8" << "\n";
	out << "PROTO Joint [" << "\n";
	out << "  exposedField     SFVec3f      center              0 0 0" << "\n";
	out << "  exposedField     MFNode       children            []" << "\n";
	out << "  exposedField     MFFloat      llimit              []" << "\n";
	out << "  exposedField     MFFloat      lvlimit             []" << "\n";
	out << "  exposedField     SFRotation   limitOrientation    0 0 1 0" << "\n";
	out << "  exposedField     SFString     name                \"\"" << "\n";
	out << "  exposedField     SFRotation   rotation            0 0 1 0" << "\n";
	out << "  exposedField     SFVec3f      scale               1 1 1" << "\n";
	out << "  exposedField     SFRotation   scaleOrientation    0 0 1 0" << "\n";
	out << "  exposedField     MFFloat      stiffness           [ 0 0 0 ]" << "\n";
	out << "  exposedField     SFVec3f      translation         0 0 0" << "\n";
	out << "  exposedField     MFFloat      ulimit              []" << "\n";
	out << "  exposedField     MFFloat      uvlimit             []" << "\n";
	out << "  exposedField     SFString     jointType           \"\"" << "\n";
	out << "  exposedField     SFInt32      jointId             -1" << "\n";
	out << "  exposedField     SFVec3f      jointAxis           0 0 1" << "\n";
	out << "  exposedField     SFFloat      gearRatio           1" << "\n";
	out << "  exposedField     SFFloat      rotorInertia        0" << "\n";
	out << "  exposedField     SFFloat      rotorResistor       0" << "\n";
	out << "  exposedField     SFFloat      torqueConst         1" << "\n";
	out << "  exposedField     SFFloat      encoderPulse        1" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform {" << "\n";
	out << "    center           IS center" << "\n";
	out << "    children         IS children" << "\n";
	out << "    rotation         IS rotation" << "\n";
	out << "    scale            IS scale" << "\n";
	out << "    scaleOrientation IS scaleOrientation" << "\n";
	out << "    translation      IS translation" << "\n";
	out << "  }" << "\n";
	out << "}" << "\n";
	out << "PROTO Segment [" << "\n";
	out << "    field           SFVec3f     bboxCenter        0 0 0" << "\n";
	out << "    field           SFVec3f     bboxSize          -1 -1 -1" << "\n";
	out << "    exposedField    SFVec3f     centerOfMass      0 0 0" << "\n";
	out << "    exposedField    MFNode      children          [ ]" << "\n";
	out << "    exposedField    SFNode      coord             NULL" << "\n";
	out << "    exposedField    MFNode      displacers        [ ]" << "\n";
	out << "    exposedField    SFFloat     mass              0" << "\n";
	out << "    exposedField    MFFloat     momentsOfInertia  [ 0 0 0 0 0 0 0 0 0 ]" << "\n";
	out << "    exposedField    SFString    name              \"\"" << "\n";
	out << "    eventIn         MFNode      addChildren" << "\n";
	out << "    eventIn         MFNode      removeChildren" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "    Group {" << "\n";
	out << "        addChildren    IS addChildren" << "\n";
	out << "        bboxCenter     IS bboxCenter" << "\n";
	out << "        bboxSize       IS bboxSize" << "\n";
	out << "        children       IS children" << "\n";
	out << "        removeChildren IS removeChildren" << "\n";
	out << "    }" << "\n";
	out << "}" << "\n";
	out << "PROTO Humanoid [" << "\n";
	out << "    field           SFVec3f    bboxCenter            0 0 0" << "\n";
	out << "    field           SFVec3f    bboxSize              -1 -1 -1" << "\n";
	out << "    exposedField    SFVec3f    center                0 0 0" << "\n";
	out << "    exposedField    MFNode     humanoidBody          [ ]" << "\n";
	out << "    exposedField    MFString   info                  [ ]" << "\n";
	out << "    exposedField    MFNode     joints                [ ]" << "\n";
	out << "    exposedField    SFString   name                  \"\"" << "\n";
	out << "    exposedField    SFRotation rotation              0 0 1 0" << "\n";
	out << "    exposedField    SFVec3f    scale                 1 1 1" << "\n";
	out << "    exposedField    SFRotation scaleOrientation      0 0 1 0" << "\n";
	out << "    exposedField    MFNode     segments              [ ]" << "\n";
	out << "    exposedField    MFNode     sites                 [ ]" << "\n";
	out << "    exposedField    SFVec3f    translation           0 0 0" << "\n";
	out << "    exposedField    SFString   version               \"1.1\"" << "\n";
	out << "    exposedField    MFNode     viewpoints            [ ]" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform {" << "\n";
	out << "    bboxCenter       IS bboxCenter" << "\n";
	out << "    bboxSize         IS bboxSize" << "\n";
	out << "    center           IS center" << "\n";
	out << "    rotation         IS rotation" << "\n";
	out << "    scale            IS scale" << "\n";
	out << "    scaleOrientation IS scaleOrientation" << "\n";
	out << "    translation      IS translation" << "\n";
	out << "    children [" << "\n";
	out << "      Group {" << "\n";
	out << "        children IS viewpoints" << "\n";
	out << "        children IS viewpoints" << "\n";
	out << "      }" << "\n";
	out << "      Group {" << "\n";
	out << "        children IS humanoidBody" << "\n";
	out << "      }" << "\n";
	out << "    ]" << "\n";
	out << "  }" << "\n";
	out << "}" << "\n";

	out << "PROTO VisionSensor [" << "\n";
	out << "  exposedField SFVec3f    translation       0 0 0" << "\n";
	out << "  exposedField SFRotation rotation          0 0 1 0" << "\n";
	out << "  exposedField MFNode     children          [ ]" << "\n";
	out << "  exposedField SFFloat    fieldOfView       0.785398" << "\n";
	out << "  exposedField SFString   name              \"\"" << "\n";
	out << "  exposedField SFFloat    frontClipDistance 0.01" << "\n";
	out << "  exposedField SFFloat    backClipDistance  10.0" << "\n";
	out << "  exposedField SFString   type              \"NONE\"" << "\n";
	out << "  exposedField SFInt32    sensorId          -1" << "\n";
	out << "  exposedField SFInt32    width             320" << "\n";
	out << "  exposedField SFInt32    height            240" << "\n";
	out << "  exposedField SFFloat    frameRate         30" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform {" << "\n";
	out << "    rotation         IS rotation" << "\n";
	out << "    translation      IS translation" << "\n";
	out << "    children         IS children" << "\n";
	out << "  }" << "\n";
	out << "}" << "\n";
	out << "PROTO ForceSensor [ " << "\n";
	out << "  exposedField SFVec3f    maxForce    -1 -1 -1" << "\n";
	out << "  exposedField SFVec3f    maxTorque   -1 -1 -1" << "\n";
	out << "  exposedField SFVec3f    translation 0 0 0" << "\n";
	out << "  exposedField SFRotation rotation    0 0 1 0" << "\n";
	out << "  exposedField SFInt32    sensorId    -1" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform {" << "\n";
	out << "    translation IS translation" << "\n";
	out << "    rotation    IS rotation" << "\n";
	out << "   }" << "\n";
	out << "}" << "\n";
	out << "PROTO Gyro [" << "\n";
	out << "  exposedField SFVec3f    maxAngularVelocity -1 -1 -1" << "\n";
	out << "  exposedField SFVec3f    translation        0 0 0" << "\n";
	out << "  exposedField SFRotation rotation           0 0 1 0" << "\n";
	out << "  exposedField SFInt32    sensorId           -1" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform {" << "\n";
	out << "    translation IS translation" << "\n";
	out << "    rotation    IS rotation" << "\n";
	out << "  }" << "\n";

	out << "}" << "\n";
	out << "PROTO AccelerationSensor [" << "\n";
	out << "  exposedField SFVec3f    maxAcceleration -1 -1 -1" << "\n";
	out << "  exposedField SFVec3f    translation     0 0 0" << "\n";
	out << "  exposedField SFRotation rotation        0 0 1 0" << "\n";
	out << "  exposedField SFInt32    sensorId        -1" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform {" << "\n";
	out << "    translation IS translation" << "\n";
	out << "    rotation    IS rotation" << "\n";
	out << "  }" << "\n";

	out << "}" << "\n";
	out << "PROTO PressureSensor [" << "\n";
	out << "  exposedField SFFloat    maxPressure -1" << "\n";
	out << "  exposedField SFVec3f    translation 0 0 0" << "\n";
	out << "  exposedField SFRotation rotation    0 0 1 0" << "\n";
	out << "  exposedField SFInt32    sensorId    -1" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform {" << "\n";
	out << "    translation IS translation" << "\n";
	out << "    rotation    IS rotation" << "\n";
	out << "  }" << "\n";
	out << "}" << "\n";
	out << "PROTO PhotoInterrupter [" << "\n";
	out << "  exposedField SFVec3f transmitter 0 0 0" << "\n";
	out << "  exposedField SFVec3f receiver    0 0 0" << "\n";
	out << "  exposedField SFInt32 sensorId    -1" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform{" << "\n";
	out << "    children [" << "\n";
	out << "      Transform{" << "\n";
	out << "        translation IS transmitter" << "\n";
	out << "      }" << "\n";
	out << "      Transform{" << "\n";
	out << "        translation IS receiver" << "\n";
	out << "      }" << "\n";
	out << "    ]" << "\n";
	out << "  }" << "\n";
	out << "}" << "\n";
	out << "PROTO CylinderSensorZ [" << "\n";
	out << "    exposedField    SFFloat    maxAngle       -1" << "\n";
	out << "    exposedField    SFFloat    minAngle        0" << "\n";
	out << "    exposedField    MFNode     children        [ ]" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform{" << "\n";
	out << "    rotation 1 0 0 1.5708" << "\n";
	out << "    children [" << "\n";
	out << "      DEF SensorY CylinderSensor{" << "\n";
	out << "        maxAngle IS maxAngle" << "\n";
	out << "        minAngle IS minAngle" << "\n";
	out << "      }" << "\n";
	out << "      DEF AxisY Transform{" << "\n";
	out << "        children [" << "\n";
	out << "          Transform{" << "\n";
	out << "            rotation 1 0 0 -1.5708" << "\n";
	out << "            children IS children" << "\n";
	out << "          }" << "\n";
	out << "       ]" << "\n";
	out << "     }" << "\n";
	out << "   ]" << "\n";
	out << "  }" << "\n";
	out << "  ROUTE SensorY.rotation_changed TO AxisY.set_rotation" << "\n";
	out << "}" << "\n";
	out << "PROTO CylinderSensorY [" << "\n";
	out << "    exposedField    SFFloat    maxAngle       -1" << "\n";
	out << "    exposedField    SFFloat    minAngle        0" << "\n";
	out << "    exposedField    MFNode     children        [ ]" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform{" << "\n";
	out << "    rotation 0 1 0 1.5708" << "\n";
	out << "    children [" << "\n";
	out << "      DEF SensorX CylinderSensor{" << "\n";
	out << "        maxAngle IS maxAngle" << "\n";
	out << "        minAngle IS minAngle" << "\n";
	out << "      }" << "\n";
	out << "      DEF AxisX Transform{" << "\n";
	out << "        children [" << "\n";
	out << "          Transform{" << "\n";
	out << "            rotation 0 1 0 -1.5708" << "\n";
	out << "            children IS children" << "\n";
	out << "          }" << "\n";
	out << "        ]" << "\n";
	out << "      }" << "\n";
	out << "    ]" << "\n";
	out << "   }" << "\n";
	out << "  ROUTE SensorX.rotation_changed TO AxisX.set_rotation" << "\n";
	out << "}" << "\n";
	out << "PROTO CylinderSensorX [" << "\n";
	out << "    exposedField    SFFloat    maxAngle       -1" << "\n";
	out << "    exposedField    SFFloat    minAngle        0" << "\n";
	out << "    exposedField    MFNode     children        [ ]" << "\n";
	out << "]" << "\n";
	out << "{" << "\n";
	out << "  Transform{" << "\n";
	out << "    rotation 0 0 1 -1.5708" << "\n";
	out << "    children [" << "\n";
	out << "      DEF SensorZ CylinderSensor{" << "\n";
	out << "        maxAngle IS maxAngle" << "\n";
	out << "        minAngle IS minAngle" << "\n";
	out << "      }" << "\n";
	out << "      DEF AxisZ Transform{" << "\n";
	out << "        children [" << "\n";
	out << "          Transform{" << "\n";

	out << "            rotation 0 0 1 1.5708" << "\n";
	out << "            children IS children" << "\n";
	out << "          }" << "\n";
	out << "        ]" << "\n";
	out << "      }" << "\n";
	out << "    ]" << "\n";
	out << "  }" << "\n";
	out << "  ROUTE SensorZ.rotation_changed TO AxisZ.set_rotation" << "\n";

	out << "}" << "\n";
	out << "NavigationInfo {" << "\n";
	out << "  avatarSize    0.5" << "\n";
	out << "  headlight     TRUE" << "\n";
	out << "  type  [\"EXAMINE\", \"ANY\"]" << "\n";
	out << "}" << "\n";
	out << "" << "\n";
	out << "" << "\n";




	QStringList TXX3;
	TXX3 = fileName.split("/");

	QStringList TXX4;
	TXX4 = TXX3[TXX3.size() - 1].split(".wrl");

	out << "DEF " << TXX4[0] << " Humanoid {" << "\n";
	out << "  humanoidBody [" << "\n";
	out << "    DEF BASE Joint {" << "\n";
	if (BType == 0)
		out << "      jointType " << "\"free\"" << "\n";
	else
		out << "      jointType " << "\"fixed\"" << "\n";
	//if(BType == 1)
	out << "children [" << "\n";
	BodyData* ONUM;
	BodyData* bd;
	for (int i = 0; i < textItem.size(); i++){
		if (textItem[i]->m_param->m_param.NUM == 0)
		{

			ONUM = textItem[i]->m_param;

			for (int j = 0; j<senItem.size(); j++)
			{
				SensorData *sd = senItem[j]->ReturnParam();
				if (senItem[j]->m_param->m_body == ONUM)
				{
					out << "Transform {" << "\n";

					out << "      translation " << sd->m_param.m_px << " " << sd->m_param.m_py << " " << sd->m_param.m_pz << "\n";




					if (sd->m_param.m_slz == 0.0 && sd->m_param.m_sly == 0.0)
					{

						out << "children [" << "\n";
						out << "Transform {" << "\n";
						out << "      rotation 0 1 0 " << -1.57 << "\n";
						out << "children [" << "\n";

					}
					else if (sd->m_param.m_slz == 0.0 && sd->m_param.m_slx == 0.0)
					{

						out << "children [" << "\n";
						out << "Transform {" << "\n";
						out << "      rotation 1 0 0 " << -1.57 << "\n";
						out << "children [" << "\n";

					}
					else if (sd->m_param.m_slx == 0.0 && sd->m_param.m_sly == 0.0)
					{

						out << "children [" << "\n";
						out << "Transform {" << "\n";
						out << "children [" << "\n";
					}
					else if (sd->m_param.m_slx != 0.0){
						float TEMPX = sd->m_param.m_slx;
						float TEMPY = sd->m_param.m_sly;
						float TEMPZ = sd->m_param.m_slz;
						float TEMPXY = sqrt(TEMPZ * TEMPZ + TEMPY * TEMPY);
						float TEMPRZ = atan2(TEMPY, TEMPZ);
						float TEMPRY = atan2(-TEMPX, TEMPXY);

						out << "      rotation 1 0 0 " << TEMPRZ << "\n";
						out << "children [" << "\n";

						out << "Transform {" << "\n";
						out << "      rotation 0 1 0 " << TEMPRY << "\n";
						out << "children [" << "\n";




					}


					if (senItem[j]->m_param->m_param.m_type == Force)out << "DEF " << senItem[j]->m_param->m_param.NAME << " ForceSensor {" << "\n";
					if (senItem[j]->m_param->m_param.m_type == Gyro)out << "DEF " << senItem[j]->m_param->m_param.NAME << " Gyro {" << "\n";
					if (senItem[j]->m_param->m_param.m_type == Range)out << "DEF " << senItem[j]->m_param->m_param.NAME << " RangeSensor {" << "\n";
					if (senItem[j]->m_param->m_param.m_type == Acceleration)out << "DEF " << senItem[j]->m_param->m_param.NAME << " AccelerationSensor {" << "\n";
					if (senItem[j]->m_param->m_param.m_type == Torque)out << "DEF " << senItem[j]->m_param->m_param.NAME << " ForceSensor {" << "\n";


					out << "sensorId " << senItem[j]->m_param->m_param.ID << "\n";




					out << "}" << "\n";
					out << "]" << "\n";
					out << "}" << "\n";
					out << "]" << "\n";
					out << "}" << "\n";

				}

			}

			bd = textItem[i]->ReturnParam();
			out << "        DEF " << bd->m_param.NAME << " Segment {" << "\n";

			out << "	  mass " << bd->m_param.m_mass << "\n";
			out << "          centerOfMass 0 0 0" << "\n";
			out << "	  momentsOfInertia [";
			for (int j = 0; j < 9; j++)out << " " << bd->m_param.I[j];
			out << " ]" << "\n";

			out << "          children [" << "\n";

			out << "Transform {" << "\n";

			out << "      translation " << bd->m_param.m_px << " " << bd->m_param.m_py << " " << bd->m_param.m_pz << "\n";
			out << "      rotation 1 0 0 " << bd->m_param.m_slx << "\n";
			out << "          children [" << "\n";
			out << "Transform {" << "\n";

			out << "      rotation 0 1 0 " << bd->m_param.m_sly << "\n";
			out << "          children [" << "\n";
			out << "Transform {" << "\n";
			out << "      rotation 0 0 1 " << bd->m_param.m_slz << "\n";

			out << "          children [" << "\n";

			if (bd->m_param.m_type == Body_Box){

				out << "Shape {" << "\n";
				out << "appearance Appearance {" << "\n";
				out << "                material Material {" << "\n";
				out << "                diffuseColor  " << bd->m_param.m_red << " " << bd->m_param.m_green << " " << bd->m_param.m_blue << " " << "\n";
				out << "}" << "\n";
				out << "}" << "\n";
				out << "    geometry Box {" << "\n";
				out << "        size " << bd->m_param.m_length << " " << bd->m_param.m_width << " " << bd->m_param.m_height << "\n";
				out << "    }" << "\n";
				out << "    }" << "\n";


			}
			if (bd->m_param.m_type == Body_Sphere){
				out << "Shape {" << "\n";
				out << "appearance Appearance {" << "\n";
				out << "                material Material {" << "\n";
				out << "                diffuseColor  " << bd->m_param.m_red << " " << bd->m_param.m_green << " " << bd->m_param.m_blue << " " << "\n";
				out << "}" << "\n";
				out << "}" << "\n";
				out << "    geometry Sphere {" << "\n";
				out << "    radius " << bd->m_param.m_rad << "\n";
				out << "    }" << "\n";
				out << "    }" << "\n";
			}
			if (bd->m_param.m_type == Body_Cone){
				out << "Shape {" << "\n";
				out << "appearance Appearance {" << "\n";
				out << "                material Material {" << "\n";
				out << "                diffuseColor  " << bd->m_param.m_red << " " << bd->m_param.m_green << " " << bd->m_param.m_blue << " " << "\n";
				out << "}" << "\n";
				out << "}" << "\n";
				out << "    geometry Cone {" << "\n";
				out << "    bottomRadius " << bd->m_param.m_rad << "\n";
				out << "    height " << bd->m_param.m_length << "\n";
				out << "    }" << "\n";
				out << "    }" << "\n";
			}
			if (bd->m_param.m_type == Body_Cylinder){
				out << "Shape {" << "\n";
				out << "appearance Appearance {" << "\n";
				out << "                material Material {" << "\n";
				out << "                diffuseColor  " << bd->m_param.m_red << " " << bd->m_param.m_green << " " << bd->m_param.m_blue << " " << "\n";
				out << "}" << "\n";
				out << "}" << "\n";
				out << "    geometry Cylinder {" << "\n";
				out << "    radius " << bd->m_param.m_rad << "\n";
				out << "    height " << bd->m_param.m_length << "\n";
				out << "    }" << "\n";
				out << "    }" << "\n";
			}
			if (bd->m_param.m_type == Body_Polygon){
				savePolygon(fileName, textItem[i]->m_param);
				out << "Inline {" << "\n";
				out << "url " << "\"" << bd->m_param.NAME << ".wrl\"" << "\n";
				out << "    }" << "\n";
			}
			out << "]" << "\n";
			out << "}" << "\n";
			out << "]" << "\n";
			out << "}" << "\n";
			out << "]" << "\n";
			out << "}" << "\n";
			out << "]" << "\n";
		}
	}
	//out << "]" << "\n";
	out << "}" << "\n";
	int GNUM = 0;
	std::vector<BodyData*> BTEMP;
	std::vector<JointData*> JTEMP;
	//JTEMP.push_back(ONUM);
	BTEMP.push_back(ONUM);
	int JN = 0;
	bool EF = true;
	float trans[3];
	trans[0] = 0;
	trans[1] = 0;
	trans[2] = 0;
	int BCOUNT = 0;

	//int JointFLAG[100];

	//for(int h=0;h<100;h++)JointFLAG[h]=0;

	int counb = 0;

	JointItem *ji = NULL;
	for (int i = 0; i < actItem.size(); i++)
	{
		if (actItem[i]->m_param->m_item1 == bd)
		{
			ji = actItem[i];
		}
	}
	if (ji)
	{
		writeJointData(fileName, out, ji->m_param, trans);
	}
	else std::cout << "test" << std::endl;
	out << "}" << "\n";
	out << "]" << "\n";
	out << "]" << "\n";
	out << "joints [" << "\n";
	out << "USE " << "BASE," << "\n";

	for (int i = 0; i < actItem.size(); i++)
	{
		out << "USE " << actItem[i]->m_param->m_param.NAME << "," << "\n";
	}


	out << "]" << "\n";


	out << "segments [" << "\n";
	for (int j = 0; j<textItem.size(); j++)
	{
		out << "USE " << textItem[j]->m_param->m_param.NAME << "," << "\n";
	}

	out << "]" << "\n";
	out << "}" << "\n";



	return 0;
}




int DiagramScene::LoadFile(const QString &fileName)
{
	std::vector<BodyItem*> tmp_textItem = textItem;
	
	
	

	for (std::vector<BodyItem*>::iterator it = tmp_textItem.begin(); it != tmp_textItem.end(); ++it)
	{
		deleteBody((*it));
	}
	std::vector<JointItem*> tmp_actItem = actItem;
	for (std::vector<JointItem*>::iterator it = tmp_actItem.begin(); it != tmp_actItem.end(); ++it)
	{
		deleteJoint((*it));
	}
	std::vector<SensorItem*> tmp_senItem = senItem;
	for (std::vector<SensorItem*>::iterator it = tmp_senItem.begin(); it != tmp_senItem.end(); ++it)
	{
		deleteSensor((*it));
	}
	std::vector<CameraItem*> tmp_camItem = camItem;
	for (std::vector<CameraItem*>::iterator it = tmp_camItem.begin(); it != tmp_camItem.end(); ++it)
	{
		deleteCamera((*it));
	}

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly)) {

		return 1;
	}
	QDataStream in(&file);

	int num;
	in >> num;
	for (int i = 0; i < num; i++)
	{
		BodyParam bp;
		in >> bp.NAME;
		in >> bp.NUM;
		in >> bp.m_px;
		in >> bp.m_py;
		in >> bp.m_pz;
		in >> bp.m_length;
		in >> bp.m_width;
		in >> bp.m_height;
		in >> bp.m_slx;
		in >> bp.m_sly;
		in >> bp.m_slz;
		in >> bp.m_mass;
		in >> bp.m_red;
		in >> bp.m_green;
		in >> bp.m_blue;
		in >> bp.m_rad;
		in >> bp.axis;
		in >> bp.m_pd.NAME;
		in >> bp.m_type;
		float px, py;
		in >> px;
		in >> py;
		createBody(bp,QPointF(px,py));
		
	}

	
	in >> num;
	for (int i = 0; i < num; i++)
	{
		JointParam jp;
		in >> jp.NAME;
		in >> jp.NUM;
		in >> jp.m_px;
		in >> jp.m_py;
		in >> jp.m_pz;
		in >> jp.m_axisx;
		in >> jp.m_axisy;
		in >> jp.m_axisz;
		in >> jp.ulimitH;
		in >> jp.ulimitL;
		in >> jp.uvlimitH;
		in >> jp.uvlimitL;
		in >> jp.rotorInertia;
		in >> jp.rotorResistor;
		in >> jp.torqueConst;
		in >> jp.encoder;
		in >> jp.m_type;
		int bnum1, bnum2;
		in >> bnum1;
		in >> bnum2;

		BodyItem *bi1 = getBodyItem(bnum1);
		BodyItem *bi2 = getBodyItem(bnum2);

		createJoint(jp,bi1,bi2);
	}

	
	in >> num;
	for (int i = 0; i < num; i++)
	{
		SensorParam sp;
		in >> sp.NAME;
		in >> sp.NUM;
		in >> sp.m_px;
		in >> sp.m_py;
		in >> sp.m_pz;
		in >> sp.m_slx;
		in >> sp.m_sly;
		in >> sp.m_slz;
		in >> sp.m_type;
		int bnum;
		in >> bnum;
		float px, py;
		in >> px;
		in >> py;
		BodyItem *bi = getBodyItem(bnum);
		createSensor(sp, QPointF(px, py), bi->m_param);
	}

	
	in >> num;
	for (int i = 0; i < num; i++)
	{
		CameraParam cp;
		in >> cp.NAME;
		in >> cp.NUM;
		in >> cp.m_px;
		in >> cp.m_py;
		in >> cp.m_pz;
		in >> cp.m_width;
		in >> cp.m_height;
		in >> cp.m_slx;
		in >> cp.m_sly;
		in >> cp.m_slz;
		in >> cp.fieldOfView;
		in >> cp.frontClipDistance;
		in >> cp.backClipDistance;
		in >> cp.m_type;
		in >> cp.ID;
		int jnum;
		in >> jnum;
		float px, py;
		in >> px;
		in >> py;
		JointItem *ji = getJointItem(jnum);
		createCamera(cp,QPointF(px,py),ji->m_param);
	}
	file.close();
	

	return 0;

}


BodyItem* DiagramScene::createBody(BodyParam bp, QPointF p)
{
	BodyData *bd = new BodyData(bp);

	BodyItem *bi = new BodyItem(bd);
	textItem.push_back(bi);
	addItem(bi);
	
	bi->setPos(p);






	if (bi->m_param->m_param.NUM == 0)bi->SetTip(true);



	bi->m_text = new QGraphicsTextItem();

	addItem(bi->m_text);

	bi->m_text->setPlainText(bi->m_param->m_param.NAME);

	bi->m_text->setPos(bi->pos() + QPointF(30, 55));



	emit textInserted(bi);

	return bi;
}
JointItem* DiagramScene::createJoint(JointParam jp, BodyItem *bi1, BodyItem *bi2)
{
	JointData *jd = new JointData(bi1->m_param, bi2->m_param, jp);
	JointItem *ji = new JointItem(jd);
	actItem.push_back(ji);


	myMode = MoveLink;
	ji->m_line = new QGraphicsLineItem(QLineF(bi1->pos() + QPointF(90, 50) / 2,
		bi2->pos() + QPointF(90, 50) / 2));
	ji->m_line->setPen(QPen(myLineColor, 2));



	addItem(ji);
	addItem(ji->m_line);
	ji->setPos((bi1->pos() + bi2->pos()) / 2 + QPointF(10, 10));



	ji->m_text = new QGraphicsTextItem;

	addItem(ji->m_text);

	ji->m_text->setPlainText(ji->m_param->m_param.NAME);

	ji->m_text->setPos(ji->pos() + QPointF(35, 120) / 2);



	updateJoint();






	emit actInserted(ji);

	return ji;
}
SensorItem* DiagramScene::createSensor(SensorParam sp, QPointF p, BodyData *bd)
{
	SensorData *sd = new SensorData(bd, sp);
	SensorItem *si = new SensorItem(sd);
	addItem(si);
	senItem.push_back(si);
	si->setPos(p);


	si->m_text = new QGraphicsTextItem();

	addItem(si->m_text);

	si->m_text->setPlainText(si->m_param->m_param.NAME);

	si->m_text->setPos(si->pos() + QPointF(10, 55));

	si->m_line = new QGraphicsLineItem(QLineF(si->pos(), si->pos()));
	addItem(si->m_line);

	


	emit senInserted(si);

	return si;
}
CameraItem* DiagramScene::createCamera(CameraParam cp, QPointF p, JointData *jd)
{
	CameraData * cd = new CameraData(jd, cp);
	CameraItem *ci = new CameraItem(cd);
	camItem.push_back(ci);
	addItem(ci);
	ci->setPos(p);



	ci->m_text = new QGraphicsTextItem();

	addItem(ci->m_text);

	ci->m_text->setPlainText(ci->m_param->m_param.NAME);

	ci->setPos(ci->pos() + QPointF(10, 55));
	ci->m_text->setPos(ci->pos() + QPointF(35, 120) / 2);

	ci->m_line = new QGraphicsLineItem(QLineF(ci->pos(), ci->pos()));
	addItem(ci->m_line);
	

	emit camInserted(ci);

	return ci;
}



void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QGraphicsScene::mousePressEvent(mouseEvent);
    if (mouseEvent->button() == Qt::RightButton)
	{
		myMode = MoveItem;
		RotNum = 100;
		emit setRotNum();
		GeoNum = 100;
		emit setGeoNum();
		SSNum = 100;
		emit setSSNum();
		tempItem = NULL;
		templine2 = NULL;
	}
	else if(mouseEvent->button() == Qt::LeftButton){
		BodyDialog dialog;
		ActDialog dialog2;
		SensorDialog dialog3;
		CameraDialog dialog4;
		//emit delTab();
		//std::cout << myMode << std::endl;
	switch (myMode) {
		case MoveItem:
			foreach (QGraphicsItem *item2, selectedItems()) {
				if (item2->type() == JointItem::Type) {
					for (int j = 0; j<actItem.size(); j++){
						if(item2->pos() == actItem[j]->pos()){
							RotNum = j;
							emit setRotNum();
							GeoNum = 100;
							emit setGeoNum();
							SSNum = 100;
							emit setSSNum();
							tempItem = actItem[j];
						}
					}
				}
				
				if (item2->type() == BodyItem::Type) {
					for (int j = 0; j<textItem.size(); j++){
						if(item2->pos() == textItem[j]->pos()){
							GeoNum = j;
							emit setGeoNum();
							RotNum = 100;
							emit setRotNum();
							SSNum = 100;
							emit setSSNum();
							tempItem = textItem[j];
						}
					}
				}
				
				if (item2->type() == SensorItem::Type) {
					for (int j = 0; j<senItem.size(); j++){
						if(item2->pos() == senItem[j]->pos()){
							GeoNum = 100;
							emit setGeoNum();
							RotNum = 100;
							emit setRotNum();
							SSNum = j;
							emit setSSNum();
							tempItem = senItem[j];
						}
					}
				}
				
				if (item2->type() == CameraItem::Type) {
					for (int j = 0; j<camItem.size(); j++){
						if(item2->pos() == camItem[j]->pos()){
							GeoNum = 100;
							emit setGeoNum();
							RotNum = 100;
							emit setRotNum();
							SSNum = 100;
							emit setSSNum();
							tempItem = camItem[j];
						}
					}
				}
				
			}
			break;

		case InsertText:
			dialog.exec();
			if (dialog.ReturnFLAG()){
				createBody(dialog.returnParam(), mouseEvent->scenePos());
				
			}
			break;
		
		case CreateCamera:

			foreach (QGraphicsItem *item2, selectedItems()) {
				if (item2->type() == JointItem::Type) {

				//camlin[cam_count] = item2;
							dialog4.exec();
			if(dialog4.ReturnFLAG()){
				JointData *jd;
				for (int j = 0; j<actItem.size(); j++)
				{
					if (item2->pos() == actItem[j]->pos())
					{
						jd = actItem[j]->m_param;
					}
				}
				createCamera(dialog4.returnParam(), mouseEvent->scenePos(),jd);
				
			}
				}
			}
			break;

			case CreateSensor:

			foreach (QGraphicsItem *item2, selectedItems()) {
				if (item2->type() == BodyItem::Type) {
							dialog3.exec();
			if(dialog3.ReturnFLAG()){
				BodyData *bd;
				for (int j = 0; j<textItem.size(); j++)
				{
					if (item2->pos() == textItem[j]->pos())
					{
						bd = textItem[j]->m_param;
					}
				}
				createSensor(dialog3.returnParam(), mouseEvent->scenePos(),bd);
				
			}
				}
			}
			break;

		case MoveLink:

			foreach (QGraphicsItem *item2, selectedItems()) {
				//std::cout << item2->type() << "\t" << BodyItem::Type << std::endl;
				if (item2->type() == BodyItem::Type) {

					
				myMode = CreateLink;
				tempItem = item2;
				}
			}
			break;


		case CreateLink:


			foreach (QGraphicsItem *item2, selectedItems()) {
				if (item2->type() == BodyItem::Type) {
		
					if (item2 != tempItem){
						dialog2.exec();
						if(dialog2.ReturnFLAG()){

							
							
							BodyItem *body1 = NULL;
							BodyItem *body2 = NULL;
							for (int j = 0; j<textItem.size(); j++){
								if (tempItem->pos() == textItem[j]->pos()){
									body1 = textItem[j];
								}
								if (item2->pos() == textItem[j]->pos()){
									body2 = textItem[j];
								}
							}
							if (body1 == NULL || body2 == NULL)return;
							createJoint(dialog2.returnParam(), body1,body2);
							
							
							

							tempItem = NULL;

							
						}
					}
					break;

				}
			}
			break;


		

			

			default:
				;
		}
	}
    

}


void DiagramScene::updateJoint()
{
	for (int i = 0; i<actItem.size(); i++)
	{
		actItem[i]->m_param->m_item2->tip = true;
		if (actItem[i]->m_param->m_item2->m_param.NUM == 0)
		{
			actItem[i]->m_param->m_item2->tip = false;
			BodyData *tmp = actItem[i]->m_param->m_item1;
			actItem[i]->m_param->m_item1 = actItem[i]->m_param->m_item2;
			actItem[i]->m_param->m_item2 = tmp;
			actItem[i]->m_param->m_item2->tip = true;
		}
		actItem[i]->m_param->m_item1->tip = false;
		
		
		
	}
	for (int i = 0; i < actItem.size(); i++)
	{
		for (int j = 0; j < actItem.size(); j++)
		{
			if (i != j)
			{
				if (actItem[i]->m_param->m_item2 == actItem[j]->m_param->m_item1)
				{
					actItem[i]->m_param->m_item2->tip = false;
				}
			}
		}
		//std::cout << actItem[i]->m_param->m_item1->tip << "\t" << actItem[i]->m_param->m_item2->tip << std::endl;
	}
}

void DiagramScene::deleteBody(BodyItem *bi)
{
	removeItem(bi);
	removeItem(bi->m_text);
	std::vector<BodyItem*>::iterator end_it = remove(textItem.begin(), textItem.end(), bi);
	textItem.erase(end_it, textItem.end());

	for (int j = 0; j<actItem.size(); j++)
	{
		if (actItem[j]->m_param->m_item1 == bi->m_param)
		{
			
			deleteJoint(actItem[j]);
			
		}
		else if (actItem[j]->m_param->m_item2 == bi->m_param)
		{
			
			deleteJoint(actItem[j]);
			
		}

	}
	for (int j = 0; j<senItem.size(); j++)
	{
		if (senItem[j]->m_param->m_body == bi->m_param){
			deleteSensor(senItem[j]);
		}
	}
}
void DiagramScene::deleteJoint(JointItem *ji)
{
	removeItem(ji);
	removeItem(ji->m_text);
	removeItem(ji->m_line);
	std::vector<JointItem*>::iterator end_it = remove(actItem.begin(), actItem.end(), ji);
	actItem.erase(end_it, actItem.end());

	for (int k = 0; k<camItem.size(); k++)
	{
		if (camItem[k]->m_param->m_joint1 == ji->m_param){
			deleteCamera(camItem[k]);
		}
	}
	updateJoint();
}
void DiagramScene::deleteSensor(SensorItem *si)
{
	removeItem(si);
	removeItem(si->m_text);
	removeItem(si->m_line);
	std::vector<SensorItem*>::iterator end_it = remove(senItem.begin(), senItem.end(), si);
	senItem.erase(end_it, senItem.end());
}
void DiagramScene::deleteCamera(CameraItem *ci)
{
	removeItem(ci);
	removeItem(ci->m_text);
	removeItem(ci->m_line);
	std::vector<CameraItem*>::iterator end_it = remove(camItem.begin(), camItem.end(), ci);
	camItem.erase(end_it, camItem.end());
}

void DiagramScene::deleteItem()
{
	foreach (QGraphicsItem *item, selectedItems()) {
			for(int i=0;i<textItem.size();i++){
			if(item->pos() == textItem[i]->pos())
			{
				deleteBody(textItem[i]);

			}
		}
		for(int i=0;i<actItem.size();i++){
			if(item->pos() == actItem[i]->pos())
			{
				deleteJoint(actItem[i]);
			}
		}
		for(int i=0;i<senItem.size();i++){
			if(item->pos() == senItem[i]->pos())
			{
				deleteSensor(senItem[i]);
			}
		}
		for(int i=0;i<camItem.size();i++){
			if(item->pos() == camItem[i]->pos())
			{
				deleteCamera(camItem[i]);
			}
		}
		


	}
	updateJoint();
}

BodyItem * DiagramScene::getBodyItem(ItemDataBase *bd)
{
	
	for (int i = 0; i < textItem.size(); i++)
	{
		if (textItem[i]->m_param == bd)
		{
			return textItem[i];
		}
	}
	return NULL;
}

BodyItem * DiagramScene::getBodyItem(int num)
{
	
	for (int i = 0; i < textItem.size(); i++)
	{
		if (textItem[i]->m_param->m_param.NUM == num)
		{
			return textItem[i];
		}
	}
	return NULL;
}


JointItem * DiagramScene::getJointItem(JointData *jd)
{
	
	for (int i = 0; i < actItem.size(); i++)
	{
		if (actItem[i]->m_param == jd)
		{
			return actItem[i];
		}
	}
	return NULL;
}

JointItem * DiagramScene::getJointItem(int num)
{
	std::vector<JointItem *> ans;
	for (int i = 0; i < actItem.size(); i++)
	{
		if (actItem[i]->m_param->m_param.NUM == num)
		{
			return actItem[i];
		}
	}
	return NULL;
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QLineF newLine(mouseEvent->scenePos(),
                                        mouseEvent->scenePos());
	
	templine->setLine(newLine);
	if (myMode == InsertLine && templine2) {
		QLineF newLine(templine2->line().p1(), mouseEvent->scenePos());
		templine2->setLine(newLine);
    } else if (myMode == MoveLink) {
		if (QLineF(mouseEvent->screenPos(), mouseEvent->buttonDownScreenPos(Qt::LeftButton))
			.length() < QApplication::startDragDistance()) {
			return;
		}
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
	else if (myMode == MoveItem) {
		for (int i = 0; i<actItem.size(); i++){
			BodyItem *item1 = getBodyItem(actItem[i]->m_param->m_item1);
			BodyItem *item2 = getBodyItem(actItem[i]->m_param->m_item2);
			QLineF newLine(item1->pos() + QPointF(90, 50) / 2,
				item2->pos() + QPointF(90, 50) / 2);
			actItem[i]->m_line->setLine(newLine);
			actItem[i]->setPos((item1->pos() + item2->pos()) / 2 + QPointF(10, 0));

			actItem[i]->m_text->setPos(actItem[i]->pos() + QPointF(35, 120) / 2);
		}
		for (int i = 0; i<textItem.size(); i++){
			textItem[i]->m_text->setPos(textItem[i]->pos() + QPointF(30, 55));
		}
		for (int i = 0; i<senItem.size(); i++){
			
			BodyItem *item1 = getBodyItem(senItem[i]->m_param->m_body);
			QLineF newLine(item1->pos() + QPointF(90, 50) / 2,
                                        senItem[i]->pos() + QPointF(30, 30));
			senItem[i]->m_line->setLine(newLine);
			senItem[i]->m_text->setPos(senItem[i]->pos() + QPointF(10, 55));
		}
		for (int i = 0; i<camItem.size(); i++){
			JointItem * item1 = getJointItem(camItem[i]->m_param->m_joint1);
			QLineF newLine(item1->pos() + QPointF(90, 50) / 2,
                                        camItem[i]->pos() + QPointF(30, 30));
			camItem[i]->m_line->setLine(newLine);
			camItem[i]->m_text->setPos(camItem[i]->pos() + QPointF(10, 55));
		}
        QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
	else if (myMode == CreateLink) {
		QLineF newLine(tempItem->pos() + QPointF(90, 50) / 2,
                                        mouseEvent->scenePos());
		templine->setLine(newLine);
		

	}
		/*QDrag *drag = new QDrag(mouseEvent->widget());
		QMimeData *mime = new QMimeData;
		drag->setMimeData(mime);
		QImage image(":/images/SensorE.png");
        mime->setImageData(image);
        drag->setPixmap(QPixmap::fromImage(image));
        drag->setHotSpot(QPoint(15, 30));





		drag->exec();*/

	
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	QLineF newLine(mouseEvent->scenePos(),
                                        mouseEvent->scenePos());
	templine->setLine(newLine);
    QGraphicsScene::mouseReleaseEvent(mouseEvent);

}

