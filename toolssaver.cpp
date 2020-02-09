#include "toolssaver.h"



ToolsSaver::ToolsSaver()
{

}

void ToolsSaver::setQtPath(QString path)
{
    settings.setValue("qtPath", path);
}

void ToolsSaver::setProfilePath(QString path)
{
    settings.setValue("profilePath", path);
}

void ToolsSaver::setCompilerPath(QString path)
{
    settings.setValue("compilerPath", path);
}

void ToolsSaver::setInstallerFramework(QString path)
{
    settings.setValue("installerFrameworkPath", path);
}

void ToolsSaver::setQMakePath(QString path)
{
    settings.setValue("qmakePath", path);
}

void ToolsSaver::setCMakePath(QString path)
{
    settings.setValue("cmakePath", path);
}
