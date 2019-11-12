/*!
 * @file  RTMath.h
 * @brief 数値計算関連の関数
 *
 */


#ifndef RTMATH_H
#define RTMATH_H

#define _USE_MATH_DEFINES
#include <cmath>
#include <chrono>
#include <vector>
#include <coil/stringutil.h>
#include <cmath>
#include <random>

using Duration = std::chrono::nanoseconds;

/**
 * @class ValueAndTime
*@brief 時間とその時間でのデータを格納するクラス
*Tは格納するデータの型
*/
template <class T>
class ValueAndTime
{
public:
	ValueAndTime(std::chrono::time_point<std::chrono::system_clock> tp,
				 T value) : m_tp(tp), m_value(value){}
	std::chrono::time_point<std::chrono::system_clock> m_tp;
	T m_value;
};


/**
 * @class RTMath
*@brief 連続的に入力されるデータ、時間を管理するクラス
*Tは格納するデータの型
*/
template <class T>
class RTMath
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTMath()
	{
		samplingTime_low = std::chrono::microseconds(1);
		setSamplingTime(std::chrono::milliseconds(10));
		realTime = false;
		resetTime();
	};
	/**
	*@brief 刻み幅設定
	* @param s 刻み幅
	*/
	virtual void setSamplingTime(Duration s)
	{
		if(samplingTime_low < s)
		{
			samplingTime = s;
		}
		else
		{
			samplingTime = samplingTime_low;
		}
	};
	/**
	*@brief 実時間でデータを保存するか、シミュレーション時間で保存するか設定
	* @param s trueで実時間、falseでシミュレーション時間
	*/
	virtual void setConfig(bool c)
	{
		realTime = c;
	};
	/**
	*@brief 最新のデータと前回入力したデータとの時間差を取得
	* @param ans 時間差(シミュレーション時間の時は設定した刻み幅)
	* @return 前回のデータが存在しない場合はfalse、それ以外はture
	*/
	virtual bool getDiffTime(Duration &ans)
	{
		if(realTime)
		{
			if(dataList.size() < 2)
			{
				return false;
			}
			else
			{
				ans = dataList[dataList.size()-1].m_tp - dataList[dataList.size()-2].m_tp;
			}
		}
		else
		{
			ans = samplingTime;
		}
		return true;
	};
	/**
	*@brief 時間、データリストを初期化する
	*/
	virtual void resetTime()
	{
		dataList.clear();
		first_time = std::chrono::system_clock::now();
		now_time = std::chrono::seconds(0);
	};
	/**
	*@brief データを追加
	* @param data データ
	*/
	virtual void addData(T data)
	{
		dataList.emplace_back(std::chrono::system_clock::now(), data);
	};
	/**
	*@brief 現在の時間を取得
	* @return 時間
	*/
	virtual Duration getTime()
	{
		if(realTime)
		{
			now_time = std::chrono::system_clock::now() - first_time;
		}
		else
		{
			now_time += samplingTime;
		}
		return now_time;
	};
	Duration samplingTime_low;
	std::chrono::time_point<std::chrono::system_clock> first_time;
	Duration now_time;
	bool realTime;
	Duration samplingTime;
	std::vector<ValueAndTime<T>> dataList;
};


/**
 * @class RTIntegrator
*@brief データを積分をする
*Tは格納するデータの型
*/
template <class T>
class RTIntegrator : public RTMath<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTIntegrator()
	{
		initialCondition = 0;
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		RTMath<T>::resetTime();
		intValue = initialCondition;
	};
	/**
	*@brief 積分値の初期値を設定
	* @param c 初期値
	*/
	void setInitialCondition(T c)
	{
		initialCondition = c;
		intValue = initialCondition;
	};
	/**
	*@brief 積分値を取得
	* @param ans 積分値
	* @return 前回のデータが存在しない場合はfalse、それ以外はture
	*/
	bool calc(T &ans)
	{
		if(RTMath<T>::dataList.size() < 2)
		{
			return false;
		}
		Duration stepTime;
		if(!RTMath<T>::getDiffTime(stepTime))
		{
			return false;
		};
		
		T tmp = (RTMath<T>::dataList[RTMath<T>::dataList.size()-1].m_value + RTMath<T>::dataList[RTMath<T>::dataList.size()-2].m_value)*stepTime/2;
		intValue += tmp;
		ans = intValue;
		return true;
	};
	T intValue;
	T initialCondition;
};



