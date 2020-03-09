#ifndef CONSOLEADAPTER_H
#define CONSOLEADAPTER_H

#include <QObject>
#include "BaseAdapter/baseadapter.h"

class ConsoleAdapter : public BaseAdapter
{
    Q_OBJECT
public:
    explicit ConsoleAdapter(SettingsStorage *storage, QObject *parent = nullptr);

    void start() override;

};

#endif // CONSOLEADAPTER_H
