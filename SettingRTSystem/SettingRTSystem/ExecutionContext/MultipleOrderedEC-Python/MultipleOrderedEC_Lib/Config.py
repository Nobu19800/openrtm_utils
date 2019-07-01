# -*- coding: utf-8 -*-
##
# @class Config.py
# @brief 実行条件のウィジェット
#

from PyQt5 import QtCore, QtWidgets


##
# @brief 実行条件のレイアウト内のウィジェットを全て削除する関数
# @param self 
# @param lt 実行条件のレイアウト
def CrearLayout(lt):
    item = lt.takeAt( 1 )
    while ( item != None ):
        item.widget().close()
        item = lt.takeAt( 1 )


##
# @class CompList
# @brief 実行条件のウィジェットに表示するRTCのクラス
#
class CompList:
    ##
    # @brief コンストラクタ
    # @param self 
    def __init__(self):
        self.name = None
        self.Name = ""
        self.c_none = None
        self.c_created = None
        self.c_inactive = None
        self.c_active = None
        self.c_error = None
        self.Lo = None
        self.Lw = None



##
# @class Configs
# @brief 実行条件のウィジェット
#
class Configs(QtWidgets.QWidget):
    ##
    # @brief コンストラクタ
    # @param self 
    # @param parent 親ウィジェット
    def __init__(self, parent=None):
        super(Configs, self).__init__(parent)
        self.Cl = []
        
        self.componentName = QtWidgets.QLabel(u"コンポーネント")
        self.noneName = QtWidgets.QLabel(u"条件なし")
        self.createdName = QtWidgets.QLabel(u"CREATED")
        self.inactiveName = QtWidgets.QLabel(u"INACTIVE")
        self.activeName = QtWidgets.QLabel(u"ACTIVE")
        self.errorName = QtWidgets.QLabel(u"ERROR")

        self.componentName.setFrameStyle( QtWidgets.QFrame.Box)
        self.noneName.setFrameStyle( QtWidgets.QFrame.Box)
        self.createdName.setFrameStyle( QtWidgets.QFrame.Box)
        self.inactiveName.setFrameStyle( QtWidgets.QFrame.Box)
        self.activeName.setFrameStyle( QtWidgets.QFrame.Box)
        self.errorName.setFrameStyle( QtWidgets.QFrame.Box)

        self.Nlist = QtWidgets.QVBoxLayout()
        self.Nlist.addWidget(self.componentName)

        self.Dl = QtWidgets.QHBoxLayout()
        self.Dl.addWidget(self.noneName)
        self.Dl.addWidget(self.createdName)
        self.Dl.addWidget(self.inactiveName)
        self.Dl.addWidget(self.activeName)
        self.Dl.addWidget(self.errorName)

        self.Dw = QtWidgets.QWidget()
        self.Dw.setLayout(self.Dl)

        


        self.CRlist = QtWidgets.QVBoxLayout()

        self.CRlist.addWidget(self.Dw)

        self.subLayout = QtWidgets.QHBoxLayout()
        self.subLayout.addLayout(self.Nlist);
        self.subLayout.addLayout(self.CRlist);

        self.mainLayout = QtWidgets.QVBoxLayout()
        self.mainLayout.addLayout(self.subLayout)
        self.mainLayout.addStretch()


        self.setLayout(self.mainLayout)

    
    ##
    # @brief RTCが追加されたときに反映する関数
    # @param self 
    # @param name RTC名
    def addComp(self, name):
        self.cl = CompList()
        self.cl.Name = name
        self.cl.name = QtWidgets.QLabel(name)
        self.cl.c_none = QtWidgets.QRadioButton()
        self.cl.c_created = QtWidgets.QRadioButton()
        self.cl.c_inactive = QtWidgets.QRadioButton()
        self.cl.c_active = QtWidgets.QRadioButton()
        self.cl.c_error = QtWidgets.QRadioButton()

        self.cl.c_none.setChecked(True)
        
        self.cl.Lo = QtWidgets.QHBoxLayout()
        self.cl.Lw = QtWidgets.QWidget()
        


        self.Nlist.addWidget(self.cl.name)
        self.cl.Lo.addWidget(self.cl.c_none,0,QtCore.Qt.AlignCenter)
        self.cl.Lo.addWidget(self.cl.c_created,0,QtCore.Qt.AlignCenter)
        self.cl.Lo.addWidget(self.cl.c_inactive,0,QtCore.Qt.AlignCenter)
        self.cl.Lo.addWidget(self.cl.c_active,0,QtCore.Qt.AlignCenter)
        self.cl.Lo.addWidget(self.cl.c_error,0,QtCore.Qt.AlignCenter)
        self.cl.Lw.setLayout(self.cl.Lo)
        self.CRlist.addWidget(self.cl.Lw)

        self.Cl.append(self.cl)
        
    
    ##
    # @brief 初期化の関数
    # @param self 
    def resetComp(self):
        self.Cl = []
        CrearLayout(self.Nlist)
        CrearLayout(self.CRlist)
