#ifndef BUILDER_H
#define BUILDER_H

#include <QObject>
#include <abstracttool.h>

class Builder : public QObject
{
    Q_OBJECT
public:
    explicit Builder(QObject *parent = nullptr);

signals:

};

#endif // BUILDER_H
