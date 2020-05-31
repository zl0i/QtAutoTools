#ifndef CONSOLE_H
#define CONSOLE_H

#include <QObject>
#include <QJsonArray>
#include "abstracttool.h"

class Console : public AbstractTool
{
    Q_OBJECT
public:
    Console(QJsonObject settings, QObject *parent = nullptr);

    void configFromJson(QJsonObject) override;
    bool exec() override;
    void cancelExec() override;

private:
    QStringList comands;
    bool sequentially;
};

#endif // CONSOLE_H
