#include "settingsreader.h"

#include "formatexception.h"
#include "ioexception.h"
#include "keyexception.h"

#include <QFile>
#include <QTextStream>

namespace Interface
{

SettingsReader SettingsReader::READER;
const QString SettingsReader::SETTINGS_PATH("Assets/settings.dat");
const QRegularExpression SettingsReader::FORMAT("(\\w+):(\\w+)\\s*");

void SettingsReader::readSettings()
{
    QString contents;
    QFile f(SETTINGS_PATH);
    if (f.open(QFile::ReadOnly))
    {
        QTextStream s(&f);
        contents = s.readAll();
        f.close();
    }
    else
    {
        throw IoException(QString("could not read file ") + SETTINGS_PATH);
    }

    QRegularExpressionMatchIterator iter = FORMAT.globalMatch(contents);
    int end = -1;
    while (iter.hasNext())
    {
        QRegularExpressionMatch match = iter.next();
        settings_[match.captured(1)] = match.captured(2);
        end = match.capturedEnd();
    }
    if (end != contents.size())
    {
        throw FormatException(QString("cannot parse settings file ") + SETTINGS_PATH);
    }

    read_ = true;
}

QString SettingsReader::getValue(QString key)
{
    if (!read_)
    {
        readSettings();
    }

    auto iter = settings_.find(key);
    if (iter != settings_.end())
    {
        return iter->second;
    }
    else
    {
        throw KeyException(QString("unknown setting key: ") + key);
    }
}

SettingsReader::SettingsReader():
    read_(false)
{
}

} // Interface
