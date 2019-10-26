#include "qmldir.h"

QmlDir::QmlDir(QObject *parent) : QObject(parent)
{
    version = "1.0";
}


void QmlDir::setPath(QString path) {
    this->path = path;
}

void QmlDir::setVersion(int major, int minor) {
    version = QString::number(major) + "." + QString::number(minor);
}

void QmlDir::createModule() {
    if(path.isEmpty() || version.isEmpty()) {
        emit error("Недопустимые аргументы");
        return;
    }

    QStringList filterList = {"*.qml", "*.js"};
    QStringList qmlFiles = QDir(path).entryList(filterList, QDir::Files, QDir::Name);
    if(qmlFiles.count() == 0) {
        emit error("Файлов не обнаружено");
        return;
    }

    QFile file(path + "/qmldir");
    if(file.exists()) file.remove();
    if(file.open(QIODevice::ReadWrite)) {
        QString nameModule = "module " + path.split("/").last() + "\n";
        file.write(nameModule.toLocal8Bit());
        for(int i = 0; i < qmlFiles.count(); ++i) {
            QString row = qmlFiles.at(i).split(".").first() + " " + version + " " + qmlFiles.at(i) + "\n";
            file.write(row.toLocal8Bit());
        }
        file.close();
        emit finished();
    }
}
