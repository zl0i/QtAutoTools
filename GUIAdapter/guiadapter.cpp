#include "guiadapter.h"

GUIAdapter::GUIAdapter(SettingsStorage *storage, QObject *parent) : BaseAdapter(storage, parent)
{
    engine.addImportPath(":/GUIAdapter/qml");
    engine.rootContext()->setContextProperty("_guiAdapter", this);

    connect(&translator, &GUITranslator::retranslate, &engine, &QQmlEngine::retranslate);
}

void GUIAdapter::start()
{
    engine.load("qrc:/GUIAdapter/main.qml");
    translator.setLanguage();
}
