# -*- coding: utf-8 -*-
##
#   @file FEComp.py
#   @brief 直列ブロックのウィジェット

from PyQt5 import QtCore, QtWidgets



##
# @class FEComp
# @brief 直列ブロックのウィジェット
#
class FEComp(QtWidgets.QWidget):
    ##
    # @brief コンストラクタ
    # @param self 
    # @param parent 親ウィジェット
    def __init__(self, parent=None):
        super(FEComp, self).__init__(parent)
        self.ECS = []
        self.CL = QtWidgets.QVBoxLayout()
        
        self.setLayout(self.CL)

        
