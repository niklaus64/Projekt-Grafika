#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QByteArray>
#include <QBuffer>
#include <QMessageBox>
#include <QFileDialog>

#include "RLE.h"
#include "Enum.h"
#include "Own5Bits.h"
#include "NoCompressed.h"
#include "decompress.h"
#include "byterun.h"
#include "cmath"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{


    QString pathToBMP;
    QImage image;
    QImage smallOryginalCopy;
    compressionType cT;
    Algorithm *al;


    int brightnessValue;
    int contrastValue;
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_2_clicked();

    void on_actionOtw_rz_triggered();

    void on_actionRozpakuj_triggered();

    void on_radioButton_pressed();

    void on_pushButton_clicked();

    void on_radioButton_released();

    void on_radioButton_clicked();

    void on_pushButton_3_clicked();

    void on_horizontalSlider_valueChanged(int value);

    void modyfikuj(int,int,bool);

    void on_horizontalSlider_2_valueChanged(int value);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
