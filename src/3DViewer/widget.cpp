#include "widget.h"

#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
  ui->setupUi(this);

  setWindowTitle("3DViewer_v1.0 (by Stephank)");
  QScreen *screen = QGuiApplication::primaryScreen();
  QRect screenGeometry = screen->geometry();
  int x = (screenGeometry.width() - 1400) / 2;
  int y = (screenGeometry.height() - 600) / 2;
  move(x, y);
  this->setFixedSize(1150, 600);

  myogl = new MyOpenGL;

  connect(this, &Widget::ox_move, myogl, &MyOpenGL::ox_move);
  connect(this, &Widget::oy_move, myogl, &MyOpenGL::oy_move);
  connect(this, &Widget::oz_move, myogl, &MyOpenGL::oz_move);
  connect(this, &Widget::ox_rotate, myogl, &MyOpenGL::ox_rotate);
  connect(this, &Widget::oy_rotate, myogl, &MyOpenGL::oy_rotate);
  connect(this, &Widget::oz_rotate, myogl, &MyOpenGL::oz_rotate);
  connect(this, &Widget::zoom_move, myogl, &MyOpenGL::zoom_move);
  connect(this, &Widget::line_type, myogl, &MyOpenGL::line_type);
  connect(this, &Widget::clear_mem, myogl, &MyOpenGL::clear_mem);
  connect(this, &Widget::line_width, myogl, &MyOpenGL::line_width);
  connect(this, &Widget::zoom_reset, myogl, &MyOpenGL::zoom_reset);
  connect(this, &Widget::color_value, myogl, &MyOpenGL::color_value);
  connect(this, &Widget::f_name_signal, myogl, &MyOpenGL::f_name_slot);
  connect(this, &Widget::vertex_width, myogl, &MyOpenGL::vertex_width);
  connect(this, &Widget::color_value_m, myogl, &MyOpenGL::color_value_m);
  connect(this, &Widget::color_value_v, myogl, &MyOpenGL::color_value_v);
  connect(this, &Widget::projection_type, myogl, &MyOpenGL::projection_type);

  connect(myogl, &MyOpenGL::vertex_facet, this, &Widget::vertex_facet);

  settings = new QSettings("settings.config", "settings");
  if (settings->value("Saved").toInt() == 1) {
    load_settings();
  }
  save_settings();
}

Widget::~Widget() {
  if (is_obj) {
    emit clear_mem();
  }
  if (is_music) {
    delete audioOutput;
    delete player;
  }
  delete settings;
  delete myogl;
  delete ui;
}

QGifImage gif(QSize(640, 480));

void Widget::save_settings() {
  settings->setValue("File_path", QString::fromStdString(name));
  settings->setValue("Is_obj", is_obj);
  settings->setValue("Rotate_X", ox_num_rotate);
  settings->setValue("Rotate_Y", oy_num_rotate);
  settings->setValue("Rotate_Z", oz_num_rotate);
  settings->setValue("Move_X", ox_num_move);
  settings->setValue("Move_Y", oy_num_move);
  settings->setValue("Move_Z", oz_num_move);
  settings->setValue("Scale_X", ox_scale);
  settings->setValue("Scale_Y", oy_scale);
  settings->setValue("Scale_Z", oz_scale);
  settings->setValue("Projection", projection);
  settings->setValue("Lines", lines);
  settings->setValue("Facets_R", r_facets);
  settings->setValue("Facets_G", g_facets);
  settings->setValue("Facets_B", b_facets);
  settings->setValue("Facets_width", width_facets);
  settings->setValue("Vertexes_R", r_vertexes);
  settings->setValue("Vertexes_G", g_vertexes);
  settings->setValue("Vertexes_B", b_vertexes);
  settings->setValue("Vertexes_width", width_vertexes);
  settings->setValue("Background_R", r_background);
  settings->setValue("Background_G", g_background);
  settings->setValue("Background_B", b_background);
  settings->setValue("Saved", 1);
}

