#include "romdup.h"

void Rd::Game::addGame(const QDomNode& node){
    QDomNodeList nodeList = node.childNodes();
    for (int i=0; i < nodeList.count(); i++){
        QString tagName{nodeList.at(i).toElement().tagName()};
        QString text{nodeList.at(i).toElement().text()};
        if (tagName == "name"){
            setName(text);
        } else if (tagName == "path"){
            setPath(text);
        }
    }
}

void Rd::Game::setName(const QString& name){
    this->name = name;
}

void Rd::Game::setPath(const QString& name){
    path.setFileName(name);
}

void Rd::Game::setDir(const QString& name){
    dir.setPath(name);
}

bool Rd::Game::fileExists() const{
    return filePathExists(getFullpath());
}

bool Rd::Game::filePathExists(const QString& fileName) const{
    QFile file {fileName};
    bool retval {true};
    if (!file.open(QIODevice::ReadOnly)){
        retval = false;
    }
    file.close();
    return retval;
}

bool Rd::Game::operator==(const Rd::Game& other){
    if (this->name == other.name && this->path.fileName() == other.path.fileName())
        return true;
    return false;
}

const QString& Rd::Game::getName() const{
    return name;
}

QString Rd::Game::getFullpath() const{
    QFileInfo fullpath {dir.absolutePath()+"/"+path.fileName()};
    return fullpath.absoluteFilePath();
}
