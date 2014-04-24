#ifndef _QTWORKER
#define _QTWORKER

#include <QObject>
#include <QImage>
#include "opencv2/highgui/highgui.hpp"
using namespace cv;

typedef QVector<double> dataVector;

class Worker: public QObject{
  Q_OBJECT

public:
  Worker();
  double count;
private:
  double normal_psnr(Mat frame1, Mat frame2);
  double cuda_psnr(Mat frame1, Mat frame2);
public slots:
  void process_next_frame();
signals:
  void updateGLView(const QImage& frame);
  void updateData(dataVector x, dataVector y);
  void updateAddData(double x, double y);
private:
  VideoCapture videoCaptured;
  Mat prevFrame;
};

#endif
