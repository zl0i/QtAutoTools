#include "lupdate.h"

Lupdate::Lupdate(QObject *parent) : QProcess(parent)
{
    QHash<int, QByteArray> hash;
    hash.insert(Qt::UserRole+1, "file");
    filesModel->setItemRoleNames(hash);
    filesModel->insertColumn(0);
    filesModel->insertRow(0);
    filesModel->setData(filesModel->index(0, 0), "", Qt::UserRole+1);

    connect(this, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
            this, QOverload<int>::of(&Lupdate::slotFinished));
    connect(this, &QProcess::readyRead, this, &Lupdate::slotReadChanel);
}

void Lupdate::slotReadChanel() {
    setReadChannel(QProcess::StandardError);
    QByteArray error = readAll();
    if(!error.isEmpty())
        emit newErrorData(error);

    setReadChannel(QProcess::StandardOutput);
    QByteArray output = readAll();
    if(!output.isEmpty())
        emit newOutputData(output);

}

void Lupdate::removeFile(int row)
{
    if(filesModel->rowCount() > 1)
        filesModel->removeRow(row);
}


void Lupdate::addFile() {
    filesModel->insertRow(filesModel->rowCount());
    QModelIndex index = filesModel->index(filesModel->rowCount()-1, 0);
    filesModel->setData(index, "", Qt::UserRole+1);
}

void Lupdate::setFiles(int row, QString url) {
    QModelIndex index = filesModel->index(row, 0);
    filesModel->setData(index, url, Qt::UserRole+1);
}

void Lupdate::setLanguage(QString list) {
    this->langList = list.split(" ", QString::SkipEmptyParts);
}

void Lupdate::setUpdateFile(QString file)
{
    this->updateFile = file;
}

void Lupdate::setTsFileName(QString name)
{
    tsFile = name;
}

QString Lupdate::getStringFileTs(QString url) {
    QStringList listPath = url.split("/");
    QString file = listPath.last();
    listPath.removeLast();
    QString path = listPath.join("/");
    QStringList name = file.split(".");

    QStringList tsFile;
    for(int i = 0; i < langList.count(); i++) {
        tsFile.append(path + "/" + name.at(0) + "_" + langList.at(i) + ".ts");
    }
    return  tsFile.join(" ");
}

void Lupdate::createTs() {    

    if(filesModel->rowCount()-1 == 0)
        return;

    if(langList.length() == 0)
        return;

    translatorList.clear();

    QStringList arguments;
    for(int i = 0; i < filesModel->rowCount()-1; i++) {
        QModelIndex index = filesModel->index(i ,0);
        arguments.append(filesModel->data(index, Qt::UserRole+1).toString());
    }

    arguments.append("-ts");

    if(!updateFile.isEmpty()) {
        translatorList = updateFile;
        arguments.append(updateFile);
    } else {
        QString url = filesModel->data(filesModel->index(0 ,0), Qt::UserRole+1).toString();
        QStringList list;
        if(url.split(" ").length() > 0) {
            list = url.split(" ").at(0).split("/");
        } else {
            list = url.split("/");
        }
        list.removeLast();
        if(!tsFile.isEmpty()) {
            translatorList = getStringFileTs(list.join("/")+"/" + tsFile + ".qml");
            arguments.append(translatorList);
        } else {
            translatorList = getStringFileTs(list.join("/")+"/main.qml");
            arguments.append(translatorList);
        }
    }

    QString program = Worker::getInstance()->compilerPath() + "/bin/lupdate " + arguments.join(" ");

    QFile *file = Worker::prepareBatFile();
    if(file) {
        file->write(program.toLocal8Bit());
        file->close();
        file->deleteLater();
        start("temp.bat");
    }
}

void Lupdate::runLinguist() {
    if(!translatorList.isEmpty()) {
        startDetached(Worker::getInstance()->compilerPath() + "/bin/linguist " + translatorList);
    } else  {
        startDetached(Worker::getInstance()->compilerPath() + "/bin/linguist");
    }
}

void Lupdate::slotFinished(int code) {
    if(code > 0) {
        emit newErrorData(readAllStandardError());
    } else {
        emit newOutputData("Done!");
    }
    Worker::removeBatFile();
}
