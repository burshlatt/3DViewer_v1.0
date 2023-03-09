#include <check.h>

#include "../CFiles/s21_3dViewer.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res_code = 0;
  if (rows > 0 && columns > 0) {
    res_code = 1;
    result->rows = rows;
    result->cols = columns;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
  }
  return res_code;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res_code = 1;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->cols; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.000001) {
        res_code = 0;
        break;
      }
    }
    if (res_code == 0) break;
  }
  return res_code;
}

START_TEST(download_test) {
  int status = 0;

  // test 1
  data_t viewer_struct = {0};
  init_struct(&viewer_struct);
  char file_name_1[50] = "../obj_files/obj_file_1.obj";
  status = s21_viewer(file_name_1, &viewer_struct);

  ck_assert_int_eq(status, ERROR_FALSE);

  ck_assert_uint_eq(viewer_struct.count_of_vertexes, 310);
  ck_assert_uint_eq(viewer_struct.count_of_facets, 393);

  ck_assert_int_eq(viewer_struct.matrix_3d.cols, 3);
  ck_assert_int_eq(viewer_struct.matrix_3d.rows, 311);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[1][0], 3.070224);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[21][1], -0.958092);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[310][2], 0.569242);

  ck_assert_int_eq(viewer_struct.polygons[6].numbers_of_vertexes_in_facets, 4);
  ck_assert_int_eq(viewer_struct.polygons[6].vertexes[0], 87);
  ck_assert_int_eq(viewer_struct.polygons[6].vertexes[1], 33);
  ck_assert_int_eq(viewer_struct.polygons[6].vertexes[2], 88);
  ck_assert_int_eq(viewer_struct.polygons[6].vertexes[3], 78);

  destoy_all(&viewer_struct);

  // test 2
  init_struct(&viewer_struct);
  char file_name_2[50] = "no_file.obj";
  status = s21_viewer(file_name_2, &viewer_struct);

  ck_assert_int_eq(status, ERROR_TRUE);

  // destoy_all(&viewer_struct);

  // test 3
  init_struct(&viewer_struct);
  char file_name_3[50] = "../test/test_1.obj";
  status = s21_viewer(file_name_3, &viewer_struct);

  ck_assert_int_eq(status, ERROR_FALSE);

  ck_assert_uint_eq(viewer_struct.count_of_vertexes, 3);
  ck_assert_uint_eq(viewer_struct.count_of_facets, 2);

  ck_assert_int_eq(viewer_struct.matrix_3d.cols, 3);
  ck_assert_int_eq(viewer_struct.matrix_3d.rows, 4);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[1][0], 1);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[1][1], 2);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[1][2], 3);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[2][0], -5);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[2][1], 4.4);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[2][2], 1);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[3][0], 0);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[3][1], -0.0005);
  ck_assert_double_eq(viewer_struct.matrix_3d.matrix[3][2], 0.156);

  ck_assert_double_eq(viewer_struct.polygons[1].numbers_of_vertexes_in_facets,
                      3);
  ck_assert_double_eq(viewer_struct.polygons[1].vertexes[0], 1);
  ck_assert_double_eq(viewer_struct.polygons[1].vertexes[1], 2);
  ck_assert_double_eq(viewer_struct.polygons[1].vertexes[2], 3);
  ck_assert_double_eq(viewer_struct.polygons[2].numbers_of_vertexes_in_facets,
                      5);
  ck_assert_double_eq(viewer_struct.polygons[2].vertexes[0], 2);
  ck_assert_double_eq(viewer_struct.polygons[2].vertexes[1], 3);
  ck_assert_double_eq(viewer_struct.polygons[2].vertexes[2], 1);
  ck_assert_double_eq(viewer_struct.polygons[2].vertexes[3], 1);
  ck_assert_double_eq(viewer_struct.polygons[2].vertexes[4], 4);

  destoy_all(&viewer_struct);
}

START_TEST(move_test) {
  double X = 2.5;
  double Y = -1;
  double Z = 100;
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double result[3][3] = {{3.5, 1, 103}, {2.5, 3, 102}, {7.5, 1, 101}};
  matrix_t A, res;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &res);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      A.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      res.matrix[i][j] = result[i][j];
    }
  }
  move_x(&A, X);
  move_y(&A, Y);
  move_z(&A, Z);
  int ret = s21_eq_matrix(&A, &res);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(rotate_test) {
  double X = M_PI / 2;
  double Y = -M_PI;
  double Z = 2 * M_PI;
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double result[3][3] = {{-1, -3, -2}, {0, -2, -4}, {-5, -1, -2}};
  matrix_t A, res;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &res);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      A.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      res.matrix[i][j] = result[i][j];
    }
  }
  rotation_by_ox(&A, X);
  rotation_by_oy(&A, Y);
  rotation_by_oz(&A, Z);
  int ret = s21_eq_matrix(&A, &res);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(scale_test) {
  double X = 2;
  double Y = 0.5;
  double Z = 10;
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double result[3][3] = {{2, 1, 30}, {0, 2, 20}, {10, 1, 10}};
  matrix_t A, res;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &res);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      A.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      res.matrix[i][j] = result[i][j];
    }
  }
  scale(&A, X, Y, Z);
  int ret = s21_eq_matrix(&A, &res);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(scale_div_test) {
  double X = 2;
  double Y = 0.5;
  double Z = 10;
  double m[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};
  double result[3][3] = {{0.5, 4, 0.3}, {0, 8, 0.2}, {2.5, 4, 0.1}};
  matrix_t A, res;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &res);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      A.matrix[i][j] = m[i][j];
    }
  }
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.cols; j++) {
      res.matrix[i][j] = result[i][j];
    }
  }
  scale_div(&A, X, Y, Z);
  int ret = s21_eq_matrix(&A, &res);
  ck_assert_int_eq(ret, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&res);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  int failed = 0;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, download_test);
  tcase_add_test(tc1_1, move_test);
  tcase_add_test(tc1_1, rotate_test);
  tcase_add_test(tc1_1, scale_test);
  tcase_add_test(tc1_1, scale_div_test);

  srunner_run_all(sr, CK_ENV);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}
