#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
import codecs
from PyQt5 import QtWidgets,QtCore,QtGui
import tempfile
import OpenRTM_aist
import RTC
import BaseTab
import CreateDataObject



class RenderPath(QtWidgets.QGraphicsItem):
    def __init__(self, scene, parent=None):
        
        super(RenderPath, self).__init__(parent)
        scene.addItem(self)
        self.path = QtGui.QPainterPath()
        self.penWidth = 1
        self.rotationAngle = 0
        self.pos_x = 0
        self.pos_y = 0

        self.width = 10
        self.height = 10
        
        color = QtGui.QColor("black")
        self.setPenColor(color)
        color1 = QtGui.QColor("black")
        color2 = QtGui.QColor("black")
        self.setFillGradient(color1,color2)

    def setPath(self, path):
        self.path = path
    def setFillRule(self, rule):
        self.path.setFillRule(rule)
    def setFillGradient(self, color1, color2):
        self.fillColor1 = color1
        self.fillColor2 = color2
    def setPenWidth(self, width):
        self.penWidth = width
    def setPenColor(self, color):
        self.penColor = color
    def setRotationAngle(self, degrees):
        self.rotationAngle = degrees
    def setCenterPoint(self, x, y):
        self.centerPoint_x = x
        self.centerPoint_y = y
    def setPosition(self, x, y):
        self.pos_x = x
        self.pos_y = y
    def setSize(self, width, height):
        self.width = width
        self.height = height
    def boundingRect(self):
        pos_x = self.pos_x*self.scene().width()/100.0
        pos_y = self.pos_y*self.scene().height()/100.0
        width = self.width*self.scene().width()/100.0
        height = self.height*self.scene().height()/100.0
        
        if width < 0:
            pos_x += width
            width = -width

        if height < 0:
            pos_y += height
            height = -height
        
        return QtCore.QRectF(pos_x, pos_y, width, height)
    
    def paint(self, painter, option, widget=None):
        self.updatePaint(painter)
    def updatePaint(self, painter):
        painter.setRenderHint(QtGui.QPainter.Antialiasing)
        painter.scale(self.scene().width() / 100.0, self.scene().height() / 100.0)
        painter.translate(self.centerPoint_x, self.centerPoint_y)
        painter.rotate(-self.rotationAngle)
        painter.translate(-self.centerPoint_x, -self.centerPoint_y)

        painter.translate(self.pos_x, self.pos_y)

        painter.setPen(QtGui.QPen(self.penColor, self.penWidth,
                QtCore.Qt.SolidLine, QtCore.Qt.RoundCap, QtCore.Qt.RoundJoin))
        gradient = QtGui.QLinearGradient(0, 0, 0, 100)
        gradient.setColorAt(0.0, self.fillColor1)
        gradient.setColorAt(1.0, self.fillColor2)
        painter.setBrush(QtGui.QBrush(gradient))
        painter.drawPath(self.path)

class RTCViewWidget(QtWidgets.QWidget):
    def __init__(self, parent=None):
        super(RTCViewWidget, self).__init__(parent)
        self.parent_window = parent
        self.scene = QtWidgets.QGraphicsScene(0, 0, 600, 600)
        self.mainLayout = QtWidgets.QVBoxLayout()
        self.setLayout(self.mainLayout)
        self.view = GraphicsView(self.scene)
        self.view.scale(0.25, 0.25)
        self.view.setViewportUpdateMode(QtWidgets.QGraphicsView.BoundingRectViewportUpdate)
        self.view.setBackgroundBrush(QtGui.QColor(255, 255, 255))
        self.mainLayout.addWidget(self.view)
        self.renderWindow = RenderRTC(None, self.scene, self.parent_window)
        #self.view.setRTC(self.renderWindow)
        
        
        

class GraphicsView(QtWidgets.QGraphicsView):
    def __init__(self, scene, parent=None):
        super(GraphicsView, self).__init__(scene, parent)



