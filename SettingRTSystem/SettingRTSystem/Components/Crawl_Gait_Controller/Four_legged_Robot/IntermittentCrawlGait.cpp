/*!
* @file  IntermittentCrawlGait.cpp
* @brief 間歇クロール歩容制御クラス
*
*/


#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "IntermittentCrawlGait.h"



#define DEFAULT_SAMPLING_TIME 0.1


#define MIN_VELOCITY_VX 0.0001
#define MIN_VELOCITY_VY 0.0001
#define MIN_VELOCITY_TH 0.0001

#define DEFAULT_SIDE_DISTANCE 0.03
#define DEFAULT_MIN_MARGIN 0.01


/**
*@brief コンストラクタ
* @param ls 脚のリスト
*/
IntermittentCrawlGait::IntermittentCrawlGait(Leg_Object *ls, Body_Object *bo) : GaitBase(ls, bo)
{
	legs = ls;

	sampling_time = DEFAULT_SAMPLING_TIME;

	current_time = 0;

	state = ON_GROUND_FOUR_LEGS_1;
	dir = WALK_STOP;

	min_margin = DEFAULT_MIN_MARGIN;
	side_move_distance = DEFAULT_SIDE_DISTANCE;
}


/**
*@brief 横方向への移動距離設定
* @param smd 移動距離
*/
void IntermittentCrawlGait::setSideMoveDistance(double smd)
{
	side_move_distance = smd;
}