void Widget::load_settings() {
  is_obj = settings->value("Is_obj").toInt();

  name = settings->value("File_path").toString().toStdString();
  char *f_name = &name[0];
  set_name(settings->value("File_path").toString());
  emit f_name_signal(f_name);

  ox_num_rotate = settings->value("Rotate_X").toDouble();
  ui->ox_line->setText(settings->value("Rotate_X").toString());
  emit ox_rotate(ox_num_rotate);

  oy_num_rotate = settings->value("Rotate_Y").toDouble();
  ui->oy_line->setText(settings->value("Rotate_Y").toString());
  emit oy_rotate(oy_num_rotate);

  oz_num_rotate = settings->value("Rotate_Z").toDouble();
  ui->oz_line->setText(settings->value("Rotate_Z").toString());
  emit oz_rotate(oz_num_rotate);

  ox_num_move = settings->value("Move_X").toDouble();
  emit ox_move(ox_num_move);

  oy_num_move = settings->value("Move_Y").toDouble();
  emit oy_move(oy_num_move);

  oz_num_move = settings->value("Move_Z").toDouble();
  emit oz_move(oz_num_move);

  ox_scale = settings->value("Scale_X").toDouble();
  ui->scale_x->setText(settings->value("Scale_X").toString());
  oy_scale = settings->value("Scale_Y").toDouble();
  ui->scale_y->setText(settings->value("Scale_Y").toString());
  oz_scale = settings->value("Scale_Z").toDouble();
  ;
  ui->scale_z->setText(settings->value("Scale_Z").toString());
  emit zoom_move(ox_scale, oy_scale, oz_scale);

  projection = settings->value("Projection").toInt();
  emit projection_type(projection);

  lines = settings->value("Lines").toInt();
  emit line_type(lines);

  r_facets = settings->value("Facets_R").toDouble();
  ui->color_r->setText(settings->value("Facets_R").toString());
  g_facets = settings->value("Facets_G").toDouble();
  ui->color_g->setText(settings->value("Facets_G").toString());
  b_facets = settings->value("Facets_B").toDouble();
  ui->color_b->setText(settings->value("Facets_B").toString());
  emit color_value(r_facets, g_facets, b_facets);

  width_facets = settings->value("Facets_width").toDouble();
  emit line_width(width_facets);

  r_vertexes = settings->value("Vertexes_R").toDouble();
  ui->color_r_v->setText(settings->value("Vertexes_R").toString());
  g_vertexes = settings->value("Vertexes_G").toDouble();
  ui->color_g_v->setText(settings->value("Vertexes_G").toString());
  b_vertexes = settings->value("Vertexes_B").toDouble();
  ui->color_b_v->setText(settings->value("Vertexes_B").toString());
  emit color_value_v(r_vertexes, g_vertexes, b_vertexes);

  width_vertexes = settings->value("Vertexes_width").toDouble();
  emit vertex_width(width_vertexes);

  r_background = settings->value("Background_R").toDouble();
  ui->color_r_m->setText(settings->value("Background_R").toString());
  g_background = settings->value("Background_G").toDouble();
  ui->color_g_m->setText(settings->value("Background_G").toString());
  b_background = settings->value("Background_B").toDouble();
  ui->color_b_m->setText(settings->value("Background_B").toString());
  emit color_value_m(r_background, g_background, b_background);
}

void Widget::on_reset_settings_clicked() {
  ox_num_rotate = 0;
  oy_num_rotate = 0;
  oz_num_rotate = 0;
  ox_num_move = 0;
  oy_num_move = 0;
  oz_num_move = 0;
  ox_scale = 1;
  oy_scale = 1;
  oz_scale = 1;
  projection = 1;
  lines = 1;
  r_facets = 1;
  g_facets = 1;
  b_facets = 1;
  width_facets = 0;
  r_vertexes = 1;
  g_vertexes = 1;
  b_vertexes = 1;
  width_vertexes = 0;
  r_background = 0;
  g_background = 0;
  b_background = 0;
  on_rotate_stop_clicked();
  on_reset_scale_clicked();
  save_settings();
  load_settings();
}

