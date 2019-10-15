#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QDebug>
#include <QSettings>


class Worker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString qtPath READ qtPath WRITE setQtPath NOTIFY qtPathChanged)
    Q_PROPERTY(QString compl1Path READ compl1Path WRITE setCompl1Path NOTIFY compl1PathChanged)
    Q_PROPERTY(QString compl2Path READ compl2Path WRITE setCompl2Path NOTIFY compl2PathChanged)


public:
    static Worker* getInstance() {
        if(!p_instance)
            p_instance = new Worker();
        return p_instance;
    }

    QString qtPath();
    void setQtPath(QString);

    QString compl1Path();
    void setCompl1Path(QString);

    QString compl2Path();
    void setCompl2Path(QString);

    Q_INVOKABLE void clearAllSettings();

private:
    static Worker *p_instance;
    QSettings *settings = new QSettings;

    QString m_qtPath = settings->value("global/qtpath").toString();
    QString m_compl1Path = settings->value("global/compl1Path").toString();
    QString m_compl2Path = settings->value("global/compl2Path").toString();


signals:
    void qtPathChanged();
    void compl1PathChanged();
    void compl2PathChanged();

public slots:
};



#endif // WORKER_H