/**
 * @class RTDerivative
*@brief データを微分をする
*Tは格納するデータの型
*/
template <class T>
class RTDerivative : public RTMath<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTDerivative()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};
	/**
	*@brief 微分値を取得
	* @param ans 微分値
	* @return 前回のデータが存在しない場合はfalse、それ以外はture
	*/
	bool calc(T &ans)
	{
		if(RTMath<T>::dataList.size() < 2)
		{
			return false;
		}
		Duration stepTime;
		if(!RTMath<T>::getDiffTime(stepTime))
		{
			return false;
		};
		
		//T tmp = (dataList[dataList.size()-1].m_value + dataList[dataList.size()-2].m_value)*stepTime/2;
		ans = (RTMath<T>::dataList[RTMath<T>::dataList.size()-1].m_value - RTMath<T>::dataList[RTMath<T>::dataList.size()-2].m_value)/stepTime;
		return true;
	};
};


/**
 * @class RTBacklash
*@brief 遊びを持つシステム(現在値の不感帯の幅内であれば出力は変化しません)
*Tは格納するデータの型
*/
template <class T>
class RTBacklash
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTBacklash()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		now_Output = m_initialOutput;
	};
	/**
	*@brief 不感帯の幅を設定
	* @param io 遊びの量
	*/
	void setDeadbandWidth(T width)
	{
		m_width = width;
	};
	/**
	*@brief 初期値を設定
	* @param io 初期値
	*/
	void setInitialOutput(T io)
	{
		m_initialOutput = io;
		//now_Output = io;
	};
	/**
	*@brief 遊びのあるシステムに入力したときの出力を取得
	* @param input 入力値
	* @return 出力値
	*/
	T calc(T input)
	{
		double low_output = now_Output-m_width/(T)2.0;
		double high_output = now_Output+m_width/(T)2.0;
		//std::cout << high_output << "\t" << low_output << "\t" << m_width << std::endl;
		if(input < high_output && input > low_output)
		{

		}
		else if(input > high_output)
		{
			now_Output = input - m_width/(T)2.0;
		}
		else if(input < low_output)
		{
			now_Output = input + m_width/(T)2.0;
		}
		return now_Output;
	};
	T now_Output;
	T m_width;
	T m_initialOutput;
};


/**
*@brief 設定した範囲内に出力を制限します
*Tは入力、出力のデータの型
* @param input 入力
* @param upperLimit 最大値
* @param lowerLimit 最小値
* @return 出力
*/
template <class T>
T RTSaturation(T input, T upperLimit, T lowerLimit)
{
	return std::min(upperLimit, std::max(lowerLimit, input));
};

/**
*@brief 入力した文字列を","で分割して、分割した文字列を設定したデータ型に変換して出力
*Tは出力するデータリストの各データの型
* @param str 入力文字列
* @param ans 出力するデータリスト
* @return trueで成功、falseで失敗
*/
template <class T>
bool getValueInString(std::string str, std::vector<T> &ans)
{
	str = coil::eraseBlank(std::move(str));
	ans.clear();
	coil::vstring va = coil::split(str, ",");
	if(va.size() == 0)
	{
		return false;
	}
	for (auto const& it : va)
	{
		T value;
		bool result = coil::stringTo<T>(value, it.c_str());
		if(result)
		{
			ans.push_back(std::move(value));
		}
		else
		{
			return false;
		}
	}
	return true;
};


/**
*@brief 入力したデータリストから指定する番号の値を出力
*Tは入力するデータリストの各データの型
* @param input データリスト
* @param num 番号
* @param ans 出力
* @return データ数が0の時はfalse、それ以外はtrue
*/
template <class T>
bool getValueInList(std::vector<T> input, int num, T &ans)
{
	if(input.size() == 0)
	{
		return false;
	}

	if((int)input.size()-1 < num)
	{
		ans = input[0];
	}
	else
	{
		ans = input[num];
	}
	return true;
};

