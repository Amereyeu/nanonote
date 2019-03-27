#include "Settings.h"

#include <QFontDatabase>
#include <QSettings>
#include <QStandardPaths>

Settings::Settings(QObject *parent) : BaseSettings(parent)
{
}

QString Settings::notePath()
{
    QString dirPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return dirPath + "/nanonote.txt";
}

void Settings::load()
{
    QSettings settings;
    QRect geometry = settings.value("geometry").toRect();
    if (geometry.isValid()) {
        setGeometry(geometry);
    }

    QVariant fontVariant = settings.value("font");
    if (fontVariant.canConvert<QFont>()) {
        setFont(fontVariant.value<QFont>());
    } else {
        setFont(defaultFont());
    }

    setAlwaysOnTop(settings.value("alwaysOnTop").toBool());
}

void Settings::save()
{
    QSettings settings;
    settings.setValue("geometry", geometry());
    settings.setValue("font", font());
    settings.setValue("alwaysOnTop", alwaysOnTop());
}

QFont Settings::defaultFont() const
{
    return QFontDatabase::systemFont(QFontDatabase::FixedFont);
}
