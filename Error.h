#pragma once
#include <QMessageBox>
#include <cstdint>

class Error
{
public:
        uint16_t code;
        Error(uint16_t code=0);
        QString showError();
        ~Error();
};