/**
*@brief 歩行更新
* @param vx 速度(X)
* @param vy 速度(Y)
* @param dthe 回転速度
* @param sd 歩幅
*/
void IntermittentCrawlGait::walk(double vx, double vy, double dthe, double sd)
{
	
	if (abs(vx) < MIN_VELOCITY_VX && abs(vy) < MIN_VELOCITY_VY && abs(dthe) < MIN_VELOCITY_TH)
	{
		return;
	}
	else if (abs(dthe) < MIN_VELOCITY_TH)
	{
		dthe = MIN_VELOCITY_TH;
	}
	body->update();
	


	//std::cout << "update_b:" << legs[2].stability_x_offset << "\t" << legs[2].state << "\t" << legs[2].target_pos(0) << "\t" << legs[2].current_pos(0) << std::endl;
	for (int i = 0; i < 4; i++)
	{

		legs[i].update();
	}
	//std::cout << "update_a:" << legs[2].stability_x_offset << "\t" << legs[2].state << "\t" << legs[2].target_pos(0) << "\t" << legs[2].current_pos(0) << std::endl;

	Direction_Object d = Direction_Object(vx, vy, dthe, legs);


	//stride = DEFAULT_STRIDE;
	stride = sd;


	double L_max = 0;
	for (int i = 0; i < 4; i++)
	{
		double len_x = d.pos(0) - (legs[i].center_pos(0) + legs[i].stability_x_offset);
		double len_y = d.pos(1) - (legs[i].center_pos(1) + legs[i].stability_y_offset);
		double L_tmp = sqrt(len_x*len_x + len_y*len_y);
		if (L_tmp > L_max)L_max = L_tmp;
	}
	int mc;
	if (d.dir == WALK_ROT_PLUS || d.dir == WALK_ROT_MINUS)
	{
		mc = (int)((stride / 3.0) / (L_max * abs(dthe) * sampling_time));
	}
	else
	{
		if (dir == WALK_FORWORD || dir == WALK_BACK || dir == WALK_RIGHT || dir == WALK_LEFT)
		{
			dthe *= 3;
		}
		mc = (int)((stride / 2.0) / (L_max * abs(dthe) * sampling_time));
	}
	//std::cout << mc << std::endl;
	/*static int count_f = 0;
	static int count_t = 0;
	static int count_m = 0;
	if (state == UP_FRONT_RIGHT_LEG || state == UP_BACK_LEFT_LEG || state == UP_BACK_RIGHT_LEG || state == UP_FRONT_LEFT_LEG)
	{
		count_t++;
	}
	else if (state == ON_GROUND_FOUR_LEGS_1 || state == ON_GROUND_FOUR_LEGS_2)
	{
		count_f++;
	}
	else if (state == MOVE_STABILITY)
	{
		count_m++;
	}
	std::cout << mc << "\t" << count_f << "\t" << count_t << "\t" << count_m << "\t" << std::endl;*/
	//int mc = (int)((stride / 4.0) / (L * abs(dthe) * sampling_time) * (step_time / 4.0));
	//std::cout << stride << "\t" << L_max << std::endl;
	//int tmp_conut = 0;
	//int tmp_offset_conut = 0;

	for (int i = 0; i < 4; i++)
	{
		legs[i].update_status(dthe, mc);
		if (dir == d.dir)
		{
			
			legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, false);

		}

	}
	
	body->update_status(dthe, mc);
	if (dir == d.dir)
	{
		
		body->setRotateStatus(d.pos, dthe, mc, sampling_time, false);
	}

	/*for (int i = 0; i < 4; i++)
	{
		if (legs[i].state != MOVE_STOP && legs[i].state != MOVE_PAUSE)
		{
			tmp_conut = legs[i].count * mc / legs[i].max_count;
		}
	}

	//if (dir == d.dir)
	{
		for (int i = 0; i < 4; i++)
		{
			if (legs[i].state != MOVE_STOP && legs[i].state != MOVE_PAUSE)
			{
				//std::cout << "be: " << legs[i].count << std::endl;
				tmp_offset_conut = legs[i].offset_count * mc / legs[i].max_count;
				legs[i].count = tmp_conut;
				//legs[i].max_count = mc;
				legs[i].offset_count = tmp_offset_conut;

				if (dir == d.dir)legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, false);
				else
				{
					legs[i].rotete_vel = dthe;
					legs[i].max_count = mc;
				}
				//std::cout << "af: " << legs[i].count << std::endl;

				//std::cout << legs[i].count << "\t" << legs[i].max_count << std::endl;
			}

		}
	}*/

	for (int i = 0; i < 4; i++)
	{
		if (legs[i].state != MOVE_PAUSE && legs[i].state != MOVE_STOP)return;
	}



	if (dir != d.dir)
	{
		//state = WALK_PAUSE;
		for (int i = 0; i < 4; i++)
		{
			legs[i].set_state(MOVE_STOP);
			legs[i].count = 0;
		}
		body->set_state(MOVE_STOP);
		body->count = 0;
		//std::cout << dir << "\t" << state << std::endl;
	}
	dir = d.dir;

	double rot = atan2(vy, vx);
	//std::cout << rot << std::endl;
	

	//std::cout << mc << std::endl;
	
	if (dir == WALK_FORWORD)
	{
		if (state == UP_FRONT_RIGHT_LEG)state = ON_GROUND_FOUR_LEGS_1;
		else if (state == ON_GROUND_FOUR_LEGS_1)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = ON_GROUND_FOUR_LEGS_2;
		else if (state == ON_GROUND_FOUR_LEGS_2)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_FRONT_RIGHT_LEG;
		else if (state == MOVE_STABILITY)state = next_state;
		//else if (state == WALK_STOP)state = UP_BACK_LEFT_LEG;

		if (state == UP_FRONT_LEFT_LEG)
		{
			legs[0].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			
			legs[0].offset_count = (int)(mc*(-1.0));
			legs[0].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 1 && Leg_Object::LegsStop(legs, 4) < 3)
			{
				legs[0].target_pos = legs[0].center_pos;
				
				//legs[0].target_pos(1) += -side_move_distance;
				//std::cout << "test" << std::endl;
			}
			//if (Leg_Object::LegsStop(legs, 4) >= 1)legs[0].target_pos = legs[0]
			judge_Stability(mc);
			//legs[0].setTargetPos(Vector3d(stride/2.0, 0, 0), mc);
		}
		else if (state == ON_GROUND_FOUR_LEGS_2)
		{
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{

				for (int i = 0; i < 4; i++)
				{
					if (legs[i].state != MOVE_STOP)legs[i].set_state(ON_GROUND_INTERMITTENT_CRAWL);
					if (i == 0 || i == 1)
					{
						//legs[i].setTargetPos(Vector3d(0, -side_move_distance, 0), mc);
						legs[i].offset_count = (int)(mc*(1.0));

					}
					else
					{
						//legs[i].setTargetPos(Vector3d(-stride / 2.0, -side_move_distance, 0), mc);
						legs[i].offset_count = (int)(mc*(0.0));

					}
					legs[i].x_offset = side_move_distance*sin(rot);
					legs[i].y_offset = -side_move_distance*cos(rot);

					legs[i].next_intermittent_x_offset += legs[i].x_offset;
					legs[i].next_intermittent_y_offset += legs[i].y_offset;
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
					
				}
				body->set_state(ON_GROUND_INTERMITTENT_CRAWL);
				body->intermittent_x_offset = -side_move_distance*sin(rot);
				body->intermittent_y_offset = side_move_distance*cos(rot);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
				
			}
			
		}
		else if (state == UP_BACK_RIGHT_LEG)
		{
			legs[2].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[2].offset_count = (int)(mc*(-1.0));
			legs[2].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 2)
			{
				legs[2].target_pos = legs[2].center_pos;
				//legs[2].target_pos(1) += side_move_distance;
			}
			judge_Stability(mc);
		}
		else if (state == UP_FRONT_RIGHT_LEG)
		{
			legs[3].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[3].offset_count = (int)(mc*(-1.0));
			legs[3].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 1 && Leg_Object::LegsStop(legs, 4) < 3)
			{
				legs[3].target_pos = legs[3].center_pos;
				//legs[3].target_pos(1) += side_move_distance;
			}
			
			judge_Stability(mc);
		}
		else if (state == ON_GROUND_FOUR_LEGS_1)
		{
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (legs[i].state != MOVE_STOP)legs[i].set_state(ON_GROUND_INTERMITTENT_CRAWL);
					if (i == 0 || i == 1)
					{
						//legs[i].setTargetPos(Vector3d(-stride / 2.0, side_move_distance, 0), mc);
						legs[i].offset_count = (int)(mc*(0.0));
						
					}
					else
					{
						//legs[i].setTargetPos(Vector3d(0, side_move_distance, 0), mc);
						legs[i].offset_count = (int)(mc*(1.0));
						
					}
					legs[i].x_offset = -side_move_distance*sin(rot);
					legs[i].y_offset = side_move_distance*cos(rot);

					legs[i].next_intermittent_x_offset += legs[i].x_offset;
					legs[i].next_intermittent_y_offset += legs[i].y_offset;
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
					
				}
				body->set_state(ON_GROUND_INTERMITTENT_CRAWL);
				body->intermittent_x_offset = side_move_distance*sin(rot);
				body->intermittent_y_offset = -side_move_distance*cos(rot);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
				
			}
			
		}
		else if (state == UP_BACK_LEFT_LEG)
		{
			legs[1].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[1].offset_count = (int)(mc*(-1.0));
			legs[1].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 2)
			{
				legs[1].target_pos = legs[1].center_pos;
				//legs[1].target_pos(1) += -side_move_distance;
			}
			judge_Stability(mc);
		}
	}
	else if (dir == WALK_BACK)
	{
		if (state == UP_FRONT_RIGHT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = ON_GROUND_FOUR_LEGS_1;
		else if (state == ON_GROUND_FOUR_LEGS_1)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = ON_GROUND_FOUR_LEGS_2;
		else if (state == ON_GROUND_FOUR_LEGS_2)state = UP_FRONT_RIGHT_LEG;
		else if (state == MOVE_STABILITY)state = next_state;

		if (state == UP_FRONT_LEFT_LEG)
		{
			legs[0].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[0].offset_count = (int)(mc*(-1.0));
			legs[0].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 2)
			{
				legs[0].target_pos = legs[0].center_pos;
			}
			judge_Stability(mc);
		}
		else if (state == ON_GROUND_FOUR_LEGS_2)
		{
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (legs[i].state != MOVE_STOP)legs[i].set_state(ON_GROUND_INTERMITTENT_CRAWL);
					if (i == 0 || i == 1)
					{

						legs[i].offset_count = (int)(mc*(1.0));
						
					}
					else
					{

						legs[i].offset_count = (int)(mc*(0.0));
						
					}
					legs[i].x_offset = side_move_distance*sin(rot - M_PI);
					legs[i].y_offset = -side_move_distance*cos(rot - M_PI);

					legs[i].next_intermittent_x_offset += legs[i].x_offset;
					legs[i].next_intermittent_y_offset += legs[i].y_offset;
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
					
				}
				body->set_state(ON_GROUND_INTERMITTENT_CRAWL);
				body->intermittent_x_offset = -side_move_distance*sin(rot - M_PI);
				body->intermittent_y_offset = side_move_distance*cos(rot - M_PI);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);

			}
		}
		else if (state == UP_BACK_RIGHT_LEG)
		{
			legs[2].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[2].offset_count = (int)(mc*(-1.0));
			legs[2].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 1 && Leg_Object::LegsStop(legs, 4) < 3)
			{
				legs[2].target_pos = legs[2].center_pos;
			}
			judge_Stability(mc);
		}
		else if (state == UP_FRONT_RIGHT_LEG)
		{
			legs[3].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[3].offset_count = (int)(mc*(-1.0));
			legs[3].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 2)
			{
				legs[3].target_pos = legs[3].center_pos;
			}
			judge_Stability(mc);
		}
		else if (state == ON_GROUND_FOUR_LEGS_1)
		{
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (legs[i].state != MOVE_STOP)legs[i].set_state(ON_GROUND_INTERMITTENT_CRAWL);
					if (i == 0 || i == 1)
					{

						legs[i].offset_count = (int)(mc*(0.0));
						legs[i].x_offset = 0;
						legs[i].y_offset = side_move_distance;
					}
					else
					{

						legs[i].offset_count = (int)(mc*(1.0));
						
					}
					legs[i].x_offset = -side_move_distance*sin(rot - M_PI);
					legs[i].y_offset = side_move_distance*cos(rot - M_PI);

					legs[i].next_intermittent_x_offset += legs[i].x_offset;
					legs[i].next_intermittent_y_offset += legs[i].y_offset;
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
					
				}
				body->set_state(ON_GROUND_INTERMITTENT_CRAWL);
				body->intermittent_x_offset = side_move_distance*sin(rot - M_PI);
				body->intermittent_y_offset = -side_move_distance*cos(rot - M_PI);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
				
			}
		}
		else if (state == UP_BACK_LEFT_LEG)
		{
			legs[1].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[1].offset_count = (int)(mc*(-1.0));
			legs[1].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 1 && Leg_Object::LegsStop(legs, 4) < 3)
			{
				legs[1].target_pos = legs[1].center_pos;
			}
			judge_Stability(mc);
		}
	}

	else if (dir == WALK_RIGHT)
	{
		if (state == UP_FRONT_RIGHT_LEG)state = ON_GROUND_FOUR_LEGS_1;
		else if (state == ON_GROUND_FOUR_LEGS_1)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = ON_GROUND_FOUR_LEGS_2;
		else if (state == ON_GROUND_FOUR_LEGS_2)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_FRONT_RIGHT_LEG;
		else if (state == MOVE_STABILITY)state = next_state;

		if (state == UP_FRONT_LEFT_LEG)
		{
			legs[0].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[0].offset_count = (int)(mc*(-1.0));
			legs[0].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 2)
			{
				legs[0].target_pos = legs[0].center_pos;
			}
			judge_Stability(mc);

		}
		else if (state == ON_GROUND_FOUR_LEGS_2)
		{
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (legs[i].state != MOVE_STOP)legs[i].set_state(ON_GROUND_INTERMITTENT_CRAWL);
					if (i == 1 || i == 2)
					{

						legs[i].offset_count = (int)(mc*(1.0));

					}
					else
					{

						legs[i].offset_count = (int)(mc*(0.0));

					}
					legs[i].x_offset = side_move_distance*cos(rot - M_PI*3.0/2.0);
					legs[i].y_offset = side_move_distance*sin(rot - M_PI*3.0/2.0);

					legs[i].next_intermittent_x_offset += legs[i].x_offset;
					legs[i].next_intermittent_y_offset += legs[i].y_offset;
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
					
				}
				body->set_state(ON_GROUND_INTERMITTENT_CRAWL);
				body->intermittent_x_offset = -side_move_distance*cos(rot - M_PI*3.0 / 2.0);
				body->intermittent_y_offset = -side_move_distance*sin(rot - M_PI*3.0 / 2.0);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
				
			}
		}
		else if (state == UP_BACK_RIGHT_LEG)
		{
			legs[2].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[2].offset_count = (int)(mc*(-1.0));
			legs[2].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 1 && Leg_Object::LegsStop(legs, 4) < 3)
			{
				legs[2].target_pos = legs[2].center_pos;
			}
			judge_Stability(mc);
		}
		else if (state == UP_FRONT_RIGHT_LEG)
		{
			legs[3].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[3].offset_count = (int)(mc*(-1.0));
			legs[3].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 1 && Leg_Object::LegsStop(legs, 4) < 3)
			{
				legs[3].target_pos = legs[3].center_pos;
			}
			judge_Stability(mc);
		}
		else if (state == ON_GROUND_FOUR_LEGS_1)
		{
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (legs[i].state != MOVE_STOP)legs[i].set_state(ON_GROUND_INTERMITTENT_CRAWL);
					if (i == 1 || i == 2)
					{

						legs[i].offset_count = (int)(mc*(0.0));
						
					}
					else
					{

						legs[i].offset_count = (int)(mc*(1.0));
						
					}
					legs[i].x_offset = -side_move_distance*cos(rot - M_PI*3.0 / 2.0);
					legs[i].y_offset = -side_move_distance*sin(rot - M_PI*3.0 / 2.0);

					legs[i].next_intermittent_x_offset += legs[i].x_offset;
					legs[i].next_intermittent_y_offset += legs[i].y_offset;
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
					
				}
				body->set_state(ON_GROUND_INTERMITTENT_CRAWL);
				body->intermittent_x_offset = side_move_distance*cos(rot - M_PI*3.0 / 2.0);
				body->intermittent_y_offset = side_move_distance*sin(rot - M_PI*3.0 / 2.0);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
				
			}
		}
		else if (state == UP_BACK_LEFT_LEG)
		{
			legs[1].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[1].offset_count = (int)(mc*(-1.0));
			legs[1].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 2)
			{
				legs[1].target_pos = legs[1].center_pos;
			}
			judge_Stability(mc);
		}
	}

	else if (dir == WALK_LEFT)
	{
		if (state == UP_FRONT_RIGHT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = ON_GROUND_FOUR_LEGS_1;
		else if (state == ON_GROUND_FOUR_LEGS_1)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = ON_GROUND_FOUR_LEGS_2;
		else if (state == ON_GROUND_FOUR_LEGS_2)state = UP_FRONT_RIGHT_LEG;
		else if (state == MOVE_STABILITY)state = next_state;

		if (state == UP_FRONT_LEFT_LEG)
		{
			legs[0].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[0].offset_count = (int)(mc*(-1.0));
			legs[0].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 1 && Leg_Object::LegsStop(legs, 4) < 3)
			{
				legs[0].target_pos = legs[0].center_pos;
			}
			judge_Stability(mc);

		}
		else if (state == ON_GROUND_FOUR_LEGS_2)
		{
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (legs[i].state != MOVE_STOP)legs[i].set_state(ON_GROUND_INTERMITTENT_CRAWL);
					if (i == 1 || i == 2)
					{

						legs[i].offset_count = (int)(mc*(1.0));
						
					}
					else
					{

						legs[i].offset_count = (int)(mc*(0.0));
						
					}
					legs[i].x_offset = side_move_distance*cos(rot - M_PI / 2.0);
					legs[i].y_offset = side_move_distance*sin(rot - M_PI / 2.0);

					legs[i].next_intermittent_x_offset += legs[i].x_offset;
					legs[i].next_intermittent_y_offset += legs[i].y_offset;
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
					
				}
				body->intermittent_x_offset = -side_move_distance*cos(rot - M_PI / 2.0);
				body->intermittent_y_offset = -side_move_distance*sin(rot - M_PI / 2.0);
				body->set_state(ON_GROUND_INTERMITTENT_CRAWL);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
				
			}
		}
		else if (state == UP_BACK_RIGHT_LEG)
		{
			legs[2].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[2].offset_count = (int)(mc*(-1.0));
			legs[2].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 2)
			{
				legs[2].target_pos = legs[2].center_pos;
			}
			judge_Stability(mc);
		}
		else if (state == UP_FRONT_RIGHT_LEG)
		{
			legs[3].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[3].offset_count = (int)(mc*(-1.0));
			legs[3].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 2)
			{
				legs[3].target_pos = legs[3].center_pos;
			}
			judge_Stability(mc);
		}
		else if (state == ON_GROUND_FOUR_LEGS_1)
		{
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (legs[i].state != MOVE_STOP)legs[i].set_state(ON_GROUND_INTERMITTENT_CRAWL);
					if (i == 1 || i == 2)
					{

						legs[i].offset_count = (int)(mc*(0.0));
						
					}
					else
					{

						legs[i].offset_count = (int)(mc*(1.0));
						
					}
					legs[i].x_offset = -side_move_distance*cos(rot - M_PI / 2.0);
					legs[i].y_offset = -side_move_distance*sin(rot - M_PI / 2.0);

					legs[i].next_intermittent_x_offset += legs[i].x_offset;
					legs[i].next_intermittent_y_offset += legs[i].y_offset;
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
					
				}
				body->set_state(ON_GROUND_INTERMITTENT_CRAWL);
				body->intermittent_x_offset = side_move_distance*cos(rot - M_PI / 2.0);
				body->intermittent_y_offset = side_move_distance*sin(rot - M_PI / 2.0);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
				
			}
		}
		else if (state == UP_BACK_LEFT_LEG)
		{
			legs[1].set_state(NOT_ON_GROUND_INTERMITTENT_CRAWL);
			legs[1].offset_count = (int)(mc*(-1.0));
			legs[1].setRotateStatus(d.pos, dthe, mc, sampling_time);
			if (Leg_Object::LegsStop(legs, 4) >= 1 && Leg_Object::LegsStop(legs, 4) < 3)
			{
				legs[1].target_pos = legs[1].center_pos;
			}
			judge_Stability(mc);
		}
	}

	else if (dir == WALK_ROT_PLUS)
	{

		if (state == UP_FRONT_RIGHT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_FRONT_RIGHT_LEG;
		else if (state == ON_GROUND_FOUR_LEGS_2)state = UP_FRONT_LEFT_LEG;
		else if (state == ON_GROUND_FOUR_LEGS_1)state = UP_FRONT_LEFT_LEG;
		else if (state == MOVE_STABILITY)state = next_state;



		if (state == UP_FRONT_LEFT_LEG)
		{
			legs[0].set_state(NOT_ON_GROUND_CRAWL);
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (i != 0)legs[i].set_state(ON_GROUND_CRAWL);
				}
				body->set_state(ON_GROUND_CRAWL);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
			}

			


			legs[0].offset_count = (int)(mc*(-1.5));
			legs[1].offset_count = (int)(mc*(-0.5));
			legs[2].offset_count = (int)(mc*(0.5));
			legs[3].offset_count = (int)(mc*(1.5));

			for (int i = 0; i < 4; i++)
			{
				if (Leg_Object::LegsStop(legs, 4) <= 1)
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
				else
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, true, 1.0 - (1.0 / 3.0*(double)(Leg_Object::LegsStop(legs, 4)-1)));
			}

			judge_Stability(mc);
			
			
		}
		else if (state == UP_BACK_LEFT_LEG)
		{
			legs[1].set_state(NOT_ON_GROUND_CRAWL);
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (i != 1)legs[i].set_state(ON_GROUND_CRAWL);
				}
				body->set_state(ON_GROUND_CRAWL);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
			}

			

			legs[0].offset_count = (int)(mc*(1.5));
			legs[1].offset_count = (int)(mc*(-1.5));
			legs[2].offset_count = (int)(mc*(-0.5));
			legs[3].offset_count = (int)(mc*(0.5));

			for (int i = 0; i < 4; i++)
			{
				if (Leg_Object::LegsStop(legs, 4) <= 1)
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
				else
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, true, 1.0 - (1.0 / 3.0*(double)(Leg_Object::LegsStop(legs, 4) - 1)));
			}

			judge_Stability(mc);
			
		}
		else if (state == UP_BACK_RIGHT_LEG)
		{
			legs[2].set_state(NOT_ON_GROUND_CRAWL);
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (i != 2)legs[i].set_state(ON_GROUND_CRAWL);
				}
				body->set_state(ON_GROUND_CRAWL);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
			}

			

			legs[0].offset_count = (int)(mc*(0.5));
			legs[1].offset_count = (int)(mc*(1.5));
			legs[2].offset_count = (int)(mc*(-1.5));
			legs[3].offset_count = (int)(mc*(-0.5));

			for (int i = 0; i < 4; i++)
			{
				if (Leg_Object::LegsStop(legs, 4) <= 1)
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
				else
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, true, 1.0 - (1.0 / 3.0*(double)(Leg_Object::LegsStop(legs, 4) - 1)));
			}

			judge_Stability(mc);
			

		}
		else if (state == UP_FRONT_RIGHT_LEG)
		{
			legs[3].set_state(NOT_ON_GROUND_CRAWL);
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (i != 3)legs[i].set_state(ON_GROUND_CRAWL);
				}
				body->set_state(ON_GROUND_CRAWL);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
			}

			
			legs[0].offset_count = (int)(mc*(-0.5));
			legs[1].offset_count = (int)(mc*(0.5));
			legs[2].offset_count = (int)(mc*(1.5));
			legs[3].offset_count = (int)(mc*(-1.5));

			for (int i = 0; i < 4; i++)
			{
				if (Leg_Object::LegsStop(legs, 4) <= 1)
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
				else
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, true, 1.0 - (1.0 / 3.0*(double)(Leg_Object::LegsStop(legs, 4) - 1)));
			}

			judge_Stability(mc);
			

		}
	}

	else if (dir == WALK_ROT_MINUS)
	{

		if (state == UP_FRONT_RIGHT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_FRONT_RIGHT_LEG;
		else if (state == ON_GROUND_FOUR_LEGS_1)state = UP_FRONT_LEFT_LEG;
		else if (state == ON_GROUND_FOUR_LEGS_2)state = UP_FRONT_LEFT_LEG;
		else if (state == MOVE_STABILITY)state = next_state;



		if (state == UP_FRONT_LEFT_LEG)
		{
			legs[0].set_state(NOT_ON_GROUND_CRAWL);
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (i != 0)legs[i].set_state(ON_GROUND_CRAWL);
				}
				body->set_state(ON_GROUND_CRAWL);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
			}

			

			legs[0].offset_count = (int)(mc*(-1.5));
			legs[1].offset_count = (int)(mc*(1.5));
			legs[2].offset_count = (int)(mc*(0.5));
			legs[3].offset_count = (int)(mc*(-0.5));

			for (int i = 0; i < 4; i++)
			{
				if (Leg_Object::LegsStop(legs, 4) <= 1)
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
				else
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, true, 1.0 - (1.0 / 3.0*(double)(Leg_Object::LegsStop(legs, 4) - 1)));
			}

			judge_Stability(mc);
			
		}
		else if (state == UP_BACK_LEFT_LEG)
		{
			legs[1].set_state(NOT_ON_GROUND_CRAWL);
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (i != 1)legs[i].set_state(ON_GROUND_CRAWL);
				}
				body->set_state(ON_GROUND_CRAWL);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
			}

			

			legs[0].offset_count = (int)(mc*(-0.5));
			legs[1].offset_count = (int)(mc*(-1.5));
			legs[2].offset_count = (int)(mc*(1.5));
			legs[3].offset_count = (int)(mc*(0.5));

			for (int i = 0; i < 4; i++)
			{
				if (Leg_Object::LegsStop(legs, 4) <= 1)
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
				else
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, true, 1.0 - (1.0 / 3.0*(double)(Leg_Object::LegsStop(legs, 4) - 1)));
			}

			judge_Stability(mc);
			
		}
		else if (state == UP_BACK_RIGHT_LEG)
		{
			legs[2].set_state(NOT_ON_GROUND_CRAWL);
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (i != 2)legs[i].set_state(ON_GROUND_CRAWL);
				}
				body->set_state(ON_GROUND_CRAWL);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
			}

			

			legs[0].offset_count = (int)(mc*(0.5));
			legs[1].offset_count = (int)(mc*(-0.5));
			legs[2].offset_count = (int)(mc*(-1.5));
			legs[3].offset_count = (int)(mc*(1.5));

			for (int i = 0; i < 4; i++)
			{
				if (Leg_Object::LegsStop(legs, 4) <= 1)
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
				else
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, true, 1.0 - (1.0 / 3.0*(double)(Leg_Object::LegsStop(legs, 4) - 1)));
			}

			judge_Stability(mc);
			

		}
		else if (state == UP_FRONT_RIGHT_LEG)
		{
			legs[3].set_state(NOT_ON_GROUND_CRAWL);
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if (i != 3)legs[i].set_state(ON_GROUND_CRAWL);
				}
				body->set_state(ON_GROUND_CRAWL);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
			}

			
			legs[0].offset_count = (int)(mc*(1.5));
			legs[1].offset_count = (int)(mc*(0.5));
			legs[2].offset_count = (int)(mc*(-0.5));
			legs[3].offset_count = (int)(mc*(-1.5));

			for (int i = 0; i < 4; i++)
			{
				if (Leg_Object::LegsStop(legs, 4) <= 1)
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
				else
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, true, 1.0 - (1.0 / 3.0*(double)(Leg_Object::LegsStop(legs, 4) - 1)));
			}

			judge_Stability(mc);
			

		}
	}
}

