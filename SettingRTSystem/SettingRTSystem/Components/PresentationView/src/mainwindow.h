// -*- C++ -*-
/*!
 * @file  mainwindow.h
 * @brief ���C���E�C���h�E
 */



#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QtWidgets>

#include "graphicsview.h"


class ToolBar;
QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QSignalMapper)


/*!
 * @class MainWindow
 * @brief ���C���E�C���h�E
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/*!
     * @brief �R���X�g���N�^
     */
    MainWindow();
	QPushButton *pageGB;	/**<�@@brief  */
	QPushButton *pageRB;	/**<�@@brief  */
	QPushButton *effGB;	/**<�@@brief  */
	QPushButton *effRB;	/**<�@@brief  */
	QPushButton *saveSB;	/**<�@@brief  */
	QPushButton *saveEB;	/**<�@@brief  */
	QSpinBox *fpsSB;	/**<�@@brief  */
	QSpinBox *scaleSB;	/**<�@@brief  */
	QPushButton *updateB;	/**<�@@brief  */
	QPushButton *connectB;	/**<�@@brief  */
	QTableWidget *grtcTable;	/**<�@@brief  */
	

//protected:
    
signals:
	
public slots:
	/*!
     * @brief �X���C�h��i�߂�{�^�����������Ƃ��̃X���b�g
     */
    void pageGclickedSlot();
	/*!
     * @brief �X���C�h��߂�{�^�����������Ƃ��̃X���b�g
     */
	void pageRclickedSlot();
	/*!
     * @brief �A�j���[�V������i�߂�{�^�����������Ƃ��̃X���b�g
     */
	void effGclickedSlot();
	/*!
     * @brief �A�j���[�V������߂�{�^�����������Ƃ��̃X���b�g
     */
	void effRclickedSlot();
	/*!
     * @brief �����ۑ�����{�^�����������Ƃ��̃X���b�g
     */
	void saveSclickedSlot();
	/*!
     * @brief ����̕ۑ����I������{�^�����������Ƃ��̃X���b�g
     */
	void saveEclickedSlot();
	/*!
     * @brief ���惊�X�g�̍X�V�{�^�����������Ƃ��̃X���b�g
     */
	void updateclickedSlot();
	/*!
     * @brief �f�[�^�|�[�g�ڑ��{�^�����������Ƃ��̃X���b�g
     */
	void connectclickedSlot();
	/*!
     * @brief �g�嗦�X�s���{�b�N�X�̒l���ω������Ƃ��̃X���b�g
     */
	void scalevalueChangedSlot(int v);
	

private:
	QTextCodec* tc;	/**<�@@brief  */
	GraphicsView *gv;	/**<�@@brief  */
	std::vector<std::vector<std::string>> m_result;	/**<�@@brief  */
    
};


#endif
