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



import BaseTab
class addServicePortTab(BaseTab.BaseTab):

    def __init__(self, comp, viewWidget, listWidget, parent=None):
        super(addServicePortTab, self).__init__(parent)
        self.comp = comp
        self.viewWidget = viewWidget
        self.listWidget = listWidget

    

        
        self.portNameTextbox = self.addTextBox("portName",u"ポート名",[], "port")
        self.interfaceNameTextbox = self.addTextBox("interfaceName",u"インターフェース名",[], "")
        self.interfaceDirCombox = self.addCombox("interfaceDir",u"方向",[],["Required","Provided"], "Required")
        self.IDLTextbox = self.addTextBox("IDL",u"IDLファイル",[], "")
        self.IDLFileButton = QtWidgets.QPushButton(u"開く")
        self.IDLFileButton.clicked.connect(self.IDLFileButtonSlot)
        self.IDLTextbox["Layout"].addWidget(self.IDLFileButton)
        
        self.interfaceTypeCombox = self.addCombox("interfaceType",u"インターフェース型",[],[], "")
        self.IDLPathTextbox = self.addTextBox("IDLPath",u"IDLパス",[], "")
        self.IDLPathButton = QtWidgets.QPushButton(u"開く")
        self.IDLPathButton.clicked.connect(self.IDLPathButtonSlot)
        self.IDLPathTextbox["Layout"].addWidget(self.IDLPathButton)
        self.createButton = QtWidgets.QPushButton(u"作成")
        self.createButton.clicked.connect(self.createButtonSlot)
        self.subLayouts[-1].addWidget(self.createButton)
        self.mainLayout.addStretch()

    def IDLFileButtonSlot(self):
        fileName = QtWidgets.QFileDialog.getOpenFileName(self,u"開く","","IDL File (*.idl);;All Files (*)")

        try:
            if fileName.isEmpty():
                return ""
            filepath = str(fileName.toLocal8Bit())
        except:
            if not fileName:
                return ""
            filepath = fileName
        self.IDLTextbox["Widget"].setText(fileName)
        try:
            s = str(self.IDLTextbox["Widget"].text().toLocal8Bit())
        except:
            s = self.IDLTextbox["Widget"].text()
        
        if self.comp is not None:
            self.interfaceTypeCombox["Widget"].clear()
            try:
                filename = str(self.IDLTextbox["Widget"].text().toLocal8Bit())
            except:
                filename = self.IDLTextbox["Widget"].text()
            filelist, classlist = self.comp.getServiceNameList(filename,"","")
            
            for k,v in classlist.items():
                self.interfaceTypeCombox["Widget"].addItem(k)
        

    def IDLPathButtonSlot(self):
        dirName = QtWidgets.QFileDialog.getExistingDirectory(self,u"開く")
        try:
            if dirName.isEmpty():
                return ""
        except:
            if not dirName:
                return ""

        self.IDLPathTextbox["Widget"].setText(dirName)
        

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
                data_name, port_name, filelist, classlist, importlist = self.comp.setServicePort(profile["portName"], profile["interfaceName"], profile["interfaceDir"], profile["IDL"], profile["interfaceType"], profile["IDLPath"])

                profile["data_variable"] = data_name
                profile["port_variable"] = port_name
                profile["file_list"] = filelist
                profile["class_list"] = classlist
                profile["import_list"] = importlist
                
                self.viewWidget.renderWindow.addServicePort(profile)
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
            profile["interfaceName"] = str(self.interfaceNameTextbox["Widget"].text().toLocal8Bit())
        except:
            profile["interfaceName"] = self.interfaceNameTextbox["Widget"].text()
        p = profile["interfaceName"].replace(" ","")
        p = p.replace("\t","")
        if p == "":
             QtWidgets.QMessageBox.question(self, u"作成失敗", u"インターフェース名が入力されていません", QtWidgets.QMessageBox.Ok)
             return
        try:
            profile["interfaceDir"] = str(self.interfaceDirCombox["Widget"].currentText().toLocal8Bit())
            profile["IDL"] = str(self.IDLTextbox["Widget"].text().toLocal8Bit())
        except:
            profile["interfaceDir"] = self.interfaceDirCombox["Widget"].currentText()
            profile["IDL"] = self.IDLTextbox["Widget"].text()
        p = profile["IDL"].replace(" ","")
        p = p.replace("\t","")
        if p == "":
             QtWidgets.QMessageBox.question(self, u"作成失敗", u"IDLファイル名が入力されていません", QtWidgets.QMessageBox.Ok)
             return
        try:
            profile["interfaceType"] = str(self.interfaceTypeCombox["Widget"].currentText().toLocal8Bit())
            profile["IDLPath"] = str(self.IDLPathTextbox["Widget"].text().toLocal8Bit())
        except:
            profile["interfaceType"] = self.interfaceTypeCombox["Widget"].currentText()
            profile["IDLPath"] = self.IDLPathTextbox["Widget"].text()
        self.addPort(profile)