/**
*@brief 零点で不連続、それ以外は線形ゲインの出力
*Tは入力、出力するデータの型
* @param input 入力データ
* @param offset オフセット
* @param gain ゲイン
* @return 出力
*/
template <class T>
T RTCoulombAndViscousFriction(T input, T offset, T gain)
{
	if(input < 0)
	{
		return gain*input - offset;
	}
	else if(input > 0)
	{
		return gain*input + offset;
	}
	else
	{
		return 0;
	}
};


/**
*@brief 不感帯では0を出力
*Tは入力、出力するデータの型
* @param input 入力データ
* @param start 不感帯の最小値
* @param end 不快帯の最大値
* @return 出力
*/
template <class T>
T RTDeadZone(T input, T start, T end)
{
	if(input < start)
	{
		return input - start;
	}
	else if(input > end)
	{
		return input - end;
	}
	else
	{
		return 0;
	}
};


/**
 * @class RTRateLimiter
*@brief 変化率を制限して出力
*Tは入力、出力のデータ型
*/
template <class T>
class RTRateLimiter : public RTMath<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTRateLimiter()
	{
		reset();
	};
	/**
	*@brief コンストラクタ
	* @param rsr 変化率の最大値
	* @param fsr 変化率の最小値
	*/
	void setSlewRate(T rsr, T fsr)
	{
		risingSlewRate = rsr;
		fallingSlewRate = fsr;
	};
	/**
	*@brief 初期値
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};
	/**
	*@brief 変化率を制限して出力
	* @param ans 出力
	* @return 前回のデータが存在しない場合はfalse、それ以外はture
	*/
	bool calc(T &ans)
	{
		if(RTMath<T>::dataList.size() == 1)
		{
			last_value = RTMath<T>::dataList[0].m_value;
		}
		if(RTMath<T>::dataList.size() < 2)
		{

			return false;
		}
		Duration stepTime;
		if(!RTMath<T>::getDiffTime(stepTime))
		{
			return false;
		};

		T rate = (RTMath<T>::dataList[RTMath<T>::dataList.size()-1].m_value - last_value)/stepTime;
		if(rate > risingSlewRate)
		{
			last_value += risingSlewRate * stepTime;
		}
		else if(rate < fallingSlewRate)
		{
			last_value += fallingSlewRate * stepTime;
		}
		else
		{
			last_value = RTMath<T>::dataList[RTMath<T>::dataList.size()-1].m_value;
		}
		ans = last_value;
		return true;
	};
	T last_value;
	T risingSlewRate;
	T fallingSlewRate;
};

/**
 * @class RTRelay
*@brief 設定したオンとオフの値の2つの値で出力を切り替える
*出力がオフの時、入力が設定したスイッチングオンポイントを上回ると出力がオンになる
*出力がオンの時、入力が設定したスイッチングオフポイントを下回ると出力がオフになる
*Tは入力、出力のデータ型
*/
template <class T>
class RTRelay
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTRelay()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		state = false;
	};
	/**
	*@brief スイッチングポイントを設定
	* @param on スイッチングオンポイント
	* @param off スイッチングオフポイント
	*/
	void setSwitchPoint(T on, T off)
	{
		switchOnPoint = on;
		switchOffPoint = off;
	};
	/**
	*@brief 出力を設定
	* @param on オンの時の出力
	* @param off オフの時の出力
	*/
	void setOutput(T on, T off)
	{
		outputWhenOn = on;
		outputWhenOff = off;
	};
	/**
	*@brief オンかオフかを判定して出力
	* @param input 入力
	* @return 出力
	*/
	T calc(T input)
	{
		T ans;
		if(state)
		{
			if(switchOffPoint > input)
			{
				state = false;
				ans = outputWhenOff;
			}
			else
			{
				ans = outputWhenOn;
			}
		}
		else
		{
			if(switchOnPoint < input)
			{
				state = true;
				ans = outputWhenOn;
			}
			else
			{
				ans = outputWhenOff;
			}
		}
		return ans;
	};
	T switchOnPoint;
	T switchOffPoint;
	T outputWhenOn;
	T outputWhenOff;
	bool state;
};


