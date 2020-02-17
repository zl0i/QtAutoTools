#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include <QObject>
#include "BaseAdapter/settingsstorage.h"

class FileStorage : public SettingsStorage
{
    Q_OBJECT
public:
    explicit FileStorage(QObject *parent = nullptr);

signals:

};

#endif // FILESTORAGE_H
