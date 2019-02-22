#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_destructButton_clicked() {
    ui->openGLWidget->destructObj();
}


void MainWindow::on_tesselationTwoSlider_valueChanged(int val) {
    ui->openGLWidget->sliderChanged(false, val);
}

void MainWindow::on_tesselationOneSlider_valueChanged(int val) {
    ui->openGLWidget->sliderChanged(true, val);
}
