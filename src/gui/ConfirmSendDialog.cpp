// Copyright (c) 2016 The Karbowanec developers
// Copyright (c) 2019 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "CurrencyAdapter.h"
#include "ConfirmSendDialog.h"

#include "ui_confirmsenddialog.h"

namespace WalletGui {

ConfirmSendDialog::ConfirmSendDialog(QWidget* _parent) : QDialog(_parent), m_ui(new Ui::ConfirmSendDialog) {
  m_ui->setupUi(this);
}

ConfirmSendDialog::~ConfirmSendDialog() {
}

void ConfirmSendDialog::showPaymentDetails(quint64 _total, QString _address) {
    QString confirmLabel = m_ui->m_confirmLabel->text();
    m_ui->m_confirmLabel->setText(confirmLabel
      .arg(CurrencyAdapter::instance().formatAmount(_total))
      .arg(_address)
    );
}

}