/*int RTAbs(int input);
double RTAbs(double input);
float RTAbs(float input);

double RTSin(double input);
float RTSin(float input);
double RTCos(double input);
float RTCos(float input);
double RTTan(double input);
float RTTan(float input);
double RTASin(double input);
float RTASin(float input);
double RTACos(double input);
float RTACos(float input);
double RTATan(double input);
float RTATan(float input);
double RTSinh(double input);
float RTSinh(float input);
double RTCosh(double input);
float RTCosh(float input);
double RTTanh(double input);
float RTTanh(float input);
double RTASinh(double input);
float RTASinh(float input);
double RTACosh(double input);
float RTACosh(float input);
double RTATanh(double input);
float RTATanh(float input);
double RTSqrt(double input);
float RTSqrt(float input);
double RTPow(double x, double y);
float RTPow(float x, float y);
*/


/**
*@brief 符号を出力
*Tは入力、出力するデータの型
* @param input 入力データ
* @return 出力
*/
template <class T>
T RTSign(T input)
{
	if(input > 0)
	{
		return 1;
	}
	else if(input < 0)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


/**
*@brief 平方根を出力(符号は入力値の符号)
*Tは入力、出力するデータの型
* @param input 入力データ
* @return 出力
*/
template <class T>
T RTSignedSqrt(T input)
{
	return RTSign<T>(input)*std::sqrt(std::abs(input));
}



/**
 * @class RTSineWave
*@brief 正弦波を出力
*Tは出力のデータ型
*/
template <class T>
class RTSineWave : public RTMath<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTSineWave()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};
	/**
	*@brief 正弦波を出力
	* @return 出力
	*/
	T calc()
	{
		std::chrono::duration<double> nt = RTMath<T>::getTime();
		return amplitude*std::sin(2*M_PI*frequency*nt.count() + phase) + bias;
	};

	/**
	*@brief 振幅を設定
	* @param input 振幅
	*/
	void setAmplitude(T input)
	{
		amplitude = input;
	};

	/**
	*@brief バイアスを設定
	* @param input バイアス
	*/
	void setBias(T input)
	{
		bias = input;
	};

	/**
	*@brief 周波数を設定
	* @param input 周波数
	*/
	void setFrequency(T input)
	{
		frequency = input;
	};

	/**
	*@brief 位相を設定
	* @param input 位相
	*/
	void setPhase(T input)
	{
		phase = input;
	};
	
	
	T amplitude;
	T bias;
	T frequency;
	T phase;
};


/**
 * @class RTRampFunction
*@brief ランプ関数を出力
*Tは出力のデータ型
*/
template <class T>
class RTRampFunction : public RTMath<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTRampFunction()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};
	
	/**
	*@brief ランプ関数を出力
	* @return 出力
	*/
	T calc()
	{
		auto nt = RTMath<T>::getTime();
		if(startTime < nt)
		{
			return slope*(nt - startTime) + initialOutput;
		}
		else
		{
			return initialOutput;
		}
	};
	/**
	*@brief 勾配を設定
	* @param input 勾配
	*/
	void setSlope(T input)
	{
		slope = input;
	};
	/**
	*@brief 開始時間を設定
	* @param input 開始時間
	*/
	void setStartTime(Duration input)
	{
		startTime = input;
	};
	/**
	*@brief 初期出力を設定
	* @param input 初期出力
	*/
	void setInitialOutput(T input)
	{
		initialOutput = input;
	};

	T slope;
	Duration startTime;
	T initialOutput;
};

/**
 * @class RTPulseGenerator
*@brief 矩形波パルスを出力
*Tは出力のデータ型
*/
template <class T>
class RTPulseGenerator : public RTMath<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTPulseGenerator()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};

	/**
	*@brief 矩形波パルスを出力
	* @return 出力
	*/
	T calc()
	{
		auto st = RTMath<T>::getTime() - phaseDelay;
		if(st < 0)
		{
			return 0;
		}
		else
		{
			auto fmodValue = st % period;
			if(fmodValue < period*(1-pulseWidth/100.0))
			{
				return 0;
			}
			else
			{
				return amplitude;
			}
		}
	};
	/**
	*@brief 振幅を設定
	* @param input 振幅
	*/
	void setAmplitude(T input)
	{
		amplitude = input;
	};
	/**
	*@brief 周期を設定
	* @param input 周期
	*/
	void setPeriod(Duration input)
	{
		period = input;
	};
	/**
	*@brief パルス幅を設定
	* @param input パルス幅
	*/
	void setPulseWidth(T input)
	{
		pulseWidth = input;
	};
	/**
	*@brief 位相遅れを設定
	* @param input 位相遅れ
	*/
	void setPhaseDelay(Duration input)
	{
		phaseDelay = input;
	};

	T amplitude;
	Duration period;
	T pulseWidth;
	Duration phaseDelay;
};

