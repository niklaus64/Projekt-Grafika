#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "RLE.h"
#include "Enum.h"
#include "Own5Bits.h"
#include "NoCompressed.h"
#include <QMessageBox>
#include <QFileDialog>
#include "decompress.h"
#include "byterun.h"
#include <QByteArray>
#include <QBuffer>
//#include <QFIle>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{

    const std::string PATH_TO_FILE_BMP = "3.bmp";
    const std::string PATH_TO_FILE_SZMIK = "wynik.szmik";
    const std::string PATH_TO_SAVE_FILE_SZMIK = "wynik.szmik";
    const std::string PATH_TO_SAVE_FILE_BMP = "wynik.bmp";
    QString pathToBMP;
    QImage image;
    QImage smallOryginalCopy;
    compressionType cT;
    Algorithm *al;


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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
