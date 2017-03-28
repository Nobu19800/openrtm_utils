cd /d %~dp0

set VC_VERSION=14
set ARCH=x86


set PYTHON_DIR=c:\python27
rem set PYTHONPATH=%PYTHON_DIR%\Lib;%PYTHON_DIR%\Lib\site-packages\rtctree\rtmidl
set RTM_VERSION=1.2.0
set DOMAIN=staging.openrtm.org
set CYGWINPATH=C:\cygwin64\bin



if %VC_VERSION% == 9  (
  set OPENCV_VERSION=2.4.11
) else (
  set OPENCV_VERSION=3.2
)

set CV_SHORT_VER=%OPENCV_VERSION:.=%
set ZIP_NAME=OpenCV%CV_SHORT_VER%_vc%VC_VERSION%_%ARCH%.zip

del /Q %ZIP_NAME%
C:\Cygwin64\bin\wget http://%DOMAIN%/pub/Windows/OpenRTM-aist/msi-buildtools/%RTM_VERSION%/%ZIP_NAME%
rmdir /S /Q OpenCV%OPENCV_VERSION%
%CYGWINPATH%\unzip %ZIP_NAME%
set OpenCV_DIR=%CD%\OpenCV%OPENCV_VERSION%\

set WORKSPACE=C:\Jenkins\workspace\
set RTM_ROOT=%WORKSPACE%10_openrtm-cxx-build-win32\label\%NODE_NAME%\OpenRTM-aist\

set COIL_ROOT=%RTM_ROOT%\coil
set OpenRTM_DIR=%RTM_ROOT%\cmake



set OMNI_ROOT=%RTM_ROOT%\omniORB


set PATH=%OMNI_ROOT%\bin\x86_win32;%PATH%;%PYTHON_DIR%;



set BuildType=Release
set LUABIND_PATH="C:\workspace\luabind-0.9.1"
set EIGEN_DIRECTORIY="C:\workspace\eigen-eigen-67e894c6cd8f"
set ODE_DIRECTORIY="C:\workspace\ode-0.13"
set QWT_DIRECTORIY="C:\workspace\Qwt"
set BOOST_DIRECTORIY="C:\workspace\boost_1_49_0"
set PACKAGE_DIRECTORIY="C:\workspace\site-packages"


cmd /c ExcelControlpy\build_Excel.bat
cmd /c ExcelControlpy\build_Package_Excel.bat

cmd /c PowerPointControlpy\build_PowerPoint.bat
cmd /c PowerPointControlpy\build_Package_PowerPoint.bat

cmd /c WordControlpy\build_Word.bat
cmd /c WordControlpy\build_Package_Word.bat

cmd /c RTCDT\build_RTCDT.bat
cmd /c RTCDT\build_Package_RTCDT.bat

cmd /c SettingRTSystem\build_SettingRTSystem.bat
cmd /c SettingRTSystem\build_Package_SettingRTSystem.bat

cmd /c python_dist\build_python_dist.bat
cmd /c python_dist\build_Package_python_dist.bat