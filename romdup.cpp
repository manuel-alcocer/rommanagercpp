#include "romdup.h"

Rd::RomDup::RomDup(){
    initRomdup();
}

Rd::RomDup::RomDup(const QString& dirName){
    initRomdup();
    /* gameXmlFile.setFileName(filename);
     QFileInfo fileInfo{filename};
    romDir.setPath(fileInfo.absolutePath());
    newRomsetDoc.appendChild(newRomsetDoc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\""));
    newGameListNode = newRomsetDoc.appendChild(QDomNode(newRomsetDoc.createElement("gameList")));
    */
}

void Rd::RomDup::initRomdup(){
    readSettings();
    setRomsetDir(QFileInfo("/run/media/manuel/DISK05/manuel/roms-351elec/snes"));
}

bool Rd::RomDup::setRomsetDir(const QFileInfo& romset){
    if (romsetList.contains(romset)){
        qDebug() << "Choosen: " << romset.canonicalFilePath();
        return true;
    }
    qDebug() << "Not choosen: " << romset.canonicalFilePath();
    return false;
}

void Rd::RomDup::settingsReadPoolDir(){
    bool setup;
    QString newDir;

    if (settings.childKeys().contains("pooldir"))
        newDir = settings.value("pooldir").toString();
    else
        newDir = QDir::currentPath();

    setup = setPoolDir(newDir);
    if (setup)
        settings.setValue("pooldir", newDir);
}

void Rd::RomDup::readSettings(){
    settingsReadPoolDir();
}

bool Rd::RomDup::setPoolDir(const QString& dirName){
    bool matched {false};
    poolDir = QDir{dirName};
    QFileInfoList dirList {poolDir.entryInfoList(QDir::NoDotAndDotDot|QDir::Dirs)};
    for (int i=0; i < dirList.count(); i++){
        QFileInfo romset(dirList.at(i).canonicalFilePath()+"/"+"gamelist.xml");
        if (romset.exists()){
            matched = true;
            qDebug() << "Appending: " << romset.canonicalPath();
            romsetList.append(romset);
        }
    }

    if (matched)
        settings.setValue("pooldir", poolDir.canonicalPath());
    return matched;
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
