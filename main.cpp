#include "romdup.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Rd::RomDup romdup ("/run/media/manuel/DISK05/manuel/roms-351elec/nes/gamelist.xml");

    romdup.parseXml();

    qDebug() << "Total games: " << romdup.totalGames();
    qDebug() << "XML written to: " << romdup.dumpXml();
}
