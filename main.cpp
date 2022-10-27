#include "romdup.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setOrganizationName("romdup");
    QCoreApplication::setApplicationName("default");
    Rd::RomDup romdup;

    //    romdup.parseXml();

    // qDebug() << "Total games: " << romdup.totalGames();
    // qDebug() << "XML written to: " << romdup.dumpXml();
}
