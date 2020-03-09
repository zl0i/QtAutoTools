#include "toolsdetector.h"

ToolsDetector::ToolsDetector() : QObject()
{

}

void ToolsDetector::setSettingsStorage(SettingsStorage *st)
{
    storage = st;
}

void ToolsDetector::detect(QString qtpath)
{
    if(qtpath.isEmpty()) {
        if(storage) {
            QJsonObject settings = storage->getUserSettings("detector");
            qtpath = settings.value("qtPath").toString();
        }
    }

    if(QDir(qtpath).exists()) {
        qtPath = qtpath;
        detectTools.insert("qtPath", qtpath);
        QStringList qtVersions = detectQtVersion();
        detectTools.insert("qtVersions", convertToJArray(qtVersions));
        QJsonObject profiles;
        QJsonObject mkSpecs;
        for(int i = 0; i < qtVersions.size(); ++i) {
            QStringList profileList = detectProfile(qtPath + QDir::separator() + qtVersions.at(i));
            profiles.insert(qtVersions.at(i), convertToJArray(profileList));

            for(int j = 0; j < profileList.size(); ++j) {
                QStringList mkspecsList = detectMkspecs(qtPath + QDir::separator() + qtVersions.at(i) + QDir::separator() + profileList.at(j));
                mkSpecs.insert(qtVersions.at(i)+"_"+profileList.at(j), convertToJArray(mkspecsList));
            }
        }
        detectTools.insert("profiles", profiles);
        detectTools.insert("mkspecs", mkSpecs);

        detectTools.insert("finstallerVersions", convertToJArray(detectIntallerFramework()));
        detectTools.insert("compilers", convertToJArray(detectCompilers()));

        //detectOtherTools();
        if(storage)
            storage->saveUserSettings("detector", ToolsDetector::instanse()->getDetectTools());

    }
}

bool ToolsDetector::checkTools()
{
    return true;
}


QStringList ToolsDetector::detectQtVersion()
{
    QDir qtDir(qtPath);
    QStringList versionsDirs = qtDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    versionsDirs = versionsDirs.filter(QRegExp("[\\d]{1}[\\.]{1}[\\d]{1,2}[\\.]{1}[\\d]{1,2}"));
    return  versionsDirs;
}

QStringList ToolsDetector::detectProfile(QString dir)
{
    QDir qtVersionDir(dir);
    QStringList qtProfile = qtVersionDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    qtProfile.removeOne("Src");
    return qtProfile;
}

QStringList ToolsDetector::detectMkspecs(QString path)
{
    QDir dir(path + QDir::separator() + "mkspecs");
    if(dir.exists()) {
        QStringList specList = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
        return specList;
    }
    return QStringList {};
}

QStringList ToolsDetector::detectCompilers()
{
    QDir qtDir(qtPath + "/Tools");
    if(qtDir.exists()) {
        QStringList compilerList = qtDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).filter(QRegExp("(mingw)(\\d+)(_)(\\d+)"));
        return  compilerList;
    }
    return QStringList {};

}

QStringList ToolsDetector::detectIntallerFramework()
{
    QDir qtDir(qtPath + "/Tools/QtInstallerFramework");
    if(qtDir.exists()) {
        QStringList installerList = qtDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).filter(QRegExp("\\d[.]\\d"));
        return  installerList;
    }
    return  QStringList {};
}

void ToolsDetector::detectOtherTools()
{
    QProcess checker;
    checker.start("git --version");
    checker.waitForFinished();
    QString output = checker.readAllStandardOutput();
    qDebug() << "git:" <<output.contains("git version");

    checker.start("docker -v");
    checker.waitForFinished();
    output = checker.readAllStandardOutput();
    qDebug() << "docker:" << output.contains("docker version");
}

QJsonArray ToolsDetector::convertToJArray(QStringList list)
{
    QJsonArray array;
    for(int i = 0; i < list.size(); ++i) {
        array.append(list.at(i));
    }
    return array;
}
