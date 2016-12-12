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
    ui->lineEdit->setText(QFileDialog::getOpenFileName(this,tr("Open file"),"./","SZMIK (*.szmik)"));
}

void Decompress::on_toolButton_2_clicked()
{
    ui->lineEdit_2->setText(QFileDialog::getSaveFileName(this,tr("Save BMP file"),"./","BMP (*.bmp)"));
}

void Decompress::on_pushButton_clicked()
{
    DataImage i;
    i.LoadFromSZMIK(ui->lineEdit->text().toStdString());

    switch (i.get_cT()) {
    case C_OWN_5_BITS:
        Own5Bits::decompress(i);
        break;
    case C_RLE:
        RLE::decompress(i);
        break;
    case C_BYTE_RUN:
        ByteRun::decompress(i);
        break;

    }

    i.WriteDataToBMP(ui->lineEdit_2->text().toStdString());
    ui->label_3->setText("ROZPAKOWANO POMYŚLNIE");
}
