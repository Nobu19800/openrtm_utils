#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
from PyQt4 import QtGui,QtWebKit,QtCore
import OpenRTM_aist
import RTC


import BaseTab



class addConfigurationTab(BaseTab.BaseTab):
    def __init__(self, comp, viewWidget, listWidget, parent=None):
        super(addConfigurationTab, self).__init__(parent)
        self.viewWidget = viewWidget
        self.listWidget = listWidget
        self.comp = comp

        type_list = ["short","long", "double", "float", "string"]
        widget_list = ["text","slider","spin","radio","checkbox","ordered_list"]
        self.paramNameTextbox = self.addTextBox("paramNameTextbox",u"パラメータ名",[], "param")
        self.paramTypeCombox = self.addCombox("paramTypeCombox",u"データ型",[],type_list, "string")
        self.paramDefaultTextbox = self.addTextBox("paramDefaultTextbox",u"デフォルト値",[], "1")
        self.paramConstraintsTextbox = self.addTextBox("paramConstraintsTextbox",u"制約条件",[], "")
        self.paramWidgetCombox = self.addCombox("paramNameTextbox",u"Widget",[],widget_list, "text")
        self.paramStepTextbox = self.addTextBox("paramStepTextbox",u"Step",[], "")
        self.createButton = QtGui.QPushButton(u"作成")
        self.createButton.clicked.connect(self.createButtonSlot)
        self.subLayouts[-1].addWidget(self.createButton)


            

    def addConfiguration(self, profile):
        if self.comp is not None:
            data_name = self.comp.setConfigParam(profile["paramName"],profile["paramType"],profile["paramDefault"],profile["paramConstraints"],profile["paramWidget"],profile["paramStep"])
            
            profile["variable"] = data_name
            self.viewWidget.renderWindow.addConfigParam(profile)
            self.listWidget.list_update(self.viewWidget.renderWindow.config_params)

            
            

    def createButtonSlot(self):
        profile = {}
        profile["paramName"] = str(self.paramNameTextbox["Widget"].text().toLocal8Bit())

        p = profile["paramName"].replace(" ","")
        p = p.replace("\t","")
        if p == "":
             QtGui.QMessageBox.question(self, u"作成失敗", u"名前が入力されていません", QtGui.QMessageBox.Ok)
             return

        profile["paramType"] = str(self.paramTypeCombox["Widget"].currentText().toLocal8Bit())
        profile["paramDefault"] = str(self.paramDefaultTextbox["Widget"].text().toLocal8Bit())

        p = profile["paramDefault"].replace(" ","")
        p = p.replace("\t","")
        if p == "":
             QtGui.QMessageBox.question(self, u"作成失敗", u"デフォルト値が入力されていません", QtGui.QMessageBox.Ok)
             return

        profile["paramConstraints"] = str(self.paramConstraintsTextbox["Widget"].text().toLocal8Bit())
        profile["paramWidget"] = str(self.paramWidgetCombox["Widget"].currentText().toLocal8Bit())
        profile["paramStep"] = str(self.paramStepTextbox["Widget"].text().toLocal8Bit())
        
            
        self.addConfiguration(profile)
        


            
            




