#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include "RLE.h"
#include "Enum.h"
#include "Own5Bits.h"
#include "ByteRun.h"
namespace Ui {
class Decompress;
}

class Decompress : public QDialog
{
	std::shared_ptr<DataImage> data;
	std::unique_ptr<Algorithm> al;
	Q_OBJECT

public:
    explicit Decompress(QWidget *parent = 0);
    ~Decompress();

private slots:
    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Decompress *ui;
};

#endif // DECOMPRESS_H
