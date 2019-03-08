// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2015-2016 XDN developers
// Copyright (c) 2016-2018 The Karbowanec developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QApplication>
#include <QFileDialog>
#include <QStandardPaths>
#include "CreateWalletDialog.h"
#include "ui_createwalletdialog.h"

namespace WalletGui {

CreateWalletDialog::CreateWalletDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::CreateWalletDialog) {
  m_ui->setupUi(this);
  m_ui->m_errorLabel->setText("");
}

CreateWalletDialog::~CreateWalletDialog() {
}

QString CreateWalletDialog::getPasswordString() const {
  return m_ui->m_password->text().trimmed();
}

QString CreateWalletDialog::getPasswordConfirmString() const {
  return m_ui->m_passwordConfirm->text().trimmed();
}

QString CreateWalletDialog::getFilePath() const {
  QString defaultDirectory = QDir::currentPath();
  QString walletName = m_ui->m_walletName->text().trimmed();
  return QDir(defaultDirectory).filePath(walletName);
}

void CreateWalletDialog::checkPassword(const QString& _password) {

  bool passwordIsConfirmed = false;

  if (!m_ui->m_password->text().trimmed().isEmpty() && !m_ui->m_passwordConfirm->text().trimmed().isEmpty())
  {
    passwordIsConfirmed = !m_ui->m_password->text().compare(m_ui->m_passwordConfirm->text());
    m_ui->m_errorLabel->setText(passwordIsConfirmed ? "" : tr("Password not match"));
  }
  else
  {
    m_ui->m_errorLabel->setText("");
  }

  m_ui->m_okButton->setEnabled(passwordIsConfirmed);
}

}
