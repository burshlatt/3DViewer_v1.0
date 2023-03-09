#include "s21_3dViewer.h"

/*
            ФУНКЦИИ ДЛЯ QT
*/

/*
  make_v_arr_for_qt
  Что делает: создаёт одномерный массив координат для QT;
  Возвращаемое значение: одномерный массив координат.
*/
double *make_v_arr_for_qt(data_t *viewer_struct) {
  double *result = (double *)calloc(
      viewer_struct->matrix_3d.cols * (viewer_struct->matrix_3d.rows),
      sizeof(double));
  int count = 0;
  for (int i = 1; i < viewer_struct->matrix_3d.rows; i++) {
    for (int j = 0; j < 3; j++) {
      result[count++] = viewer_struct->matrix_3d.matrix[i][j];
    }
  }
  return result;
}

// double *make_f_arr_for_qt
int *make_f_arr_for_qt(data_t viewer_struct, int *count_of_facets) {
  *count_of_facets = 0;
  for (unsigned int i = 1; i < viewer_struct.count_of_facets + 1; i++)
    *count_of_facets += viewer_struct.polygons[i].numbers_of_vertexes_in_facets;
  int *result = (int *)calloc(*count_of_facets * 2, sizeof(int));
  *count_of_facets *= 2;
  int count = 0;
  for (unsigned int k = 1; k < viewer_struct.count_of_facets + 1; k++) {
    for (int i = 0; i < viewer_struct.polygons[k].numbers_of_vertexes_in_facets;
         i++) {
      result[count++] = viewer_struct.polygons[k]
                            .vertexes[i % viewer_struct.polygons[k]
                                              .numbers_of_vertexes_in_facets] -
                        1;
      result[count++] =
          viewer_struct.polygons[k]
              .vertexes[(i + 1) % viewer_struct.polygons[k]
                                      .numbers_of_vertexes_in_facets] -
          1;
    }
  }
  return result;
}

void get_coord(data_t viewer_struct, int *x, int *y) {
  for (int i = 0; i < viewer_struct.matrix_3d.rows; i++) {
    for (int j = 0; j < 3; j++) {
      if (fabs(viewer_struct.matrix_3d.matrix[i][0]) > *x) {
        *x = fabs(viewer_struct.matrix_3d.matrix[i][0]);
      }
      if (fabs(viewer_struct.matrix_3d.matrix[i][1]) > *y) {
        *y = fabs(viewer_struct.matrix_3d.matrix[i][1]);
      }
    }
  }
  *x += 1;
  *y += 1;
}
