// -*- C++ -*-
/*!
 * @file  graphicsview.h
 * @brief 画像表示ウィジェット
 */


#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QImage>
#include <QRect>
#include <QWidget>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc_c.h>
#include <opencv2/imgproc/imgproc.hpp>



/*!
 * @class QGraphicsView
 * @brief 画像表示ウィジェット
 *
 */
class GraphicsView : public QGraphicsView {
	Q_OBJECT
private:
	class QTimer * my_timer;	/**<　@brief  */
	IplImage* iplimage;	/**<　@brief  */
	IplImage* resizeimage;	/**<　@brief  */
	CvVideoWriter *vw;	/**<　@brief  */

public:
	/*!
     * @brief コンストラクタ
     */
	GraphicsView(QWidget *parent);
	/*!
     * @brief デストラクタ
     */
	~GraphicsView();

	/*!
     * @brief 動画の保存を開始
	 * @param fps FPS
	 * @param fn ファイルパス
     */
	void startSaveVideo(int fps, const char* fn);

	bool saveVideo;	/**<　@brief  */
	int m_rate;	/**<　@brief  */
	std::string file_path;	/**<　@brief  */
	std::vector<int> posList;	/**<　@brief  */
	float m_scale;	/**<　@brief  */
	
	/*!
     * @brief 描画イベント
     */
	void paintEvent(QPaintEvent *);
	
protected:
	/*!
     * @brief マウスボタンクリック時のイベント
     */
	void mousePressEvent(QMouseEvent *e);
	/*!
     * @brief マウスボタンリリース時のイベント
     */
	void mouseReleaseEvent(QMouseEvent *e);
	/*!
     * @brief マウス移動時のイベント
     */
	void mouseMoveEvent(QMouseEvent *e);
public slots:
	/*!
     * @brief 一定周期で呼び出されるスロット
     */
	 void show_time();
};

#endif