#include "toolsfabric.h"



AbstractTool *ToolsFabric::createTool(QString type, QJsonObject settings)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<ToolsFabric::Tools>();

    switch (metaEnum.keyToValue(type.toUpper().toLatin1())) {
    case BUILDER: {
        return new class Builder(settings);
    }
    case WINDEPLOYQT: {
        return new class Windeployqt(settings);
    }
    case FINSTALLER: {
        return new class FInstaller(settings);
    }
    case QMLDIR: {
        return new class QmlDir(settings);
    }
    case LUPDATE: {
        return new class Lupdate(settings);
    }
    }
    return nullptr;
}
