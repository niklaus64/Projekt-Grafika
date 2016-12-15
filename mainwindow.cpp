#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


     brightnessValue=0;
     contrastValue=0;
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

    smallOryginalCopy=image;

    ui->label_3->setPixmap(QPixmap::fromImage(image));
    ui->pushButton_2->setEnabled(!pathToBMP.isNull());
    ui->groupBox->setEnabled(!pathToBMP.isNull());
    ui->groupBox_2->setEnabled(!pathToBMP.isNull());
}

void MainWindow::on_pushButton_clicked()
{
    pathToBMP = QFileDialog::getOpenFileName(this,tr("Open file"),"./","bmp (*.bmp)");
    image.load(pathToBMP);

    if(image.width()>image.height()) image=image.scaledToWidth(ui->label_3->geometry().width(),Qt::FastTransformation);
    else  image=image.scaledToWidth(ui->label_3->geometry().height(),Qt::FastTransformation);

    smallOryginalCopy=image;

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
void MainWindow::on_pushButton_3_clicked()
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
    modyfikuj(contrastValue, brightnessValue, ui->radioButton->isChecked());
}







void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    brightnessValue=value;
    modyfikuj(contrastValue,brightnessValue,ui->radioButton->isChecked());
}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{
    contrastValue = value;
    modyfikuj(contrastValue,brightnessValue,ui->radioButton->isChecked());
}


void MainWindow::modyfikuj(int contrastValue, int brightnessValue, bool grayMode){

    image=smallOryginalCopy;

        for (int ii = 0; ii < image.height(); ii++) {
            uchar* scan = image.scanLine(ii);
            int depth =4;
            for (int jj = 0; jj < image.width(); jj++) {

                QRgb* rgbpixel = reinterpret_cast<QRgb*>(scan + jj*depth);

                if(grayMode){
                    int gray = qGray(*rgbpixel);
                    *rgbpixel = QColor(gray, gray, gray).rgba();
                }

                if(contrastValue){
                    double a;
                    if(contrastValue<=0){
                         a=1.0 + (contrastValue/256.0);
                    }else{
                         a=256.0/pow(2,log2(257-contrastValue));
                    }
                    int red = [](double p, int color)->int {
                                        if((p*(color-(255/2))+(255/2))<0) return 0;
                                        else if ((p*(color-(255/2))+(255/2))>=0 && (p*(color-(255/2))+(255/2))<=255) return (p*(color-(255/2))+(255/2));
                                        else return 255;
                                }(a,qRed(*rgbpixel));


                    int green = [](double p, int color)->int {
                                         if((p*(color-(255/2))+(255/2))<0) return 0;
                                         else if ((p*(color-(255/2))+(255/2))>=0 && (p*(color-(255/2))+(255/2))<=255) return (p*(color-(255/2))+(255/2));
                                         else return 255;
                                }(a,qGreen(*rgbpixel));


                    int blue = [](double p, int color)->int {
                                          if((p*(color-(255/2))+(255/2))<0) return 0;
                                          else if ((p*(color-(255/2))+(255/2))>=0 && (p*(color-(255/2))+(255/2))<=255) return (p*(color-(255/2))+(255/2));
                                          else return 255;
                                }(a,qBlue(*rgbpixel));

                    *rgbpixel = QColor(red, green, blue).rgba();
                }


                if(brightnessValue){
                    int red = [](int p, int color)->int {
                                                        if(color+p<0) return 0;
                                                        else if (color+p>=0 && color+p<=255) return p+color;
                                                        else return 255;
                                }(brightnessValue,qRed(*rgbpixel));


                    int green = [](int p, int color)->int {
                        if(color+p<0) return 0;
                        else if (color+p>=0 && color+p<=255) return p+color;
                        else return 255;
                    }(brightnessValue,qGreen(*rgbpixel));


                    int blue = [](int p, int color)->int {
                        if(color+p<0) return 0;
                        else if (color+p>=0 && color+p<=255) return p+color;
                        else return 255;
                    }(brightnessValue,qBlue(*rgbpixel));

                    *rgbpixel = QColor(red, green, blue).rgba();
                }
            }
        }


        ui->label_3->setPixmap(QPixmap::fromImage(image));

}


