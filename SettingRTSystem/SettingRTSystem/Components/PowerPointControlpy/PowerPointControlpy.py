#!/bin/env python
# -*- encoding: cp932 -*-

##
#   @file PowerPointControlpy.py
#   @brief PowerPointControlpy Component




import optparse
import sys,os,platform
import re
import time
import random
import commands
import math



import RTC
import OpenRTM_aist

from OpenRTM_aist import CorbaNaming
from OpenRTM_aist import RTObject
from OpenRTM_aist import CorbaConsumer
from omniORB import CORBA
import CosNaming

from ImpressControl import *
from PowerPointObject import *


powerpointcontrolpy_spec = ["implementation_id", "PowerPointControlpy",
                  "type_name",         "PowerPointControlpy",
                  "description",       "PowerPoint Component",
                  "version",           "0.1",
                  "vendor",            "Miyamoto Nobuhiko",
                  "category",          "Office",
                  "activity_type",     "DataFlowComponent",
                  "max_instance",      "10",
                  "language",          "Python",
                  "lang_type",         "script",
                  "conf.default.file_path", "NewFile",
                  "conf.default.SlideNumberInRelative", "1",
                  "conf.default.SlideFileInitialNumber", "0",
                  "conf.__widget__.file_path", "text",
                  "conf.__widget__.SlideNumberInRelative", "radio",
                  "conf.__widget__.SlideFileInitialNumber", "spin",
                  "conf.__constraints__.SlideNumberInRelative", "(0,1)",
                  "conf.__constraints__.SlideFileInitialNumber", "0<=x<=1000",
                  ""]




   


##
# @class PowerPointControlpy
# @brief PowerPoint�𑀍삷�邽�߂�RTC�̃N���X
#

class PowerPointControlpy(ImpressControl):
    ##
    # @brief �R���X�g���N�^
    # @param self 
    # @param manager �}�l�[�W���[�I�u�W�F�N�g
    #
  def __init__(self, manager):
    ImpressControl.__init__(self, manager)
    
    """prop = OpenRTM_aist.Manager.instance().getConfig()
    fn = self.getProperty(prop, "powerpoint.filename", "")
    self.m_powerpoint = PowerPointObject()
    
    if fn != "":
      str1 = [fn]
      OpenRTM_aist.replaceString(str1,"/","\\")
      fn = os.path.abspath(str1[0])
    self.m_powerpoint.Open(fn)"""

    self.conf_filename = ["NewFile"]

    self.slidenum = 0
    
    
    
    
    
    return

  ##
  # @brief rtc.conf�̐ݒ���擾����֐�
  #
  def getProperty(self, prop, key, value):
        
        if  prop.findNode(key) != None:
            #print value
            value = prop.getProperty(key)
        return value

  ##
  # @brief �R���t�B�M�����[�V�����p�����[�^���ύX���ꂽ�Ƃ��ɌĂяo�����֐�
  # @param self 
  #
  def configUpdate(self):
      return
      """self._configsets.update("default","file_path")
      str1 = [self.conf_filename[0]]
      OpenRTM_aist.replaceString(str1,"/","\\")
      sfn = str1[0]
      tfn = os.path.abspath(sfn)
      if sfn == "NewFile":
        self.m_powerpoint.Open("")
      else:
        print sfn,tfn
        self.m_powerpoint.initCom()
        self.m_powerpoint.Open(tfn)"""
        #self.m_powerpoint.closeCom()

  def onInitialize(self):
    ImpressControl.onInitialize(self)
    self.bindParameter("file_path", self.conf_filename, "NewFile")
    
    self._configsets.update("default","file_path")
    self.m_powerpoint = PowerPointObject()
    fn = self.conf_filename[0]
    
    if fn == "NewFile":
        fn = ""

    if fn != "":
      str1 = [fn]
      OpenRTM_aist.replaceString(str1,"/","\\")
      fn = os.path.abspath(str1[0])
    
    self.m_powerpoint.Open(fn)
    
    
    return RTC.RTC_OK

  ##
  # @brief ���`��
  # @param self 
  # @param bx 
  # @param by 
  # @param ex 
  # @param ey 
  def drawLine(self, bx, by, ex, ey):
    self.m_powerpoint.drawLine(bx, by, ex, ey)

  ##
  # @brief �X���C�h�ԍ��̐i�߂�A�߂�
  # @param self 
  # @param num �i�߂�X���C�h��
  def changeSlideNum(self, num):
    if self.SlideNumberInRelative[0] == 0:
      self.m_powerpoint.gotoSlide(num)
      self.slidenum = num
    else:
      
      self.m_powerpoint.gotoSlide(self.slidenum+num)
      self.slidenum += num


  ##
  # @brief �A�j���[�V������i�߂�A�߂�
  # @param self 
  # @param num �i�߂�A�j���[�V�����̐�
  def changeEffeceNum(self, num):
    if num > 0:
      for i in range(0, num):
        self.m_powerpoint.next()
    else:
      for i in range(0, -num):
        self.m_powerpoint.previous()

  ##
  # @brief �X���C�h�ԍ��擾
  # @param self 
  # @return �X���C�h�ԍ�
  def getSlideNum(self):
    return self.slidenum


  
  
  def onActivated(self, ec_id):
    ImpressControl.onActivated(self, ec_id)
    
    

    #self.file = open('text3.txt', 'w')

    self.m_powerpoint.initCom()
    self.m_powerpoint.run()
    self.m_powerpoint.gotoSlide(self.SlideFileInitialNumber[0])
    self.slidenum = self.SlideFileInitialNumber[0]
    
    return RTC.RTC_OK

  def onDeactivated(self, ec_id):
    ImpressControl.onDeactivated(self, ec_id)
    self.m_powerpoint.end()
    #self.file.close()
    return RTC.RTC_OK


  ##
  # @brief ���������p�R�[���o�b�N�֐�
  # @param self 
  # @param ec_id target ExecutionContext Id
  # @return RTC::ReturnCode_t
  
  def onExecute(self, ec_id):
    ImpressControl.onExecute(self, ec_id)
    

    return RTC.RTC_OK

  
  ##
  # @brief �I�������p�R�[���o�b�N�֐�
  # @param self 
  # @param ec_id target ExecutionContext Id
  # @return RTC::ReturnCode_t
  
  def on_shutdown(self, ec_id):
      ImpressControl.onExecute(self, ec_id)
      return RTC.RTC_OK


  
  
  
      

  



##
# @brief
# @param manager �}�l�[�W���[�I�u�W�F�N�g
def MyModuleInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=powerpointcontrolpy_spec)
    manager.registerFactory(profile,
                            PowerPointControlpy,
                            OpenRTM_aist.Delete)
    comp = manager.createComponent("PowerPointControlpy")

def main():
    """po = PowerPointObject()
    fn = os.path.abspath("1.pptx")
    po.Open(fn)
    po.run()
    po.gotoSlide(2)
    return"""
    
    
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()
    
if __name__ == "__main__":
    main()
