#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tesselationOneSlider->setValue(10);
    ui->tesselationTwoSlider->setValue(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_destructButton_clicked() {
    ui->openGLWidget->destructObj();
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_E) {
        ui->openGLWidget->zoom(1);
    }
    else if (e->key() == Qt::Key_Q) {
        ui->openGLWidget->zoom(-1);
    }
    else if (e->key() == Qt::Key_D) {
        ui->openGLWidget->pan(1,0);
    }
    else if (e->key() == Qt::Key_A) {
        ui->openGLWidget->pan(-1,0);
    }
}


void MainWindow::on_tesselationTwoSlider_valueChanged(int val) {
    ui->openGLWidget->sliderChanged(false, val);
}

void MainWindow::on_tesselationOneSlider_valueChanged(int val) {
    ui->openGLWidget->sliderChanged(true, val);
}

void MainWindow::on_cylinderSelect_clicked() {
    ui->openGLWidget->changeShapeType(MainWidget::ShapeType::CylinderType);
}
void MainWindow::on_cubeSelect_clicked() {
    ui->openGLWidget->changeShapeType(MainWidget::ShapeType::CubeType);
}
void MainWindow::on_sphereSelect_clicked() {
    ui->openGLWidget->changeShapeType(MainWidget::ShapeType::SphereType);
}
void MainWindow::on_coneSelect_clicked() {
    ui->openGLWidget->changeShapeType(MainWidget::ShapeType::ConeType);
}