class Port(RenderPath):
    LEFT = 0
    RIGHT = 1
    TOP = 2
    BOTTOM = 3
    def __init__(self, profile, defsize, scene, parent):
        super(Port, self).__init__(scene, parent)
        self.profile = profile
        self.size = defsize
        
        
    def setBoxSize(self, size):
        self.size = size
        path = self.getPath()
        self.setPath(path)


class ServicePortWidget(BaseTab.BaseTab):
    def __init__(self, sport, dialog, parent=None):
        super(ServicePortWidget, self).__init__(parent)
        self.dialog = dialog
        self.sport = sport


        self.portNameTextbox = self.addTextBox("portName",u"ポート名",[], sport.profile["portName"])
        self.interfaceNameTextbox = self.addTextBox("interfaceName",u"インターフェース名",[], sport.profile["interfaceName"])
        self.interfaceDirCombox = self.addCombox("interfaceDir",u"方向",[],["Required","Provided"], sport.profile["interfaceDir"])
        self.IDLTextbox = self.addTextBox("IDL",u"IDLファイル",[], sport.profile["IDL"])
        self.interfaceTypeCombox = self.addCombox("interfaceType",u"インターフェース型",[],[], sport.profile["interfaceType"])
        self.IDLPathTextbox = self.addTextBox("IDLPath",u"IDLパス",[], sport.profile["IDLPath"])


        
        self.deleteButton = QtWidgets.QPushButton(u"削除")
        self.deleteButton.clicked.connect(self.deleteButtonSlot)
        self.subLayouts[-1].addWidget(self.deleteButton)
    def deleteButtonSlot(self):
        self.dialog.accept()
    

class ServicePortDialog(QtWidgets.QDialog):
    def __init__(self, dport, parent=None):
        super(ServicePortDialog, self).__init__(parent)
        
        self.setWindowTitle(u"サービスポート編集ダイアログ")
        self.mainLayout = QtWidgets.QVBoxLayout()
        self.setLayout(self.mainLayout)
        self.dpwidget = ServicePortWidget(dport, self)
        self.mainLayout.addWidget(self.dpwidget)

class ServicePort(Port):
    def __init__(self, profile, defsize, scene, mainwindow, parent):
        Port.__init__(self, profile, defsize, scene, parent)
        rectPath = self.getPath()
        self.mainwindow = mainwindow
        color = QtGui.QColor("black")
        self.setPenColor(color)
        self.profile = profile

        color1 = QtGui.QColor("yellow")
        color2 = QtGui.QColor("yellow")
        
        self.setFillGradient(color1,color2)

        self.setCenterPoint(0,0)
        
    def mouseDoubleClickEvent(self, event):
        self.dialog = ServicePortDialog(self)
        self.dialog.show()
        self.dialog.exec_()
        
        
        if self.dialog.result():
            self.mainwindow.deleteServicePort(self.profile["portName"])
            
        
        
    def getPath(self):
        rectPath = QtGui.QPainterPath()
        spx = self.pos_x
        spy = self.pos_y
        epx = self.pos_x
        epy = self.pos_y
        cofx = 0
        cofy = 0
        
        rectPath.moveTo(0, 0)
        rectPath.lineTo(self.size, 0)
        rectPath.lineTo(self.size, self.size)
        rectPath.lineTo(0, self.size)
        self.path.closeSubpath()


        self.position = Port.RIGHT
        self.width = self.size
        self.height = self.size
        

        return rectPath

    def paint(self, painter, option, widget=None):
        self.updatePaint(painter)

