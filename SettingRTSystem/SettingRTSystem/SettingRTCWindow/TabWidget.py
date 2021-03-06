#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file TabWidget.py
#   @brief タブの基本ウィジェット



import optparse
import sys,os,platform
import re
import time
import random
import math
import imp



import RTC
import OpenRTM_aist

from OpenRTM_aist import CorbaNaming
from OpenRTM_aist import RTObject
from OpenRTM_aist import CorbaConsumer
from omniORB import CORBA
import CosNaming

from PyQt5 import QtCore, QtWidgets

from SettingRTCConf.ConfigWidget import ConfigWidget
from SettingRTCConf.CorbaWidget import CorbaWidget
from SettingRTCConf.ExecCxtWidget import ExecCxtWidget
from SettingRTCConf.LoggerWidget import LoggerWidget
from SettingRTCWindow.ManagerControl import ManagerControl
from SettingRTCConf.ManagerWidget import ManagerWidget
from SettingRTCConf.NamingWidget import NamingWidget
from SettingRTCConf.TimerWidget import TimerWidget


##
# @class MTabWidget
# @brief 各言語の設定データ表示表示タブのウィジェット
#
class TabWidget(QtWidgets.QTabWidget):
    ##
    # @brief コンストラクタ
    # @param self 
    # @param mgrc マネージャ操作オブジェクト
    # @param language 言語
    # @param parent 親ウィジェット
    def __init__(self, mgrc, language="Python", parent=None):
        super(TabWidget, self).__init__(parent)
        self.language = language
        self.mgrc = mgrc
        
        
        self.createTabs()
        

    ##
    # @brief タブ作成
    # @param self 
    def createTabs(self):
        self.Tabs = []
        self.ManagerTab = ManagerWidget(self.mgrc,self.language)
        self.addTab(self.ManagerTab, u"マネージャ")
        self.Tabs.append(self.ManagerTab)
        self.CorbaTab = CorbaWidget(self.mgrc)
        self.addTab(self.CorbaTab, u"CORBA")
        self.Tabs.append(self.CorbaTab)
        self.ConfigTab = ConfigWidget(self.mgrc)
        self.addTab(self.ConfigTab, u"一般的")
        self.Tabs.append(self.ConfigTab)
        self.NamingTab = NamingWidget(self.mgrc)
        self.addTab(self.NamingTab, u"ネームサービス")
        self.Tabs.append(self.NamingTab)
        self.LoggerTab = LoggerWidget(self.mgrc)
        self.addTab(self.LoggerTab, u"ロガー")
        self.Tabs.append(self.LoggerTab)
        self.TimerTab = TimerWidget(self.mgrc)
        self.addTab(self.TimerTab, u"タイマ")
        self.Tabs.append(self.TimerTab)
        self.ExecCxtTab = ExecCxtWidget(self.mgrc, self.ManagerTab,self.language)
        self.addTab(self.ExecCxtTab, u"実行コンテキスト")
        self.Tabs.append(self.ExecCxtTab)

    ##
    # @brief 設定データ取得
    # @param self
    # @return 設定データ
    def getConfData(self):
        datas = []
        for t in self.Tabs:
            for k,j in t.WidList.items():
                if k.split(".")[-1] != "sub":
                    d = {}
                    d["name"] = k
                    d["value"] = ""
                    if j["Type"] == ManagerControl.TextBox:
                        try:
                            d["value"] = str(j["Widget"].text().toLocal8Bit())
                        except:
                            d["value"] = j["Widget"].text()
                    elif j["Type"] == ManagerControl.TextCombox or j["Type"] == ManagerControl.Combox:
                        
                        
                        if k == "manager.modules.load_path" or k == "manager.modules.preload" or k == "manager.components.precreate" or k == "corba.endpoints":
                            for c in range(0, j["Widget"].count()):
                                try:
                                    d["value"] += str(j["Widget"].itemText(c).toLocal8Bit()).replace("\\","/")
                                except:
                                    d["value"] += j["Widget"].itemText(c).replace("\\","/")
                                if c < j["Widget"].count()-1:
                                    d["value"] += ","
                        else:
                            try:
                                d["value"] = str(j["Widget"].currentText().toLocal8Bit())
                            except:
                                d["value"] = j["Widget"].currentText()
                    elif j["Type"] == ManagerControl.SpinBox or j["Type"] == ManagerControl.DoubleSpinBox:
                        try:
                            d["value"] = str(j["Widget"].text().toLocal8Bit())
                        except:
                            d["value"] = j["Widget"].text()
                    datas.append(d)
            
        return datas
                
        
