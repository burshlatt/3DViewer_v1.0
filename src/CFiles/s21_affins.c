#include "s21_3dViewer.h"

void move_x(matrix_t *A, double a) {
  for (int i = 0; i < A->rows; i++) A->matrix[i][0] += a;
}

void move_y(matrix_t *A, double a) {
  for (int i = 0; i < A->rows; i++) A->matrix[i][1] += a;
}

void move_z(matrix_t *A, double a) {
  for (int i = 0; i < A->rows; i++) A->matrix[i][2] += a;
}

void rotation_by_ox(matrix_t *A, double angle) {
  for (int i = 0; i < A->rows; i++) {
    double y_0 = A->matrix[i][1];
    double z_0 = A->matrix[i][2];
    A->matrix[i][1] = cos(angle) * y_0 - sin(angle) * z_0;
    A->matrix[i][2] = sin(angle) * y_0 + cos(angle) * z_0;
  }
}

void rotation_by_oy(matrix_t *A, double angle) {
  for (int i = 0; i < A->rows; i++) {
    double x_0 = A->matrix[i][0];
    double z_0 = A->matrix[i][2];
    A->matrix[i][0] = sin(angle) * z_0 + cos(angle) * x_0;
    A->matrix[i][2] = cos(angle) * z_0 - sin(angle) * x_0;
  }
}

void rotation_by_oz(matrix_t *A, double angle) {
  for (int i = 0; i < A->rows; i++) {
    double x_0 = A->matrix[i][0];
    double y_0 = A->matrix[i][1];
    A->matrix[i][0] = cos(angle) * x_0 - sin(angle) * y_0;
    A->matrix[i][1] = sin(angle) * x_0 + cos(angle) * y_0;
  }
}

void scale(matrix_t *A, double X, double Y, double Z) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][0] *= X;
    A->matrix[i][1] *= Y;
    A->matrix[i][2] *= Z;
  }
}

void scale_div(matrix_t *A, double X, double Y, double Z) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][0] /= X;
    A->matrix[i][1] /= Y;
    A->matrix[i][2] /= Z;
  }
}
