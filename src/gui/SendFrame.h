// Copyright (c) 2011-2015 The Cryptonote developers
// Copyright (c) 2018-2019 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <QFrame>

#include <IWallet.h>
#include <IWalletLegacy.h>

namespace Ui {
  class SendFrame;
}

namespace WalletGui {

class TransferFrame;

class SendFrame : public QFrame {
  Q_OBJECT
  Q_DISABLE_COPY(SendFrame)

public:
  SendFrame(QWidget* _parent);
  ~SendFrame();

private:
  QScopedPointer<Ui::SendFrame> m_ui;
  QList<TransferFrame*> m_transfers;

  void sendTransactionCompleted(CryptoNote::TransactionId _id, bool _error, const QString& _error_text);
  void walletActualBalanceUpdated(quint64 _balance);

  // Q_SLOT void addRecipientClicked();
  Q_SLOT void reset();
  Q_SLOT void mixinValueChanged(int _value);
  Q_SLOT void sendClicked();
  QString getAddress() const;
  qreal getAmount() const;
  QString getAmountString() const;
};

}
