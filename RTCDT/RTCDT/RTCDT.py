#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

"""
 @file RTCDT.py
 @brief RTC Development Tools
 @date $Date$

 @author 宮本　信彦　n-miyamoto@aist.go.jp
 産業技術総合研究所　ロボットイノベーション研究センター
 ロボットソフトウエアプラットフォーム研究チーム

 LGPL

"""
import sys
import time
import os
sys.path.append(".")
sys.path.append("RTCDTWidget")

if "PACKAGE_DIRECTORIY" in os.environ:
	package_dir = os.environ["PACKAGE_DIRECTORIY"].replace("\"","")
	sys.path.append(package_dir)
	

# Import RTM module
import RTC
import OpenRTM_aist
import SDOPackage
import threading
import importlib
import traceback
import shutil
import tempfile

from PyQt5 import QtCore,QtWidgets
import RTCDTWidget.MainWindow
from RTCDTWidget.ActivityCode import ActivityCode
import RTCDTWidget.CreateDataObject
from RTCDTWidget.ExecType import ExecType
import subprocess

# Import Service implementation class
# <rtc-template block="service_impl">

# </rtc-template>

# Import Service stub modules
# <rtc-template block="consumer_import">
# </rtc-template>


# This module's spesification
# <rtc-template block="module_spec">
rtcdt_spec = ["implementation_id", "RTCDT", 
		 "type_name",         "RTCDT", 
		 "description",       "RTC Development Tools", 
		 "version",           "1.0.0", 
		 "vendor",            "AIST", 
		 "category",          "Logic", 
		 "activity_type",     "STATIC", 
		 "max_instance",      "1", 
		 "language",          "Python", 
		 "lang_type",         "SCRIPT",
		 ""]
# </rtc-template>


class Code:
	def __init__(self, text, rtobj):
		self.text = text
		self.mutex = threading.RLock()
		self.rtobj = rtobj
	def execute(self):
		guard = OpenRTM_aist.ScopedLock(self.mutex)
		ret = RTC.RTC_OK
		exec(self.text)
		return ret
	def change(self, text):
		guard = OpenRTM_aist.ScopedLock(self.mutex)
		self.text = text
		del guard