class DataPortWidget(BaseTab.BaseTab):
    def __init__(self, dport, dialog, parent=None):
        super(DataPortWidget, self).__init__(parent)
        self.dialog = dialog
        self.dport = dport
        key_list = list(CreateDataObject.CreateDataObject.dataTypeList.keys())
        key_list.sort()
        
        self.portNameTextbox = self.addTextBox("portNameTextbox",u"ポート名",[], dport.profile["portName"])
        self.portTypeCombox = self.addCombox("portTypeCombox",u"ポート",[],["DataOutPort","DataInPort"], dport.profile["portType"])
        self.dataTypeCombox = self.addCombox("dataTypeCombox",u"データ型",[],key_list, dport.profile["dataType"])
        self.deleteButton = QtWidgets.QPushButton(u"削除")
        self.deleteButton.clicked.connect(self.deleteButtonSlot)
        self.subLayouts[-1].addWidget(self.deleteButton)
    def deleteButtonSlot(self):
        self.dialog.accept()
    

class DataPortDialog(QtWidgets.QDialog):
    def __init__(self, dport, parent=None):
        super(DataPortDialog, self).__init__(parent)
        
        self.setWindowTitle(u"データポート編集ダイアログ")
        self.mainLayout = QtWidgets.QVBoxLayout()
        self.setLayout(self.mainLayout)
        self.dpwidget = DataPortWidget(dport, self)
        self.mainLayout.addWidget(self.dpwidget)
    
        
    

class DataPort(Port):
    def __init__(self, profile, defsize, scene, mainwindow, parent):
        Port.__init__(self, profile, defsize, scene, parent)
        rectPath = self.getPath()
        self.mainwindow = mainwindow
        color = QtGui.QColor("black")
        self.setPenColor(color)
        self.profile = profile

        color1 = QtGui.QColor("yellow")
        color2 = QtGui.QColor("yellow")
        
        self.setFillGradient(color1,color2)

        self.setCenterPoint(0,0)
        
    def mouseDoubleClickEvent(self, event):
        self.dialog = DataPortDialog(self)
        self.dialog.show()
        self.dialog.exec_()
        
        
        if self.dialog.result():
            self.mainwindow.deleteDataPort(self.profile["portName"])
            
        
        
    def getPath(self):
        rectPath = QtGui.QPainterPath()
        spx = self.pos_x
        spy = self.pos_y
        epx = self.pos_x
        epy = self.pos_y
        cofx = 0
        cofy = 0
        
        if self.profile["portType"] == "DataInPort":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(-self.size, 0)
            rectPath.lineTo(-self.size/2.0, self.size/2.0)
            rectPath.lineTo(-self.size, self.size)
            rectPath.lineTo(0, self.size)
            
            self.position = Port.LEFT
            self.width = -self.size
            self.height = self.size
        elif self.profile["portType"] == "DataOutPort":
            rectPath.moveTo(0, 0)
            rectPath.lineTo(self.size, self.size/2.0)
            rectPath.lineTo(0, self.size)


            self.position = Port.RIGHT
            self.width = self.size
            self.height = self.size

        self.path.closeSubpath()
        return rectPath

    def paint(self, painter, option, widget=None):
        self.updatePaint(painter)


