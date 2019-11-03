#include "qmlplugindump.h"


QmlPluginDump::QmlPluginDump(QObject *parent) : QObject(parent)
{
    version = "1.0";
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finishedProcess(int, QProcess::ExitStatus)));

    //G:\Qt\5.13.1\mingw73_64\bin\qmlplugindump Test 1.0 D:\Project\Qt\SMAClient > D:\Project\Qt\SMAClient\Test\module.qmltypes
}

void QmlPluginDump::setPath(QString path) {
    this->path = path;
}

void QmlPluginDump::setWriteQmlDir(bool write) {
    this->wtiteQmldir = write;
}

QString QmlPluginDump::getModuleName() {
    return path.split("/").last();
}

void QmlPluginDump::finishedProcess(int code, QProcess::ExitStatus status) {
    Q_UNUSED(status)
    if(code == 0) {
        if(wtiteQmldir) {
            QFile file(path + "/qmldir");
            if(file.exists()) {
                if(file.open(QIODevice::Append)) {
                    QString str = "typeinfo " + getModuleName().toLower() + ".qmltypes\n\r";
                    file.write(str.toLocal8Bit());
                    file.close();
                }
            }
        }
        QFile::remove("temp.bat");
        emit finished();
    }
}

void QmlPluginDump::dump() {
    qDebug() << getModuleName().toLower();
    QStringList arguments;

    arguments.append(getModuleName());
    arguments.append(version);
    QStringList pathToModule = path.split("/");
    pathToModule.removeLast();
    arguments.append(pathToModule.join("/"));
    arguments.append(">");
    arguments.append(path + "/" + getModuleName().toLower() + ".qmltypes");

    QString program = Worker::getInstance()->compilerPath() + "/bin/qmlplugindump " + arguments.join(" ");

    QFile *file = new QFile("temp.bat");
    if(file->open(QIODevice::ReadWrite)) {
        file->write(program.toLocal8Bit());
        file->close();
        file->deleteLater();
        process->start("temp.bat");
    }
}
