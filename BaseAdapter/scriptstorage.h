#ifndef SCRIPTSTORAGE_H
#define SCRIPTSTORAGE_H

#include <QObject>

class ScriptStorage : public QObject
{
    Q_OBJECT
public:
    explicit ScriptStorage(QObject *parent = nullptr);

signals:

};

#endif // SCRIPTSTORAGE_H
