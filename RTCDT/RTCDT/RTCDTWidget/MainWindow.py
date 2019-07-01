#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
import codecs
from PyQt5 import QtWidgets,QtCore,QtGui
import tempfile
import OpenRTM_aist


import ActivityTab
import ActivityCode
import RTCViewWidget
import addDataPortTab
import DataPortTable
import LogViewer
import ConfigurationTable
import addConfigurationTab
import CreateDataObject
import ControlCompWidget
import ServicePortTable
import addServicePortTab
import ExecType

import struct



        
class ModuleSettingWidget(QtWidgets.QWidget):
    def __init__(self, name, module_name,  dialog, parent=None):
        super(ModuleSettingWidget, self).__init__(parent)
        self.dialog = dialog
        self.mainLayout = QtWidgets.QHBoxLayout()
        self.setLayout(self.mainLayout)
        
        self.editLayout = QtWidgets.QHBoxLayout()
        self.mainLayout.addLayout(self.editLayout)


        self.namewidget = QtWidgets.QGroupBox(u"変数名")
        self.editLayout.addWidget(self.namewidget)
        self.nameLayout = QtWidgets.QVBoxLayout()
        self.namewidget.setLayout(self.nameLayout)
        
        
        self.nameedit = QtWidgets.QLineEdit()
        self.nameedit.setMinimumWidth(150)
        self.nameedit.setText(name)
        self.nameLayout.addWidget(self.nameedit)


        self.modulewidget = QtWidgets.QGroupBox(u"モジュール名")
        self.editLayout.addWidget(self.modulewidget)
        self.moduleLayout = QtWidgets.QVBoxLayout()
        self.modulewidget.setLayout(self.moduleLayout)


        self.moduleedit = QtWidgets.QLineEdit()
        self.moduleedit.setMinimumWidth(150)
        self.moduleedit.setText(module_name)
        self.moduleLayout.addWidget(self.moduleedit)
        
        self.deleteButton = QtWidgets.QPushButton(u"削除")
        self.deleteButton.clicked.connect(self.pushSlot)
        self.mainLayout.addWidget(self.deleteButton)
    def pushSlot(self):
        self.dialog.deleteModule(self)
        
    def getModule(self):
        try:
            name = str(self.nameedit.text().toLocal8Bit())
            module_name = str(self.moduleedit.text().toLocal8Bit())
        except:
            name = self.nameedit.text()
            module_name = self.moduleedit.text()
        return {"name":name,"module":module_name}



class ModuleDialog(QtWidgets.QDialog):
    def __init__(self, module_lists, parent=None):
        super(ModuleDialog, self).__init__(parent)
        self.setMinimumWidth(500)
        self.setWindowTitle(u"モジュール設定ダイアログ")
        self.mainLayout = QtWidgets.QVBoxLayout()
        self.setLayout(self.mainLayout)


        self.editLayout = QtWidgets.QHBoxLayout()
        self.mainLayout.addLayout(self.editLayout)

        self.namewidget = QtWidgets.QGroupBox(u"変数名")
        self.editLayout.addWidget(self.namewidget)
        self.nameLayout = QtWidgets.QVBoxLayout()
        self.namewidget.setLayout(self.nameLayout)
        
        
        self.nameedit = QtWidgets.QLineEdit()
        self.nameedit.setMinimumWidth(150)
        self.nameedit.setText("")
        self.nameLayout.addWidget(self.nameedit)


        self.modulewidget = QtWidgets.QGroupBox(u"モジュール名")
        self.editLayout.addWidget(self.modulewidget)
        self.moduleLayout = QtWidgets.QVBoxLayout()
        self.modulewidget.setLayout(self.moduleLayout)


        self.moduleedit = QtWidgets.QLineEdit()
        self.moduleedit.setMinimumWidth(150)
        self.moduleedit.setText("")
        self.moduleLayout.addWidget(self.moduleedit)
    
        self.addButton = QtWidgets.QPushButton(u"追加")
        self.addButton.clicked.connect(self.addModuleSlot)
        self.mainLayout.addWidget(self.addButton)

        self.exitButton = QtWidgets.QPushButton(u"更新")
        self.exitButton.clicked.connect(self.exitSlot)
        self.mainLayout.addWidget(self.exitButton)
        
        self.modules = []
        for k,m in module_lists.items():
            name = QtCore.QString.fromLocal8Bit(k)
            module_name = QtCore.QString.fromLocal8Bit(m)
            self.addModule(name,module_name)

    def exitSlot(self):
        self.accept()
        
    def addModuleSlot(self):
        try:
            name = str(self.nameedit.text().toLocal8Bit())
            module_name = str(self.moduleedit.text().toLocal8Bit())
        except:
            name = self.nameedit.text()
            module_name = self.moduleedit.text()
        
        if module_name == "":
            return
        if name == "":
            name = module_name
        if module_name in self.modules:
            return
        self.addModule(name,module_name)

    def getModuleList(self):
        ret = {}
        for p in self.modules:
            mod = p.getModule()
            ret[mod["name"]] = mod["module"]
        return ret

    def addModule(self, name, module_name):
        widget = ModuleSettingWidget(name,module_name,self)
        self.modules.append(widget)
        self.mainLayout.addWidget(widget)

    def deleteModule(self, widget):
        self.modules.remove(widget)
        
        widget.hide()
        self.mainLayout.removeWidget(widget)




