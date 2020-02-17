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

    static AbstractTool *createTool(QString type);

    enum Tools {
        Builder = 0,
        Windeployqt,
        Installer,
        Qmldir,
        Lupdate
    };
    Q_ENUM(Tools)

private:

signals:

};

#endif // TOOLSFABRIC_H
