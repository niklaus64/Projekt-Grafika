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

void MainWindow::on_pushButton_2_clicked()
{
    compressionType mode;
    if(ui->radioButton_3->isChecked()) mode=C_OWN_5_BITS;
    else if(ui->radioButton_2->isChecked()) mode=C_BYTE_RUN;
    else if(ui->radioButton_3->isChecked()) mode=C_RLE;
    else if(ui->radioButton_5->isChecked())mode=C_NOT_COMPRESSED;

    QString pathToSave;
    switch (mode)
    {
    case C_RLE:
        //al = new RLE();
        break;
    case C_BYTE_RUN:
        //al = new ByteRun();
        break;
    case C_OWN_5_BITS:
        pathToSave = QFileDialog::getSaveFileName(this,tr("Save..."),"./","SZMIK (*.szmik)");
        al = new Own5Bits(pathToBMP.toStdString(),0,0,ui->radioButton->isChecked()); // kolejno: sciezka do plik, stopien jasnoci, stopien kontrastu, skala szarosci
        al->compress();
        al->saveToFile(pathToSave.toStdString());
        break;
    case C_NOT_COMPRESSED:
        pathToSave = QFileDialog::getSaveFileName(this,tr("Save..."),"./","BMP (*.bmp)");
        al = new NoCompressed(pathToBMP.toStdString(), 0, 0, ui->radioButton->isChecked());
        al->saveToFile(pathToSave.toStdString());

        break;
    }

   QMessageBox::information(this,"Jest juz SZMIK","utworzono nowego SZMIKa!");
}

void MainWindow::on_actionOtw_rz_triggered()
{
    pathToBMP = QFileDialog::getOpenFileName(this,tr("Open file"),"./","bmp (*.bmp)");
    ui->pushButton_2->setEnabled(!pathToBMP.isNull());
}

void MainWindow::on_actionRozpakuj_triggered()
{
    Decompress dec;
    dec.setModal(true);
    dec.exec();
}
