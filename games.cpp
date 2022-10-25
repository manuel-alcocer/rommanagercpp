#include "romdup.h"

bool Rd::Games::isGameStored(const QString& name) const{
    return gameDict.contains(name);
}
