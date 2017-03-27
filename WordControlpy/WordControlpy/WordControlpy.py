#!/bin/env python
# -*- encoding: cp932 -*-

##
#   @file WordControlpy.py
#   @brief WordControlpy Component






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

from WriterControl import *
from WordObject import *


wordcontrolpy_spec = ["implementation_id", "WordControlpy",
                  "type_name",         "WordControlpy",
                  "description",       "Word Component",
                  "version",           "0.1",
                  "vendor",            "Miyamoto Nobuhiko",
                  "category",          "Office",
                  "activity_type",     "DataFlowComponent",
                  "max_instance",      "10",
                  "language",          "Python",
                  "lang_type",         "script",
                  "conf.default.file_path", "NewFile",
                  "conf.default.fontsize", "16",
                  #"conf.default.fontname", "�l�r ����",
                  "conf.default.char_Red", "0",
                  "conf.default.char_Blue", "0",
                  "conf.default.char_Green", "0",
                  "conf.default.italic", "0",
                  "conf.default.bold", "0",
                  "conf.default.underline", "0",
                  "conf.default.shadow", "0",
                  "conf.default.strikeout", "0",
                  "conf.default.contoured", "0",
                  "conf.default.emphasis", "0",
                  "conf.default.back_Red", "255",
                  "conf.default.back_Blue", "255",
                  "conf.default.back_Green", "255",
                  "conf.default.code", "utf-8",
                  "conf.__widget__.file_path", "text",
                  "conf.__widget__.fontsize", "spin",
                  #"conf.__widget__.fontname", "radio",
                  "conf.__widget__.char_Red", "spin",
                  "conf.__widget__.char_Blue", "spin",
                  "conf.__widget__.char_Green", "spin",
                  "conf.__widget__.italic", "radio",
                  "conf.__widget__.bold", "radio",
                  "conf.__widget__.underline", "radio",
                  "conf.__widget__.shadow", "radio",
                  "conf.__widget__.strikeout", "radio",
                  "conf.__widget__.contoured", "radio",
                  "conf.__widget__.emphasis", "radio",
                  "conf.__widget__.back_Red", "spin",
                  "conf.__widget__.back_Blue", "spin",
                  "conf.__widget__.back_Green", "spin",
                  "conf.__widget__.code", "radio",
                  "conf.__constraints__.fontsize", "1<=x<=72",
                  #"conf.__constraints__.fontname", "(MS UI Gothic,MS �S�V�b�N,MS P�S�V�b�N,MS ����,MS P����,HG �S�V�b�N E,HGP �S�V�b�N E,HGS �S�V�b�N E,HG �S�V�b�N M,HGP �S�V�b�N M,HGS �S�V�b�N M,HG ��������-PRO,HG �ۃS�V�b�N M-PRO,HG ���ȏ���,HGP ���ȏ���,HGS ���ȏ���,HG �s����,HGP �s����,HGS �s����,HG �n�p�v���[���X EB,HGP �n�p�v���[���X EB,HGS �n�p�v���[���X EB,HG �n�p�p�S�V�b�N UB,HGP �n�p�p�S�V�b�N UB,HGS �n�p�p�S�V�b�N UB,HG �n�p�p�|�b�v��,HGP �n�p�p�|�b�v��,HGS �n�p�p�|�b�v��,HG ���� B,HGP ���� B,HGS ���� B,HG ���� E,HGP ���� E,HGS ���� E,���C���I)",
                  "conf.__constraints__.char_Red", "0<=x<=255",
                  "conf.__constraints__.char_Blue", "0<=x<=255",
                  "conf.__constraints__.char_Green", "0<=x<=255",
                  "conf.__constraints__.italic", "(0,1)",
                  "conf.__constraints__.bold", "(0,1)",
                  "conf.__constraints__.underline", "(0,1)",
                  "conf.__constraints__.shadow", "(0,1)",
                  "conf.__constraints__.strikeout", "(0,1)",
                  "conf.__constraints__.contoured", "(0,1)",
                  "conf.__constraints__.emphasis", "(0,1)",
                  "conf.__constraints__.back_Red", "0<=x<=255",
                  "conf.__constraints__.back_Blue", "0<=x<=255",
                  "conf.__constraints__.back_Green", "0<=x<=255",
                  "conf.__constraints__.code", "(utf-8,euc_jp,shift_jis)",
                  ""]




##
# @class WordConfigUpdateParam
# @brief �R���t�B�M�����[�V�����p�����[�^���X�V���ꂽ�Ƃ��̃R�[���o�b�N
#

class WordConfigUpdateParam(OpenRTM_aist.ConfigurationSetListener):
    ##
    # @brief �R���X�g���N�^
    # @param self 
    # @param e_rtc OOoCalcRTC
    #
   def __init__(self,e_rtc):
        self.m_rtc =  e_rtc

    ##
    # @brief 
    # @param self 
    # @param config_param_name 
    #
   def __call__(self, config_param_name):
        self.m_rtc.configUpdate()

   


##
# @class WordControlpy
# @brief Word�𑀍삷�邽�߂�RTC�̃N���X
#

