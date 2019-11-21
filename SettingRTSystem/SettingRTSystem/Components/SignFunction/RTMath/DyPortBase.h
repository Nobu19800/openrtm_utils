/*!
 * @file  RTMath.h
 * @brief データポート関連の関数
 *
 */


#ifndef DYPORTBASE_H
#define DYPORTBASE_H

#include <rtm/DataFlowComponentBase.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>



/**
 * @class DynamicComponentBase
*@brief コンフィギュレーションパラメータのコールバック時にconfigUpdate関数を呼び出すコンポーネント
*/
class DynamicComponentBase
  : public RTC::DataFlowComponentBase
{
 public:
	/**
	*@brief コンストラクタ
	* @param managerマネージャオブジェクト
	*/
	DynamicComponentBase(RTC::Manager* manager) : RTC::DataFlowComponentBase(manager)
	{
		
	};
	/**
	*@brief コンフィギュレーションパラメータ更新時に呼び出される関数
	*/
	virtual void configUpdate(){};
};


/**
 * @class RTCLogicBase
*@brief RTCに実装するロジックの基本クラス
*各コールバックはRTCの該当するコールバック時に呼び出されるように記述する
*/
class RTCLogicBase
{
public:
	/**
	*@brief デストラクタ
	*/
	virtual ~RTCLogicBase()
	{
	}
	/**
	*@brief 初期化処理用コールバック関数
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onInitialize(){return RTC::RTC_OK;};
	/**
	*@brief 終了処理用コールバック関数
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onFinalize(){return RTC::RTC_OK;};
	/**
	*@brief 開始処理用コールバック関数
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief 停止処理用コールバック関数
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief 活性化時コールバック関数
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief 不活性化時コールバック関数
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief 周期処理用コールバック関数
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief 中断処理用コールバック関数
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief エラー処理用コールバック関数
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief リセット処理用コールバック関数
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief 状態変更処理用コールバック関数
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	/**
	*@brief 実行周期変更時コールバック関数
	* @param ec_id target ExecutionContext Id
	* @return RTC::ReturnCode_t
	*/
	virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id){return RTC::RTC_OK;};
	
};

/**
 * @class DynamicDataPortBase
*@brief 動的に生成するデータポートの基本クラス
*/
class DynamicDataPortBase
{
public:
	/**
	*@brief デストラクタ
	*/
	virtual ~DynamicDataPortBase()
	{
	}
	/**
	*@brief データがバッファに溜まっているかを判定
	* @return データがバッファに1つ以上ある場合はtrue、ない場合はfalse
	*/
	virtual bool isNew()
	{
		return true;
	};
};


/**
 * @class DataTypeInPort
*@brief 動的に生成するインポート
*Tはデータポートのデータ型(TimedDouble等)、T2は取得するデータの型(double等)
*/
template <class T, class T2>
class DataTypeInPort : public DynamicDataPortBase
{
public:
	/**
	*@brief コンストラクタ
	* @param name データポート名
	* @param rtc RTコンポーネント
	*/
	DataTypeInPort(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		In = new T();
		inIn = new RTC::InPort<T>(name.c_str(),*In);
		m_rtc = rtc;
		m_rtc->addInPort(name.c_str(), *inIn);
	};
	/**
	*@brief デストラクタ
	*/
	~DataTypeInPort()
	{
		m_rtc->removePort(*inIn);
	};
	/**
	*@brief データがバッファに溜まっているかを判定
	* @return データがバッファに1つ以上ある場合はtrue、ない場合はfalse
	*/
	bool isNew()
	{
		return inIn->isNew();
	};
	/**
	*@brief データポートの入力データ取得
	* @return データ
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
*@brief 動的に生成するアウトポート
*Tはデータポートのデータ型(TimedDouble等)、T2は取得するデータの型(double等)
*/
template <class T, class T2>
class DataTypeOutPort : public DynamicDataPortBase
{
public:
	/**
	*@brief コンストラクタ
	* @param name データポート名
	* @param rtc RTコンポーネント
	*/
	DataTypeOutPort(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		Out = new T();
		outOut = new RTC::OutPort<T>(name.c_str(),*Out);
		m_rtc = rtc;
		m_rtc->addOutPort(name.c_str(), *outOut);
	};
	/**
	*@brief デストラクタ
	*/
	~DataTypeOutPort()
	{
		m_rtc->removePort(*outOut);
	};
	/**
	*@brief データポートからデータを出力
	* @param v データ
	*/
	void setData(T2 v)
	{
		Out->data = v;
		setTimestamp(*Out);
		outOut->write();
	};
	T *Out;
	RTC::OutPort<T> *outOut;
	RTC::DataFlowComponentBase *m_rtc;
};


/**
 * @class DataTypeInPortSeq
*@brief 動的に生成するインポート(配列)
*Tはデータポートのデータ型(TimedDouble等)、T2は取得するデータの型(double等)
*/
template <class T, class T2>
class DataTypeInPortSeq : public DynamicDataPortBase
{
public:
	/**
	*@brief コンストラクタ
	* @param name データポート名
	* @param rtc RTコンポーネント
	*/
	DataTypeInPortSeq(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		In = new T();
		inIn = new RTC::InPort<T>(name.c_str(),*In);
		m_rtc = rtc;
		m_rtc->addInPort(name.c_str(), *inIn);
	};
	/**
	*@brief デストラクタ
	*/
	~DataTypeInPortSeq()
	{
		m_rtc->removePort(*inIn);
	};
	/**
	*@brief データがバッファに溜まっているかを判定
	* @return データがバッファに1つ以上ある場合はtrue、ない場合はfalse
	*/
	bool isNew()
	{
		return inIn->isNew();
	};
	/**
	*@brief データポートの入力データ取得
	* @return データのリスト
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
*@brief 動的に生成するインポート(配列)
*Tはデータポートのデータ型(TimedDouble等)、T2は取得するデータの型(double等)
*/
template <class T, class T2>
class DataTypeOutPortSeq : public DynamicDataPortBase
{
public:
	/**
	*@brief コンストラクタ
	* @param name データポート名
	* @param rtc RTコンポーネント
	*/
	DataTypeOutPortSeq(std::string name, RTC::DataFlowComponentBase *rtc)
	{
		Out = new T();
		outOut = new RTC::OutPort<T>(name.c_str(),*Out);
		m_rtc = rtc;
		m_rtc->addOutPort(name.c_str(), *outOut);
	};
	/**
	*@brief デストラクタ
	*/
	~DataTypeOutPortSeq()
	{
		m_rtc->removePort(*outOut);
	};
	/**
	*@brief データポートからデータを出力
	* @param v データの配列
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
*@brief コンフィギュレーションパラメータ更新時のリスナ
*/
class DynamicPortConfigUpdateParam
    : public RTC::ConfigurationSetListener
{
public:
	/**
	*@brief コンストラクタ
	* @param e_rtc RTコンポーネント
	*/
    DynamicPortConfigUpdateParam(DynamicComponentBase *rtc)
    {
		m_rtc = rtc;
    }
	/**
	*@brief コンフィギュレーションパラメータ変更時に呼び出される関数
	* @param config_set 
	*/
    void operator()(const coil::Properties& config_set)
	{
		
		m_rtc->configUpdate();
		
    }
	DynamicComponentBase *m_rtc; /**<　@brief  */

};


/**
*@brief データポートのリスト更新
*Tはデータポートのデータ型
* @param v データポートのリスト
* @param num 新規に設定するデータポートの数
* @param id データポート名
* @param rtc RTコンポーネント
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
