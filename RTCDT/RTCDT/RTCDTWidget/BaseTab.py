#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
import codecs
from PyQt5 import QtWidgets,QtCore
import tempfile




class BaseTab(QtWidgets.QWidget):
    TextBox = 1
    Combox = 2
    TextCombox = 3
    SpinBox = 4
    DoubleSpinBox = 5
    def __init__(self, parent=None):
        super(BaseTab, self).__init__(parent)
        self.mainLayout = QtWidgets.QVBoxLayout()

        self.setLayout(self.mainLayout)

        self.WidList = {}
        self.widNum = 0

        self.subLayouts = [QtWidgets.QVBoxLayout()]
        self.mainLayout.addLayout(self.subLayouts[-1])
    def apendWidget(self, wid, name, label):
        widget = QtWidgets.QGroupBox(label)
        layout = QtWidgets.QVBoxLayout()
        widget.setLayout(layout)

        layout.addWidget(wid)


            
        self.subLayouts[-1].addWidget(widget)

        self.subLayouts[-1].addStretch()

        self.WidList[name] = {"Widget":wid,"Layout":layout}

        return self.WidList[name]
    
    def addCombox(self, name, label, value, ls, default):
        wid = QtWidgets.QComboBox()
        for l in ls:
            if l != "":
                wid.addItem(l)

        
        if len(value) != 0:
            if value[0] != "":
                wid.setCurrentIndex(wid.findText(value[0]))
            else:
                wid.setCurrentIndex(wid.findText(default))
        else:
            wid.setCurrentIndex(wid.findText(default))

        wl = self.apendWidget(wid, name, label)
        wl["Type"] = BaseTab.Combox
        
        return wl


    def addTextBox(self, name, label, value, default):
        wid = QtWidgets.QLineEdit()
        if len(value) == 0:
            wid.setText(default)
        elif value[0] == "":
            wid.setText(default)
        else:
            wid.setText(value[0])

        wl = self.apendWidget(wid, name, label)
        wl["Type"] = BaseTab.TextBox
        
        return wl


        
        return wl

		