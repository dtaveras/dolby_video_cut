#include "Worker.h"
#include <QDebug>

Worker::Worker(){
  this->videoCaptured= VideoCapture("/Users/delvistaveras/Desktop/Dolby_Video/video-input-psnr-ssim/video/Megamind.avi"); // open the video file for reading
  this->count = 0.0;
}

void Worker::process_next_frame(){
  //qDebug() << "Go ahead and process the next frame";
  Mat cvFrame; 
  bool bSuccess1 = videoCaptured.read(cvFrame);
  
  if(bSuccess1){
    //qDebug() << "video is open homie";

    if(this->count > 0.0){
      double score = normal_psnr(prevFrame,cvFrame);
      emit updateAddData(this->count, score);
    }
    else{
      emit updateAddData(this->count, 0);
    }

    QImage qtFrame(cvFrame.data, cvFrame.size().width, cvFrame.size().height, cvFrame.step, QImage::Format_RGB888);
    qtFrame = qtFrame.rgbSwapped();
    emit updateGLView(qtFrame);
    this->count += 1.0;
    this->prevFrame = cvFrame;
  }
}

double Worker::normal_psnr(Mat frame1, Mat frame2){
  double psnr = 0;

  Mat s1;
  s1.convertTo(s1, CV_32F);  // cannot make a square on 8 bits 

  absdiff(frame1, frame2, s1); // |I1 - I2|
  s1 = s1.mul(s1);           // |I1 - I2|^2
      
  Scalar s = sum(s1);        // sum elements per channel
  double sse = s.val[0] + s.val[1] + s.val[2]; // sum channels
  if( sse <= 1e-10) // for small values return zero
    psnr = 0;
  else
    {
      double mse  = sse / (double)(frame1.channels() * frame1.total());
      psnr = 10.0 * log10((255 * 255) / mse);
    }
  return psnr;
}

