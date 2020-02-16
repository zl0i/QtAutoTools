#include "toolsdetector.h"

ToolsDetector::ToolsDetector(QObject *parent) : QObject(parent)
{
    detectTools.insert("windeployqt", true);
    detectTools.insert("androiddeployqt", false);
    detectTools.insert("qtInstallerFramework", true);
    detectTools.insert("lupdate", true);
    detectTools.insert("git", false);
    detectTools.insert("docker", false);
}

void ToolsDetector::detect(QString qtpath)
{
    if(QDir(qtpath).exists()) {
        qtPath = qtpath;
        detectQtVersion();
        detectIntallerFramework();
        detectCompiler();
        detectOtherTools();
    }
}


void ToolsDetector::detectQtVersion()
{
    QDir qtDir(qtPath);
    versionsDirs = qtDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    versionsDirs = versionsDirs.filter(QRegExp("[\\d]{1}[\\.]{1}[\\d]{1,2}[\\.]{1}[\\d]{1,2}"));
    emit qtVersionChanged();
    if(versionsDirs.size() > 0)
        detectProfile(versionsDirs.at(0));

}

void ToolsDetector::detectProfile(QString versionDir)
{
    QDir qtVersionDir(qtPath + "/" + versionDir);
    qtProfile = qtVersionDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    qtProfile.removeOne("Src");
    emit qtProfileChanged();
}

void ToolsDetector::setProfile(QString path)
{
    //ToolsSaver::getInstance()->setProfilePath(path);
}

void ToolsDetector::setCompiler(QString path)
{
    //ToolsSaver::getInstance()->setCompilerPath(path);
}

void ToolsDetector::setInstallerFramework(QString path)
{
   // ToolsSaver::getInstance()->setInstallerFramework(path);
}

void ToolsDetector::detectCompiler()
{
    QDir qtDir(qtPath + "/Tools");
    if(qtDir.exists()) {
        compilerList = qtDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).filter(QRegExp("(mingw)(\\d+)(_)(\\d+)"));
        emit compilerListChanged();
    }
}

void ToolsDetector::detectIntallerFramework()
{
     QDir qtDir(qtPath + "/Tools/QtInstallerFramework");
     if(qtDir.exists()) {
         installerList = qtDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot).filter(QRegExp("\\d[.]\\d"));
         emit installerVerisonChanged();
     }
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

void ToolsDetector::checkAllTools()
{
    //QFile file(ToolsSaver::getInstance().)
}
