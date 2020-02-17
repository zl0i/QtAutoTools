#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QSettings>

class Worker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString qtPath READ qtPath WRITE setQtPath NOTIFY qtPathChanged)
    Q_PROPERTY(QString compilerPath READ compilerPath WRITE setCompilerPath NOTIFY compilerPathChanged)
    Q_PROPERTY(QString compilerToolPath READ compilerToolPath WRITE setCompilerToolPath NOTIFY compilerToolPathChanged)



    //Q_PROPERTY(QStringList installerVersionList READ installerVersionList NOTIFY installerVersionListChanged)
    //Q_PROPERTY(QString installerVersion READ installerVersion WRITE setInstallerVersion NOTIFY installerVersionChanged)


public:
    static Worker* getInstance() {
        static Worker *p_instance;        
        if(!p_instance)
            p_instance = new Worker();
        return p_instance;
    }

    QString qtPath();
    void setQtPath(QString);

    QString compilerPath();
    void setCompilerPath(QString);

    QString compilerToolPath();
    void setCompilerToolPath(QString);

    Q_INVOKABLE void clearAllSettings();    


private:
    QSettings *settings = new QSettings;

    //QString m_language = settings->value("global/language", "en").toString();
    QString m_qtPath = settings->value("global/qtPath", "").toString();
    QString m_compilerPath = settings->value("global/compilerPath", "").toString();
    QString m_compilerToolePath = settings->value("global/compilerToolPath", "").toString();
    //QStringList m_installerVersionList = settings->value("global/installerVersionList", "").toStringList();


signals:

    void qtPathChanged();
    void compilerPathChanged();
    void compilerToolPathChanged();





public slots:
};



#endif // WORKER_H