void Widget::on_openFile_clicked() {
  QString f_name_qstr = QFileDialog::getOpenFileName(
      nullptr, "Открыть файл", QString(), "Объектный файлы (*.obj)");
  if (f_name_qstr != "") {
    std::string f_name_str = f_name_qstr.toStdString();
    name = f_name_str;
    char *f_name = &f_name_str[0];
    ui->file_name->setText(f_name_qstr);
    set_name(f_name_qstr);
    is_obj = 1;
    save_settings();
    emit f_name_signal(f_name);
  }
}

void Widget::set_name(QString f_name_qstr) {
  for (int i = 0; i < f_name_qstr.size(); i++) {
    if (f_name_qstr[i] == '/') {
      ui->file_name->clear();
    } else {
      ui->file_name->setText(ui->file_name->text() + f_name_qstr[i]);
    }
  }
}

void Widget::vertex_facet(unsigned int ver, unsigned int fac) {
  ui->vertexes->setText(QString::number(ver));
  ui->facets->setText(QString::number(fac));
}

void Widget::on_rotate_clicked() {
  QString x = ui->ox_line->text();
  QString y = ui->oy_line->text();
  QString z = ui->oz_line->text();
  int error = is_error(x, y, z);
  if (!error && is_obj) {
    QPixmap pixmap(ui->widget->size());
    ox_num_rotate = ui->ox_line->text().toDouble();
    oy_num_rotate = ui->oy_line->text().toDouble();
    oz_num_rotate = ui->oz_line->text().toDouble();

    save_settings();

    emit ox_rotate(ui->ox_line->text().toDouble());
    emit oy_rotate(ui->oy_line->text().toDouble());
    emit oz_rotate(ui->oz_line->text().toDouble());

    ui->widget->render(&pixmap, QPoint(), QRegion());
    gif.insertFrame(i, pixmap.toImage());
    i++;

    player = new QMediaPlayer;
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->setSource(QUrl::fromLocalFile("../../../../Music/space_music.mp3"));
    player->play();
    player->setSource(QUrl::fromLocalFile("../Resources/space_music.mp3"));
    player->play();
    is_music = 1;
  } else {
    if (error == 1) {
      ui->ox_line->setText("ERROR!");
    } else if (error == 2) {
      ui->oy_line->setText("ERROR!");
    } else if (error == 3) {
      ui->oz_line->setText("ERROR!");
    }
  }
}

int Widget::is_error(QString x, QString y, QString z) {
  int error = 0;
  if (is_obj) {
    for (int i = 0; i < x.size() && !error; i++) {
      if ((x[i] < '0' || x[i] > '9') && x[i] != '.' && x[i] != '-') {
        error = 1;
      }
    }
    for (int i = 0; i < y.size() && !error; i++) {
      if ((y[i] < '0' || y[i] > '9') && y[i] != '.' && y[i] != '-') {
        error = 2;
      }
    }
    for (int i = 0; i < z.size() && !error; i++) {
      if ((z[i] < '0' || z[i] > '9') && z[i] != '.' && z[i] != '-') {
        error = 3;
      }
    }
  }
  return error;
}

void Widget::on_rotate_stop_clicked() {
  ui->ox_line->setText("0");
  ox_num_rotate = 0;
  ui->oy_line->setText("0");
  oy_num_rotate = 0;
  ui->oz_line->setText("0");
  oz_num_rotate = 0;
  save_settings();
  emit ox_rotate(0);
  emit oy_rotate(0);
  emit oz_rotate(0);
  if (is_music) {
    player->stop();
  }
}

void Widget::on_up_move_clicked() {
  if (is_obj) {
    QPixmap pixmap(ui->widget->size());
    oy_num_move += 0.1;
    save_settings();
    emit oy_move(0.1);
    ui->widget->render(&pixmap, QPoint(), QRegion());
    gif.insertFrame(i, pixmap.toImage());
    i++;
  }
}

