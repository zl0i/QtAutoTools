#ifndef TOOLSSAVER_H
#define TOOLSSAVER_H

#include <QObject>
#include <QSettings>

class ToolsSaver : public QObject
{
    Q_OBJECT
public:   

    static ToolsSaver* getInstance() {
        static ToolsSaver *p_instance;
        if(!p_instance)
            p_instance = new ToolsSaver();
        return p_instance;
    }

    void setQtPath(QString);
    void setProfilePath(QString);
    void setCompilerPath(QString);
    void setInstallerFramework(QString);
    void setQMakePath(QString);
    void setCMakePath(QString);

    QString windeployqtPath();
    QString compilerMakePath();
    QString qmakePath();


private:
     ToolsSaver();

     QSettings settings;



signals:

};

#endif // TOOLSSAVER_H
