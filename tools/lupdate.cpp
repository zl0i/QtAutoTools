#include "./lupdate.h"

Lupdate::Lupdate(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{
    QHash<int, QByteArray> hash;
    hash.insert(Qt::UserRole+1, "file");
    filesModel->setItemRoleNames(hash);
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

void Lupdate::runLinguist() {
    if(!translatorList.isEmpty()) {
        process->startDetached(pathFabric.linguistPath() + " " + translatorList);
    } else  {
        process->startDetached(pathFabric.linguistPath());
    }
}

void Lupdate::configFromJson(QJsonObject obj)
{
    filesModel->clear();
    QJsonArray jfiles = obj.value("files").toArray();
    filesModel->insertColumn(0);
    filesModel->insertRows(0, jfiles.size());
    for(int i = 0; i < jfiles.size(); ++i) {
        QString file = jfiles.at(i).toString();
        filesModel->setData(filesModel->index(i, 0), file, Qt::UserRole+1);
    }

    langList = obj.value("language").toString().split(" ", QString::SkipEmptyParts);
    tsFile = obj.value("translatorName").toString();
    updateFile = obj.value("updateFiles").toString();
    runQtLinguist = obj.value("runQtLinguist").toBool();
}

void Lupdate::run()
{
    if(filesModel->rowCount() == 0) {
        if(runQtLinguist)
            runLinguist();
        else
            return;
    }

    if(langList.length() == 0 && updateFile.isEmpty()) {
        if(runQtLinguist)
            runLinguist();
        else
            return;
    }

    translatorList.clear();

    QStringList arguments;
    for(int i = 0; i < filesModel->rowCount(); i++) {
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

    QString program = pathFabric.lupdatePath() + " " + arguments.join(" ");
    QFile *file = prepareBatFile(true);
    if(file) {
        file->write(program.toLocal8Bit());
        file->close();
        file->deleteLater();
        process->start(file->fileName());
    }
}

void Lupdate::successFinished()
{
    if(runQtLinguist) {
        emit newOutputData("Run QtLinguist...\r\n");
        runLinguist();
    }
}