##
# @class RTCD
# @brief RTC Development Tools
# 
# 実行中に動的に処理を書き換えるRTC
# 
# 
class RTCDT(OpenRTM_aist.DataFlowComponentBase):
	
	##
	# @brief constructor
	# @param manager Maneger Object
	# 
	def __init__(self, manager):
		OpenRTM_aist.DataFlowComponentBase.__init__(self, manager)

		self.exexType = ExecType.ExecString
		self.module = None
		self.module_list = {}
		self.exec_mutex = threading.RLock()
		self.log_list = []
		self.log_mutex = threading.RLock()
		self.workdir = tempfile.mkdtemp()
		#if not os.path.exists(self.workdir):
		#	os.mkdir(self.workdir)
		sys.path.append(os.path.abspath(self.workdir))
		self.activities = {ActivityCode.onInitialize: Code("",self),
							ActivityCode.onFinalize: Code("",self),
							ActivityCode.onStartup: Code("",self),
							ActivityCode.onShutdown: Code("",self),
							ActivityCode.onActivated: Code("",self),
							ActivityCode.onDeactivated: Code("",self),
							ActivityCode.onExecute: Code("",self),
							ActivityCode.onAborting: Code("",self),
							ActivityCode.onError: Code("",self),
							ActivityCode.onReset: Code("",self),
							ActivityCode.onStateUpdate: Code("",self),
							ActivityCode.onRateChanged: Code("",self)}
		


		# initialize of configuration-data.
		# <rtc-template block="init_conf_param">
		
		# </rtc-template>


		 
	##
	#
	# The initialize action (on CREATED->ALIVE transition)
	# formaer rtc_init_entry() 
	# 
	# @return RTC::ReturnCode_t
	# 
	#
	def onInitialize(self):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onInitialize].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onInitialize(self)
			
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
			
			
		#self.activities[ModifyingCodeWidget.ActivityCode.ActivityCode.onInitialize].execute()
		# Bind variables and configuration variable
		
		# Set InPort buffers
		
		# Set OutPort buffers
		
		# Set service provider to Ports
		
		# Set service consumers to Ports
		
		# Set CORBA Service Ports
		
		return RTC.RTC_OK
	
		##
		# 
		# The finalize action (on ALIVE->END transition)
		# formaer rtc_exiting_entry()
		# 
		# @return RTC::ReturnCode_t
	
		# 
	def onFinalize(self):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onFinalize].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onFinalize(self)
			
			
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
	
		##
		#
		# The startup action when ExecutionContext startup
		# former rtc_starting_entry()
		# 
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onStartup(self, ec_id):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onStartup].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onStartup(self)
			
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
	
		##
		#
		# The shutdown action when ExecutionContext stop
		# former rtc_stopping_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onShutdown(self, ec_id):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onShutdown].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onShutdown(self)
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
	
		##
		#
		# The activated action (Active state entry action)
		# former rtc_active_entry()
		#
		# @param ec_id target ExecutionContext Id
		# 
		# @return RTC::ReturnCode_t
		#
		#
	def onActivated(self, ec_id):
		#self.file = open("test_time.txt","w")
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onActivated].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onActivated(self)
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
	
		##
		#
		# The deactivated action (Active state exit action)
		# former rtc_active_exit()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onDeactivated(self, ec_id):
		#self.file.close()
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onDeactivated].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onDeactivated(self)
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
	
		##
		#
		# The execution action that is invoked periodically
		# former rtc_active_do()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onExecute(self, ec_id):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			start = time.time()
			
			
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onExecute].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onExecute(self)
			elapsed_time = time.time() - start
			#self.file.write(str(elapsed_time)+"\n")
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
	
		##
		#
		# The aborting action when main logic error occurred.
		# former rtc_aborting_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onAborting(self, ec_id):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onAborting].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onAborting(self)
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
	
		##
		#
		# The error action in ERROR state
		# former rtc_error_do()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onError(self, ec_id):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onError].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onError(self)
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
	
		##
		#
		# The reset action that is invoked resetting
		# This is same but different the former rtc_init_entry()
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onReset(self, ec_id):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onReset].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onReset(self)
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
	
		##
		#
		# The state update action that is invoked after onExecute() action
		# no corresponding operation exists in OpenRTm-aist-0.2.0
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#

		#
	def onStateUpdate(self, ec_id):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onStateUpdate].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onStateUpdate(self)
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret
	
		##
		#
		# The action that is invoked when execution context's rate is changed
		# no corresponding operation exists in OpenRTm-aist-0.2.0
		#
		# @param ec_id target ExecutionContext Id
		#
		# @return RTC::ReturnCode_t
		#
		#
	def onRateChanged(self, ec_id):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		ret = RTC.RTC_OK
		try:
			
			if self.exexType == ExecType.ExecString:
				ret = self.activities[ActivityCode.onRateChanged].execute()
			elif self.exexType == ExecType.FileMethod:
				if self.module is not None:
					ret = self.module.onRateChanged(self)
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)
			del guard_log
			ret = RTC.RTC_ERROR
		return ret

	def getLog(self):
		guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
		ret = self.log_list[:]
		self.log_list = []
		return ret

	def setExecute(self, execList):
		self.exexType = ExecType.ExecString
		for i in range(ActivityCode.num):
			self.activities[i].change(execList[i])
	
	#def setActivity(self, name, text):
	#	self.activities[name].change(text)
	def setModule(self, filepath):
		self.exexType = ExecType.FileMethod
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		dir_path = os.path.dirname(filepath)
		name, ext = os.path.splitext(os.path.basename(filepath))
		sys.path.append(dir_path)
		try:
			self.module = importlib.import_module(name)
			reload (self.module)
		except:
			guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
			log = traceback.format_exc()
			self.log_list.append(log)



	def setParam(self, conf, set_name, param_name, value=None):
		
		
		try:
			confset = conf.get_configuration_set(set_name)
		except:
			confset = SDOPackage.ConfigurationSet(set_name,"",[])
			conf.add_configuration_set(confset)
		
		confData = confset.configuration_data
		prop = OpenRTM_aist.Properties()
		OpenRTM_aist.NVUtil.copyToProperties(prop, confData)
		if value is None:
			prop.removeNode(param_name)
			
		else:
			prop.setProperty(param_name,value)
		OpenRTM_aist.NVUtil.copyFromProperties(confData,prop)
		
		confset.configuration_data = confData
		
		conf.set_configuration_set_values(confset)




	def deleteConfigParam(self, name):
		conf = self.get_configuration()
		#self.setParam(conf, "default",name)
		#self.setParam(conf, "__widget__",name)
		#self.setParam(conf, "__constraints__",name)
		#conf.activate_configuration_set("default")
		

	def setConfigParam(self, name, data_type, defalut_value, constraints, widget, step):
		conf = self.get_configuration()
		self.setParam(conf, "default",name,defalut_value)
		widget_name = widget
		step = step.replace(" ","")
		step = step.replace("\t","")
		if step:
			widget_name = widget_name+"."+step
		self.setParam(conf, "__widget__",name,widget_name)
		self.setParam(conf, "__constraints__",name,constraints)
		conf.activate_configuration_set("default")
		
		data_name = "_"+name
		self.__dict__[data_name] = [self.getValue(defalut_value,data_type)]
		
		self.bindParameter(name, self.__dict__[data_name], defalut_value)
		return data_name

	def getValue(self ,v, type):
		try:
			if type == "int" or type == "short":
				return int(v)
			elif type == "long":
				return int(v)
			elif type == "float" or type == "double":
				return float(v)
			elif type == "string":
				return v
			else:
				return v
		except:
			return v

	def getServiceNameList(self, idl_file, dir_path, idl_path):
		com = 'omniidl -I"%RTM_ROOT%rtm\idl" -bcreateTemplate ' + idl_file
		if os.name == 'posix':
			com = com.replace("\\","/")
			com = com.split(" ")
		elif os.name == 'nt':
			com = com.replace("/","\\")
		
		sp = subprocess.Popen(com, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		ret = sp.communicate()[0]
		ret = ret.replace("\r","")
		ret = ret.split("\n")

		filelist = []
		
		classlist = {}

		for r in ret:
			if r.find("file:") != -1:
				s = r.replace("file:","")
				if os.path.exists(s):
					filelist.append(s)
				else:
					ps = os.path.join(dir_path, s)
					if os.path.exists(ps):
						filelist.append(ps)
					elif idl_path != "":
						ps = os.path.join(idl_path, s)
						if os.path.exists(ps):
							filelist.append(ps)
			elif r.find("name:") != -1:
				s = r.replace("name:","")
				classlist[s] = []
			elif r.find("operation:") != -1:
				s = r.replace("operation:","")
				n = s.split("#")[0]
				if n in classlist:
					classlist[n].append(s.split("#")[1])
		


		return filelist, classlist

	def idlCompile(self, filelist, idl_path, dir_path, workdir):
		com = 'omniidl -I"%RTM_ROOT%rtm\idl" ' + '-C"' + workdir + '"'
		if idl_path != "":
			com += ' -I"' + idl_path + '" '
		if dir_path != "":
			com += ' -I"' + dir_path + '" '
		com += '-bpython '
		for f in filelist:
			basename = os.path.basename(f)
			copyname = os.path.join(self.workdir, basename)
			copyname = os.path.relpath(copyname)
			shutil.copyfile(f, copyname)
			com += copyname + " "
		
		
		if os.name == 'posix':
			com = com.replace("\\","/")
			com = com.split(" ")
		elif os.name == 'nt':
			com = com.replace("/","\\")	
				
		sp = subprocess.Popen(com, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
		sp.communicate()

	def setServicePort(self, name, interface_name, interface_dir, idl_file, interface_type, idl_path):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		data_name = "_i_" + interface_name
		port_name = "_" + interface_name + "Port"
		

		
		dir_path = os.path.dirname(idl_file)

		filelist,classlist  = self.getServiceNameList(idl_file, dir_path, idl_path)

		if len(filelist) == 0:
			return "","",[],{},[]
		
			
		self.idlCompile(filelist, idl_path, dir_path, self.workdir)
		
		
		idl_name, ext = os.path.splitext(os.path.basename(idl_file))
		module_name = "_GlobalIDL"
		
		spif = interface_type.split(".")
		interface_class = spif[0]
		
		if len(spif) >= 2:
			module_name = spif[0]
			interface_class = spif[1]
		import_name = {}
		#s = "idl/ManipulatorCommonInterface_MiddleLevel_idl.py"
		#name, ext = os.path.splitext(os.path.basename(s))
		#sys.path.append("idl")
		import_name["idl"] = idl_name+"_idl"
		import_name["module"] = module_name
		import_name["module__POA"] = module_name+"__POA"
		
		
		interface_idl = importlib.import_module(import_name["idl"])
		module_obj = importlib.import_module(import_name["module"])
		module_obj__POA = importlib.import_module(import_name["module__POA"])
		#import ManipulatorCommonInterface_MiddleLevel_idl
		#import JARA_ARM, JARA_ARM__POA
		self.__dict__[port_name] = OpenRTM_aist.CorbaPort(name)
		if interface_dir == "Required":
			self.__dict__[data_name] = OpenRTM_aist.CorbaConsumer(interfaceType=module_obj.__dict__[interface_class])
			
		elif interface_dir == "Provided":
			pass
		resname = interface_type.replace(".",":")
		self.__dict__[port_name].registerConsumer(name, resname, self.__dict__[data_name])
		self.addPort(self.__dict__[port_name])
		
		return data_name, port_name, filelist, classlist, import_name


				
	def setDataPort(self, name, port_type, data_type):
		guard = OpenRTM_aist.ScopedLock(self.exec_mutex)
		data_name = "_d_"+name
		self.__dict__[data_name] = RTCDTWidget.CreateDataObject.CreateDataObject.create(data_type)
		port_name = "_"+name

		if port_type == "DataInPort":
			port_name += "In"
			self.__dict__[port_name] = OpenRTM_aist.InPort(name, self.__dict__[data_name])
			self.addInPort(name,self.__dict__[port_name])
		elif port_type == "DataOutPort":
			port_name += "Out"
			self.__dict__[port_name] = OpenRTM_aist.OutPort(name, self.__dict__[data_name])
			self.addOutPort(name,self.__dict__[port_name])
		return data_name, port_name



	def update_modulelist(self, module_names):
		self.module_list = {}
		for k,m in module_names.items():
			try:
				mod = __import__(m)
				reload(mod)
				self.module_list[k] = mod
			except:
				guard_log = OpenRTM_aist.ScopedLock(self.log_mutex)
				log = traceback.format_exc()
				self.log_list.append(log)
		



def RTCDTInit(manager):
    profile = OpenRTM_aist.Properties(defaults_str=rtcdt_spec)
    manager.registerFactory(profile,
                            RTCDT,
                            OpenRTM_aist.Delete)

def MyModuleInit(manager):
    RTCDTInit(manager)

    # Create a component
    comp = manager.createComponent("RTCDT")

def main():
	file_arg = ""
	if len(sys.argv) > 1:
		root, ext = os.path.splitext(sys.argv[1])
		#print(ext)
		if ext == ".rtc":
			file_arg = sys.argv[1]
			del sys.argv[1]
	
	mgr = OpenRTM_aist.Manager.init(sys.argv)
	mgr.setModuleInitProc(MyModuleInit)
	mgr.activateManager()
	mgr.runManager(True)

	comp = mgr.getComponent("RTCDT0")

	
	

	app = QtWidgets.QApplication(sys.argv)
	
	
	sys.path.append("C:/Python27/Lib/site-packages")
	sys.path.append("C:/Python27/DLLs")
	sys.path.append("C:/Python27/lib")
	m = RTCDTWidget.MainWindow.MainWindow(comp, file_arg)
	m.show()
	app.exec_()
	mgr.shutdown()
	
	

if __name__ == "__main__":
	main()