void Widget::on_down_move_clicked() {
  if (is_obj) {
    QPixmap pixmap(ui->widget->size());
    oy_num_move -= 0.1;
    save_settings();
    emit oy_move(-0.1);
    ui->widget->render(&pixmap, QPoint(), QRegion());
    gif.insertFrame(i, pixmap.toImage());
    i++;
  }
}

void Widget::on_left_move_clicked() {
  if (is_obj) {
    QPixmap pixmap(ui->widget->size());
    ox_num_move -= 0.1;
    save_settings();
    emit ox_move(-0.1);
    ui->widget->render(&pixmap, QPoint(), QRegion());
    gif.insertFrame(i, pixmap.toImage());
    i++;
  }
}

void Widget::on_right_move_clicked() {
  if (is_obj) {
    QPixmap pixmap(ui->widget->size());
    ox_num_move += 0.1;
    save_settings();
    emit ox_move(0.1);
    ui->widget->render(&pixmap, QPoint(), QRegion());
    gif.insertFrame(i, pixmap.toImage());
    i++;
  }
}

void Widget::on_z_move_up_clicked() {
  if (is_obj) {
    QPixmap pixmap(ui->widget->size());
    oz_num_move += 0.1;
    save_settings();
    emit oz_move(0.1);
    ui->widget->render(&pixmap, QPoint(), QRegion());
    gif.insertFrame(i, pixmap.toImage());
    i++;
  }
}

void Widget::on_z_move_down_clicked() {
  if (is_obj) {
    QPixmap pixmap(ui->widget->size());
    oz_num_move -= 0.1;
    save_settings();
    emit oz_move(-0.1);
    ui->widget->render(&pixmap, QPoint(), QRegion());
    gif.insertFrame(i, pixmap.toImage());
    i++;
  }
}

void Widget::on_scale_clicked() {
  if (is_obj) {
    QString x = ui->scale_x->text();
    QString y = ui->scale_y->text();
    QString z = ui->scale_z->text();
    int error = is_error(x, y, z);
    if (!error && x.toDouble() && y.toDouble() && z.toDouble()) {
      QPixmap pixmap(ui->widget->size());
      ox_scale = x.toDouble();
      oy_scale = y.toDouble();
      oz_scale = z.toDouble();
      save_settings();
      emit zoom_move(ox_scale, oy_scale, oz_scale);
      ui->widget->render(&pixmap, QPoint(), QRegion());
      gif.insertFrame(i, pixmap.toImage());
      i++;
    } else {
      if (error == 1) {
        ui->scale_x->setText("ERROR!");
      } else if (error == 2) {
        ui->scale_y->setText("ERROR!");
      } else if (error == 3) {
        ui->scale_z->setText("ERROR!");
      }
    }
  }
}

void Widget::on_reset_scale_clicked() {
  QPixmap pixmap(ui->widget->size());
  ox_scale = 1;
  oy_scale = 1;
  oz_scale = 1;
  save_settings();
  ui->scale_x->setText("1");
  ui->scale_y->setText("1");
  ui->scale_z->setText("1");
  emit zoom_reset();
  ui->widget->render(&pixmap, QPoint(), QRegion());
  gif.insertFrame(i, pixmap.toImage());
  i++;
}

void Widget::on_show_panel_clicked() {
  if (ui->show_panel->text() == '>') {
    this->setFixedSize(1400, 600);
    ui->show_panel->setText("<");
  } else {
    this->setFixedSize(1150, 600);
    ui->show_panel->setText(">");
  }
}

void Widget::on_parallel_prj_clicked() {
  if (is_obj) {
    projection = 1;
    save_settings();
    emit projection_type(1);
  }
}

void Widget::on_central_prj_clicked() {
  if (is_obj) {
    projection = 2;
    save_settings();
    emit projection_type(2);
  }
}

void Widget::on_no_stipple_clicked() {
  if (is_obj) {
    lines = 1;
    save_settings();
    emit line_type(1);
  }
}

void Widget::on_stipple_clicked() {
  if (is_obj) {
    lines = 2;
    save_settings();
    emit line_type(2);
  }
}

