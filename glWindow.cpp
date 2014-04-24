#include "glWindow.h"
#include <qgl.h>
#include <QDebug>
#include <QKeyEvent>
#include <GL/freeglut.h>

GLWindow::GLWindow(QWidget *parent) :
    QGLWidget(parent)
{
    connect(&timer,SIGNAL(timeout()),this,SLOT(updateGL()));
    timer.start(16);
}

void GLWindow::initializeGL()
{
  glClearColor(0.0,0.0,0.0,0.0);
}

void GLWindow::keyPressEvent(QKeyEvent *kEvent)
{
}

void GLWindow::updateFrame(QImage frame){
  //qDebug() << "Updating Frame";
  m_GLFrame = QGLWidget::convertToGLFormat(frame);
  this->updateGL();
}

void GLWindow::resizeGL(int w, int h){
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, w, h, 0, 0, 1);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void GLWindow::paintGL()
{
  glClear (GL_COLOR_BUFFER_BIT);
  glClearColor (0.0, 0.0, 0.0, 1.0);
  if (!m_GLFrame.isNull()) {
    m_GLFrame = m_GLFrame.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, m_GLFrame.width(), m_GLFrame.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, m_GLFrame.bits() );
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex2f(0, m_GLFrame.height());
    glTexCoord2f(0, 1); glVertex2f(0, 0);
    glTexCoord2f(1, 1); glVertex2f(m_GLFrame.width(), 0);
    glTexCoord2f(1, 0); glVertex2f(m_GLFrame.width(), m_GLFrame.height());
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glFlush();
    emit frameChanged();
  }
}
