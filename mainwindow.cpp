#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tesselationOneSlider->setValue(30);
    ui->tesselationTwoSlider->setValue(30);
    exitDestruct();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_destructButton_clicked() {
    ui->openGLWidget->destructObj();
    enterDestruct();
}

void MainWindow::on_resetButton_clicked() {
    ui->openGLWidget->reset();
    exitDestruct();
}

void MainWindow::on_advanceSplitButton_clicked() {
    ui->openGLWidget->advanceSplitIncr();
}

void MainWindow::keyPressEvent(QKeyEvent *e) {
    if (e->key() == Qt::Key_E) {
        ui->openGLWidget->zoom(1);
    }
    else if (e->key() == Qt::Key_Q) {
        ui->openGLWidget->zoom(-1);
    }
    else if (e->key() == Qt::Key_D) {
        ui->openGLWidget->pan(-1,0);
    }
    else if (e->key() == Qt::Key_A) {
        ui->openGLWidget->pan(1,0);
    }
    else if (e->key() == Qt::Key_W) {
        ui->openGLWidget->pan(0,-1);
    }
    else if (e->key() == Qt::Key_S) {
        ui->openGLWidget->pan(0,1);
    }
}

void MainWindow::on_unpauseSplitButton_clicked() {
    m_splitPaused = !m_splitPaused;
    if (m_splitPaused) {
        ui->unpauseSplitButton->setText("Resume Split");
    }
    else {
        ui->unpauseSplitButton->setText("Pause Split");
    }

    ui->openGLWidget->pauseResumeSplit(m_splitPaused);
}

void MainWindow::on_tesselationTwoSlider_valueChanged(int val) {
    ui->openGLWidget->sliderChanged(false, val);
    exitDestruct();
}

void MainWindow::enterDestruct() {
    ui->destructButton->setEnabled(false);
    ui->advanceSplitButton->setEnabled(true);
    ui->unpauseSplitButton->setEnabled(true);
}

void MainWindow::exitDestruct() {
    ui->destructButton->setEnabled(true);
    ui->advanceSplitButton->setEnabled(false);
    ui->unpauseSplitButton->setEnabled(false);
}

void MainWindow::on_tesselationOneSlider_valueChanged(int val) {
    ui->openGLWidget->sliderChanged(true, val);
    exitDestruct();
}

void MainWindow::on_cylinderSelect_clicked() {
    ui->openGLWidget->changeShapeType(MainWidget::ShapeType::CylinderType);
    exitDestruct();
}
void MainWindow::on_cubeSelect_clicked() {
    ui->openGLWidget->changeShapeType(MainWidget::ShapeType::CubeType);
    exitDestruct();
}
void MainWindow::on_sphereSelect_clicked() {
    ui->openGLWidget->changeShapeType(MainWidget::ShapeType::SphereType);
    exitDestruct();
}
void MainWindow::on_coneSelect_clicked() {
    ui->openGLWidget->changeShapeType(MainWidget::ShapeType::ConeType);
    exitDestruct();
}
