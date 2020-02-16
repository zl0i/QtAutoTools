#ifndef GUIADAPTER_H
#define GUIADAPTER_H

#include <QObject>
#include <QQmlContext>
#include <QQmlApplicationEngine>
#include "BaseAdapter/baseadapter.h"
#include "guitranslator.h"
#include "worker.h"

class GUIAdapter : public BaseAdapter
{
    Q_OBJECT
public:
    explicit GUIAdapter(QObject *parent = nullptr);

    void start();

private:
    QQmlApplicationEngine engine;
    GUITranslator translator;

signals:

};

#endif // GUIADAPTER_H
