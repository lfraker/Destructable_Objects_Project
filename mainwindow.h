#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_destructButton_clicked();
    void on_tesselationTwoSlider_valueChanged(int val);
    void on_tesselationOneSlider_valueChanged(int val);
    void on_cylinderSelect_clicked();
    void on_cubeSelect_clicked();
    void on_sphereSelect_clicked();
    void on_coneSelect_clicked();

private:
    Ui::MainWindow *ui;
    //MainWidget *widget;
};

#endif // MAINWINDOW_H
