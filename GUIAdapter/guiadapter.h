#ifndef GUIADAPTER_H
#define GUIADAPTER_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QLocale>
#include "BaseAdapter/baseadapter.h"
#include "guitranslator.h"

class GUIAdapter : public BaseAdapter
{
    Q_OBJECT
public:
    explicit GUIAdapter(SettingsStorage *storage, QObject *parent = nullptr);

    void start();

private:
    QQmlApplicationEngine engine;
    GUITranslator translator;

signals:

public slots:
    void setLanguage(QString);

};

#endif // GUIADAPTER_H
