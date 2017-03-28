/*!
 * @file  RTMath.h
 * @brief ���l�v�Z�֘A�̊֐�
 *
 */


#ifndef RTMATH_H
#define RTMATH_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <vector>
#include <coil/stringutil.h>
#include <coil/Time.h>
#include <coil/TimeMeasure.h>
#include <cmath>
#include <random>


/**
 * @class ValueAndTime
*@brief ���ԂƂ��̎��Ԃł̃f�[�^���i�[����N���X
*T�͊i�[����f�[�^�̌^
*/
template <class T>
class ValueAndTime
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param tm ����
	* @param value �f�[�^
	*/
	ValueAndTime(coil::TimeValue tm, T value)
	{
		m_tm = tm;
		m_value = value;
	};
	coil::TimeValue m_tm;
	T m_value;
};


/**
 * @class RTMath
*@brief �A���I�ɓ��͂����f�[�^�A���Ԃ��Ǘ�����N���X
*T�͊i�[����f�[�^�̌^
*/
template <class T>
class RTMath
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTMath()
	{
		samplingTime_low = 0.000001;
		setSamplingTime(0.01);
		realTime = false;
		resetTime();
	};
	/**
	*@brief ���ݕ��ݒ�
	* @param s ���ݕ�
	*/
	virtual void setSamplingTime(double s)
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
	*@brief �����ԂŃf�[�^��ۑ����邩�A�V�~�����[�V�������Ԃŕۑ����邩�ݒ�
	* @param s true�Ŏ����ԁAfalse�ŃV�~�����[�V��������
	*/
	virtual void setConfig(bool c)
	{
		realTime = c;
	};
	/**
	*@brief �ŐV�̃f�[�^�ƑO����͂����f�[�^�Ƃ̎��ԍ����擾
	* @param ans ���ԍ�(�V�~�����[�V�������Ԃ̎��͐ݒ肵�����ݕ�)
	* @return �O��̃f�[�^�����݂��Ȃ��ꍇ��false�A����ȊO��ture
	*/
	virtual bool getDiffTime(double &ans)
	{
		if(realTime)
		{
			if(dataList.size() < 2)
			{
				return false;
			}
			else
			{
				ans = (double)(dataList[dataList.size()-1].m_tm - dataList[dataList.size()-2].m_tm);
			}
		}
		else
		{
			ans = samplingTime;
		}
		return true;
	};
	/**
	*@brief ���ԁA�f�[�^���X�g������������
	*/
	virtual void resetTime()
	{
		dataList.clear();
		first_time = coil::TimeValue(coil::gettimeofday());
		now_time = 0;
	};
	/**
	*@brief �f�[�^��ǉ�
	* @param data �f�[�^
	*/
	virtual void addData(T data)
	{
		coil::TimeValue t0(coil::gettimeofday());
		dataList.push_back(ValueAndTime<T>(t0,data));
	};
	/**
	*@brief ���݂̎��Ԃ��擾
	* @return ����
	*/
	virtual double getTime()
	{
		if(realTime)
		{
			coil::TimeValue t0(coil::gettimeofday());
			now_time = (double)(t0-first_time);
		}
		else
		{
			now_time += samplingTime;
		}
		return now_time;
	};
	double samplingTime_low;
	coil::TimeValue first_time;
	double now_time;
	bool realTime;
	double samplingTime;
	std::vector<ValueAndTime<T>> dataList;
};


/**
 * @class RTIntegrator
*@brief �f�[�^��ϕ�������
*T�͊i�[����f�[�^�̌^
*/
template <class T>
class RTIntegrator : public RTMath<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTIntegrator()
	{
		initialCondition = 0;
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		RTMath<T>::resetTime();
		intValue = initialCondition;
	};
	/**
	*@brief �ϕ��l�̏����l��ݒ�
	* @param c �����l
	*/
	void setInitialCondition(T c)
	{
		initialCondition = c;
		intValue = initialCondition;
	};
	/**
	*@brief �ϕ��l���擾
	* @param ans �ϕ��l
	* @return �O��̃f�[�^�����݂��Ȃ��ꍇ��false�A����ȊO��ture
	*/
	bool calc(T &ans)
	{
		if(RTMath<T>::dataList.size() < 2)
		{
			return false;
		}
		double stepTime;
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
*@brief �f�[�^�����������
*T�͊i�[����f�[�^�̌^
*/
template <class T>
class RTDerivative : public RTMath<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTDerivative()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};
	/**
	*@brief �����l���擾
	* @param ans �����l
	* @return �O��̃f�[�^�����݂��Ȃ��ꍇ��false�A����ȊO��ture
	*/
	bool calc(T &ans)
	{
		if(RTMath<T>::dataList.size() < 2)
		{
			return false;
		}
		double stepTime;
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
*@brief �V�т����V�X�e��(���ݒl�̕s���т̕����ł���Ώo�͕͂ω����܂���)
*T�͊i�[����f�[�^�̌^
*/
template <class T>
class RTBacklash
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTBacklash()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		now_Output = m_initialOutput;
	};
	/**
	*@brief �s���т̕���ݒ�
	* @param io �V�т̗�
	*/
	void setDeadbandWidth(T width)
	{
		m_width = width;
	};
	/**
	*@brief �����l��ݒ�
	* @param io �����l
	*/
	void setInitialOutput(T io)
	{
		m_initialOutput = io;
		//now_Output = io;
	};
	/**
	*@brief �V�т̂���V�X�e���ɓ��͂����Ƃ��̏o�͂��擾
	* @param input ���͒l
	* @return �o�͒l
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
*@brief �ݒ肵���͈͓��ɏo�͂𐧌����܂�
*T�͓��́A�o�͂̃f�[�^�̌^
* @param input ����
* @param upperLimit �ő�l
* @param lowerLimit �ŏ��l
* @return �o��
*/
template <class T>
T RTSaturation(T input, T upperLimit, T lowerLimit)
{
	T val = input;
	if(val > upperLimit)
	{
		val = upperLimit;
	}
	else if(val < lowerLimit)
	{
		val = lowerLimit;
	}
	return val;
};

/**
*@brief ���͂����������","�ŕ������āA���������������ݒ肵���f�[�^�^�ɕϊ����ďo��
*T�͏o�͂���f�[�^���X�g�̊e�f�[�^�̌^
* @param str ���͕�����
* @param ans �o�͂���f�[�^���X�g
* @return true�Ő����Afalse�Ŏ��s
*/
template <class T>
bool getValueInString(std::string str, std::vector<T> &ans)
{
	coil::eraseBlank(str);
	ans.clear();
	coil::vstring va = coil::split(str, ",");
	if(va.size() == 0)
	{
		return false;
	}
	for (coil::vstring::iterator it = va.begin(); it != va.end(); ++it)
	{
		T value;
		bool result = coil::stringTo<T>(value, (*it).c_str());
		if(result)
		{
			ans.push_back(value);
		}
		else
		{
			return false;
		}
	}
	
	return true;
};


/**
*@brief ���͂����f�[�^���X�g����w�肷��ԍ��̒l���o��
*T�͓��͂���f�[�^���X�g�̊e�f�[�^�̌^
* @param input �f�[�^���X�g
* @param num �ԍ�
* @param ans �o��
* @return �f�[�^����0�̎���false�A����ȊO��true
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
*@brief ��_�ŕs�A���A����ȊO�͐��`�Q�C���̏o��
*T�͓��́A�o�͂���f�[�^�̌^
* @param input ���̓f�[�^
* @param offset �I�t�Z�b�g
* @param gain �Q�C��
* @return �o��
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
*@brief �s���тł�0���o��
*T�͓��́A�o�͂���f�[�^�̌^
* @param input ���̓f�[�^
* @param start �s���т̍ŏ��l
* @param end �s���т̍ő�l
* @return �o��
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
*@brief �ω����𐧌����ďo��
*T�͓��́A�o�͂̃f�[�^�^
*/
template <class T>
class RTRateLimiter : public RTMath<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTRateLimiter()
	{
		reset();
	};
	/**
	*@brief �R���X�g���N�^
	* @param rsr �ω����̍ő�l
	* @param fsr �ω����̍ŏ��l
	*/
	void setSlewRate(T rsr, T fsr)
	{
		risingSlewRate = rsr;
		fallingSlewRate = fsr;
	};
	/**
	*@brief �����l
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};
	/**
	*@brief �ω����𐧌����ďo��
	* @param ans �o��
	* @return �O��̃f�[�^�����݂��Ȃ��ꍇ��false�A����ȊO��ture
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
		double stepTime;
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
*@brief �ݒ肵���I���ƃI�t�̒l��2�̒l�ŏo�͂�؂�ւ���
*�o�͂��I�t�̎��A���͂��ݒ肵���X�C�b�`���O�I���|�C���g������Əo�͂��I���ɂȂ�
*�o�͂��I���̎��A���͂��ݒ肵���X�C�b�`���O�I�t�|�C���g�������Əo�͂��I�t�ɂȂ�
*T�͓��́A�o�͂̃f�[�^�^
*/
template <class T>
class RTRelay
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTRelay()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		state = false;
	};
	/**
	*@brief �X�C�b�`���O�|�C���g��ݒ�
	* @param on �X�C�b�`���O�I���|�C���g
	* @param off �X�C�b�`���O�I�t�|�C���g
	*/
	void setSwitchPoint(T on, T off)
	{
		switchOnPoint = on;
		switchOffPoint = off;
	};
	/**
	*@brief �o�͂�ݒ�
	* @param on �I���̎��̏o��
	* @param off �I�t�̎��̏o��
	*/
	void setOutput(T on, T off)
	{
		outputWhenOn = on;
		outputWhenOff = off;
	};
	/**
	*@brief �I�����I�t���𔻒肵�ďo��
	* @param input ����
	* @return �o��
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
*@brief �������o��
*T�͓��́A�o�͂���f�[�^�̌^
* @param input ���̓f�[�^
* @return �o��
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
*@brief ���������o��(�����͓��͒l�̕���)
*T�͓��́A�o�͂���f�[�^�̌^
* @param input ���̓f�[�^
* @return �o��
*/
template <class T>
T RTSignedSqrt(T input)
{
	return RTSign<T>(input)*std::sqrt(std::abs(input));
}



/**
 * @class RTSineWave
*@brief �����g���o��
*T�͏o�͂̃f�[�^�^
*/
template <class T>
class RTSineWave : public RTMath<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTSineWave()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};
	/**
	*@brief �����g���o��
	* @return �o��
	*/
	T calc()
	{
		double nt = RTMath<T>::getTime();
		return amplitude*std::sin(2*M_PI*frequency*nt + phase) + bias;
	};

	/**
	*@brief �U����ݒ�
	* @param input �U��
	*/
	void setAmplitude(T input)
	{
		amplitude = input;
	};

	/**
	*@brief �o�C�A�X��ݒ�
	* @param input �o�C�A�X
	*/
	void setBias(T input)
	{
		bias = input;
	};

	/**
	*@brief ���g����ݒ�
	* @param input ���g��
	*/
	void setFrequency(T input)
	{
		frequency = input;
	};

	/**
	*@brief �ʑ���ݒ�
	* @param input �ʑ�
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
*@brief �����v�֐����o��
*T�͏o�͂̃f�[�^�^
*/
template <class T>
class RTRampFunction : public RTMath<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTRampFunction()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};
	
	/**
	*@brief �����v�֐����o��
	* @return �o��
	*/
	T calc()
	{
		double nt = RTMath<T>::getTime();
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
	*@brief ���z��ݒ�
	* @param input ���z
	*/
	void setSlope(T input)
	{
		slope = input;
	};
	/**
	*@brief �J�n���Ԃ�ݒ�
	* @param input �J�n����
	*/
	void setStartTime(T input)
	{
		startTime = input;
	};
	/**
	*@brief �����o�͂�ݒ�
	* @param input �����o��
	*/
	void setInitialOutput(T input)
	{
		initialOutput = input;
	};
	
	
	T slope;
	T startTime;
	T initialOutput;
};

/**
 * @class RTPulseGenerator
*@brief ��`�g�p���X���o��
*T�͏o�͂̃f�[�^�^
*/
template <class T>
class RTPulseGenerator : public RTMath<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTPulseGenerator()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};
	
	/**
	*@brief ��`�g�p���X���o��
	* @return �o��
	*/
	T calc()
	{
		double nt = RTMath<T>::getTime();
		T st = nt - phaseDelay;
		if(st < 0)
		{
			return 0;
		}
		else
		{
			T fmodValue = std::fmod(st, period);
			//std::cout << fmodValue << "\t" << period*(1-pulseWidth/100.0) << std::endl;
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
	*@brief �U����ݒ�
	* @param input �U��
	*/
	void setAmplitude(T input)
	{
		amplitude = input;
	};
	/**
	*@brief ������ݒ�
	* @param input ����
	*/
	void setPeriod(T input)
	{
		period = input;
	};
	/**
	*@brief �p���X����ݒ�
	* @param input �p���X��
	*/
	void setPulseWidth(T input)
	{
		pulseWidth = input;
	};
	/**
	*@brief �ʑ��x���ݒ�
	* @param input �ʑ��x��
	*/
	void setPhaseDelay(T input)
	{
		phaseDelay = input;
	};
	
	
	T amplitude;
	T period;
	T pulseWidth;
	T phaseDelay;
};

/**
 * @class RTUniformRandomNumber
*@brief ��l���z���闐�����o��
*T�͏o�͂̃f�[�^�^
*/
template <class T, class T2>
class RTUniformRandomNumber
{
public:
	/**
	*@brief �R���X�g���N�^
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
	*@brief ������
	*/
	void reset()
	{
		setMt();
		m_rand = T2(m_maximum,m_minimum);
	};
	/**
	*@brief �����G���W���̏�����
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
	*@brief ��l���z���闐�����o��
	* @return �o��
	*/
	T calc()
	{
		return m_rand(m_mt);
	};
	/**
	*@brief �ő�l�̐ݒ�
	* @param input �ő�l
	*/
	void setMaximum(T input)
	{
		m_maximum = input;
		m_rand = T2(m_maximum,m_minimum);
	};
	/**
	*@brief �ŏ��l�̐ݒ�
	* @param input �ŏ��l
	*/
	void setMinimum(T input)
	{
		m_minimum = input;
		m_rand = T2(m_maximum,m_minimum);
	};
	/**
	*@brief �V�[�h��ݒ�
	* @param input �V�[�h
	*/
	void setSeed(unsigned int input)
	{
		m_seed = input;
		setMt();
	};
	/**
	*@brief �����ŃV�[�h�𐶐����邩�A�ݒ肵���V�[�h���g������ݒ�
	* @param input true�ŗ����𗘗p�Afalse�Őݒ�l�𗘗p
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
*@brief ���K���z���ꂽ�������o��
*T�͏o�͂̃f�[�^�^
*/
template <class T>
class RTRandomNumber
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTRandomNumber() : m_rand(-1,1), m_mt(0)
	{
		m_mean = 0;
		m_variable = 1;
		m_seed = 0;
		m_randomSeedGenerator = true;

	};
	/**
	*@brief ������
	*/
	void reset()
	{
		setMt();
		m_rand = std::normal_distribution<T>(m_mean,m_variable);
	};
	/**
	*@brief �����G���W���̏�����
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
	*@brief ���K���z���ꂽ�������o��
	* @return �o��
	*/
	T calc()
	{
		return m_rand(m_mt);
	};
	/**
	*@brief ���ς�ݒ�
	* @param input ����
	*/
	void setMean(T input)
	{
		m_mean = input;
		m_rand = std::normal_distribution<T>(m_mean,m_variable);
	};
	/**
	*@brief ���U��ݒ�
	* @param input ���U
	*/
	void setVariable(T input)
	{
		m_variable = input;
		m_rand = std::normal_distribution<T>(m_mean,m_variable);
	};
	/**
	*@brief �V�[�h��ݒ�
	* @param input �V�[�h
	*/
	void setSeed(unsigned int input)
	{
		m_seed = input;
		setMt();
	};
	/**
	*@brief �����ŃV�[�h�𐶐����邩�A�ݒ肵���V�[�h���g������ݒ�
	* @param input true�ŗ����𗘗p�Afalse�Őݒ�l�𗘗p
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
*@brief �X�e�b�v�֐����o��
*T�͏o�͂̃f�[�^�^
*/
template <class T>
class RTStepFunction : public RTMath<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTStepFunction()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		RTMath<T>::resetTime();
	};
	
	/**
	*@brief �X�e�b�v�֐����o��
	* @return �o��
	*/
	T calc()
	{
		double nt = RTMath<T>::getTime();
		//std::cout << nt << std::endl;
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
	*@brief �����l��ݒ�
	* @param input �����l
	*/
	void setInitialValue(T input)
	{
		initialValue = input;
	};
	/**
	*@brief �ŏI�l��ݒ�
	* @param input �ŏI�l
	*/
	void setFinalValue(T input)
	{
		finalValue = input;
	};
	/**
	*@brief �X�e�b�v���Ԃ�ݒ�
	* @param input �X�e�b�v����
	*/
	void setStepTime(T input)
	{
		stepTime = input;
	};
	
	
	
	T initialValue;
	T finalValue;
	T stepTime;
};

/**
 * @class RTController
*@brief ����R���g���[���[�̊�{�N���X
*T�͓��́A�o�͂̃f�[�^�^
*/
template <class T>
class RTController
{
public:
	/**
	*@brief �R���X�g���N�^
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
	*@brief ������
	*/
	virtual void reset()
	{

	};
	/**
	*@brief ���g�Q�C����ݒ�
	* @param value ���Q�C��
	*/
	virtual void setProportionalValue(T value)
	{
		m_proportional = value;
	};
	/**
	*@brief �����Q�C����ݒ�
	* @param value �����Q�C��
	*/
	virtual void setIntegralValue(T value)
	{
		m_integral = value;
	};
	/**
	*@brief �ϕ��Q�C����ݒ�
	* @param value �ϕ��Q�C��
	*/
	virtual void setDerivativeValue(T value)
	{
		m_derivative = value;
	};
	/**
	*@brief 2���R�x����n�̖ڕW�l�Ɋ|����W��
	* @param value �W��
	*/
	virtual void setAlpha(T value)
	{
		m_alpha = value;
	};
	/**
	*@brief 2���R�x����n�̖ڕW�l�̔����l�Ɋ|����W��
	* @param value �W��
	*/
	virtual void setBeta(T value)
	{
		m_beta = value;
	};
	/**
	*@brief ����n����o�͂��v�Z
	* @param input �ڕW�l
	* @param value �����
	* @param ans �o��
	* @return false�Ȃ�Όv�Z���s
	*/
	virtual bool calc(T input, T value, T &ans)
	{
		return true;
	};
	/**
	*@brief ���ݕ���ݒ�
	* @param s ���ݕ�
	*/
	virtual void setSamplingTime(double s)
	{
		
	};
	/**
	*@brief true�Ŏ����ԁAfalse�ŃV�~�����[�V�������Ԃɐݒ�
	* @param c true�Ŏ����ԁAfalse�ŃV�~�����[�V��������
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
*@brief P����
*T�͓��́A�o�͂̃f�[�^�^
*/
template <class T>
class RTPController : public RTController<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTPController()
	{

	};
	/**
	*@brief P����ŏo�͂��v�Z
	* @param input �ڕW�l
	* @param value �����
	* @param ans �o��
	* @return false�Ȃ�Όv�Z���s
	*/
	bool calc(T input, T value, T &ans)
	{
		ans = RTController<T>::m_proportional*(RTController<T>::m_alpha*input - value);
		return true;
	};
};

/**
 * @class RTPDController
*@brief PD����
*T�͓��́A�o�͂̃f�[�^�^
*/
template <class T>
class RTPDController : public RTController<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTPDController()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		d_func.reset();
	};
	/**
	*@brief PD����ŏo�͂��v�Z
	* @param input �ڕW�l
	* @param value �����
	* @param ans �o��
	* @return false�Ȃ�Όv�Z���s
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
	*@brief ���ݕ���ݒ�
	* @param s ���ݕ�
	*/
	void setSamplingTime(double s)
	{
		d_func.setSamplingTime(s);
	};
	/**
	*@brief true�Ŏ����ԁAfalse�ŃV�~�����[�V�������Ԃɐݒ�
	* @param c true�Ŏ����ԁAfalse�ŃV�~�����[�V��������
	*/
	void setConfig(bool c)
	{
		d_func.setConfig(c);
	};
	RTDerivative<T> d_func;
};

/**
 * @class RTPIController
*@brief PI����
*T�͓��́A�o�͂̃f�[�^�^
*/
template <class T>
class RTPIController : public RTController<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTPIController()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		i_func.reset();
	};
	/**
	*@brief PI����ŏo�͂��v�Z
	* @param input �ڕW�l
	* @param value �����
	* @param ans �o��
	* @return false�Ȃ�Όv�Z���s
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
	*@brief ���ݕ���ݒ�
	* @param s ���ݕ�
	*/
	void setSamplingTime(double s)
	{
		i_func.setSamplingTime(s);
	};
	/**
	*@brief true�Ŏ����ԁAfalse�ŃV�~�����[�V�������Ԃɐݒ�
	* @param c true�Ŏ����ԁAfalse�ŃV�~�����[�V��������
	*/
	void setConfig(bool c)
	{
		i_func.setConfig(c);
	};
	RTIntegrator<T> i_func;
};

