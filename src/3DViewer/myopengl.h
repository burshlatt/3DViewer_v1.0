#ifndef MYOPENGL_H
#define MYOPENGL_H

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

#include <QOpenGLWidget>
#include <QWidget>
#include <QtOpenGL>

extern "C" {
#include "../CFiles/s21_3dViewer.h"
}

class MyOpenGL : public QOpenGLWidget {
  Q_OBJECT

 public:
  MyOpenGL(QWidget *parent = nullptr);

 private:
  int status = 1;

  void draw_object();
  void paintGL() override;
  void initializeGL() override;
  void resizeGL(int w, int h) override;

 public slots:
  void clear_mem();
  void zoom_reset();
  void line_type(int type);
  void ox_move(double value);
  void oy_move(double value);
  void oz_move(double value);
  void ox_rotate(double value);
  void oy_rotate(double value);
  void oz_rotate(double value);
  void line_width(double value);
  void projection_type(int type);
  void vertex_width(double value);
  void f_name_slot(char *file_name);
  void zoom_move(double x, double y, double z);
  void color_value(double r, double g, double b);
  void color_value_v(double r, double g, double b);
  void color_value_m(double r, double g, double b);

 signals:
  void vertex_facet(unsigned int, unsigned int);
};

#endif  // MYOPENGL_H
