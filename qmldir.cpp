#include "qmldir.h"

QmlDir::QmlDir(QObject *parent) : QObject(parent)
{

}


void QmlDir::setPath(QString path) {
    this->path = path;
}

void QmlDir::setMajorVersion(uint major) {
   this->major = major;
}

void QmlDir::setMinorVersion(uint minor) {
   this->minor = minor;
}


QString QmlDir::getStringVersion() {
    return  QString::number(major) +"." + QString::number(minor);
}

void QmlDir::createModule() {
    if(path.isEmpty() || major == 0) {
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
            QString row = qmlFiles.at(i).split(".").first() + " " + getStringVersion() + " " + qmlFiles.at(i) + "\n";
            file.write(row.toLocal8Bit());
        }
        file.close();
        emit finished();
    }
    else {
        emit error("Не удалось открыть файл");
    }
}