/**
 * @class RTUniformRandomNumber
*@brief 一様分布する乱数を出力
*Tは出力のデータ型
*/
template <class T, class T2>
class RTUniformRandomNumber
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTUniformRandomNumber() : m_rand(-1,1), m_mt(0)
	{
		m_maximum = 1;
		m_minimum = -1;
		m_seed = 0;
		m_randomSeedGenerator = true;
		//m_rand = T2(m_maximum,m_minimum);
		//setMt();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		setMt();
		m_rand = T2(m_maximum,m_minimum);
	};
	/**
	*@brief 乱数エンジンの初期化
	*/
	void setMt()
	{
		unsigned int t_seed;
		if(m_randomSeedGenerator)
		{
			std::random_device rnd;
			t_seed = rnd();
		}
		else if(m_randomSeedGenerator)
		{
			t_seed = m_seed;
		}
		m_mt = std::mt19937(t_seed);
	};
	
	/**
	*@brief 一様分布する乱数を出力
	* @return 出力
	*/
	T calc()
	{
		return m_rand(m_mt);
	};
	/**
	*@brief 最大値の設定
	* @param input 最大値
	*/
	void setMaximum(T input)
	{
		m_maximum = input;
		m_rand = T2(m_maximum,m_minimum);
	};
	/**
	*@brief 最小値の設定
	* @param input 最小値
	*/
	void setMinimum(T input)
	{
		m_minimum = input;
		m_rand = T2(m_maximum,m_minimum);
	};
	/**
	*@brief シードを設定
	* @param input シード
	*/
	void setSeed(unsigned int input)
	{
		m_seed = input;
		setMt();
	};
	/**
	*@brief 乱数でシードを生成するか、設定したシードを使うかを設定
	* @param input trueで乱数を利用、falseで設定値を利用
	*/
	void setRandomSeedGenerator(bool input)
	{
		m_randomSeedGenerator = input;
		setMt();
	};
	
	
	T m_maximum;
	T m_minimum;
	unsigned int m_seed;
	bool m_randomSeedGenerator;
	T2 m_rand;
	std::mt19937 m_mt;
};



/**
 * @class RTRandomNumber
*@brief 正規分布された乱数を出力
*Tは出力のデータ型
*/
template <class T>
class RTRandomNumber
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTRandomNumber() : m_rand(-1,1), m_mt(0)
	{
		m_mean = 0;
		m_variable = 1;
		m_seed = 0;
		m_randomSeedGenerator = true;

	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		setMt();
		m_rand = std::normal_distribution<T>(m_mean,m_variable);
	};
	/**
	*@brief 乱数エンジンの初期化
	*/
	void setMt()
	{
		unsigned int t_seed;
		if(m_randomSeedGenerator)
		{
			std::random_device rnd;
			t_seed = rnd();
		}
		else
		{
			t_seed = m_seed;
		}
		m_mt = std::mt19937(t_seed);
	};
	
	/**
	*@brief 正規分布された乱数を出力
	* @return 出力
	*/
	T calc()
	{
		return m_rand(m_mt);
	};
	/**
	*@brief 平均を設定
	* @param input 平均
	*/
	void setMean(T input)
	{
		m_mean = input;
		m_rand = std::normal_distribution<T>(m_mean,m_variable);
	};
	/**
	*@brief 分散を設定
	* @param input 分散
	*/
	void setVariable(T input)
	{
		m_variable = input;
		m_rand = std::normal_distribution<T>(m_mean,m_variable);
	};
	/**
	*@brief シードを設定
	* @param input シード
	*/
	void setSeed(unsigned int input)
	{
		m_seed = input;
		setMt();
	};
	/**
	*@brief 乱数でシードを生成するか、設定したシードを使うかを設定
	* @param input trueで乱数を利用、falseで設定値を利用
	*/
	void setRandomSeedGenerator(bool input)
	{
		m_randomSeedGenerator = input;
		setMt();
	};

	T m_mean;
	T m_variable;
	unsigned int m_seed;
	bool m_randomSeedGenerator;
	std::normal_distribution<T> m_rand;
	std::mt19937 m_mt;
};