void Widget::on_apply_color_clicked() {
  QString r = ui->color_r->text();
  QString g = ui->color_g->text();
  QString b = ui->color_b->text();
  int error = is_error(r, g, b);
  if (is_obj && !error) {
    double r = ui->color_r->text().toDouble();
    double g = ui->color_g->text().toDouble();
    double b = ui->color_b->text().toDouble();
    r_facets = r;
    g_facets = g;
    b_facets = b;
    save_settings();
    emit color_value(r, g, b);
  } else {
    if (error == 1) {
      ui->color_r->setText("ERROR!");
    } else if (error == 2) {
      ui->color_g->setText("ERROR!");
    } else if (error == 3) {
      ui->color_b->setText("ERROR!");
    }
  }
}

void Widget::on_width_plus_clicked() {
  if (is_obj) {
    width_facets += 0.5;
    save_settings();
    emit line_width(0.5);
  }
}

void Widget::on_width_minus_clicked() {
  if (width_facets >= 0 && is_obj) {
    width_facets -= 0.5;
    save_settings();
    emit line_width(-0.5);
  }
}

void Widget::on_apply_color_v_clicked() {
  QString r = ui->color_r_v->text();
  QString g = ui->color_g_v->text();
  QString b = ui->color_b_v->text();
  int error = is_error(r, g, b);
  if (is_obj && !error) {
    double r = ui->color_r_v->text().toDouble();
    double g = ui->color_g_v->text().toDouble();
    double b = ui->color_b_v->text().toDouble();
    r_vertexes = r;
    g_vertexes = g;
    b_vertexes = b;
    save_settings();
    emit color_value_v(r, g, b);
  } else {
    if (error == 1) {
      ui->color_r_v->setText("ERROR!");
    } else if (error == 2) {
      ui->color_g_v->setText("ERROR!");
    } else if (error == 3) {
      ui->color_b_v->setText("ERROR!");
    }
  }
}

void Widget::on_width_plus_v_clicked() {
  if (is_obj) {
    width_vertexes += 0.5;
    save_settings();
    emit vertex_width(0.5);
  }
}

void Widget::on_width_minus_v_clicked() {
  if (width_vertexes >= 0 && is_obj) {
    width_vertexes -= 0.5;
    save_settings();
    emit vertex_width(-0.5);
  }
}

void Widget::on_apply_color_m_clicked() {
  QString r = ui->color_r_m->text();
  QString g = ui->color_g_m->text();
  QString b = ui->color_b_m->text();
  int error = is_error(r, g, b);
  if (!error) {
    double r = ui->color_r_m->text().toDouble();
    double g = ui->color_g_m->text().toDouble();
    double b = ui->color_b_m->text().toDouble();
    r_background = r;
    g_background = g;
    b_background = b;
    save_settings();
    emit color_value_m(r, g, b);
  } else {
    if (error == 1) {
      ui->color_r_m->setText("ERROR!");
    } else if (error == 2) {
      ui->color_g_m->setText("ERROR!");
    } else if (error == 3) {
      ui->color_b_m->setText("ERROR!");
    }
  }
}

void Widget::on_screencast_clicked() {
  QVector<QRgb> ctable;
  ctable << qRgb(255, 255, 255) << qRgb(0, 0, 0) << qRgb(255, 0, 0)
         << qRgb(0, 255, 0) << qRgb(0, 0, 255) << qRgb(255, 255, 0)
         << qRgb(0, 255, 255) << qRgb(255, 0, 255);

  gif.setDefaultDelay(100);

  QPixmap pixmap(ui->widget->size());
  ui->widget->render(&pixmap, QPoint(), QRegion());

  gif.addFrame(pixmap.toImage());

  QString way_file_gif = QFileDialog::getSaveFileName(
      this, "Загрузить файл", "/Users/burshlat/Desktop",
      "BMP Image (*.bmp);; JPEG Image (*.jpeg);; GIF(*.gif)");
  gif.save(way_file_gif);
}
