#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
from PyQt5 import QtWidgets,QtCore
import OpenRTM_aist
import RTC

import BaseTab
import CreateDataObject



class addDataPortTab(BaseTab.BaseTab):

    def __init__(self, comp, viewWidget, listWidget, parent=None):
        super(addDataPortTab, self).__init__(parent)
        self.comp = comp
        self.viewWidget = viewWidget
        self.listWidget = listWidget

    
        key_list = list(CreateDataObject.CreateDataObject.dataTypeList.keys())
        key_list.sort()
        
        self.portNameTextbox = self.addTextBox("portNameTextbox",u"ポート名",[], "port")
        self.portTypeCombox = self.addCombox("portTypeCombox",u"ポート",[],["DataOutPort","DataInPort"], "DataOutPort")
        self.dataTypeCombox = self.addCombox("dataTypeCombox",u"データ型",[],key_list, "RTC.TimedLong")
        self.createButton = QtWidgets.QPushButton(u"作成")
        self.createButton.clicked.connect(self.createButtonSlot)
        self.subLayouts[-1].addWidget(self.createButton)
        self.mainLayout.addStretch()
        

    def searchPort(self, name):
        ports = self.comp.get_ports()
        for p in ports:
            pp = p.get_port_profile()
            pname = self.comp.getInstanceName()+"."+name
            if pp.name == pname:
                return p
        return None
    def addPort(self, profile):
        if self.comp is not None:
            
            if not self.searchPort(profile["portName"]):
                data_name, port_name = self.comp.setDataPort(profile["portName"], profile["portType"], profile["dataType"])
                
                
                    
                
                
                
            
                profile["data_variable"] = data_name
                profile["port_variable"] = port_name
                self.viewWidget.renderWindow.addDataPort(profile)
                self.listWidget.list_update(self.viewWidget.renderWindow.ports)



    def createButtonSlot(self):
        profile = {}
        try:
            profile["portName"] = str(self.portNameTextbox["Widget"].text().toLocal8Bit())
        except:
            profile["portName"] = self.portNameTextbox["Widget"].text()
        p = profile["portName"].replace(" ","")
        p = p.replace("\t","")
        if p == "":
             QtWidgets.QMessageBox.question(self, u"作成失敗", u"名前が入力されていません", QtWidgets.QMessageBox.Ok)
             return

        try:
            profile["portType"] = str(self.portTypeCombox["Widget"].currentText().toLocal8Bit())
            profile["dataType"] = str(self.dataTypeCombox["Widget"].currentText().toLocal8Bit())
        except:
            profile["portType"] = self.portTypeCombox["Widget"].currentText()
            profile["dataType"] = self.dataTypeCombox["Widget"].currentText()

        self.addPort(profile)

        
		