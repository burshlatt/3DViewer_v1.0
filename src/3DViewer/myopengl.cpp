#include "myopengl.h"

MyOpenGL::MyOpenGL(QWidget *parent) : QOpenGLWidget(parent) {
    connect(&tmr, SIGNAL(timeout()), this, SLOT(change_coord()));
    tmr.start(100);
}

void MyOpenGL::initializeGL() { // Инициализация окна
    glEnable(GL_DEPTH_TEST);
}

void MyOpenGL::resizeGL(int w, int h) { // Изменение размеров окна (x, y - координаты левого верхнего угла окна (первые 2 значения), w и h - ширина и высота окна)
    glViewport(0, 0, w, h); // Область видимости нашего окна
    glMatrixMode(GL_PROJECTION); // Используем 1 из 3 основных матриц (GL_PROJECTION - ортагональная проекция)
    glLoadIdentity(); // Загружаем в стек единичную матрицу (все матрицы от -1 до 1 по дефолту)
    glFrustum(-1, 1, -1, 1, 1, 3);
}

void MyOpenGL::paintGL() { // Отрисовка окна
    glClearColor(0, 0, 0, 0); // Изменение цвета фона окна (r, g, b, параметр прозрачности)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Очистка буфера цвета
    glMatrixMode(GL_MODELVIEW); // Используем 1 из 3 основных матриц (GL_MODELVIEW - видовая матрица)
    glLoadIdentity(); // Загружаем в стек единичную матрицу (все матрицы от -1 до 1 по дефолту)

    glTranslatef(0, 0, -2);
    glRotatef(xRot, 1, 0, 0); // Поворот системы координа на какой то угол (градусы, x, y, z)
    glRotatef(yRot, 0, 1, 0); // Поворот системы координа на какой то угол (градусы, x, y, z)
    glRotatef(zRot, 0, 0, 1); // Поворот системы координа на какой то угол (градусы, x, y, z)
    draw_cube(0.5); // Функция отрисовки куба
}

void MyOpenGL::mousePressEvent(QMouseEvent* mo) {
    mPos = mo->pos();
}

void MyOpenGL::mouseMoveEvent(QMouseEvent* mo) {
    xRot = 1 / M_PI * (mo->pos().y() - mo->pos().y());
    yRot = 1 / M_PI * (mo->pos().x() - mo->pos().x());
    update();
}

void MyOpenGL::change_coord() {
    xRot += 0.01;
    update();
}

void MyOpenGL::draw_cube(float a) {
    float vertex_cube[] = {
        -a, -a, a,     a, -a, a,     a, a, a,    -a, a, a,
        a, -a, -a,    -a, -a, -a,   -a, a, -a,    a, a, -a,
        -a, -a, -a,   -a, -a, -a,   -a, a, a,    -a, a, -a,
        a, -a, a,      a, -a, -a,    a, a, -a,    a, a, a,
        -a, -a, a,     a, -a, a,     a, -a, -a,   -a, -a, -a,
        -a, a, a,      a, a, a,      a, a, -a,    -a, a, -a
    };
    float color_array[] = {
        1, 1, 0,        1, 1, 0,        1, 1, 0,        1, 1, 0,
        0, 0, 1,        0, 0, 1,        0, 0, 1,        0, 0, 1,
        1, 1, 0,        1, 1, 0,        1, 1, 0,        1, 1, 0,
        0, 1, 1,        0, 1, 1,        0, 1, 1,        0, 1, 1,
        1, 0, 1,        1, 0, 1,        1, 0, 1,        1, 0, 1,
        1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5,    1, 0.5, 0.5
    };
    glVertexPointer(3, GL_FLOAT, 0, &vertex_cube);
    glEnableClientState(GL_VERTEX_ARRAY);

    glColorPointer(3, GL_FLOAT, 0, &color_array);
    glEnableClientState(GL_COLOR_ARRAY);

    glDrawArrays(GL_QUADS, 0, 24);

    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