class PathSettingWidget(QtWidgets.QWidget):
    def __init__(self, text, dialog, parent=None):
        super(PathSettingWidget, self).__init__(parent)
        self.dialog = dialog
        self.mainLayout = QtWidgets.QHBoxLayout()
        self.setLayout(self.mainLayout)
        self.lineedit = QtWidgets.QLineEdit()
        self.lineedit.setMinimumWidth(300)
        self.lineedit.setText(text)
        self.mainLayout.addWidget(self.lineedit)
        self.deleteButton = QtWidgets.QPushButton(u"削除")
        #self.deleteButton.setParent(None)
        self.deleteButton.clicked.connect(self.pushSlot)
        self.mainLayout.addWidget(self.deleteButton)
        
    def pushSlot(self):
        #self.mainLayout.removeItem(self.mainLayout.takeAt(0))
        #self.mainLayout.removeItem(self.mainLayout.takeAt(1))
        #self.mainLayout.removeWidget(self.deleteButton)
        #del self.deleteButton
        #self.mainLayout.removeWidget(self.deleteButton)
        self.dialog.deletePath(self)
        
    def getPath(self):
        try:
            return str(self.lineedit.text().toLocal8Bit())
        except:
            return self.lineedit.text()
        
        

class PathDialog(QtWidgets.QDialog):
    def __init__(self, path_lists, parent=None):
        super(PathDialog, self).__init__(parent)
        self.setMinimumWidth(500)
        self.setWindowTitle(u"パス設定ダイアログ")
        self.mainLayout = QtWidgets.QVBoxLayout()
        self.setLayout(self.mainLayout)

        self.addButton = QtWidgets.QPushButton(u"追加")
        self.addButton.clicked.connect(self.addPathSlot)
        self.mainLayout.addWidget(self.addButton)

        self.exitButton = QtWidgets.QPushButton(u"更新")
        self.exitButton.clicked.connect(self.exitSlot)
        self.mainLayout.addWidget(self.exitButton)
        
        self.paths = []
        for p in path_lists:
            text = QtCore.QString.fromLocal8Bit(p)
            self.addPath(text)

    def exitSlot(self):
        self.accept()
        
    def addPathSlot(self):
        dirName = QtWidgets.QFileDialog.getExistingDirectory(self,u"開く")
        try:
            if dirName.isEmpty():
                return ""
        except:
            if not dirName:
                return ""
        self.addPath(dirName)

    def getPathList(self):
        ret = []
        for p in self.paths:
            ret.append(p.getPath())
        return ret

    def addPath(self, text):
        widget = PathSettingWidget(text,self)
        self.paths.append(widget)
        self.mainLayout.addWidget(widget)

    def deletePath(self, widget):
        self.paths.remove(widget)
        #w = self.mainLayout.takeAt(0)
        
        widget.hide()
        self.mainLayout.removeWidget(widget)
        
    
        

def writeString(f, s):
    length = len(s)
    length_data = struct.pack("i",length)
    f.write(length_data)
    data = struct.pack(str(length)+"s",s)
    f.write(data)


def readString(f):
    d = f.read(4)
    length = struct.unpack("i",d)[0]
    d = f.read(length)
    return struct.unpack(str(length)+"s",d)[0]




