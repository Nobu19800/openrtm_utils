#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
from PyQt5 import QtCore, QtWidgets, QtGui
import Highlighter, Editor
from omniORB import CORBA

class ActivityTab(QtWidgets.QWidget):
    def __init__(self, name, text, parent=None):
        super(ActivityTab, self).__init__(parent)
        self.name = name
        self.text = text
        
        self.mainLayout = QtWidgets.QVBoxLayout()
        
        self.editor = Editor.Editor()
        self.mainLayout.addWidget(self.editor)
        self.highlight = Highlighter.Highlighter(self.editor.document())
        self.editor.setPlainText(self.text[0])
        
        #self.setFixedSize(500,500)
        self.setLayout(self.mainLayout)
        self.editor.textCursor().setPosition(0, QtGui.QTextCursor.MoveAnchor)

        #self.save_button = QtWidgets.QPushButton(u'保存')
        #self.mainLayout.addWidget(self.save_button)
        #self.save_button.clicked.connect(self.save_button_slot)
    def getText(self):
        return str(self.editor.toPlainText())
    def setFontSize(self, s):
        self.editor.setFontSize(s)
    """def save_button_slot(self):
        self.text[0] = str(self.editor.toPlainText())
        #exec self.text[0]
        if self.comp is not None:#not CORBA.is_nil(self.comp):
            self.comp.setActivity(self.name, self.text[0])
        """