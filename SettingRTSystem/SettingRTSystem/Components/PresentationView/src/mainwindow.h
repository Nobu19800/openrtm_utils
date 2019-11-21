// -*- C++ -*-
/*!
 * @file  mainwindow.h
 * @brief メインウインドウ
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
 * @brief メインウインドウ
 *
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	/*!
     * @brief コンストラクタ
     */
    MainWindow();
	QPushButton *pageGB;	/**<　@brief  */
	QPushButton *pageRB;	/**<　@brief  */
	QPushButton *effGB;	/**<　@brief  */
	QPushButton *effRB;	/**<　@brief  */
	QPushButton *saveSB;	/**<　@brief  */
	QPushButton *saveEB;	/**<　@brief  */
	QSpinBox *fpsSB;	/**<　@brief  */
	QSpinBox *scaleSB;	/**<　@brief  */
	QPushButton *updateB;	/**<　@brief  */
	QPushButton *connectB;	/**<　@brief  */
	QTableWidget *grtcTable;	/**<　@brief  */
	

//protected:
    
signals:
	
public slots:
	/*!
     * @brief スライドを進めるボタンを押したときのスロット
     */
    void pageGclickedSlot();
	/*!
     * @brief スライドを戻るボタンを押したときのスロット
     */
	void pageRclickedSlot();
	/*!
     * @brief アニメーションを進めるボタンを押したときのスロット
     */
	void effGclickedSlot();
	/*!
     * @brief アニメーションを戻るボタンを押したときのスロット
     */
	void effRclickedSlot();
	/*!
     * @brief 動画を保存するボタンを押したときのスロット
     */
	void saveSclickedSlot();
	/*!
     * @brief 動画の保存を終了するボタンを押したときのスロット
     */
	void saveEclickedSlot();
	/*!
     * @brief 動画リストの更新ボタンを押したときのスロット
     */
	void updateclickedSlot();
	/*!
     * @brief データポート接続ボタンを押したときのスロット
     */
	void connectclickedSlot();
	/*!
     * @brief 拡大率スピンボックスの値が変化したときのスロット
     */
	void scalevalueChangedSlot(int v);
	

private:
	QTextCodec* tc;	/**<　@brief  */
	GraphicsView *gv;	/**<　@brief  */
	std::vector<std::vector<std::string>> m_result;	/**<　@brief  */
    
};


#endif
