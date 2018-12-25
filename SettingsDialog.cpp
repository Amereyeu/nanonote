#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"

#include <QSpinBox>

#include "Settings.h"

SettingsDialog::SettingsDialog(Settings *settings, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
    , mSettings(settings)
{
    ui->setupUi(this);
    ui->fontComboBox->setFont(mSettings->font());
    ui->fontSizeSpinBox->setValue(mSettings->font().pixelSize());

    connect(ui->fontComboBox, &QFontComboBox::currentFontChanged, mSettings, &Settings::setFont);
    connect(ui->fontSizeSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int value) {
       auto font = mSettings->font();
       font.setPixelSize(value);
       mSettings->setFont(font);
    });
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
