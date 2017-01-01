#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), brightnessValue(0), contrastValue(0)
{
    ui->setupUi(this);
}


void MainWindow::on_pushButton_2_clicked()
{
	//sprawdzenie ktora opcja zostala wybrana
    if(ui->radioButton_3->isChecked()) data.cT=C_OWN_5_BITS;
    else if(ui->radioButton_2->isChecked()) data.cT=C_BYTE_RUN;
    else if(ui->radioButton_4->isChecked()) data.cT=C_RLE;
    else if(ui->radioButton_5->isChecked()) data.cT=C_NOT_COMPRESSED;

    QString pathToSave;

	try
	{
		data.loadFile(pathToBMP.toStdString(), false);
	}
	catch (Error &error)
	{
		QMessageBox::information(this, "BLAD PROGRAMU", error.showError());
		exit(error.code);
	}

	if (ui->radioButton->isChecked()) data.GrayScale();
	
	switch (data.cT)
    {
    case C_RLE:
		pathToSave = QFileDialog::getSaveFileName(this, tr("Save..."), "./", "RLE (*.rle)");
		al = new RLE(&data);
		al->compress();
		break;
    case C_BYTE_RUN:
		pathToSave = QFileDialog::getSaveFileName(this, tr("Save..."), "./", "BYTERUN (*.br)");
		al = new ByteRun(&data);
		al->compress();
		break;
    case C_OWN_5_BITS:
		pathToSave = QFileDialog::getSaveFileName(this, tr("Save..."), "./", "SZMIK (*.szmik)");
		al = new Own5Bits(&data);
		al->compress();
		break;
    case C_NOT_COMPRESSED:
		pathToSave = QFileDialog::getSaveFileName(this, tr("Save..."), "./", "BMP (*.bmp)");
		break;
    }
	try {
		data.writeData(pathToSave.toStdString(), data.cT);
	}
	catch (Error &error)
	{
		QMessageBox::information(this, "BLAD PROGRAMU", error.showError());
		exit(error.code);
	}
	QMessageBox::information(this, "Kompresja zakonczona sukcesem", "Udalo siê! Twoja kompresja siê powiodla :)");
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
    pathToBMP = QFileDialog::getOpenFileName(this,tr("Open file"),"./","BMP (*.bmp)");
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


MainWindow::~MainWindow()
{
	delete al;
    delete ui;
}
