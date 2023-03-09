#include "myopengl.h"

MyOpenGL::MyOpenGL(QWidget *parent) : QOpenGLWidget(parent) {}

int count = 0;
data_t viewer_struct;
int *facets_array = NULL;
double *vertex_array = NULL;

int x_prj = 0;
int y_prj = 0;

int l_type = 1;

double zoom_x = 1;
double zoom_y = 1;
double zoom_z = 1;

double red_l = 1;
double blue_l = 1;
double green_l = 1;
double width_l = 1;

double red_v = 1;
double blue_v = 1;
double green_v = 1;
double width_v = 1;

int projection = 1;

double red_main = 0;
double blue_main = 0;
double green_main = 0;

double rotate_ox_value = 0;
double rotate_oy_value = 0;
double rotate_oz_value = 0;

void MyOpenGL::f_name_slot(char *file_name) {
  init_struct(&viewer_struct);
  rotate_ox_value = 0;
  rotate_oy_value = 0;
  rotate_oz_value = 0;
  zoom_x = 1;
  zoom_y = 1;
  zoom_z = 1;
  status = s21_viewer(file_name, &viewer_struct);
  vertex_array = make_v_arr_for_qt(&viewer_struct);
  facets_array = make_f_arr_for_qt(viewer_struct, &count);
  emit vertex_facet(viewer_struct.count_of_vertexes,
                    viewer_struct.count_of_facets);
  x_prj = 0;
  y_prj = 0;
  get_coord(viewer_struct, &x_prj, &y_prj);
}

void MyOpenGL::clear_mem() {
  if (status == ERROR_FALSE) {
    free(vertex_array);
    free(facets_array);
    destoy_all(&viewer_struct);
  }
}

void MyOpenGL::ox_rotate(double value) {
  rotate_ox_value = value;
  rotation_by_ox(&viewer_struct.matrix_3d, value);
  free(vertex_array);
  vertex_array = make_v_arr_for_qt(&viewer_struct);
  update();
}

void MyOpenGL::oy_rotate(double value) {
  rotate_oy_value = value;
  rotation_by_oy(&viewer_struct.matrix_3d, value);
  free(vertex_array);
  vertex_array = make_v_arr_for_qt(&viewer_struct);
  update();
}

void MyOpenGL::oz_rotate(double value) {
  rotate_oz_value = value;
  rotation_by_oz(&viewer_struct.matrix_3d, value);
  free(vertex_array);
  vertex_array = make_v_arr_for_qt(&viewer_struct);
  update();
}

void MyOpenGL::ox_move(double value) {
  move_x(&viewer_struct.matrix_3d, value);
  free(vertex_array);
  vertex_array = make_v_arr_for_qt(&viewer_struct);
  update();
}

void MyOpenGL::oy_move(double value) {
  move_y(&viewer_struct.matrix_3d, value);
  free(vertex_array);
  vertex_array = make_v_arr_for_qt(&viewer_struct);
  update();
}

void MyOpenGL::oz_move(double value) {
  move_z(&viewer_struct.matrix_3d, value);
  free(vertex_array);
  vertex_array = make_v_arr_for_qt(&viewer_struct);
  update();
}

void MyOpenGL::zoom_move(double x, double y, double z) {
  scale_div(&viewer_struct.matrix_3d, zoom_x, zoom_y, zoom_z);
  zoom_x = x;
  zoom_y = y;
  zoom_z = z;
  scale(&viewer_struct.matrix_3d, x, y, z);
  free(vertex_array);
  vertex_array = make_v_arr_for_qt(&viewer_struct);
  update();
}

void MyOpenGL::zoom_reset() {
  scale_div(&viewer_struct.matrix_3d, zoom_x, zoom_y, zoom_z);
  zoom_x = 1;
  zoom_y = 1;
  zoom_z = 1;
  free(vertex_array);
  vertex_array = make_v_arr_for_qt(&viewer_struct);
  update();
}

void MyOpenGL::projection_type(int type) { projection = type; }

void MyOpenGL::line_type(int type) { l_type = type; }

void MyOpenGL::color_value(double r, double g, double b) {
  red_l = r;
  green_l = g;
  blue_l = b;
}

void MyOpenGL::line_width(double value) { width_l += value; }

void MyOpenGL::color_value_v(double r, double g, double b) {
  red_v = r;
  green_v = g;
  blue_v = b;
}

void MyOpenGL::vertex_width(double value) { width_v += value; }

void MyOpenGL::color_value_m(double r, double g, double b) {
  red_main = r;
  green_main = g;
  blue_main = b;
}

void MyOpenGL::initializeGL() { glEnable(GL_DEPTH_TEST); }

void MyOpenGL::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void MyOpenGL::paintGL() {
  glClearColor(red_main, green_main, blue_main, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (projection == 1) {
    glOrtho(-x_prj, x_prj, -y_prj, y_prj, -100, 100);
  } else {
    float fov = 60.0 * M_PI / 180;
    float heap_height = y_prj / (2 * tan(fov / 2));
    glFrustum(-x_prj, x_prj, -y_prj, y_prj, heap_height, 100);
    glTranslated(0, 0, -heap_height * 3);
  }
  ox_rotate(rotate_ox_value);
  oy_rotate(rotate_oy_value);
  oz_rotate(rotate_oz_value);
  draw_object();
}

void MyOpenGL::draw_object() {
  glVertexPointer(3, GL_DOUBLE, 0, vertex_array);
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnable(GL_POINT_SMOOTH);
  glPointSize(width_v);
  glColor3d(red_v, green_v, blue_v);
  glDrawArrays(GL_POINTS, 0, viewer_struct.count_of_vertexes);
  glLineWidth(width_l);
  glColor3d(red_l, green_l, blue_l);
  if (l_type == 2) {
    glLineStipple(5, 0x3333);
    glEnable(GL_LINE_STIPPLE);
  }
  glDrawElements(GL_LINES, count, GL_UNSIGNED_INT, facets_array);
  glDisableClientState(GL_VERTEX_ARRAY);
  glDisable(GL_POINT_SMOOTH);
  if (l_type == 2) {
    glDisable(GL_LINE_STIPPLE);
  }
}
