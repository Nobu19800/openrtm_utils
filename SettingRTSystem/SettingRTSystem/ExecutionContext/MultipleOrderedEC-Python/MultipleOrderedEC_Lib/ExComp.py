# -*- coding: utf-8 -*-

##
#   @file ExComp.py
#   @brief RTCのブロックのウィジェット


from PyQt5 import QtCore, QtWidgets, QtGui
from FEComp import FEComp



##
# @class CompLayout
# @brief 並列ブロックのレイアウト
#
class CompLayout:
    ##
    # @brief コンストラクタ
    # @param self 
    def __init__(self):
        self.VL = []
        self.subLayout = None
        self.AB = None
        self.mainLayout = None
        self.mainWidget = None
        self.subWidget = None
        self.Lb = None



##
# @class ExComp
# @brief RTCのブロックのウィジェット
#
class ExComp(QtWidgets.QWidget):
    AddCompSignal = QtCore.pyqtSignal(QtWidgets.QWidget, QtWidgets.QWidget)
    ##
    # @brief コンストラクタ
    # @param self 
    # @param parent 親ウィジェット
    def __init__(self, parent=None):
        super(ExComp, self).__init__(parent)
        self.Fc = None
        self.CB = QtWidgets.QComboBox()
        self.setMaximumSize(100, 160)
        self.setMinimumSize(100, 160)
        self.subLayout = QtWidgets.QVBoxLayout()
        self.subWidget = QtWidgets.QWidget(self)
        self.subWidget.setLayout(self.subLayout)
        self.palette = QtWidgets.QPalette()
        self.palette.setColor(QtWidgets.QPalette.Background, QtGui.QColor(140, 140, 140))
        self.subWidget.setPalette(self.palette)
        self.subWidget.setForegroundRole(QtWidgets.QPalette.Dark)

        self.subWidget.setAutoFillBackground(True)

        self.BT = QtWidgets.QPushButton(u"削除")
        self.BT.clicked.connect(self.DeleteComp)

        self.DT = QtWidgets.QPushButton(u"追加")
        self.DT.clicked.connect(self.AddCompSlot)

        self.Lb = QtWidgets.QLabel()

        self.mainLayout = QtWidgets.QVBoxLayout()
        self.subLayout.addStretch()
        self.subLayout.addWidget(self.CB)
        self.subLayout.addWidget(self.BT)
        self.subLayout.addStretch()
        self.mainLayout.addWidget(self.subWidget)
        self.mainLayout.addWidget(self.Lb)
        self.mainLayout.addWidget(self.DT)
        self.mainLayout.addStretch()

        self.Lb.setPixmap(QtWidgets.QPixmap(":/images/arrow.png").scaled(self.DT.sizeHint()))

        self.setLayout(self.mainLayout)

    
    ##
    # @brief RTCを追加ボタンを押したときに呼び出されるスロット
    # @param self 
    def AddCompSlot(self):
        self.AddCompSignal.emit(self, self.Fc)

    
    ##
    # @brief RTCが追加、削除されたときに実行条件に反映する関数
    # @param self 
    # @param rtclist RTCのリスト
    # @param rtclist2 未使用
    def UpdateComp(self, rtclist, rtclist2):
        Id = self.CB.currentIndex()
        if Id <= 0:
            Id = 0
        self.CB.clear()
        
        for i in range(0,len(rtclist)):
            self.CB.addItem(rtclist[i])

        if Id < len(rtclist):
            self.CB.setCurrentIndex(Id)

	

    ##
    # @brief ブロック削除ボタンのスロット
    # @param self 
    def DeleteComp(self):
        self.Fc.ECS.remove(self)
        
        self.Fc.CL.removeWidget(self)

        self.close()




        
