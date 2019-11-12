/*!
* @file  MultipleOrderedEC.cpp
* @brief 実行順序の設定ができる実行コンテキスト
*
*/


#include "MultipleOrderedEC.h"
#include <rtm/ECFactory.h>
#include <iostream>
#include <rtm/CorbaConsumer.h>
#include <rtm/idl/BasicDataTypeSkel.h>
#include <coil/stringutil.h>
#include <rtm/RTObjectStateMachine.h>


#include "MPTask.h"
#include "FileStreamFunc.h"

using namespace std;

namespace RTC_exp
{
	/**
	*@brief 実行順序の設定ができる実行コンテキストのコンストラクタ
	*/
  MultipleOrderedEC::MultipleOrderedEC()
	   : PeriodicExecutionContext()
  {
	  coil::Properties& prop(::RTC::Manager::instance().getConfig());
	  SetGui = "YES";
	  FileName = "";
	  getProperty(prop, "exec_cxt.periodic.gui", SetGui);
	  getProperty(prop, "exec_cxt.periodic.filename", FileName);

	  coil::eraseBlank(SetGui);
	  coil::eraseBlank(FileName);

	  /*if (FileName == "")
	  {
		  FileName = "CompList.conf";
	  }*/

	  if(SetGui == "YES")
	  {
#ifdef QT_GUI_LIB
		g_task = new GUITask(this);
		g_task->activate();
#endif
	  }



	  //main_Rule R;
	  //rs.push_back(R);

	  r_num = 0;

	  

	  

	  



	

  }

  /**
  *@brief 実行順序の設定ができる実行コンテキストのデストラクタ
  */
  MultipleOrderedEC::~MultipleOrderedEC()
  {
  }

  
   
  /**
  *@brief 番号からコンポーネントの名前取得の関数
  * @param num 番号
  * @return RTC名
  */
  std::string MultipleOrderedEC::getCompName(int num)
  {
	  mutex_2.lock();
	  RTC::ComponentProfile *mc = m_comps[num]->get_component_profile();
	  std::string Name = (const char*)mc->instance_name;
	
	  delete mc;
	   mutex_2.unlock();
	  return Name;
  }

  /**
  *@brief コンポーネントの数取得の関数
  * @return RTC数
  */
  int MultipleOrderedEC::getCompNum()
  {
	return m_comps.size();
  }

  /**
  *@brief コンポーネントのロジック実行の関数
  * @param c ブロック
  */
  void MultipleOrderedEC::workerComp(sub_Rule *c)
  {
	  
				
		CompItr it;
		


		
		RTC_impl::RTObjectStateMachine* rtobj = m_worker.findComponent(c->r);
		
		if (rtobj == NULL)
		{
			
			bool Flag = false;
			for(int i=0;i < m_comps.size();i++)
			{
				if(getCompName(i) == c->v)
				{
					c->r = m_comps[i];
					//m_comps[i]._sm.m_obj->get_ports();
					//m_comps[i]._sm.m_obj._retn()->get_ports()[0][0]->
				}
			}
			
		}
		else
		{
			
			rtobj->workerDo();
		}
	  
	  
  }

  /**
  *@brief ファイルから実行順序の読み込みの関数
  */
  void MultipleOrderedEC::LoadRules()
  {
	  mutex_2.lock();
	  for(int h=0;h < rs.size();h++)
	  {
		  for(int i=0;i < rs[h].ar.size();i++)
		  {
			  for(int j=0;j <  m_comps.size();j++)
			  {
				RTC::ComponentProfile *mc = m_comps[j]->get_component_profile();
				std::string Name = (const char*)mc->instance_name;
				
				delete mc;
				if(Name == rs[h].ar[i].name)
				{
					rs[h].ar[i].r = m_comps[j];
				}
			  }
		  }
		  for(int i=0;i < rs[h].rs.size();i++)
		  {
			  for(int j=0;j < rs[h].rs[i].SR.size();j++)
			  {
				  for(int k=0;k < rs[h].rs[i].SR[j].size();k++)
				  {
					for(int l=0;l < m_comps.size();l++)
					{
						RTC::ComponentProfile *mc = m_comps[l]->get_component_profile();
						std::string Name = (const char*)mc->instance_name;
						
						delete mc;
						
						if(Name == rs[h].rs[i].SR[j][k].v)
						{
							rs[h].rs[i].SR[j][k].r = m_comps[l];
							
						}
					}
				  }
			  }
		  }
	  }
	  mutex_2.unlock();


  }

  /**
  *@brief GUIから実行順序の読み込みの関数
  * @param RS_d 実行順序のリスト
  */
  void MultipleOrderedEC::LoadRuleGUI(std::vector<main_Rule> &RS_d)
  {

	  work_mutex.lock();

	  rs.clear();
	  rs = RS_d;

	  //LoadRules();

	  work_mutex.unlock();
  }

  /**
  *@brief ファイルから実行順序の読み込みの関数
  */
  void MultipleOrderedEC::LoadRule()
  {

	  
	  work_mutex.lock();
	
	
	
	
	for(int h=0;h < rs.size();h++)
		rs[h].rs.clear();
	rs.clear();

	
	LoadMainRule(rs, FileName);

	//LoadRules();
	

	work_mutex.unlock();
	

  }

