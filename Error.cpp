#include "Error.h"

Error::Error(uint16_t code)
        : code(code) { };

QString Error::showError()
{
        QString errormsg;
        switch (code)
        {
        case 0:
                errormsg = "Blad domyslny";
                break;
        case 1:
                errormsg = "Blad odczytu pliku!\nByc moze plik nie istnieje lub nie ma do niego dostepu?";
                break;
        case 2:
                errormsg = "Blad zapisu pliku!\nBrak miejsca na dysku lub brak dostepu?";
                break;
        default:
                errormsg = "Nieznany blad!";
        }
        return errormsg;
}

Error::~Error() { }
