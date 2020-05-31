#ifndef TOOLSFABRIC_H
#define TOOLSFABRIC_H

#include <QObject>
#include <QMetaEnum>
#include "itool.h"
#include "tools/builder.h"
#include "tools/finstaller.h"
#include "tools/windeployqt.h"
#include "tools/qmldir.h"
#include "tools/lupdate.h"
#include "tools/console.h"

class ToolsFabric : public QObject
{
    Q_OBJECT
public:

    static ITool *createTool(QString type, QJsonObject settings);

    enum Tools {
        BUILDER = 0,
        WINDEPLOYQT,
        FINSTALLER,
        QMLDIR,
        LUPDATE,
        CONSOLE
    };
    Q_ENUM(Tools)

private:

signals:

};

#endif // TOOLSFABRIC_H
