#include "Util.h"

#include <QDebug>
#include <QSettings>
#include <QDir>
#include <QCoreApplication>

Util::Util()
{

}

void Util::setAutorun(bool flag)
{
    if (flag) {
        QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settings.setValue("MidiTool", QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
        settings.sync();
    }
    else {
        QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
        settings.remove("MidiTool");
        settings.sync();
    }
}

bool Util::isAutorun()
{
    QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    QString value = settings.value("MidiTool", "").toString();
    return !value.isEmpty();
}
