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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
