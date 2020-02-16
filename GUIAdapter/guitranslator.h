#ifndef GUITRANSLATOR_H
#define GUITRANSLATOR_H

#include <QObject>
#include <QGuiApplication>
#include <QTranslator>

class GUITranslator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)

public:
    explicit GUITranslator(QObject *parent = nullptr);

    QString language();
    void setLanguage(QString);
    void setLanguage();

private:
    QTranslator translator;

    QString m_language;

signals:
    void languageChanged();
    void retranslate();

};

#endif // GUITRANSLATOR_H
