#ifndef _QTWORKER
#define _QTWORKER

#include <QObject>
#include <QImage>
#include "opencv2/highgui/highgui.hpp"

using namespace cv;

class Worker: public QObject{
  Q_OBJECT

public:
  Worker();

public slots:
  void process_next_frame();
signals:
  void updateGLView(const QImage& frame);
private:
  VideoCapture videoCaptured;
};

#endif
