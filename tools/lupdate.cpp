#include "./lupdate.h"

Lupdate::Lupdate(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{
    QHash<int, QByteArray> hash;
    hash.insert(Qt::UserRole+1, "file");
    filesModel->setItemRoleNames(hash);
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
        execCommand(pathFabric.linguistPath() + " " + translatorList, true);
    } else  {
        execCommand(pathFabric.linguistPath(), true);
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

bool Lupdate::exec()
{
    if(filesModel->rowCount() == 0) {
        if(runQtLinguist) {
            emit newOutputData("Run QtLinguist...\r\n");
            runLinguist();
            return true;
        }
        else {
            emit newErrorData("Files is not selected.");
            return false;
        }
    }

    if(langList.length() == 0 && updateFile.isEmpty()) {
        if(runQtLinguist) {
            emit newOutputData("Run QtLinguist...\r\n");
            runLinguist();
            return true;
        }
        else {
            emit newErrorData("Language is not selected");
            return false;
        }
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

    if(execCommand(program)) {
        if(runQtLinguist) {
            emit newOutputData("Run QtLinguist...\r\n");
            runLinguist();
        }
        return true;
    }
    return false;
}

void Lupdate::cancelExec()
{
    QFile::remove("");
}
