/*!
* @file  MultipleOrderedEC.h
* @brief 実行順序の設定ができる実行コンテキスト
*
*/

#ifndef RTC_MUTIPLEORDEREDEC_H
#define RTC_MUTIPLEORDEREDEC_H

#include <rtm/RTC.h>



#include <rtm/Manager.h>
#include <rtm/PeriodicExecutionContext.h>

#include "MPComp.h"


#ifdef WIN32
#pragma warning( disable : 4290 )
#endif

class MPTask;
class GUITask;

namespace RTC_exp
{
  
	/**
	* @class MultipleOrderedEC
	*@brief 実行順序の設定ができる実行コンテキスト
	*/
  class MultipleOrderedEC
    : public virtual PeriodicExecutionContext
  {
	  typedef coil::Guard<coil::Mutex> Guard;
  public:
	/**
	*@brief コンストラクタ
	*/
    MultipleOrderedEC();

	/**
	*@brief デストラクタ
	*/
    virtual ~MultipleOrderedEC(void);

	
	/**
	*@brief スレッド実行関数
	* @return
	*/
    virtual int svc(void);
	
	/**
	*@brief コンポーネントのロジック実行の関数
	* @param c ブロック
	*/
	void workerComp(sub_Rule *c);

	
	
	/**
	*@brief ファイルから実行順序の読み込みの関数
	*/
	void LoadRule();

	
	
	/**
	*@brief 番号からコンポーネントの名前取得の関数
	* @param num 番号
	* @return RTC名
	*/
	std::string getCompName(int num);
	
	/**
	*@brief コンポーネントの数取得の関数
	* @return RTC数
	*/
	int getCompNum();

	
	/**
	*@brief GUIから実行順序の読み込みの関数
	* @param RS_d 実行順序のリスト
	*/
	void LoadRuleGUI(std::vector<main_Rule> &RS_d);

	/**
	*@brief 設定した実行順序のRTCを格納する関数
	*/
	void LoadRules();

	std::vector<main_Rule> rs;
	GUITask *g_task;

	int r_num;
	std::vector<RTC::RTObject_ptr> m_comps;

	coil::Mutex mutex_2;
	coil::Mutex work_mutex;

	std::string FileName;
	std::string SetGui;

	//std::vector<Comp> s_comp;
	/**
	*@brief rtc.confの設定を取得する関数
	* @param prop プロパティ
	* @param key キー
	* @param value 値
	*/
	template <class T>
    void getProperty(coil::Properties& prop, const char* key, T& value)
    {
    if (prop.findNode(key) != 0)
      {
        T tmp;
        if (coil::stringTo(tmp, prop[key].c_str()))
          {
            value = tmp;
          }
      }
    }

  protected:
	  // template virtual functions adding/removing component
	  /*!
	  * @brief onAddedComponent() template function
	  */
	  virtual RTC::ReturnCode_t
		  onAddedComponent(RTC::LightweightRTObject_ptr rtobj);
	  /*!
	  * @brief onRemovedComponent() template function
	  */
	  virtual RTC::ReturnCode_t
		  onRemovedComponent(RTC::LightweightRTObject_ptr rtobj);
	
	  typedef std::vector<RTC::RTObject_ptr>::iterator CompItr;



  };
};

#ifdef WIN32
#pragma warning( default : 4290 )
#endif


extern "C"
{
  DLL_EXPORT void MultipleOrderedECInit(RTC::Manager* manager);
};

#endif
