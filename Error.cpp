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
	case 1:
		errormsg = "Blad tworzenia pliku";
	default:
		break;
	}
	return errormsg;
}

Error::~Error() { }
