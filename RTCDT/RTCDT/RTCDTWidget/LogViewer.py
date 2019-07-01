#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
import os
import codecs
from PyQt5 import QtWidgets,QtCore, QtGui





class LogViewer(QtWidgets.QTextEdit):
    def __init__(self, comp, parent=None):
        super(LogViewer,self).__init__(parent)
        self.comp = comp
        self.setReadOnly(True)
        
        self.timer = QtCore.QTimer()
        self.timer.setInterval(100)
        self.timer.timeout.connect(self.check_log)
        self.timer.start()
    def check_log(self):
        if self.comp is not None:
            sb = self.verticalScrollBar()
            log = self.comp.getLog()
            if len(log) > 0:
                curs= self.textCursor()
                curs.movePosition(QtGui.QTextCursor.End)
                for l in log:
                    curs.insertText(l)
                    sb.setValue(sb.maximum())
        
     