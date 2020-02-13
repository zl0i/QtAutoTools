#include "toolsfabric.h"



AbstractTool *ToolsFabric::createTool(QString type)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<ToolsFabric::Tools>();

    switch (metaEnum.keyToValue(type.toLatin1())) {
    case Builder: {
        return new class Builder();
    }
    case Windeployqt: {
        return new class Windeployqt();
    }
    case Installer: {
        return new class FInstaller();
    }
    case Qmldir: {
        return new class QmlDir();
    }
    case Lupdate: {
        return new class Lupdate();
    }
    }
    return nullptr;
}
