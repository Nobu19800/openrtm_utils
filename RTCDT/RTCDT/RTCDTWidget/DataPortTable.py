#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
import codecs
from PyQt5 import QtWidgets,QtCore
import tempfile
import OpenRTM_aist



class DataPortTable(QtWidgets.QTableWidget):
    def __init__(self):
        super(DataPortTable, self).__init__(5,3)
        horzHeaders=[u"名前" ,u"変数名(データ)", u"変数名(ポート)"]
        self.setHorizontalHeaderLabels(horzHeaders)
        self.setSelectionMode(QtWidgets.QAbstractItemView.NoSelection)
    def list_update(self, ports):
        self.setRowCount(len(ports))
        num = 0
        for k,p in ports.items():
            if p.profile["portType"] == "DataOutPort" or p.profile["portType"] == "DataInPort":
                data_variable = "self."+p.profile["data_variable"]
                port_variable = "self."+p.profile["port_variable"]
                self.setItem(num,0, QtWidgets.QTableWidgetItem(p.profile["portName"]))
                self.setItem(num,1, QtWidgets.QTableWidgetItem(data_variable))
                self.setItem(num,2, QtWidgets.QTableWidgetItem(port_variable))
                num += 1
            
        #self.setColumnCount(2)



		