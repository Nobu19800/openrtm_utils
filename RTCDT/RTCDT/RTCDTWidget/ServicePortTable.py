#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
import codecs
from PyQt5 import QtWidgets,QtCore
import tempfile
import OpenRTM_aist


import struct




class ServicePortOperationDialog(QtWidgets.QDialog):
    def __init__(self, classlist, parent=None):
        super(ServicePortOperationDialog, self).__init__(parent)
        self.classlist = classlist
        self.setWindowTitle(u"関数一覧")
        self.mainLayout = QtWidgets.QVBoxLayout()
        self.setLayout(self.mainLayout)

        self.tables = []
        for k,v in classlist.items():
            widget = QtWidgets.QGroupBox(k)
            layout = QtWidgets.QVBoxLayout()
            widget.setLayout(layout)

            table = QtWidgets.QTableWidget(5,1)
            vheader = QtWidgets.QHeaderView(QtCore.Qt.Vertical)
            vheader.setResizeMode(QtWidgets.QHeaderView.ResizeToContents)
            table.setVerticalHeader(vheader)
            hheader = QtWidgets.QHeaderView(QtCore.Qt.Horizontal)
            hheader.setResizeMode(QtWidgets.QHeaderView.ResizeToContents)
            table.setHorizontalHeader(hheader)
            

            
            layout.addWidget(table)
            table.setRowCount(len(v))
            num = 0
            for func in v:
                table.setItem(num,0, QtWidgets.QTableWidgetItem(func))
                num += 1
            self.tables.append(widget)
            self.mainLayout.addWidget(widget)
            

        


class ServicePortSettingButton(QtWidgets.QPushButton):
    def __init__(self, name, profile):
        super(ServicePortSettingButton, self).__init__(name)
        self.profile = profile
        self.clicked.connect(self.pushSlot)
    def pushSlot(self):
        self.dialog = ServicePortOperationDialog(self.profile["class_list"])
        self.dialog.show()
        
        

class ServicePortTable(QtWidgets.QTableWidget):
    def __init__(self):
        super(ServicePortTable, self).__init__(5,3)
        horzHeaders = [u"名前", u"変数名", u"関数"]
        self.setHorizontalHeaderLabels(horzHeaders)
        self.setSelectionMode(QtWidgets.QAbstractItemView.NoSelection)
    def list_update(self, ports):
        self.setRowCount(len(ports))
        num = 0
        for k,p in ports.items():
            if p.profile["portType"] == "ServicePort":
                data_variable = "self."+p.profile["data_variable"]
                self.setItem(num,0, QtWidgets.QTableWidgetItem(p.profile["portName"]))
                self.setItem(num,1, QtWidgets.QTableWidgetItem(data_variable))
                self.setCellWidget(num,2, ServicePortSettingButton(u"表示",p.profile))
                num += 1



