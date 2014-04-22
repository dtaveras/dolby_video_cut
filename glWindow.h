#ifndef GLWINDOW_H
#define GLWINDOW_H

#include <QImage>
#include <QtOpenGL/QGLWidget>
#include <GL/freeglut.h>
#include <QTimer>
#include <QObject>

class GLWindow : public QGLWidget
{
    Q_OBJECT
public:
    explicit GLWindow(QWidget *parent = 0);

 protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

public:
    void keyPressEvent(QKeyEvent* key);
    QTimer timer;    
    void drawCube();

private:
    QImage m_GLFrame;

signals:
    void frameChanged();
public slots:
    void updateFrame(QImage frame);
};

#endif
