#ifndef ROMDUP2_H
#define ROMDUP2_H

#include <QCoreApplication>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>
#include <QHash>
#include <QStringList>
#include <QTemporaryFile>
#include <QDir>

namespace Rd {
    class Game {
    public:
        void addGame(const QDomNode&);
        void setName(const QString&);
        void setPath(const QString&);
        void setDir(const QString&);
        void setVideo(const QString&);
        void setThumbnail(const QString&);
        void setImage(const QString&);
        bool fileExists() const;
        bool videoExists() const;
        bool thumbnailExists() const;
        bool imageExists() const;
        const QString& getName() const;
        const QFile& getPath() const;
        bool operator==(const Game&);
        QString getFullpath() const;
    private:
        QString name;
        QDir dir;
        QFile fullpath;
        QFile path;
        QFile video;
        QFile thumbnail;
        QFile image;
        QDomNode node;
        // Exists means: exists and is readable by us
        bool filePathExists(const QString&) const;
    };

    class Games {
    public:
        bool isGameStored(const QString& name) const;
    private:
        QHash<QString,QHash<QString, QString>> gameDict;
    };

    class RomDup : public Games {
    public:
        RomDup(const QString&);
        void parseXml();
        bool parseNode(const QDomNode&);
        bool hasToRemoveGame(const Rd::Game&);
        const QString dumpXml() const;
        int totalGames() const;
    private:
        bool loadGamelist();
        bool filterByNameStartsWith(const QString&);
        QString createTmpFile() const;
        QFile gameXmlFile;
        QDir romDir;
        QDomDocument romsetDoc;
        QDomDocument newRomsetDoc;
        QDomNode newGameListNode;
        QDomElement romsetElem;
    };
}

#endif // ROMDUP2_H
