#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwidget.h"
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent*e) override;
    bool m_splitPaused = true;

private slots:
    void on_destructButton_clicked();
    void on_advanceSplitButton_clicked();
    void on_resetButton_clicked();
    void on_tesselationTwoSlider_valueChanged(int val);
    void on_tesselationOneSlider_valueChanged(int val);
    void on_cylinderSelect_clicked();
    void on_cubeSelect_clicked();
    void on_sphereSelect_clicked();
    void on_coneSelect_clicked();
    void on_unpauseSplitButton_clicked();


private:
    Ui::MainWindow *ui;
    //MainWidget *widget;
};

#endif // MAINWINDOW_H
