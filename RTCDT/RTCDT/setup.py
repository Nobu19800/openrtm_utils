# coding=utf-8

import sys
from setuptools import setup
\
import os
if "PACKAGE_DIRECTORIY" in os.environ:
	package_dir = os.environ["PACKAGE_DIRECTORIY"].replace("\"","")
	sys.path.append(package_dir)

NAME = 'RTCDT'
LICENSE = 'GPL'
AUTHOR = ''
AUTHOR_EMAIL = ''
DESCRIPTION = ''
URL = ''

if sys.platform == 'win32':
    # Windows
    import py2exe, innosetup
    
    PY2EXE_OPTIONS = {'compressed': 1,
                      'optimize': 2,
                      'bundle_files': 3,
                      'includes': ["rtcprofile_plugin","cv2","numpy","PyQt5.QtNetwork","sip","ActArray_idl","AIO_idl","Bumper_idl","Camera_idl","DIO_idl","Fiducial_idl","GPS_idl","Gripper_idl","IMU_idl","INS_idl","Limb_idl","Map_idl","Multicamera_idl","PanTilt_idl","Paths_idl","PointCloud_idl","Position_idl","Ranger_idl","RFID_idl"],
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
        scripts = ['RTCDT.py'],
        #windows=[{"script": "RTCDT.py"}],# 'icon_resources': [(1, "icon.ico")] }],
        console=[{"script": "RTCDT.py"}],
        options = {'py2exe': PY2EXE_OPTIONS,
                   'innosetup': INNOSETUP_OPTIONS},
        zipfile = 'RTCDT.lib',
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
        app = ['RTCDT.py'],
        options = {'py2app': OPTIONS},
        setup_requires=["py2app"],
    )