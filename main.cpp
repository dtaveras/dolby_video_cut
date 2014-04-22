#include "glWindow.h"
#include <QApplication>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QThread>
#include <QObject>
#include "Worker.h"
#include "QCustomGraph/qcustomplot.h"
#include <QDebug>

#define WIND_WIDTH 800
#define WIND_HEIGHT 600
#define GRAPH_HEIGHT 100

int main( int argc, char **argv )
{
  QApplication app( argc, argv );
  qDebug() << "Starting Transition Detector";
  QWidget* window = new QWidget;
  window->setWindowTitle("Video Transition Detector");
  window->setMinimumSize(WIND_WIDTH, WIND_HEIGHT);

  GLWindow* rGLWindow = new GLWindow(window);
  rGLWindow->setFocusPolicy(Qt::StrongFocus);
  rGLWindow->grabKeyboard();

  QFrame* graphFrame = new QFrame;
  graphFrame->setMaximumSize(WIND_WIDTH, GRAPH_HEIGHT);
  graphFrame->setStyleSheet("background-color: #2B2E3F");

  //Set Custom Plot which shows the time vs score
  QCustomPlot* customPlot = new QCustomPlot;
  QVector<double> x(101), y(101); // initialize with entries 0..100
  for (int i=0; i<101; ++i)
  {
    x[i] = i/50.0 - 1; // x goes from -1 to 1
    y[i] = x[i]*x[i];  // let's plot a quadratic function
  }

  customPlot->setMinimumSize(WIND_WIDTH, GRAPH_HEIGHT);
  customPlot->setMaximumSize(WIND_WIDTH, GRAPH_HEIGHT);
  customPlot->rescaleAxes(true);
  // create graph and assign data to it:
  customPlot->addGraph();
  customPlot->graph(0)->setData(x, y);
  // give the axes some labels:
  //customPlot->xAxis->setLabel("x");
  //customPlot->yAxis->setLabel("y");
  // set axes ranges, so we see all data:
  customPlot->xAxis->setRange(-1, 1);
  customPlot->yAxis->setRange(0, 1);

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(rGLWindow);
  mainLayout->addWidget(customPlot);
  window->setLayout(mainLayout);
  
  QThread* thread = new QThread;
  Worker* worker = new Worker();
  worker->moveToThread(thread);

  QObject::connect(rGLWindow, SIGNAL(frameChanged()), worker, SLOT(process_next_frame()));
  QObject::connect(thread, SIGNAL(started()), worker, SLOT(process_next_frame()));
  QObject::connect(worker, SIGNAL(updateGLView(QImage)), rGLWindow, SLOT(updateFrame(QImage)));
  
  thread->start();

  window->show();

  return app.exec();
}
