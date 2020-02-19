#include "guiadapter.h"

GUIAdapter::GUIAdapter(SettingsStorage *storage, QObject *parent) : BaseAdapter(storage, parent)
{
    engine.addImportPath(":/GUIAdapter/qml");
    engine.rootContext()->setContextProperty("_guiAdapter", this);

    connect(&translator, &GUITranslator::retranslate, &engine, &QQmlEngine::retranslate);
    //qDebug() << QLocale::system().name();
}

void GUIAdapter::start()
{
    QString lg = storage()->getCustomValue("language").toString();
    translator.setLanguage(lg);
    engine.load("qrc:/GUIAdapter/main.qml");    
}

void GUIAdapter::setLanguage(QString lg)
{
    storage()->setCustomValue("language", lg);
    translator.setLanguage(lg);
}
