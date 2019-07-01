# coding=utf-8

import sys
from setuptools import setup
\
import os
if "PACKAGE_DIRECTORIY" in os.environ:
	package_dir = os.environ["PACKAGE_DIRECTORIY"].replace("\"","")
	sys.path.append(package_dir)

if "SettingRTSystemPath" in os.environ:
	sys.path.append(os.environ["SettingRTSystemPath"])
	sys.path.append(os.path.join(os.environ["SettingRTSystemPath"],"RTCD_IDL"))
	sys.path.append(os.path.join(os.environ["SettingRTSystemPath"],"rtcConfSet"))
#	print(sys.path.append(os.environ["SettingRTSystemPath"]))
#	print(sys.path.append(os.path.join(os.environ["SettingRTSystemPath"],"RTCD_IDL")))
#	print(sys.path)

NAME = 'SettingRTSystem'
LICENSE = 'GPL'
AUTHOR = ''
AUTHOR_EMAIL = ''
DESCRIPTION = ''
URL = ''

import os
#os.environ["SettingRTSystemPath"] = "."
sys.path.append(".\\RTCD_IDL")



if sys.platform == 'win32':
    # Windows
    import py2exe, innosetup
    
    PY2EXE_OPTIONS = {'compressed': 1,
                      'optimize': 2,
                      'bundle_files': 3,
                      'includes': ["rtcprofile_plugin","rtcControl_idl","rtcconf_idl","lxml._elementpath", "PyQt5.QtNetwork","sip","ActArray_idl","AIO_idl","Bumper_idl","Camera_idl","DIO_idl","Fiducial_idl","GPS_idl","Gripper_idl","IMU_idl","INS_idl","Limb_idl","Map_idl","Multicamera_idl","PanTilt_idl","Paths_idl","PointCloud_idl","Position_idl","Ranger_idl","RFID_idl"],
                      'excludes': ["tcl", "Tkinter", "_ssl", "bz2"],
                      }
    
    INNOSETUP_OPTIONS = {'inno_script': innosetup.DEFAULT_ISS,
                         'bundle_vcr': True,
                         'zip': False,
                         }
    setup(
        name = NAME,
        version = 0,
        license = LICENSE,
        author = AUTHOR,
        author_email = AUTHOR_EMAIL,
        description = DESCRIPTION,
        url = URL,
        scripts = ['SettingRTSystem.py'],
        #windows=[{"script": "SettingRTSystem.py"}],
        console=[{"script": "SettingRTSystem.py"}],
        options = {'py2exe': PY2EXE_OPTIONS,
                   'innosetup': INNOSETUP_OPTIONS},
        zipfile = 'SettingRTSystem.lib',
    )

elif sys.platform == 'darwin':
    # Mac
    OPTIONS = {
               "argv_emulation": False,
               "includes": ["sip", "BeautifulSoup", "html5lib", "jsm"],
               'iconfile': 'jsm.icns',
               }
    setup(
        name = NAME,
        version = VERSION,
        license = LICENSE,
        author = AUTHOR,
        author_email = AUTHOR_EMAIL,
        description = DESCRIPTION,
        url = URL,
        app = ['SettingRTSystem.py'],
        options = {'py2app': OPTIONS},
        setup_requires=["py2app"],
    )