class RenderRTC(RenderPath):
    def __init__(self, profile, scene, mainwindow, parent=None):
        super(RenderRTC, self).__init__(scene, parent)
        self.path = QtGui.QPainterPath()
        self.mainwindow = mainwindow
        self.comp = mainwindow.comp
        self.current_state = RTC.INACTIVE_STATE
        
        self.penWidth = 1
        self.rotationAngle = 0

        self.centerPoint_x = 50
        self.centerPoint_y = 50

        self.pos_x = 0
        self.pos_y = 0

        self.width = 10
        self.height = 10

        
        #self.setBoxSize(10)

        color = QtGui.QColor("black")
        self.setPenColor(color)

        color1 = QtGui.QColor("blue")
        color2 = QtGui.QColor("blue")

        self.setFillGradient(color1,color2)

        self.def_size_x = 50
        self.def_size_y = 10
        self.port_size = 10

        self.ports = {}
        self.config_params = {}
        
        
        
        
        
        
        
        #self.dp = DataPort({"portType":"DataOutPort"},10,self.scene(),self)
        #self.dp.setBoxSize(100)
        #size = 10
        #self.dp.setPosition(20,0-size*2.0*0.5)
        #self.dp.setBoxSize(10)
        

        self.setRTC()


        self.timer = QtCore.QTimer()
        self.timer.setInterval(1000)
        self.timer.timeout.connect(self.check_rtc)
        self.timer.start()

    def check_rtc(self):
        if self.comp is not None:
            ec_num = self.mainwindow.controlCompWidget.getECNum()
            ret, state = OpenRTM_aist.CORBA_RTCUtil.get_state(self.comp.getObjRef(),ec_num)
            if ret:
                 
                if state == RTC.INACTIVE_STATE:
                    if self.current_state != RTC.INACTIVE_STATE:
                        color1 = QtGui.QColor("blue")
                        color2 = QtGui.QColor("blue")

                        self.setFillGradient(color1,color2)
                        self.scene().update()
                    self.current_state = RTC.INACTIVE_STATE
                elif state == RTC.ACTIVE_STATE:
                    if self.current_state != RTC.ACTIVE_STATE:
                        color1 = QtGui.QColor("lime")
                        color2 = QtGui.QColor("lime")

                        self.setFillGradient(color1,color2)
                        self.scene().update()
                    self.current_state = RTC.ACTIVE_STATE
                elif state == RTC.ERROR_STATE:
                    if self.current_state != RTC.ERROR_STATE:
                        color1 = QtGui.QColor("red")
                        color2 = QtGui.QColor("red")

                        self.setFillGradient(color1,color2)
                        self.scene().update()
                    self.current_state = RTC.ERROR_STATE


    def addConfigParam(self, profile):
        self.config_params[profile["paramName"]] = profile
    def removeConfigParam(self, name):
        del self.config_params[name]
    def removeAllConfigParam(self):
        self.config_params = {}

    def addDataPort(self, profile):
        
        dp = DataPort(profile,self.port_size,self.scene(),self.mainwindow,self)
        dp.setBoxSize(self.port_size)
        self.ports[profile["portName"]] = dp
        

        self.setRTC()
        self.scene().update()


    def addServicePort(self, profile):
        
        sp = ServicePort(profile,self.port_size,self.scene(),self.mainwindow,self)
        sp.setBoxSize(self.port_size)
        profile["portType"] = "ServicePort"
        self.ports[profile["portName"]] = sp
        
        

        self.setRTC()
        self.scene().update()

    def removePort(self, name):
        self.scene().removeItem(self.ports[name])
        
        del self.ports[name]
        self.setRTC()
        self.scene().update()

    def removeAllPort(self):
        for k,p in self.ports.items():
            self.scene().removeItem(self.ports[k])
        
        self.ports = {}
        self.setRTC()
        self.scene().update()

    def setRTC(self):
        num = self.getPortNum()
        size_x = self.def_size_x
        size_y = self.def_size_y + self.port_size*2*num
        pos_x = (100-size_x)/2
        pos_y = (100-size_y)/2

        l_num = 0.5
        r_num = 0.5
        for k,p in self.ports.items():
            if p.position == Port.LEFT:
                p.setPosition(pos_x, pos_y+size_y/num*l_num - p.size/2)
                l_num += 1.0
            elif p.position == Port.RIGHT:
                p.setPosition(pos_x+size_x, pos_y+size_y/num*r_num - p.size/2)
                r_num += 1.0
        
        self.setPosition(pos_x,pos_y)
        self.setSize(size_x,size_y)
        
        self.path = QtGui.QPainterPath()
        self.path.moveTo(0, 0)
        self.path.lineTo(size_x, 0)
        self.path.lineTo(size_x, size_y)
        self.path.lineTo(0, size_y)
        self.path.closeSubpath()

    def getPortNum(self):
        l_count = 0
        r_count = 0
        for k,p in self.ports.items():
            if p.position == Port.LEFT:
                l_count += 1
            elif p.position == Port.RIGHT:
                r_count += 1
        if l_count > r_count:
            return l_count
        else:
            return r_count






		