#!/bin/env python
# -*- encoding: utf-8 -*-

##
#   @file SettingRTCConf.py
#   @brief 複合コンポーネント作成支援ツール


import sys,os,platform
import re
import time
import random
import math
import imp

import subprocess

import rtctree.tree

import RTC
import OpenRTM_aist

from OpenRTM_aist import CorbaNaming
from OpenRTM_aist import RTObject
from OpenRTM_aist import CorbaConsumer
from omniORB import CORBA
import CosNaming

from PyQt5 import QtCore, QtWidgets

import SettingRTCWindow.MainWindow


import SettingRTSystem_rc

if "RTM_ROOT" in os.environ:
	rtm_root = os.environ["RTM_ROOT"]
else:
	rtm_root = ".\\"

        
##
# @brief メイン関数
def main():
    #mgrc = ManagerControl("")
    app = QtWidgets.QApplication([""])
    #splash_pix = QtWidgets.QPixmap(':/images/splash_loading.png')
    #splash = QtWidgets.QSplashScreen(splash_pix, QtCore.Qt.WindowStaysOnTopHint)
    #splash.setMask(splash_pix.mask())
    #splash.show()
    #app.processEvents()
    if "SettingRTSystemPath" in os.environ:
        tool_path = os.environ["SettingRTSystemPath"]
    else:
        tool_path = "./"
    
    if os.name == 'posix':
        #process_rtcd = subprocess.Popen("python Manager/Python/rtcd.py -f Manager/Python/rtc.conf".split(" "))
        cmd = "sh " + str(os.path.join(tool_path,"rtcConfSet.sh"))
        process_confset = subprocess.Popen(cmd.split(" "))
        #process_confset = os.system("sh rtcConfSet.sh&")
    elif os.name == 'nt':
        #process_rtcd = subprocess.Popen("python Manager/Python/rtcd.py -f Manager/Python/rtc.conf")
        #process_rtcd = os.system("start python Manager/Python/rtcd.py -f Manager/Python/rtc.conf")
        if "TOOLEXE" in os.environ and os.environ["TOOLEXE"]=="TRUE":
            cmd = "\""+str(os.path.join(rtm_root,"utils\\python_dist","rtcConfSet.exe"))+"\" -f rtc.conf"
        else:
            cmd = "python " + "\""+str(os.path.join(tool_path,"rtcConfSet\\rtcConfSet.py"))+"\" -f rtc.conf"
        cmd = cmd.replace("/","\\")
        process_confset = subprocess.Popen(cmd)
        #process_confset = os.system("start rtcConfSet.bat")
    
    

    
    mainWin = SettingRTCWindow.MainWindow.MainWindow()
    mainWin.show()
    #splash.finish(mainWin)
    app.exec_()

    

    if os.name == 'posix':
        cmd = "python " + str(os.path.join(tool_path,"exitRTCs.py"))
        subprocess.Popen(cmd.split(" "))
    elif os.name == 'nt':
        cmd = "python " + "\""+str(os.path.join(tool_path,"exitRTCs.py"))+"\""
        subprocess.Popen(cmd)
        
    
    
    
    
    
    

    
    
    
if __name__ == "__main__":
    main()
