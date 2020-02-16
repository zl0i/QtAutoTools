#include "guiadapter.h"

GUIAdapter::GUIAdapter(QObject *parent) : BaseAdapter(parent)
{
    engine.addImportPath(":/GUIAdapter/qml");
    engine.rootContext()->setContextProperty("_worker", Worker::getInstance());
    engine.rootContext()->setContextProperty("_guiAdapter", this);

    /*qmlRegisterType<Builder>("AutoTools", 1, 0, "Builder");
    qmlRegisterType<Windeployqt>("AutoTools", 1, 0, "Windeployqt");
    qmlRegisterType<QmlDir>("AutoTools", 1, 0, "QmlDir");
    qmlRegisterType<Lupdate>("AutoTools", 1, 0, "Lupdate");
    qmlRegisterType<FInstaller>("AutoTools", 1, 0, "FInstaller");*/

    connect(&translator, &GUITranslator::retranslate, &engine, &QQmlEngine::retranslate);
}

void GUIAdapter::start()
{
    engine.load("qrc:/GUIAdapter/main.qml");
    translator.setLanguage();
}
