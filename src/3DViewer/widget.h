#ifndef WIDGET_H
#define WIDGET_H

#include <stdlib.h>

#include <QAudioOutput>
#include <QDebug>
#include <QGuiApplication>
#include <QImage>
#include <QMediaPlayer>
#include <QPainter>
#include <QScreen>
#include <QSettings>
#include <QUrl>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QPushButton>

#include "../QtGifImage/src/gifimage/qgifimage.h"
#include "myopengl.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget {
  Q_OBJECT

 public:
  Widget(QWidget *parent = nullptr);
  ~Widget();

 signals:
  void clear_mem();
  void zoom_reset();
  void line_type(int);
  void ox_move(double);
  void oy_move(double);
  void oz_move(double);
  void ox_rotate(double);
  void oy_rotate(double);
  void oz_rotate(double);
  void line_width(double);
  void f_name_signal(char *);
  void projection_type(int);
  void vertex_width(double);
  void zoom_move(double, double, double);
  void color_value(double, double, double);
  void color_value_v(double, double, double);
  void color_value_m(double, double, double);

 private slots:
  int is_error(QString x, QString y, QString z);
  void save_settings();
  void load_settings();
  void on_scale_clicked();
  void on_rotate_clicked();
  void on_up_move_clicked();
  void on_stipple_clicked();
  void on_down_move_clicked();
  void on_left_move_clicked();
  void on_z_move_up_clicked();
  void on_right_move_clicked();
  void on_show_panel_clicked();
  void on_no_stipple_clicked();
  void on_width_plus_clicked();
  void on_screencast_clicked();
  void on_z_move_down_clicked();
  void on_reset_scale_clicked();
  void on_central_prj_clicked();
  void on_apply_color_clicked();
  void on_width_minus_clicked();
  void on_rotate_stop_clicked();
  void on_parallel_prj_clicked();
  void on_width_plus_v_clicked();
  void on_width_minus_v_clicked();
  void on_apply_color_m_clicked();
  void on_apply_color_v_clicked();
  void on_reset_settings_clicked();
  void set_name(QString f_name_qstr);

 private:
  Ui::Widget *ui;
  MyOpenGL *myogl;
  std::string name;
  QSettings *settings;
  QMediaPlayer *player;
  QAudioOutput *audioOutput;
  int i = 0;
  int is_obj = 0;
  int is_music = 0;
  double lines = 1;
  double ox_scale = 1;
  double oy_scale = 1;
  double oz_scale = 1;
  double r_facets = 1;
  double g_facets = 1;
  double b_facets = 1;
  double r_vertexes = 1;
  double g_vertexes = 1;
  double b_vertexes = 1;
  double projection = 1;
  double ox_num_move = 0;
  double oy_num_move = 0;
  double oz_num_move = 0;
  double r_background = 0;
  double g_background = 0;
  double b_background = 0;
  double width_facets = 0;
  double ox_num_rotate = 0;
  double oy_num_rotate = 0;
  double oz_num_rotate = 0;
  double width_vertexes = 0;

 public slots:
  void on_openFile_clicked();
  void vertex_facet(unsigned int ver, unsigned int fac);
};

#endif  // WIDGET_H
