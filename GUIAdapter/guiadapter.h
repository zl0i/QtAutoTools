#ifndef GUIADAPTER_H
#define GUIADAPTER_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QLocale>
#include "BaseAdapter/baseadapter.h"
#include "BaseAdapter/toolsdetector.h"
#include "guitranslator.h"

class GUIAdapter : public BaseAdapter
{
    Q_OBJECT

    Q_PROPERTY(QJsonObject settings READ getSettings WRITE setSettings NOTIFY settingsChanged)
    Q_PROPERTY(bool settingsExist READ getSettingsExist NOTIFY settingsExistChanged)

    Q_PROPERTY(ScriptStorage *scripts READ getScriptStorage NOTIFY scriptsChanged)


public:
    explicit GUIAdapter(SettingsStorage *storage, QObject *parent = nullptr);

    bool start() override;

    QJsonObject getSettings() { return settings; }
    void setSettings(QJsonObject obj) {  settings = obj; storage()->saveUserSettings("guiAdapter", settings); }
    ScriptStorage *getScriptStorage() { return &scriptStorage; }
    bool getSettingsExist() { return !settings.value("qtPath").toString().isEmpty(); }

    QJsonObject getDetectTools() { return  ToolsDetector::instanse()->getDetectTools(); }

    Q_INVOKABLE QJsonObject detectToolsByQtPath(QString);
    Q_INVOKABLE void clearAllSettings();



protected:
    bool isRunningTask(QObject *sender = nullptr) override;
    QJsonObject getUserSettings(QObject *sender = nullptr) override;

private:
    QQmlApplicationEngine engine;
    GUITranslator translator;
    QString taskName;

    QJsonObject settings;

signals:
    void startedTask();
    void newErrorDataTask(QByteArray line);
    void newOutputDataTask( QByteArray line);
    void finishedTask(int exitCode, int exitStatus);

    void settingsChanged();
    void settingsExistChanged();
    void detectToolsChanged();
    void scriptsChanged();

public slots:

    void started(QString name) override;
    void newErrorData(QString name, QByteArray line) override;
    void newOutputData(QString name, QByteArray line) override;
    void finished(QString name, int exitCode, int exitStatus) override;

    void kill() override;

    void setLanguage(QString);


};

#endif // GUIADAPTER_H
