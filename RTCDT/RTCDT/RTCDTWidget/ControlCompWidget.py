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


import struct



    







class ControlCompWidget(BaseTab.BaseTab):
    def __init__(self, comp, parent=None):
        super(ControlCompWidget, self).__init__(parent)

        self.comp = comp
        eclist = []
        if self.comp is not None:
            own_eclist = self.comp.get_owned_contexts()
            for i in range(len(own_eclist)):
                eclist.append(str(i))
            part_eclist = self.comp.get_participating_contexts()
            for i in range(len(part_eclist)):
                eclist.append(str(i+OpenRTM_aist.RTObject.ECOTHER_OFFSET))
        

        self.ECCombox = self.addCombox("ECCombox",u"実行コンテキスト",[],eclist, "0")
        
            

        self.activeButton = QtWidgets.QPushButton(u"アクティブ")
        self.activeButton.clicked.connect(self.activeButtonSlot)
        self.subLayouts[-1].addWidget(self.activeButton)
        self.subLayouts[-1].addStretch()

        self.deactiveButton = QtWidgets.QPushButton(u"非アクティブ")
        self.deactiveButton.clicked.connect(self.deactiveButtonSlot)
        self.subLayouts[-1].addWidget(self.deactiveButton)
        self.subLayouts[-1].addStretch()

        self.resetButton = QtWidgets.QPushButton(u"リセット")
        self.resetButton.clicked.connect(self.resetButtonSlot)
        self.subLayouts[-1].addWidget(self.resetButton)
        self.subLayouts[-1].addStretch()
    def getECNum(self):
        try:
            s = str(self.ECCombox["Widget"].currentText().toLocal8Bit())
        except:
            s = self.ECCombox["Widget"].currentText()
        return int(s)

    def activeButtonSlot(self):
        if self.comp is not None:
            ecnum = self.getECNum()
            OpenRTM_aist.CORBA_RTCUtil.activate(self.comp.getObjRef(), ecnum)
    def deactiveButtonSlot(self):
        if self.comp is not None:
            ecnum = self.getECNum()
            OpenRTM_aist.CORBA_RTCUtil.deactivate(self.comp.getObjRef(), ecnum)
    def resetButtonSlot(self):
        if self.comp is not None:
            ecnum = self.getECNum()
            OpenRTM_aist.CORBA_RTCUtil.reset(self.comp.getObjRef(), ecnum)