class MainWindow(QtWidgets.QMainWindow):
    
    def __init__(self, comp, file_arg, parent=None):
        super(MainWindow, self).__init__(parent)
        self.comp = comp
        self.path_list = []
        self.module_list = {}
        self.setWindowTitle(u"RTC開発ツール")
        self.cw = QtWidgets.QWidget()
        self.tab_widget = QtWidgets.QTabWidget(self)
        
        self.ml = QtWidgets.QVBoxLayout()

        self.subLayout = QtWidgets.QHBoxLayout()
        self.tabLayout = QtWidgets.QVBoxLayout()
        self.subLayout.addLayout(self.tabLayout)

        
        self.ml.addLayout(self.subLayout)

        self.tabLayout.addWidget(self.tab_widget)

        self.rtcLayout = QtWidgets.QHBoxLayout()
        self.subLayout.addLayout(self.rtcLayout)

        self.vw = RTCViewWidget.RTCViewWidget(self)
        self.vw.setFixedWidth(350)
        
        self.viewLayout = QtWidgets.QVBoxLayout()
        self.viewLayout.addWidget(self.vw)


        self.controlCompWidget = ControlCompWidget.ControlCompWidget(self.comp)
        self.viewLayout.addWidget(self.controlCompWidget)

        self.rtcLayout.addLayout(self.viewLayout)

        

        self.rtc_tab_widget = QtWidgets.QTabWidget(self)
        self.rtc_tab_widget.setFixedWidth(350)
        self.rtcLayout.addWidget(self.rtc_tab_widget)

        self.dataport_widget = DataPortTable.DataPortTable()

        self.addDataPortTab = addDataPortTab.addDataPortTab(self.comp, self.vw, self.dataport_widget)
        self.rtc_tab_widget.addTab(self.addDataPortTab, u"データポート")

        
        self.rtc_tab_widget.addTab(self.dataport_widget,u"データポート変数名")


        self.config_widget = ConfigurationTable.ConfigurationTable(self)

        self.addConfigurationTab = addConfigurationTab.addConfigurationTab(self.comp, self.vw, self.config_widget)
        self.rtc_tab_widget.addTab(self.addConfigurationTab, u"コンフィギュレーションパラメータ")

        
        self.rtc_tab_widget.addTab(self.config_widget,u"コンフィギュレーションパラメータ変数名")



        self.serviceport_widget = ServicePortTable.ServicePortTable()

        self.addServicePortTab = addServicePortTab.addServicePortTab(self.comp, self.vw, self.serviceport_widget)
        self.rtc_tab_widget.addTab(self.addServicePortTab, u"サービスポート")

        self.rtc_tab_widget.addTab(self.serviceport_widget,u"サービスポート変数名")



        self.setCentralWidget(self.cw)
        self.cw.setLayout(self.ml)
        self.tab_list = {}
        self.activities = {ActivityCode.ActivityCode.onInitialize: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onFinalize: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onStartup: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onShutdown: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onActivated: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onDeactivated: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onExecute: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onAborting: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onError: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onReset: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onStateUpdate: ["\n\nreturn RTC.RTC_OK"],
                           ActivityCode.ActivityCode.onRateChanged: ["\n\nreturn RTC.RTC_OK"]}
        
        for k,i in self.activities.items():
            self.addActivityTab(k,i)
        self.global_tab = ActivityTab.ActivityTab("global", [""])
        self.tab_widget.addTab(self.global_tab, u"グローバル")

        self.tab_widget.setCurrentIndex(ActivityCode.ActivityCode.onExecute)
        self.save_button = QtWidgets.QPushButton(u'更新')
        self.tabLayout.addWidget(self.save_button)
        self.save_button.clicked.connect(self.save_button_slot)


        self.logViewer = LogViewer.LogViewer(self.comp)
        self.ml.addWidget(self.logViewer)

        self.tmp_path = ""
        self.exexType = ExecType.ExecType.ExecString
        self.curFile = ""
        self.createAction()
        self.createMenus()

        if file_arg != "":
            self.openfile(file_arg)
    
        

    def createAction(self):

        self.newAct = QtWidgets.QAction(QtGui.QIcon(':/images/new.png'),u"&新規作成...",self)
        self.newAct.setShortcuts(QtGui.QKeySequence.New)
        self.newAct.triggered.connect(self.newFile)
        


        self.openAct = QtWidgets.QAction(QtGui.QIcon(':/images/open.png'),u"&開く...",self)
        self.openAct.setShortcuts(QtGui.QKeySequence.Open)
        self.openAct.triggered.connect(self.open)


        self.saveAct = QtWidgets.QAction(QtGui.QIcon(':/images/save.png'),u"&保存",self)
        self.saveAct.setShortcuts(QtGui.QKeySequence.Save)
        self.saveAct.triggered.connect(self.save)

        self.saveAsAct = QtWidgets.QAction(u"&名前を付けて保存",self)
        self.saveAsAct.setShortcuts(QtGui.QKeySequence.SaveAs)
        self.saveAsAct.triggered.connect(self.saveAs)

        self.savePythonFileAct = QtWidgets.QAction(u"&Python &File出力",self)
        self.savePythonFileAct.triggered.connect(self.savePythonFile)

        self.saveXMLFileAct = QtWidgets.QAction(u"&XML &File 出力",self)
        self.saveXMLFileAct.triggered.connect(self.saveXMLFile)

        
        self.size10Act = QtWidgets.QAction("&10",self,checkable=True)
        self.size10Act.triggered.connect(self.set10FontSize)
        self.size12Act = QtWidgets.QAction("&12",self,checkable=True)
        self.size12Act.triggered.connect(self.set12FontSize)
        self.size24Act = QtWidgets.QAction("&24",self,checkable=True)
        self.size24Act.triggered.connect(self.set24FontSize)
        self.size48Act = QtWidgets.QAction("&48",self,checkable=True)
        self.size48Act.triggered.connect(self.set48FontSize)
        
        self.sizeGroup = QtWidgets.QActionGroup(self)
        self.sizeGroup.addAction(self.size10Act)
        self.sizeGroup.addAction(self.size12Act)
        self.sizeGroup.addAction(self.size24Act)
        self.sizeGroup.addAction(self.size48Act)
        self.size12Act.setChecked(True)

        self.pathAct = QtWidgets.QAction(u"&Path設定",self)
        self.pathAct.triggered.connect(self.setPath)

        self.moduleAct = QtWidgets.QAction(u"&インポートモジュール設定",self)
        self.moduleAct.triggered.connect(self.setModule)

        self.execStringAct = QtWidgets.QAction("&exec",self,checkable=True)
        self.execStringAct.triggered.connect(self.setExecString)
        
        self.fileMethodAct = QtWidgets.QAction("&file",self,checkable=True)
        self.fileMethodAct.triggered.connect(self.setFileMethod)

        self.execGroup = QtWidgets.QActionGroup(self)
        self.execGroup.addAction(self.execStringAct)
        self.execGroup.addAction(self.fileMethodAct)
        self.execStringAct.setChecked(True)

    def setModule(self):
        dialog = ModuleDialog(self.module_list, self)
        dialog.show()
        dialog.exec_()
        if dialog.result():
            self.module_list = dialog.getModuleList()
            self.update_modulelist()
            

    def update_modulelist(self):
        
        if self.comp is not None:
            self.comp.update_modulelist(self.module_list)

    def setPath(self):
        dialog = PathDialog(self.path_list, self)
        dialog.show()
        dialog.exec_()
        if dialog.result():
            self.path_list = dialog.getPathList()
            self.update_path()
        
    def update_path(self):
        for p in self.path_list:
            if not (p in sys.path):
                sys.path.append(p)

    def set10FontSize(self):
        for k,i in self.tab_list.items():
            i.setFontSize(10)
        self.global_tab.setFontSize(10)
    def set12FontSize(self):
        for k,i in self.tab_list.items():
            i.setFontSize(12)
        self.global_tab.setFontSize(12)
    def set24FontSize(self):
        for k,i in self.tab_list.items():
            i.setFontSize(24)
        self.global_tab.setFontSize(24)
    def set48FontSize(self):
        for k,i in self.tab_list.items():
            i.setFontSize(48)
        self.global_tab.setFontSize(48)



    def setExecString(self):
        self.update_exec()
        


    def setFileMethod(self):
        self.update_module()
        
        

    def createMenus(self):

        self.fileMenu = self.menuBar().addMenu(u"&ファイル")
        self.fileMenu.addAction(self.newAct)
        self.fileMenu.addAction(self.openAct)
        self.fileMenu.addAction(self.saveAct)
        self.fileMenu.addAction(self.saveAsAct)
        self.exportMenu = self.fileMenu.addMenu(u"&出力")
        self.exportMenu.addAction(self.savePythonFileAct)
        self.exportMenu.addAction(self.saveXMLFileAct)

        self.editMenu = self.menuBar().addMenu(u"&編集")
        self.fontMenu = self.editMenu.addMenu(u"&フォント")
        self.fontMenu.addSeparator().setText("&サイズ")
        self.fontMenu.addAction(self.size10Act)
        self.fontMenu.addAction(self.size12Act)
        self.fontMenu.addAction(self.size24Act)
        self.fontMenu.addAction(self.size48Act)
        
        self.optionMenu = self.menuBar().addMenu(u"&設定")
        self.optionMenu.addAction(self.pathAct)
        self.optionMenu.addAction(self.moduleAct)
        
        self.execMenu = self.optionMenu.addMenu(u"&実行方法")
        self.execMenu.addAction(self.execStringAct)
        self.execMenu.addAction(self.fileMethodAct)
        
        self.helpMenu = self.menuBar().addMenu("&Help")
        


    def saveXMLFile(self):
        
        
        
        fileName = QtWidgets.QFileDialog.getSaveFileName(self,u"保存", "","XML File (*.xml);;All Files (*)")
        
        try:
            if fileName.isEmpty():
                return False
            ba = str(fileName.toLocal8Bit())
        except:
            if not fileName:
                return False
            ba = fileName

        with open(ba, "w") as f:
            #from wasanbon.core.rtc.rtcprofile import RTCProfile
            from rtcprofile_plugin import rtcprofile
            import xml.etree.ElementTree
            from xml.dom import minidom
        
        
            rtcb = rtcprofile.RTCProfileBuilder()
            
            ports = self.comp.get_ports()
            ports_wid = self.vw.renderWindow.ports
            config_params = self.vw.renderWindow.config_params
            key_list = config_params.keys()
            
            for port in ports:
                pp = port.get_port_profile()
                name = pp.name
                rtc_name_len = len(self.comp.getInstanceName())
                p = ports_wid[name[rtc_name_len+1:]]
                portType = p.profile["portType"]
                if portType == "DataOutPort" or portType == "DataInPort":
                    portName = p.profile["portName"]
                    dataType = p.profile["dataType"]
                    rtcb.appendDataPort(portType,dataType,portName)
                elif portType == "ServicePort":
                    portName = p.profile["portName"]
                    IDLFile = p.profile["IDL"]
                    IDLPath = p.profile["IDLPath"]
                    interfaceName = p.profile["interfaceName"]
                    interfaceDir = p.profile["interfaceDir"]
                    interfaceType = p.profile["interfaceType"]
                    rtcb.appendServicePort(portName)
                    rtcb.appendServiceInterfaceToServicePort(portName,IDLPath,IDLFile,interfaceType,interfaceDir,interfaceName)
                    
            for k in key_list:
                name = config_params[k]["paramName"]
                value = config_params[k]["paramDefault"]
                param_type = config_params[k]["paramType"]
                rtcb.appendConfiguration(param_type,name,value)
                
            rp = rtcb.buildRTCProfile()
            tree = rtcprofile.get_etree(rp)
            rough_string = xml.etree.ElementTree.tostring(tree, 'utf-8')
            reparsed = minidom.parseString(rough_string)
            f.write(reparsed.toprettyxml(indent="  "))

                
                    

            
        
    def savePythonFile(self):
        fileName = QtWidgets.QFileDialog.getSaveFileName(self,u"保存", "","Python File (*.py);;All Files (*)")
        try:
            if fileName.isEmpty():
                return False
            ba = str(fileName.toLocal8Bit())
        except:
            if not fileName:
                return False
            ba = fileName
        
        with codecs.open(ba, 'w', 'utf-8') as fh:
            ports = self.comp.get_ports()
            ports_wid = self.vw.renderWindow.ports
            
            file_dir = os.path.relpath(os.path.dirname(ba))
            
            for port in ports:
                pp = port.get_port_profile()
                name = pp.name
                rtc_name_len = len(self.comp.getInstanceName())
                p = ports_wid[name[rtc_name_len+1:]]
                portType = p.profile["portType"]
                if portType == "ServicePort":
                    
                    file_list = p.profile["file_list"]
                    IDLFile = p.profile["IDL"]
                    IDLPath = p.profile["IDLPath"]
                    file_list = p.profile["file_list"]
                    idl_dir = os.path.dirname(IDLFile)
                    self.comp.idlCompile(file_list,IDLPath,idl_dir,file_dir)
            
            
            config_params = self.vw.renderWindow.config_params
            key_list = config_params.keys()
            
            implementation_id, ext = os.path.splitext(os.path.basename(ba))
            type_name = implementation_id
            description = ""
            version = ""
            vendor = ""
            category = ""
            activity_type = "STATIC"
            max_instance = "1"
            language = "Python"
            lang_type = "SCRIPT"
            fh.write("#!/usr/bin/env python\n")
            fh.write("# -*- coding: utf-8 -*-\n")
            fh.write("\n")
            fh.write("\n")
            fh.write("import sys\n")
            fh.write("import time\n")
            fh.write("import os\n")
            fh.write('sys.path.append(".")\n')
            fh.write("import RTC\n")
            fh.write("import OpenRTM_aist\n")
            fh.write("import threading\n")
            fh.write("\n")
            fh.write("\n")

            for k,m in self.module_list.items():
                fh.write("import "+m+" as "+k+"\n")

            for port in ports:
                pp = port.get_port_profile()
                name = pp.name
                rtc_name_len = len(self.comp.getInstanceName())
                p = ports_wid[name[rtc_name_len+1:]]
                portType = p.profile["portType"]
                if portType == "ServicePort":
                    importlist = p.profile["import_list"]
                    fh.write("import "+importlist["idl"]+"\n")
                    fh.write("import "+importlist["module"]+"\n")
                    fh.write("import "+importlist["module__POA"]+"\n")
                        
                    
                    fh.write("\n")
                    fh.write("\n")


            
             
            spec = implementation_id.lower()+"_spec = [\n"
            spec += '\t\t"implementation_id", "' + implementation_id + '",\n'
            spec += '\t\t"type_name", "' + type_name + '",\n'
            spec += '\t\t"description", "' + description + '",\n'
            spec += '\t\t"version", "' + version + '",\n'
            spec += '\t\t"vendor", "' + vendor + '",\n'
            spec += '\t\t"category", "' + category + '",\n'
            spec += '\t\t"activity_type", "' + activity_type + '",\n'
            spec += '\t\t"max_instance", "' + max_instance + '",\n'
            spec += '\t\t"language", "' + language + '",\n'
            spec += '\t\t"lang_type", "' + lang_type + '",\n'

            for k in key_list:
                name = config_params[k]["paramName"]
                value = config_params[k]["paramDefault"]
                spec += '\t\t"conf.default.' + name + '",' + '"' + value + '",\n'
                widget = config_params[k]["paramWidget"]
                spec += '\t\t"conf.__widget__.' + name + '",' + '"' + widget + '",\n'
                constraints = config_params[k]["paramConstraints"]
                spec += '\t\t"conf.__constraints__.' + name + '",' + '"' + constraints + '",\n'
                
                


            spec += '\t\t""]\n'
            
            fh.write(spec)
            fh.write("\n")
            fh.write("\n")

            text = self.global_tab.getText()
            split_text = text.split("\n")
            for st in split_text:
                fh.write(st + "\n")
            fh.write("\n")
            fh.write("\n")

            
            fh.write("class "+implementation_id+"(OpenRTM_aist.DataFlowComponentBase):\n")
            fh.write("\tdef __init__(self, manager):\n")
            fh.write("\t\tOpenRTM_aist.DataFlowComponentBase.__init__(self, manager)\n")
            for port in ports:
                pp = port.get_port_profile()
                name = pp.name
                rtc_name_len = len(self.comp.getInstanceName())
                p = ports_wid[name[rtc_name_len+1:]]

                
                portType = p.profile["portType"]
                if portType == "DataOutPort" or portType == "DataInPort":
                    portName = p.profile["portName"]
                    dataType = p.profile["dataType"]
                    data_variable = p.profile["data_variable"]
                    port_variable = p.profile["port_variable"]
                    dstr = CreateDataObject.CreateDataObject.dataTypeList[dataType]
                    fh.write("\t\tself." + data_variable + " = " + dataType + dstr + "\n")
                    
                    if portType == "DataOutPort":
                        data_type_str = "OutPort"
                    elif portType == "DataInPort":
                        data_type_str = "InPort"
                    else:
                        data_type_str = "OutPort"
                    fh.write("\t\tself." + port_variable + " = OpenRTM_aist." + data_type_str +'("' + portName + '",self.' + data_variable + ")\n")
                elif portType == "ServicePort":
                    portName = p.profile["portName"]
                    
                    interfaceDir = p.profile["interfaceDir"]
                    
                    interfaceType = p.profile["interfaceType"]
                    
                    
                    
                    data_variable = p.profile["data_variable"]
                    port_variable = p.profile["port_variable"]
                    
                    fh.write("\t\tself." + port_variable + ' = OpenRTM_aist.CorbaPort("' + portName + '")\n')
                    if interfaceDir == "Required":
                        fh.write("\t\tself." + data_variable + " = OpenRTM_aist.CorbaConsumer(interfaceType=" + interfaceType + ")\n")
                    elif interfaceDir == "Provided":
                        pass
                    
                
            for k in key_list:
                variable = config_params[k]["variable"]
                value = config_params[k]["paramDefault"]
                data_type = config_params[k]["paramType"]
                
                if type == "int" or type == "short":
                    dt = "int"
                elif type == "long":
                    dt = "long"
                elif type == "float" or type == "double":
                    dt = "float"
                elif type == "string":
                    dt = "str"
                else:
                    dt = "str"
                fh.write("\t\tself."+variable+"= ["+dt+"("+value+")" +"]\n")
            


            fh.write("\n")
            fh.write("\n")
            
            for i in range(0,ActivityCode.ActivityCode.num):
                s = ActivityCode.ActivityCode.toString(i)
                if i == ActivityCode.ActivityCode.onInitialize or i == ActivityCode.ActivityCode.onFinalize:
                    fh.write("\tdef " + s + "(self):\n")
                else:
                    fh.write("\tdef " + s + "(self, ec_id):\n")

                if i == ActivityCode.ActivityCode.onInitialize:
                    for port in ports:
                        pp = port.get_port_profile()
                        name = pp.name
                        rtc_name_len = len(self.comp.getInstanceName())
                        p = ports_wid[name[rtc_name_len+1:]]
                        portType = p.profile["portType"]
                        if portType == "DataOutPort" or portType == "DataInPort":
                            portName = p.profile["portName"]
                            
                            port_variable = p.profile["port_variable"]
                            if portType == "DataOutPort":
                                data_type_str = "addOutPort"
                            elif portType == "DataInPort":
                                data_type_str = "addInPort"
                            else:
                                data_type_str = "addPort"
                            fh.write('\t\tself.' + data_type_str + '("' + portName + '",self.' + port_variable +  ")\n")
                        elif portType == "ServicePort":
                            portName = p.profile["portName"]
                            interfaceName = p.profile["interfaceName"]
                            interfaceDir = p.profile["interfaceDir"]
                            
                            interfaceType = p.profile["interfaceType"]
                            IDLPath = p.profile["IDLPath"]
                            classlist = p.profile["class_list"]
                            importlist = p.profile["import_list"]
                            data_variable = p.profile["data_variable"]
                            port_variable = p.profile["port_variable"]
                            
                            fh.write('\t\tself.' + port_variable + '.registerConsumer("' + interfaceName + '","' + interfaceType + '",self.' + port_variable +  ")\n")
                            fh.write('\t\tself.addPort(self.' + port_variable +  ")\n")
                    for k in key_list:
                        name = config_params[k]["paramName"]
                        variable = config_params[k]["variable"]
                        value = config_params[k]["paramDefault"]
                        fh.write('\t\tself.bindParameter("' + name + '",self.' + variable + ',"' + value + '")\n')


                text = self.tab_list[i].getText()
                tmp_text = text.replace(" ","")
                tmp_text = tmp_text.replace("\t","")
                tmp_text = tmp_text.replace("\n","")
                if tmp_text == "":
                    text = "return RTC.RTC_OK"
                split_text = text.split("\n")
                for st in split_text:
                    fh.write("\t\t" + st + "\n")
                fh.write("\n")
                fh.write("\n")
                    
            fh.write("def "+implementation_id+"Init(manager):\n")
            fh.write("\tprofile = OpenRTM_aist.Properties(defaults_str="+implementation_id.lower()+"_spec)\n")
            fh.write("\tmanager.registerFactory(profile,\n")
            fh.write("\t\t"+implementation_id+",\n")
            fh.write("\t\tOpenRTM_aist.Delete)\n")
            fh.write("\n")
            fh.write("\n")


            fh.write("def MyModuleInit(manager):\n")
            fh.write("\t"+implementation_id+"Init(manager)\n")
            fh.write('\tcomp = manager.createComponent("'+implementation_id+'")\n')
            fh.write("\n")
            fh.write("\n")

            fh.write("def main():\n")
            fh.write("\tmgr = OpenRTM_aist.Manager.init(sys.argv)\n")
            fh.write("\tmgr.setModuleInitProc(MyModuleInit)\n")
            fh.write("\tmgr.activateManager()\n")
            fh.write("\tmgr.runManager()\n")
            fh.write("\n")
            fh.write("\n")

            fh.write('if __name__ == "__main__":\n')
            fh.write("\tmain()")
            

    def openfile(self, filepath):
        with open(filepath, "rb") as f:
            for i in range(0,ActivityCode.ActivityCode.num):
                wid = self.tab_list[i]
                s = readString(f)
                s = QtCore.QString.fromLocal8Bit(s)
                wid.editor.setText(s)
            s = readString(f)
            s = QtCore.QString.fromLocal8Bit(s)
            self.global_tab.editor.setText(s)
            if self.comp is not None:
                self.save_button_slot()
            
            
            self.removeAllPort()
            d = f.read(4)
            length = struct.unpack("i",d)[0]
            for i in range(length):
                profile = {}
                profile["portType"] = readString(f)
                if profile["portType"] == "DataOutPort" or profile["portType"] == "DataInPort":
                    profile["portName"] = readString(f)
                    profile["dataType"] = readString(f)
                
                    self.addDataPortTab.addPort(profile)
                elif profile["portType"] == "ServicePort":
                    profile["portName"] = readString(f)
                    profile["interfaceName"] = readString(f)
                    profile["interfaceDir"] = readString(f)
                    profile["IDL"] = readString(f)
                    profile["interfaceType"] = readString(f)
                    profile["IDLPath"] = readString(f)
                    
                    self.addServicePortTab.addPort(profile)                    
                

            self.removeAllConfigParam()
            d = f.read(4)
            length = struct.unpack("i",d)[0]
            for i in range(length):
                profile = {}
                profile["paramName"] = readString(f)
                profile["paramType"] = readString(f)
                profile["paramDefault"] = readString(f)
                profile["paramConstraints"] = readString(f)
                profile["paramWidget"] = readString(f)
                profile["paramStep"] = readString(f)
                self.addConfigurationTab.addConfiguration(profile)
            self.path_list = []
            d = f.read(4)
            length = struct.unpack("i",d)[0]
            for i in range(length):
                s = readString(f)
                self.path_list.append(s)
            self.update_path()

            d = f.read(4)
            length = struct.unpack("i",d)[0]
            for i in range(length):
                k = readString(f)
                m = readString(f)
                self.module_list[k] = m
                self.update_modulelist()
            
            self.exexType = ord(f.read(1))
                       
                
            

        self.curFile = filepath
    def open(self):
        fileName = QtWidgets.QFileDialog.getOpenFileName(self,u"開く","","RTComponent File (*.rtc);;All Files (*)")
        try:
            if fileName.isEmpty():
                return ""
            filepath = str(fileName.toLocal8Bit())
        except:
            if not fileName:
                return ""
            filepath = fileName
        self.openfile(filepath)

        

    def saveAs(self):
        fileName = QtWidgets.QFileDialog.getSaveFileName(self,u"保存", "","RTComponent File (*.rtc);;All Files (*)")

        try:
            if fileName.isEmpty():
                return False
            ba = str(fileName.toLocal8Bit())
        except:
            if not fileName:
                return False
            ba = fileName
        
        self.saveFile(ba)
        self.curFile = ba
        return True

    def removeAllPort(self):
        self.vw.renderWindow.removeAllPort()
        if self.comp is not None:
            ports = self.comp.get_ports()[:]
            for p in ports:
                p.disconnect_all()
                self.comp.removePort(p)
        self.dataport_widget.list_update({})


    def removeAllConfigParam(self):
        self.vw.renderWindow.removeAllConfigParam()
        self.config_widget.list_update({})

    def saveFile(self, filename):
        with open(filename, "wb") as f:
            for i in range(0,ActivityCode.ActivityCode.num):
                s = self.tab_list[i].getText()
                writeString(f, s)
            s = self.global_tab.getText()
            writeString(f, s)

            if self.comp is not None:
                ports = self.comp.get_ports()
                ports_wid = self.vw.renderWindow.ports
                length = len(ports)
                length_data = struct.pack("i",length)
                f.write(length_data)
                for port in ports:
                    pp = port.get_port_profile()
                    name = pp.name
                    rtc_name_len = len(self.comp.getInstanceName())
                    p = ports_wid[name[rtc_name_len+1:]]
                    s = p.profile["portType"]
                    writeString(f, s)
                    if p.profile["portType"] == "DataOutPort" or p.profile["portType"] == "DataInPort":
                        s = p.profile["portName"]
                        writeString(f, s)
                        s = p.profile["dataType"]
                        writeString(f, s)
                    elif p.profile["portType"] == "ServicePort":
                        s = p.profile["portName"]
                        writeString(f, s)
                        s = p.profile["interfaceName"]
                        writeString(f, s)
                        s = p.profile["interfaceDir"]
                        writeString(f, s)
                        s = p.profile["IDL"]
                        writeString(f, s)
                        s = p.profile["interfaceType"]
                        writeString(f, s)
                        s = p.profile["IDLPath"]
                        writeString(f, s)
                config_params = self.vw.renderWindow.config_params
                key_list = list(config_params.keys())
                key_list.sort()
                length = len(key_list)
                length_data = struct.pack("i",length)
                f.write(length_data)
                for k in key_list:
                    s = config_params[k]["paramName"]
                    writeString(f, s)
                    s = config_params[k]["paramType"]
                    writeString(f, s)
                    s = config_params[k]["paramDefault"]
                    writeString(f, s)
                    s = config_params[k]["paramConstraints"]
                    writeString(f, s)
                    s = config_params[k]["paramWidget"]
                    writeString(f, s)
                    s = config_params[k]["paramStep"]
                    writeString(f, s)
                    
                length = len(self.path_list)
                length_data = struct.pack("i",length)
                f.write(length_data)
                for p in self.path_list:
                    writeString(f, p)
                    
                length = len(self.module_list)
                length_data = struct.pack("i",length)
                f.write(length_data)
                for k,m in self.module_list.items():
                    writeString(f, k)
                    writeString(f, m)
                f.write(chr(self.exexType))
                
          
                
            
            
        

    def save(self):
        if self.curFile == "":
            return self.saveAs()
        else:
            self.saveFile(self.curFile)
            return True

    def newFile(self):
        for k,s in self.activities.items():
            self.tab_list[k].editor.setText(s[0])
        self.global_tab.editor.setText("")
        self.path_list = []
        self.curFile = ""
        self.removeAllPort()
        self.removeAllConfigParam()

    def deleteServicePort(self, name):
        self.vw.renderWindow.removePort(name)
        if self.comp is not None:
            port = self.addServicePortTab.searchPort(name)
            if port:
                port.disconnect_all()
                self.comp.removePort(port)
                self.serviceport_widget.list_update(self.vw.renderWindow.ports)
            

    def deleteDataPort(self, name):
        self.vw.renderWindow.removePort(name)
        if self.comp is not None:
            port = self.addDataPortTab.searchPort(name)
            if port:
                port.disconnect_all()
                self.comp.removePort(port)
                self.dataport_widget.list_update(self.vw.renderWindow.ports)
            
    def deleteConfig(self, name):
        self.vw.renderWindow.removeConfigParam(name)
        if self.comp is not None:
            self.comp.deleteConfigParam(name)
            self.config_widget.list_update(self.vw.renderWindow.config_params)
                
        

    def addActivityTab(self, name, text):
        self.tab_list[name] = ActivityTab.ActivityTab(name, text)
        s = ActivityCode.ActivityCode.toString(name)
        self.tab_widget.addTab(self.tab_list[name], s)
    def save_button_slot(self):
        if self.exexType == ExecType.ExecType.ExecString:
            self.update_exec()
        elif self.exexType == ExecType.ExecType.FileMethod:
            self.update_module()



        

    def update_module(self):
        self.exexType = ExecType.ExecType.FileMethod
        if self.tmp_path == "":
            self.tmp_path = tempfile.mkdtemp()
        filename = "module-" + str(OpenRTM_aist.uuid4()) + ".py"
        filepath = os.path.join(self.tmp_path,filename)
        
        with codecs.open(filepath, 'w', 'utf-8') as fh:
            fh.write("#!/usr/bin/env python\n")
            fh.write("# -*- coding: utf-8 -*-\n")
            fh.write("import RTC\n")
            fh.write("import OpenRTM_aist\n")
            
            text = self.global_tab.getText()
            split_text = text.split("\n")
            for st in split_text:
                fh.write(st + "\n")
                
            
            for i in range(0,ActivityCode.ActivityCode.num):
                s = ActivityCode.ActivityCode.toString(i)
                fh.write("def " + s + "(self):" "\n")
                for k,m in self.module_list.items():
                    fh.write("\t" + k + ' = self.module_list["' + k + '"]\n')
                
                text = self.tab_list[i].getText()
                tmp_text = text.replace(" ","")
                #tmp_text = tmp_text.replace("\t","")
                tmp_text = tmp_text.replace("\n","")
                if tmp_text == "":
                    text = "return RTC.RTC_OK"
                split_text = text.split("\n")
                for st in split_text:
                    fh.write("\t" + st + "\n")
            
        if self.comp is not None:
            self.comp.setModule(filepath)
            
    def update_exec(self):
        self.exexType = ExecType.ExecType.ExecString
        execList = {}
        for i in range(0,ActivityCode.ActivityCode.num):
            execList[i] = ""
            s = ActivityCode.ActivityCode.toString(i)
            execList[i] += "def " + s + "(self):" "\n"
            
            for k,m in self.module_list.items():
                execList[i] += "\t" + k + ' = self.module_list["' + k + '"]\n'

            text = self.tab_list[i].getText()
            tmp_text = text.replace(" ","")
            #tmp_text = tmp_text.replace("\t","")
            tmp_text = tmp_text.replace("\n","")

                            


            if tmp_text == "":
                text = "\treturn RTC.RTC_OK"
            split_text = text.split("\n")
            for st in split_text:
                execList[i] += "\t" + st + "\n"
            execList[i] += s+"(self.rtobj)\n"
            
            
        if self.comp is not None:
            
            self.comp.setExecute(execList)
		