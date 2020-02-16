#include "guitranslator.h"

GUITranslator::GUITranslator(QObject *parent) : QObject(parent)
{
    m_language = "ru";
}

QString GUITranslator::language()
{
    return m_language;
}

void GUITranslator::setLanguage(QString ln)
{
    m_language = ln;
    //settings->setValue("global/language", m_language);

    if(ln == "ru") {
        QCoreApplication::removeTranslator(&translator);
    } else {
        translator.load(":translation/qm_files/QtAutoTools_" + ln);
        QCoreApplication::installTranslator(&translator);
    }
    emit retranslate();
}

void GUITranslator::setLanguage()
{
    if(m_language == "ru") {
        QCoreApplication::removeTranslator(&translator);
    } else {
        translator.load(":translation/qm_files/QtAutoTools_" + m_language);
        QCoreApplication::installTranslator(&translator);
    }
    emit retranslate();
}
