// Copyright (c) 2016 The Karbowanec developers
// Copyright (c) 2018-2019 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "PrivateKeysDialog.h"
#include "ui_privatekeysdialog.h"
#include <QClipboard>
#include <Common/Base58.h>
#include <Common/StringTools.h>
#include "CurrencyAdapter.h"
#include "WalletAdapter.h"

namespace WalletGui {

PrivateKeysDialog::PrivateKeysDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::PrivateKeysDialog) {
  m_ui->setupUi(this);
  connect(&WalletAdapter::instance(), &WalletAdapter::walletInitCompletedSignal, this, &PrivateKeysDialog::walletOpened, Qt::QueuedConnection);
  connect(&WalletAdapter::instance(), &WalletAdapter::walletCloseCompletedSignal, this, &PrivateKeysDialog::walletClosed, Qt::QueuedConnection);
}

PrivateKeysDialog::~PrivateKeysDialog() {
}

void PrivateKeysDialog::walletOpened() {
  CryptoNote::AccountKeys keys;
  WalletAdapter::instance().getAccountKeys(keys);

  QString privateKeys = QString::fromStdString(Tools::Base58::encode_addr(CurrencyAdapter::instance().getAddressPrefix(),
    std::string(reinterpret_cast<char*>(&keys), sizeof(keys))));

  // m_ui->m_privateKeyEdit->setText(privateKeys);
  //m_ui->m_qrLabel->showQRCode(privateKeys);

  QString spendSecretKey = QString::fromStdString(Common::podToHex(keys.spendSecretKey));
  QString viewSecretKey = QString::fromStdString(Common::podToHex(keys.viewSecretKey));

  m_ui->m_spendSecretKeyEdit->setText(spendSecretKey);
  m_ui->m_viewSecretKeyEdit->setText(viewSecretKey);

  // make private key fields have no border
  m_ui->m_spendSecretKeyEdit->setStyleSheet("QLineEdit { qproperty-frame: false }");
  m_ui->m_viewSecretKeyEdit->setStyleSheet("QLineEdit { qproperty-frame: false }");
  
  // make private key fields have a transparent background
  m_ui->m_spendSecretKeyEdit->setStyleSheet("background:transparent;");
  m_ui->m_viewSecretKeyEdit->setStyleSheet("background:transparent;");

  // make private key fields' cursor an I beam
  m_ui->m_spendSecretKeyEdit->setCursor(Qt::IBeamCursor);
  m_ui->m_viewSecretKeyEdit->setCursor(Qt::IBeamCursor);

}

void PrivateKeysDialog::walletClosed() {
  m_ui->m_spendSecretKeyEdit->clear();
  m_ui->m_viewSecretKeyEdit->clear();
  //m_ui->m_qrLabel->clear();
}

// void PrivateKeysDialog::copyKey() {
  // QApplication::clipboard()->setText(m_ui->m_privateKeyEdit->toPlainText());
// }

}
