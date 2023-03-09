#ifndef VIEWER_3D_H
#define VIEWER_3D_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LENGTH 500

#define ERROR_FALSE 0
#define ERROR_TRUE 1

typedef struct Matrix {
  double **matrix;
  int rows;
  int cols;
} matrix_t;

typedef struct facets {
  int *vertexes;
  int numbers_of_vertexes_in_facets;
} polygon_t;

typedef struct data_t {
  unsigned int count_of_vertexes;
  unsigned int count_of_facets;
  matrix_t matrix_3d;
  polygon_t *polygons;
} data_t;

int get_facets_count(char *str);
int check_obj(char *file_name, data_t *viewer_struct);
int s21_viewer(char *file_name, data_t *viewer_struct);
int *make_f_arr_for_qt(data_t viewer_struct, int *count_of_facets);

double *make_v_arr_for_qt(data_t *viewer_struct);

void move_x(matrix_t *A, double a);
void move_y(matrix_t *A, double a);
void move_z(matrix_t *A, double a);
void destoy_all(data_t *viewer_struct);
void init_struct(data_t *viewer_struct);
void make_matrix(data_t *viewer_struct);
void destroy_matrix(data_t *viewer_struct);
void make_facets_arr(data_t *viewer_struct);
void destroy_facets_arr(data_t *viewer_struct);
void rotation_by_ox(matrix_t *A, double angle);
void rotation_by_oy(matrix_t *A, double angle);
void rotation_by_oz(matrix_t *A, double angle);
void add_facets_to_arr(polygon_t *facet, char *str);
void get_coord(data_t viewer_struct, int *x, int *y);
void scale(matrix_t *A, double X, double Y, double Z);
void scale_div(matrix_t *A, double X, double Y, double Z);

#endif  // VIEWER_3D_H
