#include "guitranslator.h"

GUITranslator::GUITranslator(QObject *parent) : QObject(parent)
{
    m_language = "ru_RU";
}

QString GUITranslator::language()
{
    return m_language;
}

void GUITranslator::setLanguage(QString ln)
{
    m_language = ln;
    if(ln == "ru_RU") {
        QCoreApplication::removeTranslator(&translator);
    } else {
        translator.load(":translation/qm_files/QtAutoTools_" + m_language);
        QCoreApplication::installTranslator(&translator);
    }
    emit retranslate();
}

void GUITranslator::setLanguage()
{
    if(m_language == "ru_RU") {
        QCoreApplication::removeTranslator(&translator);
    } else {
        bool loading = translator.load(":translation/qm_files/QtAutoTools_" + m_language);
        if(loading)
            QCoreApplication::installTranslator(&translator);
    }
    emit retranslate();
}