/**
 * @class RTIController
*@brief I����
*T�͓��́A�o�͂̃f�[�^�^
*/
template <class T>
class RTIController : public RTController<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTIController()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		i_func.reset();
	};
	/**
	*@brief I����ŏo�͂��v�Z
	* @param input �ڕW�l
	* @param value �����
	* @param ans �o��
	* @return false�Ȃ�Όv�Z���s
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
	*@brief ���ݕ���ݒ�
	* @param s ���ݕ�
	*/
	void setSamplingTime(double s)
	{
		i_func.setSamplingTime(s);
	};
	/**
	*@brief true�Ŏ����ԁAfalse�ŃV�~�����[�V�������Ԃɐݒ�
	* @param c true�Ŏ����ԁAfalse�ŃV�~�����[�V��������
	*/
	void setConfig(bool c)
	{
		i_func.setConfig(c);
	};
	RTIntegrator<T> i_func;
};

/**
 * @class RTPIDController
*@brief PID����
*T�͓��́A�o�͂̃f�[�^�^
*/
template <class T>
class RTPIDController : public RTController<T>
{
public:
	/**
	*@brief �R���X�g���N�^
	*/
	RTPIDController()
	{
		reset();
	};
	/**
	*@brief ������
	*/
	void reset()
	{
		d_func.reset();
		i_func.reset();
	};
	/**
	*@brief PID����ŏo�͂��v�Z
	* @param input �ڕW�l
	* @param value �����
	* @param ans �o��
	* @return false�Ȃ�Όv�Z���s
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
	*@brief ���ݕ���ݒ�
	* @param s ���ݕ�
	*/
	void setSamplingTime(double s)
	{
		d_func.setSamplingTime(s);
		i_func.setSamplingTime(s);
	};
	/**
	*@brief true�Ŏ����ԁAfalse�ŃV�~�����[�V�������Ԃɐݒ�
	* @param c true�Ŏ����ԁAfalse�ŃV�~�����[�V��������
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
