#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tesselationOneSlider->setValue(30);
    ui->tesselationTwoSlider->setValue(30);
    ui->splitDepthLabel->setText(QString::number(ui->splitDepthSlider->value()));
    exitDestruct();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_destructButton_clicked() {
    ui->openGLWidget->destructObj(ui->splitDepthSlider->value());
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

    ui->unpauseJoinButton->setText("Resume Join");
    m_joinPaused = true;
    ui->openGLWidget->pauseResumeJoin(m_joinPaused);

    ui->openGLWidget->pauseResumeSplit(m_splitPaused);

}

void MainWindow::on_advanceJoinButton_clicked() {
    ui->openGLWidget->advanceJoinIncr();
}

void MainWindow::on_unpauseJoinButton_clicked() {
    m_joinPaused = !m_joinPaused;
    if (m_joinPaused) {
        ui->unpauseJoinButton->setText("Resume Join");
    }
    else {
        ui->unpauseJoinButton->setText("Pause Join");
    }

    ui->unpauseSplitButton->setText("Resume Split");
    m_splitPaused = true;
    ui->openGLWidget->pauseResumeSplit(m_splitPaused);

    ui->openGLWidget->pauseResumeJoin(m_joinPaused);
}

void MainWindow::on_tesselationTwoSlider_valueChanged(int val) {
    ui->openGLWidget->sliderChanged(false, val);
    qDebug("Tesselation Two value: %i", val);
    exitDestruct();
}

void MainWindow::on_splitDepthSlider_valueChanged(int val) {
    ui->splitDepthLabel->setText(QString::number(ui->splitDepthSlider->value()));
}

void MainWindow::on_renderLinesButton_clicked() {
    m_linesRender = !m_linesRender;
    ui->openGLWidget->triggerRenderLines(m_linesRender);
    if (m_linesRender) {
        ui->renderLinesButton->setText("Turn Lines Off");
    }
    else {
        ui->renderLinesButton->setText("Turn Lines On");
    }
}

void MainWindow::enterDestruct() {
    ui->destructButton->setEnabled(false);
    ui->advanceSplitButton->setEnabled(true);
    ui->unpauseSplitButton->setEnabled(true);
    ui->splitDepthSlider->setEnabled(false);
    ui->unpauseJoinButton->setEnabled(true);
    ui->advanceJoinButton->setEnabled(true);
}

void MainWindow::exitDestruct() {
    ui->destructButton->setEnabled(true);
    ui->advanceSplitButton->setEnabled(false);
    ui->unpauseSplitButton->setEnabled(false);
    ui->splitDepthSlider->setEnabled(true);
    ui->unpauseJoinButton->setEnabled(false);
    ui->advanceJoinButton->setEnabled(false);
    m_joinPaused = true;
    m_splitPaused = true;
    ui->unpauseJoinButton->setText("Resume Join");
    ui->unpauseSplitButton->setText("Resume Split");
    ui->openGLWidget->pauseResumeSplit(m_splitPaused);
    ui->openGLWidget->pauseResumeJoin(m_joinPaused);
}

void MainWindow::on_tesselationOneSlider_valueChanged(int val) {
    ui->openGLWidget->sliderChanged(true, val);
    qDebug("Tesselation One value: %i", val);
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