class WordControlpy(WriterControl):
    ##
    # @brief �R���X�g���N�^
    # @param self 
    # @param manager �}�l�[�W���[�I�u�W�F�N�g
    #
  def __init__(self, manager):
    WriterControl.__init__(self, manager)
    
    """prop = OpenRTM_aist.Manager.instance().getConfig()
    fn = self.getProperty(prop, "word.filename", "")
    self.m_word = WordObject()
    if fn != "":
      str1 = [fn]
      OpenRTM_aist.replaceString(str1,"/","\\")
      fn = os.path.abspath(str1[0])
    self.m_word.Open(fn)"""

    self.conf_filename = ["NewFile"]
    
    
    
    
    
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
      self.m_word.initCom()
      if sfn == "NewFile":
        self.m_word.Open("")
      else:
        print sfn,tfn
        self.m_word.Open(tfn)"""

      #self.m_word.closeCom()
        
      
  
  ##
  # @brief �����������݂̊֐�
  # @param self 
  # @param m_str �������ޕ�����
  #

  def setWord(self, m_str):
      self.m_word.setFontColor(self.char_Red, self.char_Green, self.char_Blue)
      self.m_word.setBackColor(self.back_Red, self.back_Green, self.back_Blue)
      self.m_word.setFontSize(self.fontSize)
      self.m_word.setFontName(self.fontName)
      self.m_word.bold = self.bold
      #print SetCoding(m_str, self.conf_Code[0])
      self.m_word.setWord(SetCoding(m_str, self.conf_Code[0]))


  ##
  # @brief �J�[�\���ʒu�̕����擾�̊֐�
  # @param self
  # @return �J�[�\���ʒu�̕�����
  #

  def getWord(self):
      return self.m_word.getSelWord()


  ##
  # @brief �����������p�R�[���o�b�N�֐�
  # @param self 
  # @return RTC::ReturnCode_t
  def onInitialize(self):
    WriterControl.onInitialize(self)

    self.bindParameter("file_path", self.conf_filename, "NewFile")

    self._configsets.update("default","file_path")
    self.m_word = WordObject()
    fn = self.conf_filename[0]
    
    if fn == "NewFile":
        fn = ""

    if fn != "":
      str1 = [fn]
      OpenRTM_aist.replaceString(str1,"/","\\")
      fn = os.path.abspath(str1[0])
    
    self.m_word.Open(fn)


    self.addConfigurationSetListener(OpenRTM_aist.ConfigurationSetListenerType.ON_SET_CONFIG_SET, WordConfigUpdateParam(self))
    
    return RTC.RTC_OK
   
  ##
  # @brief �����������p�R�[���o�b�N�֐�
  # @param self 
  # @param ec_id target ExecutionContext Id
  # @return RTC::ReturnCode_t
  
  def onActivated(self, ec_id):
    WriterControl.onActivated(self, ec_id)
    
    

    #self.file = open('text3.txt', 'w')

    self.m_word.initCom()
    
    return RTC.RTC_OK


  ##
  # @brief �s�����������p�R�[���o�b�N�֐�
  # @param self 
  # @param ec_id target ExecutionContext Id
  # @return RTC::ReturnCode_t
  
  def onDeactivated(self, ec_id):
    WriterControl.onDeactivated(self, ec_id)
    #self.m_word.closeCom()
    #self.file.close()
    return RTC.RTC_OK


  ##
  # @brief ���������p�R�[���o�b�N�֐�
  # @param self 
  # @param ec_id target ExecutionContext Id
  # @return RTC::ReturnCode_t
  
  def onExecute(self, ec_id):
    WriterControl.onExecute(self, ec_id)
        

    return RTC.RTC_OK

  
  ##
  # @brief �I�������p�R�[���o�b�N�֐�
  # @param self 
  # @param ec_id target ExecutionContext Id
  # @return RTC::ReturnCode_t
  
  def on_shutdown(self, ec_id):
      WriterControl.on_shutdown(self, ec_id)
      return RTC.RTC_OK


  
  
  
      

  ##
  # @brief �������ړ�����֐�
  # @param self 
  # @param diff �ړ����镶����
  #
  def moveCharacter(self, diff):
      self.m_word.moveSelection(WordObject.wdCharacter,diff)
          
  ##
  # @brief �P�ꐔ�ړ�����֐�
  # @param self 
  # @param diff �ړ�����P�ꐔ
  #
  def moveWord(self, diff):
      self.m_word.moveSelection(WordObject.wdWord,diff)

  ##
  # @brief �s���ړ�����֐�
  # @param self 
  # @param diff �ړ�����s��
  #
  def moveLine(self, diff):
      self.m_word.moveSelection(WordObject.wdLine,diff)

  ##
  # @brief �i�����ړ�����֐�
  # @param self 
  # @param diff �ړ�����i����
  #
  def moveParagraph(self, diff):
      self.m_word.moveSelection(WordObject.wdParagraph,diff)

  ##
  # @brief �E�C���h�E���ړ�����֐�
  # @param self 
  # @param diff �ړ�����i����
  #
  def moveWindow(self, diff):
      self.m_word.moveSelection(WordObject.wdWindow,diff)

  ##
  # @brief �X�N���[�����ړ�����֐�
  # @param self 
  # @param diff �ړ�����i����
  #
  def moveScreen(self, diff):
      self.m_word.moveSelection(WordObject.wdScreen,diff)




##
# @brief
# @param manager �}�l�[�W���[�I�u�W�F�N�g
def MyModuleInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=wordcontrolpy_spec)
    manager.registerFactory(profile,
                            WordControlpy,
                            OpenRTM_aist.Delete)
    comp = manager.createComponent("WordControlpy")

def main():
    
    
    
    mgr = OpenRTM_aist.Manager.init(sys.argv)
    mgr.setModuleInitProc(MyModuleInit)
    mgr.activateManager()
    mgr.runManager()

    
if __name__ == "__main__":
    main()
