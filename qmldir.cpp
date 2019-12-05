#include "qmldir.h"

QmlDir::QmlDir(QObject *parent) : QObject(parent)
{

}


void QmlDir::setPath(QString path) {
    this->path = path;
}

void QmlDir::setCreateTypes(bool b)
{
    this->createTypes = b;
}


void QmlDir::createQmlDir() {


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
            //QString row = qmlFiles.at(i).split(".").first() + " " + getStringVersion() + " " + qmlFiles.at(i) + "\n";
            //file.write(row.toLocal8Bit());
        }
        file.close();
        emit finished();
    }
    else {
        emit error("Не удалось открыть файл");
    }
}
