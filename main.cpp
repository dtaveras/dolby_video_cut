#include "glWindow.h"
#include <QApplication>
#include <qpushbutton.h>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QThread>
#include <QObject>
#include "Worker.h"
#include "QCustomGraph/qcustomplotwidget.h"
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
  window->setStyleSheet("background-color: #353439;");

  GLWindow* rGLWindow = new GLWindow(window);
  rGLWindow->setFocusPolicy(Qt::StrongFocus);
  rGLWindow->grabKeyboard();

  QFrame* graphFrame = new QFrame;
  graphFrame->setMaximumSize(WIND_WIDTH, GRAPH_HEIGHT);
  graphFrame->setStyleSheet("background-color: #2B2E3F");

  //Set Custom Plot which shows the time vs score
  QCustomPlotWidget* customPlot = new QCustomPlotWidget;

  /*customPlot->plotLayout()->insertRow(0);
  customPlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(customPlot, "Regenerat \
  ive Energies"));*/
  customPlot->setMinimumSize(WIND_WIDTH, GRAPH_HEIGHT);
  customPlot->setMaximumSize(WIND_WIDTH, GRAPH_HEIGHT);
  customPlot->rescaleAxes(true);
  // create graph and assign data to it:
  customPlot->addGraph();

  //Remove the x y labels and ticks
  customPlot->rescaleAxes();
  //customPlot->yAxis->setTicks(false);
  //customPlot->yAxis->setTickLabels(false);
  //customPlot->xAxis->setTickLabels(false);

  // set axes ranges, so we see all data:
  //customPlot->xAxis->setRange(0, 275);
  //customPlot->yAxis->setRange(0, 300);
  customPlot->axisRect(0)->setBackground(QBrush(QColor(43, 46, 63, 127)));

  QVBoxLayout* mainLayout = new QVBoxLayout;
  mainLayout->addWidget(rGLWindow);
  mainLayout->addWidget(customPlot);
  window->setLayout(mainLayout);

  QThread* thread = new QThread;
  Worker* worker = new Worker();
  worker->moveToThread(thread);

  QObject::connect(rGLWindow, SIGNAL(frameChanged()), worker, SLOT(process_next_frame()));
  QObject::connect(thread, SIGNAL(started()), worker, SLOT(process_next_frame()));

  // Connect Updates
  QObject::connect(worker, SIGNAL(updateGLView(QImage)), rGLWindow, SLOT(updateFrame(QImage)));
  qRegisterMetaType<dataVector>("dataVector");
  QObject::connect(worker, SIGNAL(updateData(dataVector,dataVector)), customPlot, SLOT(updateGraphData(dataVector,dataVector)) );
  QObject::connect(worker, SIGNAL(updateAddData(double,double)), customPlot, SLOT(addGraphData(double,double)) );
  
  thread->start();

  window->show();

  return app.exec();
}
