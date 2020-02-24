#include "./qmldir.h"

QmlDir::QmlDir(QJsonObject settings, QObject *parent) : AbstractTool(settings, parent)
{

    QHash<int, QByteArray> hash;
    //hash.insert(QmlDir::Extension, "extension");
    //hash.insert(QmlDir::Types, "types");
    hash.insert(QmlDir::Type, "type");
    hash.insert(QmlDir::Name, "name");
    hash.insert(QmlDir::Version, "version");
    hash.insert(QmlDir::File, "file");
    filesModel->setItemRoleNames(hash);
}


void QmlDir::setPath(QString path)
{
    this->path = path;

    filesModel->clear();

    QStringList filterList = {"*.qml", "*.js", "*.dll", "*.so", "*.h"};
    QStringList filesDir = QDir(path).entryList(filterList, QDir::Files, QDir::Name);

    filesModel->insertColumn(0);
    filesModel->insertRows(0, filesDir.size());
    for(int i = 0; i < filesDir.size(); i++) {
        QString ext = getExtension(filesDir.at(i));
        QModelIndex index = filesModel->index(i, 0);
        if(ext == "qml") {
            filesModel->setData(index, "", QmlDir::Type);
            filesModel->setData(index, getFileName(filesDir.at(i)), QmlDir::Name);
            filesModel->setData(index, "1.0", QmlDir::Version);
            filesModel->setData(index, filesDir.at(i), QmlDir::File);
        } else if (ext == "js") {
            filesModel->setData(index, "", QmlDir::Type);
            filesModel->setData(index, getFileName(filesDir.at(i)), QmlDir::Name);
            filesModel->setData(index, "1.0", QmlDir::Version);
            filesModel->setData(index, filesDir.at(i), QmlDir::File);
        } else if (ext == "dll" || ext == "so") {
            filesModel->setData(index, "plugin", QmlDir::Type);
            filesModel->setData(index, getFileName(filesDir.at(i)), QmlDir::Name);
            filesModel->setData(index, "", QmlDir::Version);
            filesModel->setData(index, "", QmlDir::File);
        } else if (ext == "h") {

        }
    }
}

void QmlDir::setCreateTypes(bool b)
{
    this->createTypes = b;
}

void QmlDir::setSupportDesigner(bool b)
{
    this->supportDesigner = b;
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

void QmlDir::run()
{
    if(path.isEmpty()) {
        emit finished(1, QProcess::CrashExit);
        return;
    }

    emit started();
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

            QString program =profilePath + "/bin/qmlplugindump " + arguments.join(" ");
            emit newOutputData("Starting " + program.toLocal8Bit()+ "\r\n");
            QFile *batFile = prepareBatFile(true);
            qDebug() << program;
            batFile->write(program.toLocal8Bit());
            batFile->close();
            batFile->deleteLater();
            process->start(batFile->fileName());

        } else {
            emit newOutputData("Ready!\r\n");
            emit finished(0, QProcess::NormalExit);
        }
        file.close();
    } else {
        emit newErrorData("File not open\r\n");
    }
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
    qDebug() << line;
    return line + "\r\n";
}

QString QmlDir::getMinimumVersion()
{
    int major = 100;
    int minor = 100;
    for(int i = 0; i < filesModel->rowCount(); i++) {
        QModelIndex index = filesModel->index(i, 0);
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

void QmlDir::slotFinished(int exitCode)
{
    removeBatFile();
    if(exitCode == 0) {
        emit newOutputData("Write typeinfo to qmldir\r\n");
        QFile file(path + "/qmldir");
        if(file.exists()) {
            if(file.open(QIODevice::Append)) {
                QString str = "typeinfo " + path.split("/").last().toLower() + ".qmltypes\r\n";
                file.write(str.toLocal8Bit());
                file.close();
            }
        }
        emit newOutputData("Ready!\r\n");
    }
    emit finished(process->exitCode(), process->exitStatus());
}


