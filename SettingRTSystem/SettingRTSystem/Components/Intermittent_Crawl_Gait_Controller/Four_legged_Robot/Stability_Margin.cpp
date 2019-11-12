/*!
* @file  Stability_Margin.cpp
* @brief 安定余裕計算クラス
*
*/


#define _USE_MATH_DEFINES
#include <math.h>
#include <fstream>
#include "Stability_Margin.h"








#define MIN_CALC_VALUE 0.000001


/**
*@brief コンストラクタ
*/
Stability_Margin::Stability_Margin()
{

}

/**
*@brief 全脚から安定余裕計算
*@param legs 脚のリスト
*/
Stability_Margin Stability_Margin::calc_stability_margin(Leg_Object *legs, bool ne, bool tf)
{
	//std::cout << legs[1].current_pos(0) << "\t" << legs[2].current_pos(0) << std::endl;
	if (legs[0].onGround() && legs[1].onGround() && legs[2].onGround() && legs[3].onGround())
	{
		Stability_Margin d01_b = calc_distance(legs[0].current_pos, legs[1].current_pos, STB_Y_MINUS, ne);
		Stability_Margin d12_b = calc_distance(legs[1].current_pos, legs[2].current_pos, STB_X_PLUS, ne);
		Stability_Margin d23_b = calc_distance(legs[2].current_pos, legs[3].current_pos, STB_Y_PLUS, ne);
		Stability_Margin d30_b = calc_distance(legs[3].current_pos, legs[0].current_pos, STB_X_MINUS, ne);

		

		Stability_Margin min_value = d01_b;


		if (min_value.getDistance(ne) > d12_b.getDistance(ne))
		{
			min_value = d12_b;
		}
		if (min_value.getDistance(ne) > d23_b.getDistance(ne))
		{
			min_value = d23_b;
		}
		if (min_value.getDistance(ne) > d30_b.getDistance(ne))
		{
			min_value = d30_b;
		}

		if (tf)
		{
			Stability_Margin d01_a = calc_distance(legs[0].target_pos, legs[1].target_pos, STB_Y_MINUS, ne);
			Stability_Margin d12_a = calc_distance(legs[1].target_pos, legs[2].target_pos, STB_X_PLUS, ne);
			Stability_Margin d23_a = calc_distance(legs[2].target_pos, legs[3].target_pos, STB_Y_PLUS, ne);
			Stability_Margin d30_a = calc_distance(legs[3].target_pos, legs[0].target_pos, STB_X_MINUS, ne);

			if (min_value.getDistance(ne) > d01_a.getDistance(ne))
			{
				min_value = d01_a;
			}
			if (min_value.getDistance(ne) > d12_a.getDistance(ne))
			{
				min_value = d12_a;
			}
			if (min_value.getDistance(ne) > d23_a.getDistance(ne))
			{
				min_value = d23_a;
			}
			if (min_value.getDistance(ne) > d30_a.getDistance(ne))
			{
				min_value = d30_a;
			}
		}

		return min_value;
		//std::cout << legs[0].current_pos(1) << "\t" << legs[1].current_pos(1) << std::endl;
		//std::cout << d01 << "\t" << d12 << "\t" << d23 << "\t" << d30 << std::endl;


	}
	else if (!legs[0].onGround())
	{
		Stability_Margin d12_b = calc_distance(legs[1].current_pos, legs[2].current_pos, STB_X_PLUS, ne);
		Stability_Margin d23_b = calc_distance(legs[2].current_pos, legs[3].current_pos, STB_Y_PLUS, ne);
		Stability_Margin d31_b = calc_distance(legs[3].current_pos, legs[1].current_pos, STB_X_MINUS, ne);

		
		//std::cout << "distance:" << d12.distance << "\t" << d23.distance << "\t" << d31.distance << std::endl;
		//std::cout << legs[1].current_pos(0) << "\t" << legs[2].current_pos(0) << std::endl;
		Stability_Margin min_value = d12_b;
		if (min_value.getDistance(ne) > d23_b.getDistance(ne))
		{
			min_value = d23_b;
		}
		if (min_value.getDistance(ne) > d31_b.getDistance(ne))
		{
			min_value = d31_b;
		}

		if (tf)
		{
			Stability_Margin d12_a = calc_distance(legs[1].target_pos, legs[2].target_pos, STB_X_PLUS, ne);
			Stability_Margin d23_a = calc_distance(legs[2].target_pos, legs[3].target_pos, STB_Y_PLUS, ne);
			Stability_Margin d31_a = calc_distance(legs[3].target_pos, legs[1].target_pos, STB_X_MINUS, ne);
			if (min_value.getDistance(ne) > d12_a.getDistance(ne))
			{
				min_value = d12_a;
			}
			if (min_value.getDistance(ne) > d23_a.getDistance(ne))
			{
				min_value = d23_a;
			}
			if (min_value.getDistance(ne) > d31_a.getDistance(ne))
			{
				min_value = d31_a;
			}
		}


		return min_value;
	}
	else if (!legs[1].onGround())
	{
		Stability_Margin d02_b = calc_distance(legs[0].current_pos, legs[2].current_pos, STB_X_PLUS, ne);
		Stability_Margin d23_b = calc_distance(legs[2].current_pos, legs[3].current_pos, STB_Y_PLUS, ne);
		Stability_Margin d30_b = calc_distance(legs[3].current_pos, legs[0].current_pos, STB_X_MINUS, ne);

		

		Stability_Margin min_value = d02_b;
		if (min_value.getDistance(ne) > d23_b.getDistance(ne))
		{
			min_value = d23_b;
		}
		if (min_value.getDistance(ne) > d30_b.getDistance(ne))
		{
			min_value = d30_b;
		}

		if (tf)
		{
			Stability_Margin d02_a = calc_distance(legs[0].target_pos, legs[2].target_pos, STB_X_PLUS, ne);
			Stability_Margin d23_a = calc_distance(legs[2].target_pos, legs[3].target_pos, STB_Y_PLUS, ne);
			Stability_Margin d30_a = calc_distance(legs[3].target_pos, legs[0].target_pos, STB_X_MINUS, ne);

			if (min_value.getDistance(ne) > d02_a.getDistance(ne))
			{
				min_value = d02_a;
			}
			if (min_value.getDistance(ne) > d23_a.getDistance(ne))
			{
				min_value = d23_a;
			}
			if (min_value.getDistance(ne) > d30_a.getDistance(ne))
			{
				min_value = d30_a;
			}
		}

		return min_value;
	}
	else if (!legs[2].onGround())
	{
		Stability_Margin d01_b = calc_distance(legs[0].current_pos, legs[1].current_pos, STB_Y_MINUS, ne);
		Stability_Margin d13_b = calc_distance(legs[1].current_pos, legs[3].current_pos, STB_X_PLUS, ne);
		Stability_Margin d30_b = calc_distance(legs[3].current_pos, legs[0].current_pos, STB_X_MINUS, ne);

		

		Stability_Margin min_value = d01_b;
		if (min_value.getDistance(ne) > d13_b.getDistance(ne))
		{
			min_value = d13_b;
		}
		if (min_value.getDistance(ne) > d30_b.getDistance(ne))
		{
			min_value = d30_b;
		}


		if (tf)
		{
			Stability_Margin d01_a = calc_distance(legs[0].target_pos, legs[1].target_pos, STB_Y_MINUS, ne);
			Stability_Margin d13_a = calc_distance(legs[1].target_pos, legs[3].target_pos, STB_X_PLUS, ne);
			Stability_Margin d30_a = calc_distance(legs[3].target_pos, legs[0].target_pos, STB_X_MINUS, ne);

			if (min_value.getDistance(ne) > d01_a.getDistance(ne))
			{
				min_value = d01_a;
			}
			if (min_value.getDistance(ne) > d13_a.getDistance(ne))
			{
				min_value = d13_a;
			}
			if (min_value.getDistance(ne) > d30_a.getDistance(ne))
			{
				min_value = d30_a;
			}
		}

		return min_value;
	}
	else if (!legs[3].onGround())
	{
		Stability_Margin d01_b = calc_distance(legs[0].current_pos, legs[1].current_pos, STB_Y_MINUS, ne);
		Stability_Margin d12_b = calc_distance(legs[1].current_pos, legs[2].current_pos, STB_X_PLUS, ne);
		Stability_Margin d20_b = calc_distance(legs[2].current_pos, legs[0].current_pos, STB_X_MINUS, ne);

		

		Stability_Margin min_value = d01_b;
		if (min_value.getDistance(ne) > d12_b.getDistance(ne))
		{
			min_value = d12_b;
		}
		if (min_value.getDistance(ne) > d20_b.getDistance(ne))
		{
			min_value = d20_b;
		}

		if (tf)
		{
			Stability_Margin d01_a = calc_distance(legs[0].target_pos, legs[1].target_pos, STB_Y_MINUS, ne);
			Stability_Margin d12_a = calc_distance(legs[1].target_pos, legs[2].target_pos, STB_X_PLUS, ne);
			Stability_Margin d20_a = calc_distance(legs[2].target_pos, legs[0].target_pos, STB_X_MINUS, ne);
			if (min_value.getDistance(ne) > d01_a.getDistance(ne))
			{
				min_value = d01_a;
			}
			if (min_value.getDistance(ne) > d12_a.getDistance(ne))
			{
				min_value = d12_a;
			}
			if (min_value.getDistance(ne) > d20_a.getDistance(ne))
			{
				min_value = d20_a;
			}
		}

		return min_value;
	}
	return Stability_Margin();
}


