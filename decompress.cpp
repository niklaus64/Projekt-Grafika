#include "decompress.h"
#include "ui_decompress.h"

Decompress::Decompress(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Decompress)
{
    ui->setupUi(this);
}

Decompress::~Decompress()
{
    delete ui;
}

void Decompress::on_toolButton_clicked()
{
	ui->lineEdit->setText(QFileDialog::getOpenFileName(this, tr("Open file"), "./", "Pliki skompresowane (*.szmik *.rle *.br)"));
}

void Decompress::on_toolButton_2_clicked()
{
    ui->lineEdit_2->setText(QFileDialog::getSaveFileName(this,tr("Save BMP file"),"./", "BMP (*.bmp)"));
}

void Decompress::on_pushButton_clicked()
{

	data.loadFile(ui->lineEdit->text().toStdString(), true);

	switch (data.cT)
	{
	case C_BYTE_RUN:
		al = new ByteRun(&data);
		al->decompress();
		break;
	case C_OWN_5_BITS:
		al = new Own5Bits(&data);
		al->decompress();
		break;
	case C_RLE:
		al = new RLE(&data);
		al->decompress();
		break;
	case C_NOT_COMPRESSED:
		//error
		break;
	default:
		break;
	}
 
    data.writeData(ui->lineEdit_2->text().toStdString(),C_NOT_COMPRESSED);
	QMessageBox::information(this, "Dekompresja udana", "Plik zostal zdekompresowany");
}