/*!
* @file  CrawlGait.cpp
* @brief クロール歩容制御クラス
*
*/


#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "CrawlGait.h"






#define DEFAULT_SAMPLING_TIME 0.1


#define MIN_VELOCITY_VX 0.0001
#define MIN_VELOCITY_VY 0.0001
#define MIN_VELOCITY_TH 0.0001


#define MIN_CALC_VALUE 0.000001
#define DEFAULT_MIN_MARGIN -0.001


/**
*@brief コンストラクタ
* @param ls 脚のリスト
*/
CrawlGait::CrawlGait(Leg_Object *ls, Body_Object *bo) : GaitBase(ls, bo)
{
	legs = ls;

	sampling_time = DEFAULT_SAMPLING_TIME;

	current_time = 0;

	state = UP_FRONT_RIGHT_LEG;
	dir = WALK_STOP;

	min_margin = DEFAULT_MIN_MARGIN;
}


/**
*@brief 歩行更新
* @param vx 速度(X)
* @param vy 速度(Y)
* @param dthe 回転速度
* @param sd 歩幅
*/
void CrawlGait::walk(double vx, double vy, double dthe, double sd)
{
	if (abs(vx) < MIN_VELOCITY_VX && abs(vy) < MIN_VELOCITY_VY && abs(dthe) < MIN_VELOCITY_TH)
	{
		return;
	}
	else if (abs(dthe) < MIN_VELOCITY_TH)
	{
		dthe = MIN_VELOCITY_TH;
	}

	for (int i = 0; i < 4; i++)
	{
		legs[i].update();
	}
	body->update();

	

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
	int mc = (int)((stride / 3.0) / (L_max * abs(dthe) * sampling_time));
	//int mc = (int)((stride / 4.0) / (L * abs(dthe) * sampling_time) * (step_time / 4.0));



	//std::cout << mc << "\t" << dthe << std::endl;
	//std::cout << dir << "\t" << d.dir << std::endl;
	for (int i = 0; i < 4; i++)
	{
		legs[i].update_status(dthe, mc);
		if (dir == d.dir)
		{
			
			legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, false);

		}

	}
	//std::cout << dir << "\t" << d.dir << std::endl;
	
	body->update_status(dthe, mc);
	//std::cout << dir << "\t" << d.dir << "\t" << dthe << "\t" << L_max << std::endl;
	if (dir == d.dir)
	{
		//std::cout << "update" << std::endl;
		body->setRotateStatus(d.pos, dthe, mc, sampling_time, false);
	}

	for (int i = 0; i < 4; i++)
	{
		if (legs[i].state != MOVE_PAUSE && legs[i].state != MOVE_STOP)return;
	}
	//double c_pos = fmod(current_time,3.0);
	//std::cout << mc << "\t" << L << "\t" << L_max << std::endl;
	//std::cout << p(0) << "\t" << p(1) << std::endl;


	/*for (int i = 0; i < 4; i++)
	{
	if (legs[i].state == MOVE_STOP)
	{
	legs[i].setRotateStatus(p, dthe, mc, sampling_time, step_time);
	}
	}*/


	//std::cout << dir << std::endl;
	//std::cout << pos_distance << "\t" << leg_distance << std::endl;
	//std::cout << offset_angle << "\t" << leg_angle[0] << "\t" << leg_angle[1] << "\t" << leg_angle[2] << "\t" << leg_angle[3] << std::endl;


	//std::cout << dir << std::endl;

	
	if (dir != d.dir)
	{
		for (int i = 0; i < 4; i++)
		{
			legs[i].set_state(MOVE_STOP);
			legs[i].count = 0;
			
		}
		body->set_state(MOVE_STOP);
		body->count = 0;
		
	}
	dir = d.dir;

	

	if (dir == WALK_FORWORD)
	{
		
		//state = (CrawlGaitState)(state % 4 + 1);
		//if (state == 4)state = UP_FRONT_LEFT_LEG;
		if (state == UP_FRONT_RIGHT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_FRONT_RIGHT_LEG;
		else if (state == MOVE_STABILITY)state = next_state;

		
		if (state == UP_FRONT_LEFT_LEG)
		{
			legs[0].set_state(NOT_ON_GROUND_CRAWL);
			if (Leg_Object::LegsStop(legs, 4) == 0)
			{
				for (int i = 0; i < 4; i++)
				{
					if(i!=0)legs[i].set_state(ON_GROUND_CRAWL);
				}
				body->set_state(ON_GROUND_CRAWL);
				body->setRotateStatus(d.pos, dthe, mc, sampling_time);
			}
			
			
			legs[0].offset_count = (int)((double)mc*(-1.5));
			legs[1].offset_count = (int)((double)mc*(1.5));
			legs[2].offset_count = (int)((double)mc*(-0.5));
			legs[3].offset_count = (int)((double)mc*(0.5));

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
			
			legs[0].offset_count = (int)((double)mc*(-0.5));
			legs[1].offset_count = (int)((double)mc*(-1.5));
			legs[2].offset_count = (int)((double)mc*(0.5));
			legs[3].offset_count = (int)((double)mc*(1.5));

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
			
			legs[0].offset_count = (int)((double)mc*(1.5));
			legs[1].offset_count = (int)((double)mc*(0.5));
			legs[2].offset_count = (int)((double)mc*(-1.5));
			legs[3].offset_count = (int)((double)mc*(-0.5));

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
			
			legs[0].offset_count = (int)((double)mc*(0.5));
			legs[1].offset_count = (int)((double)mc*(-0.5));
			legs[2].offset_count = (int)((double)mc*(1.5));
			legs[3].offset_count = (int)((double)mc*(-1.5));

			for (int i = 0; i < 4; i++)
			{
				if (Leg_Object::LegsStop(legs, 4) <= 1)
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time);
				else
					legs[i].setRotateStatus(d.pos, dthe, mc, sampling_time, true, 1.0 - (1.0 / 3.0*(double)(Leg_Object::LegsStop(legs, 4) - 1)));
			}
			judge_Stability(mc);
		

		}
		//std::cout << mc << std::endl;
		/*if (state == UP_FRONT_LEFT_LEG)
		{
		for (int i = 0; i < 4; i++)
		{
		if (i == 0)legs[i].state = NOT_ON_GROUND_CRAWL;
		else legs[i].state = ON_GROUND_CRAWL;
		}

		legs[0].offset_count = (int)(mc*(1.5));
		legs[1].offset_count = (int)(mc*(0.5));
		legs[2].offset_count = (int)(mc*(-1.5));
		legs[3].offset_count = (int)(mc*(-0.5));
		}
		else if (state == UP_BACK_LEFT_LEG)
		{
		for (int i = 0; i < 4; i++)
		{
		if (i == 1)legs[i].state = NOT_ON_GROUND_CRAWL;
		else legs[i].state = ON_GROUND_CRAWL;
		}

		legs[0].offset_count = (int)(mc*(-1.5));
		legs[1].offset_count = (int)(mc*(1.5));
		legs[2].offset_count = (int)(mc*(-0.5));
		legs[3].offset_count = (int)(mc*(0.5));

		}
		else if (state == UP_BACK_RIGHT_LEG)
		{
		for (int i = 0; i < 4; i++)
		{
		if (i == 2)legs[i].state = NOT_ON_GROUND_CRAWL;
		else legs[i].state = ON_GROUND_CRAWL;
		}

		legs[0].offset_count = (int)(mc*(0.5));
		legs[1].offset_count = (int)(mc*(-0.5));
		legs[2].offset_count = (int)(mc*(1.5));
		legs[3].offset_count = (int)(mc*(-1.5));

		}
		else if (state == UP_FRONT_RIGHT_LEG)
		{
		for (int i = 0; i < 4; i++)
		{
		if (i == 3)legs[i].state = NOT_ON_GROUND_CRAWL;
		else legs[i].state = ON_GROUND_CRAWL;
		}
		legs[0].offset_count = (int)(mc*(-0.5));
		legs[1].offset_count = (int)(mc*(-1.5));
		legs[2].offset_count = (int)(mc*(0.5));
		legs[3].offset_count = (int)(mc*(1.5));



		}*/


	}
	else if (dir == WALK_BACK)
	{

		if (state == UP_FRONT_RIGHT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_FRONT_RIGHT_LEG;
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

			
			legs[0].offset_count = (int)(mc*(-0.5));
			legs[1].offset_count = (int)(mc*(0.5));
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

			
			legs[0].offset_count = (int)(mc*(0.5));
			legs[1].offset_count = (int)(mc*(1.5));
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

	else if (dir == WALK_RIGHT)
	{
		if (state == UP_FRONT_RIGHT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_FRONT_RIGHT_LEG;
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
			legs[1].offset_count = (int)(mc*(0.5));
			legs[2].offset_count = (int)(mc*(1.5));
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



			legs[0].offset_count = (int)(mc*(0.5));
			legs[1].offset_count = (int)(mc*(-1.5));
			legs[2].offset_count = (int)(mc*(-0.5));
			legs[3].offset_count = (int)(mc*(1.5));

			legs[1].setRotateStatus(d.pos, dthe, mc, sampling_time);
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


			legs[0].offset_count = (int)(mc*(-0.5));
			legs[1].offset_count = (int)(mc*(1.5));
			legs[2].offset_count = (int)(mc*(-1.5));
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
			legs[1].offset_count = (int)(mc*(-0.5));
			legs[2].offset_count = (int)(mc*(0.5));
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
		/*
		if (state == UP_FRONT_RIGHT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_FRONT_RIGHT_LEG;
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
			legs[1].offset_count = (int)(mc*(0.5));
			legs[2].offset_count = (int)(mc*(-0.5));
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

			

			legs[0].offset_count = (int)(mc*(0.5));
			legs[1].offset_count = (int)(mc*(-1.5));
			legs[2].offset_count = (int)(mc*(1.5));
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

			

			legs[0].offset_count = (int)(mc*(1.5));
			legs[1].offset_count = (int)(mc*(-0.5));
			legs[2].offset_count = (int)(mc*(-1.5));
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
			legs[1].offset_count = (int)(mc*(1.5));
			legs[2].offset_count = (int)(mc*(0.5));
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
		*/
	}

	else if (dir == WALK_LEFT)
	{
		if (state == UP_FRONT_RIGHT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_FRONT_RIGHT_LEG;
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
			legs[1].offset_count = (int)(mc*(0.5));
			legs[2].offset_count = (int)(mc*(-0.5));
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



			legs[0].offset_count = (int)(mc*(0.5));
			legs[1].offset_count = (int)(mc*(-1.5));
			legs[2].offset_count = (int)(mc*(1.5));
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



			legs[0].offset_count = (int)(mc*(1.5));
			legs[1].offset_count = (int)(mc*(-0.5));
			legs[2].offset_count = (int)(mc*(-1.5));
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
			legs[1].offset_count = (int)(mc*(1.5));
			legs[2].offset_count = (int)(mc*(0.5));
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
		/*
		if (state == UP_FRONT_RIGHT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_FRONT_RIGHT_LEG;
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
			legs[1].offset_count = (int)(mc*(0.5));
			legs[2].offset_count = (int)(mc*(1.5));
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

			

			legs[0].offset_count = (int)(mc*(0.5));
			legs[1].offset_count = (int)(mc*(-1.5));
			legs[2].offset_count = (int)(mc*(-0.5));
			legs[3].offset_count = (int)(mc*(1.5));

			legs[1].setRotateStatus(d.pos, dthe, mc, sampling_time);
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

			
			legs[0].offset_count = (int)(mc*(-0.5));
			legs[1].offset_count = (int)(mc*(1.5));
			legs[2].offset_count = (int)(mc*(-1.5));
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
			legs[1].offset_count = (int)(mc*(-0.5));
			legs[2].offset_count = (int)(mc*(0.5));
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
		*/
	}

	else if (dir == WALK_ROT_PLUS)
	{

		if (state == UP_FRONT_RIGHT_LEG)state = UP_FRONT_LEFT_LEG;
		else if (state == UP_FRONT_LEFT_LEG)state = UP_BACK_LEFT_LEG;
		else if (state == UP_BACK_LEFT_LEG)state = UP_BACK_RIGHT_LEG;
		else if (state == UP_BACK_RIGHT_LEG)state = UP_FRONT_RIGHT_LEG;
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
