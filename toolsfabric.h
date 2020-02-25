#ifndef TOOLSFABRIC_H
#define TOOLSFABRIC_H

#include <QObject>
#include <QMetaEnum>
#include "abstracttool.h"
#include "tools/builder.h"
#include "tools/finstaller.h"
#include "tools/windeployqt.h"
#include "tools/qmldir.h"
#include "tools/lupdate.h"

class ToolsFabric : public QObject
{
    Q_OBJECT
public:

    static AbstractTool *createTool(QString type, QJsonObject settings);

    enum Tools {
        BUILDER = 0,
        WINDEPLOYQT,
        FINSTALLER,
        QMLDIR,
        LUPDATE
    };
    Q_ENUM(Tools)

private:

signals:

};

#endif // TOOLSFABRIC_H
