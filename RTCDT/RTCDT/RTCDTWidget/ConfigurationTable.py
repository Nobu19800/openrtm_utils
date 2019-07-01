#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
import codecs
from PyQt5 import QtWidgets,QtCore
import tempfile
import OpenRTM_aist
import BaseTab


class ConfigParamWidget(BaseTab.BaseTab):
    def __init__(self, config, dialog, parent=None):
        super(ConfigParamWidget, self).__init__(parent)
        self.dialog = dialog
        
        type_list = ["short","long", "double", "float", "string"]
        widget_list = ["text","slider","spin","radio","checkbox","ordered_list"]
        self.paramNameTextbox = self.addTextBox("paramNameTextbox",u"パラメータ名",[], config["paramName"])
        self.paramTypeCombox = self.addCombox("paramTypeCombox",u"データ型",[],type_list, config["paramType"])
        self.paramDefaultTextbox = self.addTextBox("paramDefaultTextbox",u"デフォルト値",[], config["paramDefault"])
        self.paramConstraintsTextbox = self.addTextBox("paramConstraintsTextbox",u"制約条件",[], config["paramConstraints"])
        self.paramWidgetCombox = self.addCombox("paramNameTextbox",u"Widget",[],widget_list, config["paramWidget"])
        self.paramStepTextbox = self.addTextBox("paramStepTextbox",u"Step",[], config["paramStep"])
        self.deleteButton = QtWidgets.QPushButton(u"削除")
        self.deleteButton.clicked.connect(self.deleteButtonSlot)
        self.subLayouts[-1].addWidget(self.deleteButton)
    def deleteButtonSlot(self):
        self.dialog.accept()

class ConfigParamDialog(QtWidgets.QDialog):
    def __init__(self, config, parent=None):
        super(ConfigParamDialog, self).__init__(parent)
        
        self.setWindowTitle(u"コンフィギュレーションパラメータ編集ダイアログ")
        self.mainLayout = QtWidgets.QVBoxLayout()
        self.setLayout(self.mainLayout)
        self.cfwidget = ConfigParamWidget(config, self)
        self.mainLayout.addWidget(self.cfwidget)

class ConfigSettingButton(QtWidgets.QPushButton):
    def __init__(self, name, profile, mainwindow):
        super(ConfigSettingButton, self).__init__(name)
        self.profile = profile
        self.mainwindow = mainwindow
        self.clicked.connect(self.pushSlot)
    def pushSlot(self):
        self.dialog = ConfigParamDialog(self.profile)
        self.dialog.show()
        self.dialog.exec_()
        if self.dialog.result():
            self.mainwindow.deleteConfig(self.profile["paramName"])


class ConfigurationTable(QtWidgets.QTableWidget):
    def __init__(self, mainwindow):
        super(ConfigurationTable, self).__init__(5,3)
        self.comp = mainwindow.comp
        self.viewWidget = mainwindow.vw
        self.mainwindow = mainwindow
        self.button_list = {}
        horzHeaders=[u"名前", u"変数名"]
        self.setHorizontalHeaderLabels(horzHeaders)
        self.setSelectionMode(QtWidgets.QAbstractItemView.NoSelection)
    def list_update(self, params):
        self.setRowCount(len(params))
        num = 0
        for k,p in params.items():
            data_variable = "self."+p["variable"]
            self.setItem(num,0, QtWidgets.QTableWidgetItem(p["paramName"]))
            self.setItem(num,1, QtWidgets.QTableWidgetItem(data_variable))
            self.setCellWidget(num,2,ConfigSettingButton(u"設定",p,self.mainwindow))
            num += 1
		