// Copyright (c) 2016 The Karbowanec developers
// Copyright (c) 2018-2019 The Cash2 developers
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

void ConfirmSendDialog::showPaymentDetails(quint64 _amount, QString _address, quint64 _fee) {
    // QString confirmLabel = m_ui->m_confirmLabel->text();
    // m_ui->m_confirmLabel->setText(confirmLabel
      // .arg(CurrencyAdapter::instance().formatAmount(_amount))
      // .arg(_address)
    // );

    QString feeStr = CurrencyAdapter::instance().formatAmount(_fee);
    // Remove any number of trailing 0's
    feeStr.remove( QRegExp("0+$") );

    m_ui->m_amount->setText(CurrencyAdapter::instance().formatAmount(_amount));
    m_ui->m_address->setText(_address);
    m_ui->m_fee->setText(feeStr);
    m_ui->m_total->setText(CurrencyAdapter::instance().formatAmount(_amount + _fee));
}

}