/**
 * @class RTStepFunction
*@brief ステップ関数を出力
*Tは出力のデータ型
*/
template <class T>
class RTStepFunction : public RTMath<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTStepFunction()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};

	/**
	*@brief ステップ関数を出力
	* @return 出力
	*/
	T calc()
	{
		auto nt = RTMath<T>::getTime();
		if(nt < stepTime)
		{
			return initialValue;
		}
		else
		{
			return finalValue;
		}
	};
	/**
	*@brief 初期値を設定
	* @param input 初期値
	*/
	void setInitialValue(T input)
	{
		initialValue = input;
	};
	/**
	*@brief 最終値を設定
	* @param input 最終値
	*/
	void setFinalValue(T input)
	{
		finalValue = input;
	};
	/**
	*@brief ステップ時間を設定
	* @param input ステップ時間
	*/
	void setStepTime(Duration input)
	{
		stepTime = input;
	};

	T initialValue;
	T finalValue;
	Duration stepTime;
};

/**
 * @class RTController
*@brief 制御コントローラーの基本クラス
*Tは入力、出力のデータ型
*/
template <class T>
class RTController
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTController()
	{
		m_proportional = 1;
		m_integral = 0;
		m_derivative = 0;
		m_alpha = 1;
		m_beta = 0;
	};
	/**
	*@brief 初期化
	*/
	virtual void reset()
	{

	};
	/**
	*@brief 比例gゲインを設定
	* @param value 比例ゲイン
	*/
	virtual void setProportionalValue(T value)
	{
		m_proportional = value;
	};
	/**
	*@brief 微分ゲインを設定
	* @param value 微分ゲイン
	*/
	virtual void setIntegralValue(T value)
	{
		m_integral = value;
	};
	/**
	*@brief 積分ゲインを設定
	* @param value 積分ゲイン
	*/
	virtual void setDerivativeValue(T value)
	{
		m_derivative = value;
	};
	/**
	*@brief 2自由度制御系の目標値に掛かる係数
	* @param value 係数
	*/
	virtual void setAlpha(T value)
	{
		m_alpha = value;
	};
	/**
	*@brief 2自由度制御系の目標値の微分値に掛かる係数
	* @param value 係数
	*/
	virtual void setBeta(T value)
	{
		m_beta = value;
	};
	/**
	*@brief 制御系から出力を計算
	* @param input 目標値
	* @param value 制御量
	* @param ans 出力
	* @return falseならば計算失敗
	*/
	virtual bool calc(T input, T value, T &ans)
	{
		return true;
	};
	/**
	*@brief 刻み幅を設定
	* @param s 刻み幅
	*/
	virtual void setSamplingTime(Duration s)
	{
		
	};
	/**
	*@brief trueで実時間、falseでシミュレーション時間に設定
	* @param c trueで実時間、falseでシミュレーション時間
	*/
	virtual void setConfig(bool c)
	{

	};
	T m_proportional;
	T m_integral;
	T m_derivative;
	T m_alpha;
	T m_beta;
};


/**
 * @class RTPController
*@brief P制御
*Tは入力、出力のデータ型
*/
template <class T>
class RTPController : public RTController<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTPController()
	{

	};
	/**
	*@brief P制御で出力を計算
	* @param input 目標値
	* @param value 制御量
	* @param ans 出力
	* @return falseならば計算失敗
	*/
	bool calc(T input, T value, T &ans)
	{
		ans = RTController<T>::m_proportional*(RTController<T>::m_alpha*input - value);
		return true;
	};
};

/**
 * @class RTPDController
*@brief PD制御
*Tは入力、出力のデータ型
*/
template <class T>
class RTPDController : public RTController<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTPDController()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		d_func.reset();
	};
	/**
	*@brief PD制御で出力を計算
	* @param input 目標値
	* @param value 制御量
	* @param ans 出力
	* @return falseならば計算失敗
	*/
	bool calc(T input, T value, T &ans)
	{
		d_func.addData(RTController<T>::m_beta*input - value);
		T d_value;
		if(!d_func.calc(d_value))return false;

		ans = RTController<T>::m_proportional*(RTController<T>::m_alpha*input - value) + RTController<T>::m_derivative*d_value;
		return true;
	};
	/**
	*@brief 刻み幅を設定
	* @param s 刻み幅
	*/
	void setSamplingTime(Duration s)
	{
		d_func.setSamplingTime(s);
	};
	/**
	*@brief trueで実時間、falseでシミュレーション時間に設定
	* @param c trueで実時間、falseでシミュレーション時間
	*/
	void setConfig(bool c)
	{
		d_func.setConfig(c);
	};
	RTDerivative<T> d_func;
};

