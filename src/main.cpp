#include "ihmconvertisseur.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHMConvertisseur w;
    w.show();

    return a.exec();
}
