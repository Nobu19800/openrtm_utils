#!/bin/env python
# -*- encoding: cp932 -*-

##
#   @file WordRTC.py
#   @brief WordControl Component

import win32com
import pythoncom
import pdb
from win32com.client import *
import pprint
import datetime
import msvcrt




import optparse
import sys,os,platform
import re
import time
import random
import commands
import math





##
# @class WordObject
# @brief Word�𑀍삷��N���X
#
class WordObject:
    wdCharacter = 1
    wdWord = 2
    wdSentence = 3
    wdParagraph = 4
    wdLine = 5
    wdStory = 6
    wdScreen = 7
    wdSection = 8
    wdColumn = 9
    wdRow = 10
    wdWindow = 11
    wdTable = 15

    wdMove = 0
    wdExtend = 1

    ##
    # @brief �R���X�g���N�^
    # @param self 
    #
    def __init__(self):
        self.dcApplication = None
        self.dcDocuments = None
        self.dcDocument = None
        self.fontSize = 20
        self.fontName = "�l�r ����"
        self.filename = " "
        self.char_Red = 0
        self.char_Green = 0
        self.char_Blue = 0
        self.movementType = False
        self.italic = False
        self.bold = False

        self.underline = False
        self.shadow = False
        self.strikeout = False
        self.contoured = False
        self.emphasis = False

        self.back_Red = 255
        self.back_Green = 255
        self.back_Blue = 255

        self.thread_dcApplication = None
        self.thread_dcDocuments = None
        self.thread_dcDocument = None

        self.t_dcApplication = None
        self.t_dcDocuments = None
        self.t_dcDocument = None

    ##
    # @brief �����̐F��ύX����֐�
    # @param self
    # @param r �����̐F(R)
    # @param g �����̐F(G)
    # @param b �����̐F(B)
    #
    def setFontColor(self, r, g, b):
        self.char_Red = r
        self.char_Green = g
        self.char_Blue = b

    ##
    # @brief �w�i�F��ύX����֐�
    # @param self
    # @param r �����̐F(R)
    # @param g �����̐F(G)
    # @param b �����̐F(B)
    #
    def setBackColor(self, r, g, b):
        self.back_Red = r
        self.back_Green = g
        self.back_Blue = b

    ##
    # @brief �t�H���g�̃T�C�Y��ύX����֐�
    # @param self
    # @param fs �t�H���g�T�C�Y
    #
    def setFontSize(self, fs):
        self.fontSize = fs

    ##
    # @brief �t�H���g�̎�ނ�ύX����֐�
    # @param self
    # @param fn �t�H���g�̎��
    #
    def setFontName(self, fn):
        self.fontName = fn

    ##
    # @brief ��������������ފ֐�
    # @param self
    # @param st �������ޕ�����
    #
    def setWord(self, st):
        
        
        currentSelection = self.dcApplication.Selection
        

        slc = currentSelection.End

        
        tr = self.dcDocument.Range(slc,slc)
        

        tr.Text = st

        tr.Font.Size = self.fontSize
        tr.Font.Name = self.fontName
        tr.Font.Bold = self.bold

        currentSelection.MoveRight(WordObject.wdCharacter, len(st) , WordObject.wdMove)

    ##
    # @brief �I���ʒu�̕�������擾����֐�
    # @param self
    # @return �擾����������
    #
    def getSelWord(self):

        currentSelection = self.dcApplication.Selection
        
        return currentSelection.Text.encode("utf-8")

    ##
    # @brief �I���ʒu��ύX����֐�
    # @param self
    # @param m_type �ړ��̃^�C�v
    # @param leng �ړ���
    #
    def moveSelection(self, m_type, leng):
        currentSelection = self.dcApplication.Selection
        if not self.MovementType:
            currentSelection.MoveRight(m_type, leng, WordObject.wdMove)
        else:
            currentSelection.MoveRight(m_type, leng, WordObject.wdExtend)

    ##
    # @brief 
    # @param self
    #
    def preInitCom(self):
        self.thread_dcApplication = pythoncom.CoMarshalInterThreadInterfaceInStream (pythoncom.IID_IDispatch, self.t_dcApplication)
        self.thread_dcDocuments = pythoncom.CoMarshalInterThreadInterfaceInStream (pythoncom.IID_IDispatch, self.t_dcDocuments)
        self.thread_dcDocument = pythoncom.CoMarshalInterThreadInterfaceInStream (pythoncom.IID_IDispatch, self.t_dcDocument)

    ##
    # @brief 
    # @param self
    #
    def initCom(self):
        #if self.dcApplication == None:
           pythoncom.CoInitialize()
           self.dcApplication = win32com.client.Dispatch ( pythoncom.CoGetInterfaceAndReleaseStream (self.thread_dcApplication, pythoncom.IID_IDispatch))
           self.dcDocuments = win32com.client.Dispatch ( pythoncom.CoGetInterfaceAndReleaseStream (self.thread_dcDocuments, pythoncom.IID_IDispatch))
           self.dcDocument = win32com.client.Dispatch ( pythoncom.CoGetInterfaceAndReleaseStream (self.thread_dcDocument, pythoncom.IID_IDispatch))

    ##
    # @brief 
    # @param self
    #
    def closeCom(self):
        pythoncom.CoUninitialize()
        self.dcApplication = None
        self.dcDocuments = None
        self.dcDocument = None
        

    ##
    # @brief Word�t�@�C�����J���֐�
    # @param self
    # @param fn �t�@�C���p�X
    #
    def Open(self, fn):
        if self.filename == fn:
            return
        self.filename = fn

        
        
        try:
            
            
            t_dcApplication = win32com.client.Dispatch("Word.Application")
               
            
              
            
            
            
            t_dcApplication.Visible = True
            try:
                t_dcDocuments = t_dcApplication.Documents
                

                try:
                    t_dcDocument = None
                    if self.filename == "":
                        t_dcDocument = t_dcDocuments.Add()
                    else:
                        t_dcDocument = t_dcDocuments.Open(self.filename)

                    
                    if self.t_dcApplication == None:
                       self.t_dcApplication = t_dcApplication
                       self.t_dcDocuments = t_dcDocuments
                       self.t_dcDocument = t_dcDocument
                       self.preInitCom()
                    
                    
                    

                    

                    
                except:
                    return
            except:
                return
        except:
            return