/**
 * @class RTPIController
*@brief PI制御
*Tは入力、出力のデータ型
*/
template <class T>
class RTPIController : public RTController<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTPIController()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		i_func.reset();
	};
	/**
	*@brief PI制御で出力を計算
	* @param input 目標値
	* @param value 制御量
	* @param ans 出力
	* @return falseならば計算失敗
	*/
	bool calc(T input, T value, T &ans)
	{
		i_func.addData(input-value);
		T i_value;
		if(!i_func.calc(i_value))return false;

		ans = RTController<T>::m_integral*i_value + RTController<T>::m_proportional*(RTController<T>::m_alpha*input - value);
		return true;
	};
	/**
	*@brief 刻み幅を設定
	* @param s 刻み幅
	*/
	void setSamplingTime(Duration s)
	{
		i_func.setSamplingTime(s);
	};
	/**
	*@brief trueで実時間、falseでシミュレーション時間に設定
	* @param c trueで実時間、falseでシミュレーション時間
	*/
	void setConfig(bool c)
	{
		i_func.setConfig(c);
	};
	RTIntegrator<T> i_func;
};

/**
 * @class RTIController
*@brief I制御
*Tは入力、出力のデータ型
*/
template <class T>
class RTIController : public RTController<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTIController()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		i_func.reset();
	};
	/**
	*@brief I制御で出力を計算
	* @param input 目標値
	* @param value 制御量
	* @param ans 出力
	* @return falseならば計算失敗
	*/
	bool calc(T input, T value, T &ans)
	{
		i_func.addData(input-value);
		T i_value;
		if(!i_func.calc(i_value))return false;

		ans = RTController<T>::m_integral*i_value;
		return true;
	};
	/**
	*@brief 刻み幅を設定
	* @param s 刻み幅
	*/
	void setSamplingTime(Duration s)
	{
		i_func.setSamplingTime(s);
	};
	/**
	*@brief trueで実時間、falseでシミュレーション時間に設定
	* @param c trueで実時間、falseでシミュレーション時間
	*/
	void setConfig(bool c)
	{
		i_func.setConfig(c);
	};
	RTIntegrator<T> i_func;
};

/**
 * @class RTPIDController
*@brief PID制御
*Tは入力、出力のデータ型
*/
template <class T>
class RTPIDController : public RTController<T>
{
public:
	/**
	*@brief コンストラクタ
	*/
	RTPIDController()
	{
		reset();
	};
	/**
	*@brief 初期化
	*/
	void reset()
	{
		d_func.reset();
		i_func.reset();
	};
	/**
	*@brief PID制御で出力を計算
	* @param input 目標値
	* @param value 制御量
	* @param ans 出力
	* @return falseならば計算失敗
	*/
	bool calc(T input, T value, T &ans)
	{
		d_func.addData(RTController<T>::m_beta*input - value);
		T d_value;
		if(!d_func.calc(d_value))return false;

		i_func.addData(input-value);
		T i_value;
		if(!i_func.calc(i_value))return false;

		ans = RTController<T>::m_integral*i_value + RTController<T>::m_proportional*(RTController<T>::m_alpha*input - value) + RTController<T>::m_derivative*d_value;
		return true;
	};
	/**
	*@brief 刻み幅を設定
	* @param s 刻み幅
	*/
	void setSamplingTime(Duration s)
	{
		d_func.setSamplingTime(s);
		i_func.setSamplingTime(s);
	};
	/**
	*@brief trueで実時間、falseでシミュレーション時間に設定
	* @param c trueで実時間、falseでシミュレーション時間
	*/
	void setConfig(bool c)
	{
		d_func.setConfig(c);
		i_func.setConfig(c);
	};
	RTDerivative<T> d_func;
	RTIntegrator<T> i_func;
};






#endif 
