#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QtOpenGL>

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

class MyOpenGL : public QOpenGLWidget {
    Q_OBJECT

public:
    MyOpenGL(QWidget *parent = nullptr);

public slots:
    void change_coord();

private:
    QTimer tmr;
    QPoint mPos;

    float xRot = 30, yRot = 0, zRot = 0;

    void draw_cube(float a);
    void mousePressEvent(QMouseEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;
};

#endif // MYOPENGL_H