/**
*@brief 重心位置と線の距離を計算
*@param pos0 脚0の位置
*@param pos1 脚1の位置
*@param dir 安定になる重心位置の方向
*/
Stability_Margin Stability_Margin::calc_distance(Vector3d pos0, Vector3d pos1, Stability_Direction dir, bool ne)
{
	Stability_Margin s = Stability_Margin();
	s.stb_dir = dir;
	

	if (abs(pos1(0) - pos0(0)) > MIN_CALC_VALUE && abs(pos1(1) - pos0(1)) > MIN_CALC_VALUE)
	{
		double a = -(pos1(1) - pos0(1)) / (pos1(0) - pos0(0));
		double b = 1;
		double c = -b * pos1(1) - a * pos1(0);

		s.distance = abs(c) / (sqrt(a*a + b*b));



		double at = -1.0 / a;
		double bt = 1;
		double ct = 0;


		s.slope = at;

		if (abs(a - at) < MIN_CALC_VALUE)
		{
			s.distance = 0;
		}
		else
		{

			double xt = (c - ct) / (-(a - at));
			double yt = -a * xt - c;





			if (-xt > 0 && dir == STB_X_PLUS)
			{

			}
			else if (-xt <= 0 && dir == STB_X_PLUS)
			{
				s.distance = -s.distance;
			}
			else if (-xt > 0 && dir == STB_X_MINUS)
			{
				s.distance = -s.distance;
			}
			else if (-xt <= 0 && dir == STB_X_MINUS)
			{

			}
			else if (-yt > 0 && dir == STB_Y_PLUS)
			{

			}
			else if (-yt <= 0 && dir == STB_Y_PLUS)
			{
				s.distance = -s.distance;
			}
			else if (-yt > 0 && dir == STB_Y_MINUS)
			{
				s.distance = -s.distance;
			}
			else if (-yt <= 0 && dir == STB_Y_MINUS)
			{

			}
			//std::cout << "test\t" << s.distance << "\t" << xt << "\t" << yt << "\t" << pos0(0) << "\t" << pos1(0) << std::endl;
		}
		
	}
	else if (abs(pos1(0) - pos0(0)) < MIN_CALC_VALUE)
	{
		if (dir == STB_X_PLUS)
		{
			s.distance = -pos1(0);
		}
		else
		{
			s.distance = pos1(0);
		}
		
	}
	else
	{
		if (dir == STB_Y_PLUS)
		{
			s.distance = -pos1(1);
		}
		else
		{
			s.distance = pos1(1);
		}
	}

	if (ne)
	{
		Vector3d v01 = pos1 - pos0;
		Vector3d v01_norm = v01.normalized();
		Vector3d v0b = - pos0;
		double d = v0b.dot(v01_norm);
		Vector3d v0d = d * v01_norm;
		Vector3d vdp = v0b - v0d;
		double l_max = vdp.norm();
		double l = vdp(2);

		s.ne_distance = l_max - l;
		if (s.distance < 0)
		{
			s.ne_distance = -s.ne_distance;
		}
	}
	//std::cout << s.ne_distance << std::endl;
	return s;
}

double Stability_Margin::getDistance(bool ne)
{
	if (ne)
	{
		return ne_distance;
	}
	else
	{
		return distance;
	}
}

