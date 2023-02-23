#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    setWindowTitle("3DViewer_v1.0 (by Stephank, Fossowan, Marbrand)");
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - 1150) / 2;
    int y = (screenGeometry.height() - 600) / 2;
    move(x, y);
}

Widget::~Widget() {
    delete ui;
}
