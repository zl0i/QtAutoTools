#include "./qmldir.h"

QmlDir::QmlDir(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{

    QHash<int, QByteArray> hash;
    hash.insert(QmlDir::Type, "type");
    hash.insert(QmlDir::Name, "name");
    hash.insert(QmlDir::Version, "version");
    hash.insert(QmlDir::File, "file");
    filesModel->setItemRoleNames(hash);
}

void QmlDir::configFromJson(QJsonObject obj)
{
    filesModel->clear();
    QJsonArray files = obj.value("files").toArray();
    filesModel->insertColumn(0);
    filesModel->insertRows(0, files.size());
    for(int i = 0; i < files.size(); i++) {
        QJsonObject file = files.at(i).toObject();

        QModelIndex index = filesModel->index(i, 0);

        filesModel->setData(index, file.value("type"), QmlDir::Type);
        filesModel->setData(index, file.value("name"), QmlDir::Name);
        filesModel->setData(index, file.value("version"), QmlDir::Version);
        filesModel->setData(index, file.value("path"), QmlDir::File);

    }
    path = obj.value("path").toString();
    createTypes = obj.value("qmltypes").toBool();
    supportDesigner = obj.value("supportDesigner").toBool();
}

bool QmlDir::exec()
{
    if(path.isEmpty()) {
        emit newErrorData("Path is empty.");
        return false;
    }

    emit newOutputData("Create qmldir file \r\n");

    QFile file(path + "/qmldir");

    if(file.exists())
        file.remove();

    if(file.open(QIODevice::ReadWrite)) {
        emit newOutputData("Write to qmldir file \r\n");
        QTextStream stream(&file);
        QString nameModule = "module " + path.split("/").last() + "\r\n";
        stream << nameModule;
        for(int i = 0; i < filesModel->rowCount(); i++) {
            QModelIndex index = filesModel->index(i, 0);
            stream << buildString(index);
        }

        if(supportDesigner)
            stream << "designersupported\n";

        if(createTypes) {
            QStringList arguments;

            arguments.append(path.split("/").last());
            arguments.append(getMinimumVersion());
            QStringList pathToModule = path.split("/");
            pathToModule.removeLast();
            arguments.append(pathToModule.join("/"));
            arguments.append(">");
            arguments.append(path + "/" + path.split("/").last().toLower() + ".qmltypes");

            QString program = pathFabric.qmlplugindumpPath() + " " + arguments.join(" ");
            emit newOutputData("Create qmltypes.\r\n");

            if(execCommand(program)) {
                stream << "typeinfo " + path.split("/").last().toLower() + ".qmltypes\r\n";
                return true;
            } else {
                emit newErrorData("File qmltypes is not created.\r\n");
            }
        }
        file.close();
        emit newOutputData("Ready!\r\n");
        return true;
    } else {
        emit newErrorData("File not open\r\n");
        return false;
    }
}

void QmlDir::cancelExec()
{
    QFile::remove(path + "/qmldir");
    if(createTypes)
        QFile::remove(path + "/" + path.split("/").last().toLower() + ".qmltypes");
}


QString QmlDir::getFileName(QString file)
{
    QStringList list = file.split(".");
    if(list.length() > 0) {
        return list.at(0);
    }
    return "";
}


QString QmlDir::getExtension(QString file)
{
    QStringList list = file.split(".");
    if(list.length() == 2) {
        return list.at(1);
    }
    return "";

}

QString QmlDir::buildString(QModelIndex index)
{
    QString line;
    if(!filesModel->data(index, QmlDir::Type).toString().isEmpty()) {
        line += filesModel->data(index, QmlDir::Type).toString() + " ";
    }
    if(!filesModel->data(index, QmlDir::Name).toString().isEmpty()) {
        line += filesModel->data(index, QmlDir::Name).toString() + " ";
    } else {
        emit newErrorData("Empty name\r\n");
    }
    if(!filesModel->data(index, QmlDir::Version).toString().isEmpty()) {
        line += filesModel->data(index, QmlDir::Version).toString() + " ";
    }
    if(!filesModel->data(index, QmlDir::File).toString().isEmpty()) {
        line += filesModel->data(index, QmlDir::File).toString().split("/").last();
    } else {
        emit newErrorData("Empty file name\r\n");
    }
    return line + "\r\n";
}

QString QmlDir::getMinimumVersion()
{
    int major = 100;
    int minor = 100;
    for(int i = 0; i < filesModel->rowCount(); i++) {
        QModelIndex index = filesModel->index(i, 0);
        if(filesModel->data(index, QmlDir::Type).toString() == "internal")
            continue;

        QStringList version = filesModel->data(index, QmlDir::Version).toString().split(".");
        if(major > version.at(0).toInt()) {
            major = version.at(0).toInt();
            minor = version.at(1).toInt();
        } else if (major == version.at(0).toInt() && minor > version.at(1).toInt()) {
            minor = version.at(1).toInt();
        }
    }
    return QString::number(major) + "." + QString::number(minor);
}
