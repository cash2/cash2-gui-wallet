// Copyright (c) 2011-2016 The Cryptonote developers
// Copyright (c) 2015-2016 XDN developers
// Copyright (c) 2016-2017 The Karbowanec developers
// Copyright (c) 2018-2019 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <QDialog>

namespace Ui {
class RestoreWalletFromKeysDialog;
}

namespace WalletGui {

class RestoreWalletFromKeysDialog : public QDialog {
  Q_OBJECT

public:
  RestoreWalletFromKeysDialog(QWidget* _parent);
  ~RestoreWalletFromKeysDialog();

  QString getSpendSecretKeyString() const;
  QString getViewSecretKeyString() const;
  QString getPasswordString() const;
  QString getPasswordConfirmString() const;
  QString getFilePath() const;

private:
  QScopedPointer<Ui::RestoreWalletFromKeysDialog> m_ui;

  int wordCount = 0;

  Q_SLOT void checkPassword(const QString& _password);
  // Q_SLOT void selectPathClicked();
  // Q_SLOT void onTextChanged();
};

}
