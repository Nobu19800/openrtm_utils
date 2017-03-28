/*!
 * @file  RTMath.h
 * @brief �f�[�^�|�[�g�֘A�̊֐�
 *
 */


#ifndef DYPORTBASE_H
#define DYPORTBASE_H

#include <rtm/DataFlowComponentBase.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>



/**
 * @class DynamicComponentBase
*@brief �R���t�B�M�����[�V�����p�����[�^�̃R�[���o�b�N����configUpdate�֐����Ăяo���R���|�[�l���g
*/
class DynamicComponentBase
  : public RTC::DataFlowComponentBase
{
 public:
	/**
	*@brief �R���X�g���N�^
	* @param manager�}�l�[�W���I�u�W�F�N�g
	*/
	DynamicComponentBase(RTC::Manager* manager) : RTC::DataFlowComponentBase(manager)
	{
		
	};
	/**
	*@brief �R���t�B�M�����[�V�����p�����[�^�X�V���ɌĂяo�����֐�
	*/
	virtual void configUpdate(){};
};


/**
 * @class RTCLogicBase
*@brief RTC�Ɏ������郍�W�b�N�̊�{�N���X
*�e�R�[���o�b�N��RTC�̊Y������R�[���o�b�N���ɌĂяo�����悤�ɋL�q����
*/
class RTCLogicBase
{
public:
	/**
	*@brief �f�X�g���N�^
	*/
	virtual ~RTCLogicBase()
	{
	}
	/**
	*@brief �����������p�R�[���o�b�N�֐�
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onInitialize(){return RTC::RTC_OK;};
	/**
	*@brief �I�������p�R�[���o�b�N�֐�
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onFinalize(){return RTC::RTC_OK;};
	/**
	*@brief �J�n�����p�R�[���o�b�N�֐�
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief ��~�����p�R�[���o�b�N�֐�
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief ���������R�[���o�b�N�֐�
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief �s���������R�[���o�b�N�֐�
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief ���������p�R�[���o�b�N�֐�
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief ���f�����p�R�[���o�b�N�֐�
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief �G���[�����p�R�[���o�b�N�֐�
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief ���Z�b�g�����p�R�[���o�b�N�֐�
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief ��ԕύX�����p�R�[���o�b�N�֐�
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief ���s�����ύX���R�[���o�b�N�֐�
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	
};

/**
 * @class DynamicDataPortBase
*@brief ���I�ɐ�������f�[�^�|�[�g�̊�{�N���X
*/
class DynamicDataPortBase
{
public:
	/**
	*@brief �f�X�g���N�^
	*/
	virtual ~DynamicDataPortBase()
	{
	}
	/**
	*@brief �f�[�^���o�b�t�@�ɗ��܂��Ă��邩�𔻒�
	* @return �f�[�^���o�b�t�@��1�ȏ゠��ꍇ��true�A�Ȃ��ꍇ��false
	*/
	virtual bool isNew()
	{
		return true;
	};
};


/**
 * @class DataTypeInPort
*@brief ���I�ɐ�������C���|�[�g
*T�̓f�[�^�|�[�g�̃f�[�^�^(TimedDouble��)�AT2�͎擾����f�[�^�̌^(double��)
*/
template <class T, class T2>
class DataTypeInPort : public DynamicDataPortBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param name �f�[�^�|�[�g��
	* @param rtc RT�R���|�[�l���g
	*/
	DataTypeInPort(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		In = new T();
		inIn = new RTC::InPort<T>(name.c_str(),*In);
		m_rtc = rtc;
		m_rtc->addInPort(name.c_str(), *inIn);
	};
	/**
	*@brief �f�X�g���N�^
	*/
	~DataTypeInPort()
	{
		m_rtc->removePort(*inIn);
	};
	/**
	*@brief �f�[�^���o�b�t�@�ɗ��܂��Ă��邩�𔻒�
	* @return �f�[�^���o�b�t�@��1�ȏ゠��ꍇ��true�A�Ȃ��ꍇ��false
	*/
	bool isNew()
	{
		return inIn->isNew();
	};
	/**
	*@brief �f�[�^�|�[�g�̓��̓f�[�^�擾
	* @return �f�[�^
	*/
	T2 getData()
	{
		inIn->read();
		return In->data;
	};
	T *In;
	RTC::InPort<T> *inIn;
	RTC::DataFlowComponentBase *m_rtc;
};

/**
 * @class DataTypeOutPort
*@brief ���I�ɐ�������A�E�g�|�[�g
*T�̓f�[�^�|�[�g�̃f�[�^�^(TimedDouble��)�AT2�͎擾����f�[�^�̌^(double��)
*/
template <class T, class T2>
class DataTypeOutPort : public DynamicDataPortBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param name �f�[�^�|�[�g��
	* @param rtc RT�R���|�[�l���g
	*/
	DataTypeOutPort(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		Out = new T();
		outOut = new RTC::OutPort<T>(name.c_str(),*Out);
		m_rtc = rtc;
		m_rtc->addOutPort(name.c_str(), *outOut);
	};
	/**
	*@brief �f�X�g���N�^
	*/
	~DataTypeOutPort()
	{
		m_rtc->removePort(*outOut);
	};
	/**
	*@brief �f�[�^�|�[�g����f�[�^���o��
	* @param v �f�[�^
	*/
	void setData(T2 v)
	{
		Out->data = v;
		outOut->write();
	};
	T *Out;
	RTC::OutPort<T> *outOut;
	RTC::DataFlowComponentBase *m_rtc;
};


/**
 * @class DataTypeInPortSeq
*@brief ���I�ɐ�������C���|�[�g(�z��)
*T�̓f�[�^�|�[�g�̃f�[�^�^(TimedDouble��)�AT2�͎擾����f�[�^�̌^(double��)
*/
template <class T, class T2>
class DataTypeInPortSeq : public DynamicDataPortBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param name �f�[�^�|�[�g��
	* @param rtc RT�R���|�[�l���g
	*/
	DataTypeInPortSeq(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		In = new T();
		inIn = new RTC::InPort<T>(name.c_str(),*In);
		m_rtc = rtc;
		m_rtc->addInPort(name.c_str(), *inIn);
	};
	/**
	*@brief �f�X�g���N�^
	*/
	~DataTypeInPortSeq()
	{
		m_rtc->removePort(*inIn);
	};
	/**
	*@brief �f�[�^���o�b�t�@�ɗ��܂��Ă��邩�𔻒�
	* @return �f�[�^���o�b�t�@��1�ȏ゠��ꍇ��true�A�Ȃ��ꍇ��false
	*/
	bool isNew()
	{
		return inIn->isNew();
	};
	/**
	*@brief �f�[�^�|�[�g�̓��̓f�[�^�擾
	* @return �f�[�^�̃��X�g
	*/
	std::vector<T2> getData()
	{
		inIn->read();
		std::vector<T2> ans;
		for(int i=0;i < In->data.length();i++)
		{
			ans.push_back(In->data[i]);
		}
		return ans;
	};
	T *In;
	RTC::InPort<T> *inIn;
	RTC::DataFlowComponentBase *m_rtc;
};

/**
 * @class DataTypeOutPortSeq
*@brief ���I�ɐ�������C���|�[�g(�z��)
*T�̓f�[�^�|�[�g�̃f�[�^�^(TimedDouble��)�AT2�͎擾����f�[�^�̌^(double��)
*/
template <class T, class T2>
class DataTypeOutPortSeq : public DynamicDataPortBase
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param name �f�[�^�|�[�g��
	* @param rtc RT�R���|�[�l���g
	*/
	DataTypeOutPortSeq(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		Out = new T();
		outOut = new RTC::OutPort<T>(name.c_str(),*Out);
		m_rtc = rtc;
		m_rtc->addOutPort(name.c_str(), *outOut);
	};
	/**
	*@brief �f�X�g���N�^
	*/
	~DataTypeOutPortSeq()
	{
		m_rtc->removePort(*outOut);
	};
	/**
	*@brief �f�[�^�|�[�g����f�[�^���o��
	* @param v �f�[�^�̔z��
	*/
	void setData(std::vector<T2> v)
	{
		//Out->data = v;
		Out->data.length(v.size());
		for(int i=0;i < v.size();i++)
		{
			Out->data[i] = v[i];
		}
		outOut->write();
	};
	T *Out;
	RTC::OutPort<T> *outOut;
	RTC::DataFlowComponentBase *m_rtc;
};


/**
 * @class DynamicPortConfigUpdateParam
*@brief �R���t�B�M�����[�V�����p�����[�^�X�V���̃��X�i
*/
class DynamicPortConfigUpdateParam
    : public RTC::ConfigurationSetListener
{
public:
	/**
	*@brief �R���X�g���N�^
	* @param e_rtc RT�R���|�[�l���g
	*/
    DynamicPortConfigUpdateParam(DynamicComponentBase *rtc)
    {
		m_rtc = rtc;
    }
	/**
	*@brief �R���t�B�M�����[�V�����p�����[�^�ύX���ɌĂяo�����֐�
	* @param config_set 
	*/
    void operator()(const coil::Properties& config_set)
	{
		
		m_rtc->configUpdate();
		
    }
	DynamicComponentBase *m_rtc; /**<�@@brief  */

};


/**
*@brief �f�[�^�|�[�g�̃��X�g�X�V
*T�̓f�[�^�|�[�g�̃f�[�^�^
* @param v �f�[�^�|�[�g�̃��X�g
* @param num �V�K�ɐݒ肷��f�[�^�|�[�g�̐�
* @param id �f�[�^�|�[�g��
* @param rtc RT�R���|�[�l���g
*/
template <class T>
void updatePortList(std::vector<T*> &v, int num, std::string id, RTC::DataFlowComponentBase* rtc)
{
	
	if(num > v.size())
	{
		for(int i=v.size();i < num;i++)
		{
			std::string name = id + coil::otos<int>(i);

			T* iep = new T(name, rtc);

			v.push_back(iep);

		}
		
	}
	else if(num < v.size())
	{
		for (typename std::vector<T*>::iterator it = v.begin()+num; it != v.end();)
		{
			delete *it;
			it = v.erase( it );
		}
	}
};



#endif 
