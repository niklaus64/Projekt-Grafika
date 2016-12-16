#ifndef DECOMPRESS_H
#define DECOMPRESS_H

#include <QDialog>
#include <QFileDialog>
#include "RLE.h"
#include "Enum.h"
#include "Own5Bits.h"
#include "NoCompressed.h"
#include "byterun.h"
namespace Ui {
class Decompress;
}

class Decompress : public QDialog
{
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
