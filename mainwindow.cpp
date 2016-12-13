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
    else if(ui->radioButton_4->isChecked()) mode=C_RLE;
    else if(ui->radioButton_5->isChecked())mode=C_NOT_COMPRESSED;

    QString pathToSave;
    switch (mode)
    {
    case C_RLE:
        pathToSave = QFileDialog::getSaveFileName(this,tr("Save..."),"./","SZMIK (*.szmik)");
        if(!pathToSave.isEmpty()){
        al = new RLE(pathToBMP.toStdString(),0,0,ui->radioButton->isChecked()); // kolejno: sciezka do plik, stopien jasnoci, stopien kontrastu, skala szarosci
        al->compress();
        al->saveToFile(pathToSave.toStdString());
        QMessageBox::information(this,"Jest juz SZMIK","utworzono nowego SZMIKa!");
        }
        break;
    case C_BYTE_RUN:
        pathToSave = QFileDialog::getSaveFileName(this,tr("Save..."),"./","SZMIK (*.szmik)");
        if(!pathToSave.isEmpty()){
        al = new ByteRun(pathToBMP.toStdString(),0,0,ui->radioButton->isChecked());
        al->compress();
        al->saveToFile(pathToSave.toStdString());
        QMessageBox::information(this,"Jest juz SZMIK","utworzono nowego SZMIKa!");
        }
        break;
    case C_OWN_5_BITS:
        pathToSave = QFileDialog::getSaveFileName(this,tr("Save..."),"./","SZMIK (*.szmik)");
         if(!pathToSave.isEmpty()){
        al = new Own5Bits(pathToBMP.toStdString(),0,0,ui->radioButton->isChecked()); // kolejno: sciezka do plik, stopien jasnoci, stopien kontrastu, skala szarosci
        al->compress();
        al->saveToFile(pathToSave.toStdString());
        QMessageBox::information(this,"Jest juz SZMIK","utworzono nowego SZMIKa!");
         }
        break;
    case C_NOT_COMPRESSED:
        pathToSave = QFileDialog::getSaveFileName(this,tr("Save..."),"./","BMP (*.bmp)");
         if(!pathToSave.isEmpty()){
        al = new NoCompressed(pathToBMP.toStdString(), 0, 0, ui->radioButton->isChecked());
        al->saveToFile(pathToSave.toStdString());
        QMessageBox::information(this,"Jest juz SZMIK","utworzono nowego SZMIKa!");
        }
        break;
    }


}

void MainWindow::on_actionOtw_rz_triggered()
{
    pathToBMP = QFileDialog::getOpenFileName(this,tr("Open file"),"./","bmp (*.bmp)");
    image.load(pathToBMP);

    if(image.width()>image.height()) image=image.scaledToWidth(ui->label_3->geometry().width(),Qt::FastTransformation);
    else  image=image.scaledToWidth(ui->label_3->geometry().height(),Qt::FastTransformation);
    ui->label_3->setPixmap(QPixmap::fromImage(image));
    ui->pushButton_2->setEnabled(!pathToBMP.isNull());
    ui->groupBox->setEnabled(!pathToBMP.isNull());
    ui->groupBox_2->setEnabled(!pathToBMP.isNull());
}

void MainWindow::on_actionRozpakuj_triggered()
{
    Decompress dec;
    dec.setModal(true);
    dec.exec();
}

void MainWindow::on_radioButton_pressed()
{

}
void MainWindow::on_radioButton_released()
{

}

void MainWindow::on_radioButton_clicked()
{
    if(!ui->radioButton->isChecked()){
        image.load(pathToBMP);
        if(image.width()>image.height()) image=image.scaledToWidth(ui->label_3->geometry().width(),Qt::FastTransformation);
        else  image=image.scaledToWidth(ui->label_3->geometry().height(),Qt::FastTransformation);
         ui->label_3->setPixmap(QPixmap::fromImage(image));
    }else{
        for (int ii = 0; ii < image.height(); ii++) {
            uchar* scan = image.scanLine(ii);
            int depth =4;
            for (int jj = 0; jj < image.width(); jj++) {

                QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);
                int gray = qGray(*rgbpixel);
                *rgbpixel = QColor(gray, gray, gray).rgba();
            }
        }
        ui->label_3->setPixmap(QPixmap::fromImage(image));
    }
}

void MainWindow::on_pushButton_clicked()
{

}
