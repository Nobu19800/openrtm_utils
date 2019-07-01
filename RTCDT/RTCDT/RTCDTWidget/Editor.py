#!/usr/bin/env python
# -*- coding: utf-8 -*-
# -*- Python -*-

import sys
from PyQt5 import QtWidgets,QtCore,QtGui





class Editor(QtWidgets.QTextEdit):
    tab_keywords = [
        'break', 'return'
    ]
    def __init__(self, parent=None):
        super(Editor,self).__init__(parent)
        self.setTabStopWidth(20)
        self.fontSize = 12
        self.wrapColumn = 80
        self.createFont(self.fontSize, self.wrapColumn)
        
        #self.setTabChangesFocus(False)
        #self.setTabStopWidth(100)


    def createFont(self, fontSize, wrapColumn):
        font = QtGui.QFont("monospace", fontSize)
        font.setStyleHint(QtGui.QFont.TypeWriter)
        fontPxSize = QtGui.QFontMetrics(font).width('0')
        self.setFont(font)
        self.setWordWrapMode(QtGui.QTextOption.WrapAtWordBoundaryOrAnywhere)
        self.setLineWrapMode(QtWidgets.QTextEdit.FixedPixelWidth)
        self.setLineWrapColumnOrWidth(fontSize * wrapColumn)

    def insertFromMimeData(self, source):
        if source.hasText():
            self.textCursor().insertText(source.text())
            
    def resizeEvent(self, e):
        return

    def setFontSize(self, s):
        self.createFont(s, self.wrapColumn)

    def keyPressEvent(self,e):
        super(Editor,self).keyPressEvent(e)


        cu = self.textCursor()
        c = self.document().lineCount()

        
        if e.key() == QtCore.Qt.Key_Enter or e.key() == QtCore.Qt.Key_Return:
            
            try:
                s = str(self.document().findBlockByLineNumber(cu.blockNumber()-1).text().toLocal8Bit())
            except:
                s = self.document().findBlockByLineNumber(cu.blockNumber()-1).text()
            if len(s) > 0:
                add_str = ""
                for c in s:
                    if c == "\t" or c == " ":
                        add_str += c
                    else:
                        break
                if s[-1] == ":":
                    add_str += "\t"
                if len(add_str) > 0:
                    for k in Editor.tab_keywords:
                        p = s.replace("\t", " ")
                        p = p.split(" ")[-1]
                        
                        if p == k:
                            add_str = add_str[:-1]
                cu.insertText(add_str)
            

        
        




