#include "romdup.h"

Rd::RomDup::RomDup(const QString& filename){
    gameXmlFile.setFileName(filename);
    QFileInfo fileInfo{filename};
    romDir.setPath(fileInfo.absolutePath());
    newRomsetDoc.appendChild(newRomsetDoc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\""));
    newGameListNode = newRomsetDoc.appendChild(QDomNode(newRomsetDoc.createElement("gameList")));
}

bool Rd::RomDup::filterByNameStartsWith(const QString& name){
    QStringList filtersForRemoving {
        "ZZZ(notgame)"
    };
    for (qsizetype i=0; i < filtersForRemoving.size(); i++){
        if (name.startsWith(filtersForRemoving.at(i)))
            return true;
    }
    return false;
}

bool Rd::RomDup::hasToRemoveGame(const Rd::Game& game){
    bool retval { false };
    if (filterByNameStartsWith(game.getName())){
        qDebug() << "[FILTERED] Skipping: " << game.getName();
        retval = true;
    }
    if (!game.fileExists()){
        qDebug() << "[PATHNOTEXISTS] Skipping: " << game.getFullpath();
    }
    return retval;
}

bool Rd::RomDup::parseNode(const QDomNode &node){
    QString tagName {node.toElement().tagName()};
    if (tagName == "provider"){
        return true;
    } else if (tagName != "game"){
        qDebug() << "[TAGINVALID] Skipping: " << tagName;
        return false;
    }
    Rd::Game newGame;
    newGame.addGame(node);
    newGame.setDir(romDir.absolutePath());
    if (hasToRemoveGame(newGame)){
        return false;
    }
    return true;
}

bool Rd::RomDup::loadGamelist(){
    bool retval {true};

    if (!gameXmlFile.open(QIODevice::ReadOnly)){
        qDebug() << "Cannot read: " << gameXmlFile.fileName();
        retval = false;
    }

    if (!romsetDoc.setContent(&gameXmlFile)){
        qDebug() << "Cannot parse XML: " << gameXmlFile.fileName();
        retval = false;
    } else {
        romsetElem = romsetDoc.documentElement();
    }
    gameXmlFile.close();

    return retval;
}

QString Rd::RomDup::createTmpFile() const{
    QTemporaryFile tmpFile;
    tmpFile.setAutoRemove(false);
    if (tmpFile.open())
        tmpFile.close();
    return tmpFile.fileName();
}

const QString Rd::RomDup::dumpXml() const{
    QFile t(createTmpFile());
    if (t.open(QIODevice::ReadWrite)){
        QTextStream stream(&t);
        stream << newRomsetDoc.toString();
        t.close();
    }
    return t.fileName();
}

int Rd::RomDup::totalGames() const{
    return newRomsetDoc.elementsByTagName("game").count();
}

void Rd::RomDup::parseXml(){
    if (!loadGamelist())
        return;
    QDomNodeList nodes = romsetDoc.documentElement().childNodes();
    for (int i=0; i < nodes.count(); i++){
        QDomNode node = nodes.at(i);
        if (parseNode(node)){
            newGameListNode.appendChild(node);
        }
    }
}
