#include "Worker.h"
#include <QDebug>

Worker::Worker(){
  this->videoCaptured= VideoCapture("/Users/delvistaveras/Desktop/Dolby_Video/video-input-psnr-ssim/video/Megamind.avi"); // open the video file for reading
}

void Worker::process_next_frame(){
  qDebug() << "Go ahead and process the next frame";
  Mat cvFrame;
  bool bSuccess = videoCaptured.read(cvFrame);
  if(bSuccess){
    qDebug() << "video is open homie";
    QImage qtFrame(cvFrame.data, cvFrame.size().width, cvFrame.size().height, cvFrame.step, QImage::Format_RGB888);
    qtFrame = qtFrame.rgbSwapped();
    emit updateGLView(qtFrame);
  }

}


