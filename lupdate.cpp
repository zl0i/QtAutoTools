#include "lupdate.h"

Lupdate::Lupdate(QObject *parent) : QObject(parent)
{
    connect(process, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(finishedProcess(int, QProcess::ExitStatus)));

}

void Lupdate::setPath(QString path) {
    this->path = path;
}

void Lupdate::setLanguage(QStringList list) {
    this->langList = list;
}

QString Lupdate::getStringFileTs() {
    const QString name = getProFileName().split(".").first();
    QStringList tsFile;
    for(int i = 0; i < langList.count(); i++) {
        tsFile.append(path + "/" + name + "_" + langList.at(i) + ".ts");
    }
    return  tsFile.join(" ");
}

QString Lupdate::getProFileName() {
    QDir dir(path);
    QStringList filter = {"*.pro"};
    QFileInfoList infoList = dir.entryInfoList(filter);
    if(infoList.count() != 0) {
        return infoList.at(0).fileName();
    }
    return "";
}

void Lupdate::createTs() {

    QStringList arguments;
    arguments.append(path + "/" +getProFileName());
    arguments.append("-ts " + getStringFileTs());
    QString program = Worker::getInstance()->compilerPath() + "/bin/lupdate " + arguments.join(" ");
    qDebug() << program;

    QFile *file = new QFile("temp.bat");
    if(file->open(QIODevice::ReadWrite)) {
        file->write(program.toLocal8Bit());
        file->close();
        file->deleteLater();
        process->start("temp.bat");
    }
}

void Lupdate::runLinguist() {
    if(langList.count() != 0) {
        process->startDetached(Worker::getInstance()->compilerPath() + "/bin/linguist " + getStringFileTs());
    }
    else  {
        process->startDetached(Worker::getInstance()->compilerPath() + "/bin/linguist");
    }
}

void Lupdate::finishedProcess(int code, QProcess::ExitStatus status) {
    Q_UNUSED(code)
    Q_UNUSED(status)
    QFile::remove("temp.bat");
    emit finished();
}
