#ifndef SQLSTORAGE_H
#define SQLSTORAGE_H

#include <QObject>
#include "BaseAdapter/settingsstorage.h"

class SQLStorage : public SettingsStorage
{
    Q_OBJECT
public:
    explicit SQLStorage(QObject *parent = nullptr);

signals:

};

#endif // SQLSTORAGE_H