  /**
  *@brief スレッド実行関数
  * @return
  */
  int MultipleOrderedEC::svc(void)
  {
	  RTC_TRACE(("svc()"));
      int count(0);

	  LoadRule();
	  
	  
	  do{
		  
		  ExecutionContextBase::invokeWorkerPreDo();
		  {
			  Guard guard(m_workerthread.mutex_);
			  while (!m_workerthread.running_)
			  {
				  m_workerthread.cond_.wait();
			  }
		  }
			
			coil::TimeValue t0(coil::gettimeofday());
			work_mutex.lock();
			//std::cout << m_comps.size() << std::endl;
			for(int i=0;i < rs.size();i++)
			{
				bool S = true;
				for(int j=0;j < rs[i].ar.size();j++)
				{
					bool Flag = false;
					for(int k=0;k < m_comps.size();k++)
					{
						if(rs[i].ar[j].r == m_comps[k])
						{
							Flag = true;
							if(rs[i].ar[j].state == -1)
							{

							}
							else
							{
								RTC_impl::RTObjectStateMachine* rtobj = m_worker.findComponent(m_comps[k]);
								if (rtobj != NULL)
								{
									if (rs[i].ar[j].state != rtobj->getState())
									{
										S = false;
									}
								}
							}
						}
					}
					if(!Flag)
					{
							
						for(int k=0;k < m_comps.size();k++)
						{
							if(getCompName(k) == rs[i].ar[j].name)
							{
								rs[i].ar[j].r = m_comps[k];
								if(rs[i].ar[j].state == -1)
								{

								}
								else
								{
									RTC_impl::RTObjectStateMachine* rtobj = m_worker.findComponent(m_comps[k]);
									if (rtobj != NULL)
									{
										if (rs[i].ar[j].state != rtobj->getState())
										{
											S = false;
										}
									}
								}
							}
						}
					}

				}

					
				if(S)
				{
					r_num = i;
					break;
				}
			}

				
			{
				
				
				if(r_num < rs.size())
				{
					for(int i=0;i < rs[r_num].rs.size();i++)
					{
						
						//std::cout << rs[r_num].rs[i].SR.size() << std::endl;
						if(rs[r_num].rs[i].SR.size() == 0)
						{

						}
						else if(rs[r_num].rs[i].SR.size() == 1)
						{
							for(int j=0;j < rs[r_num].rs[i].SR[0].size();j++)
							{
								rs[r_num].rs[i].SR[0][j].s = 1;
								workerComp(&rs[r_num].rs[i].SR[0][j]);
								rs[r_num].rs[i].SR[0][j].s = 0;

							}
						}
						else
						{
							int p_num = rs[r_num].rs[i].SR.size();
							MPTask **m_task = new MPTask *[p_num];
							for(int j=0;j < p_num;j++)
							{
								
								m_task[j] = new MPTask(this);
								for(int k=0;k < rs[r_num].rs[i].SR[j].size();k++)
								{
									m_task[j]->addComp(&rs[r_num].rs[i].SR[j][k],i,j,k);
								}
								m_task[j]->activate();
							}

							for(int j=0;j < p_num;j++)
							{
								m_task[j]->wait();
								m_task[j]->close();
								delete m_task[j];
							}
							coil::TimeValue T0(coil::gettimeofday());
				
							/*coil::Task *mTask = new coil::Task();
							mTask->close();
							delete mTask;

							coil::TimeValue T1(coil::gettimeofday());
							std::cout << T1 - T0 << std::endl;*/

							

							delete m_task;
						}
					}
				}

			}
			
			work_mutex.unlock();
			ExecutionContextBase::invokeWorkerPostDo();

			coil::TimeValue t1(coil::gettimeofday());

			coil::TimeValue period(getPeriod());
			if (count > 1000)
			{
				RTC_PARANOID(("Period:    %f [s]", (double)period));
				RTC_PARANOID(("Execution: %f [s]", (double)(t1 - t0)));
				RTC_PARANOID(("Sleep:     %f [s]", (double)(period - (t1 - t0))));
			}
			coil::TimeValue t2(coil::gettimeofday());
			if (!m_nowait && period > (t1 - t0))
			{
				if (count > 1000) { RTC_PARANOID(("sleeping...")); }
				coil::sleep((coil::TimeValue)(period - (t1 - t0)));
			}
			if (count > 1000)
			{
				coil::TimeValue t3(coil::gettimeofday());
				RTC_PARANOID(("Slept:     %f [s]", (double)(t3 - t2)));
				count = 0;
			}
			++count;

			
			
	  }while (threadRunning());

    
    return 0;
  }

  // template virtual functions adding/removing component
  /*!
  * @brief onAddedComponent() template function
  */
  RTC::ReturnCode_t MultipleOrderedEC::
	  onAddedComponent(RTC::LightweightRTObject_ptr rtobj)
  {
	  
	  PeriodicExecutionContext::onAddedComponent(rtobj);
	  RTC::RTObject_ptr obj = RTC::RTObject::_narrow(rtobj);
	  m_comps.push_back(obj);
	  return RTC::RTC_OK;
  }
  /*!
  * @brief onRemovedComponent() template function
  */
  RTC::ReturnCode_t MultipleOrderedEC::
	  onRemovedComponent(RTC::LightweightRTObject_ptr rtobj)
  {
	  PeriodicExecutionContext::onRemovedComponent(rtobj);
	  for (CompItr itr = m_comps.begin(); itr != m_comps.end(); ++itr) {
		  if ((*itr)->_is_equivalent(rtobj))
		  {
			  m_comps.erase(itr);
		  }
	  }
	  return RTC::RTC_OK;
  }



};



extern "C"
{
   void MultipleOrderedECInit(RTC::Manager* manager)
  {
	RTC::ExecutionContextFactory::
		instance().addFactory("MultipleOrderedEC",
		::coil::Creator< ::RTC::ExecutionContextBase,
		::RTC_exp::MultipleOrderedEC>,
		::coil::Destructor< ::RTC::ExecutionContextBase,
		::RTC_exp::MultipleOrderedEC>);
  }
};
