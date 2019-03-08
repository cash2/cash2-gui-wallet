// Copyright (c) 2011-2015 The Cryptonote developers
// Copyright (c) 2015-2016 XDN developers
// Copyright (c) 2016-2017 The Karbowanec developers
// Copyright (c) 2018-2019 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QDateTime>

#include "crypto/crypto.h"
#include "CurrencyAdapter.h"
#include "TransactionDetailsDialog.h"
#include "TransactionsModel.h"
#include "WalletAdapter.h"
#include "Common/StringTools.h"

#include "ui_transactiondetailsdialog.h"

namespace WalletGui {

TransactionDetailsDialog::TransactionDetailsDialog(const QModelIndex& _index, QWidget* _parent) : QDialog(_parent),
  m_ui(new Ui::TransactionDetailsDialog) {
  m_ui->setupUi(this);

  QModelIndex index = TransactionsModel::instance().index(_index.data(TransactionsModel::ROLE_ROW).toInt(),
    _index.data(TransactionsModel::ROLE_ROW).toInt());

  quint64 numberOfConfirmations = index.data(TransactionsModel::ROLE_NUMBER_OF_CONFIRMATIONS).value<quint64>();
  QString amountText = index.sibling(index.row(), TransactionsModel::COLUMN_AMOUNT).data().toString() + " " +
    CurrencyAdapter::instance().getCurrencyTicker().toUpper();
  QString feeText = CurrencyAdapter::instance().formatAmount(index.data(TransactionsModel::ROLE_FEE).value<quint64>()) + " " +
    CurrencyAdapter::instance().getCurrencyTicker().toUpper();

  Crypto::Hash tx_hash;
  size_t size;
  QString transactionHash = index.sibling(index.row(), TransactionsModel::COLUMN_HASH).data().toString();
  std::string tx_hash_str = transactionHash.toStdString();
  Common::fromHex(tx_hash_str, &tx_hash, sizeof(tx_hash), size);
  Crypto::SecretKey tx_key = WalletAdapter::instance().getTxKey(tx_hash);
  QString transactionKey = QString(tr("unknown"));
  TransactionType transactionType = static_cast<TransactionType>(index.data(TransactionsModel::ROLE_TYPE).value<quint8>());
  if (transactionType == TransactionType::OUTPUT) {

    // Outgoing transaction

    if (tx_key != CryptoNote::NULL_SECRET_KEY)
    {
      transactionKey = QString::fromStdString(Common::podToHex(tx_key)).toUpper();
    }

    m_detailsTemplate = 
      "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
      "</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
      "<span style=\" font-size:40px;\">You sent %1</span></p><br><br>\n"
      "<span style=\" text-decoration:underline;\">Block Confirmations</span></p><br>\n%2</p></p><br><br>\n\n"
      "<span style=\" text-decoration:underline;\">Date</span></p><br>\n%3</p></p><br><br>\n\n"
      "<span style=\" text-decoration:underline;\">Sent To</span></p><br>\n%4</p></p><br><br>\n\n"
      "<span style=\" text-decoration:underline;\">Fee</span></p><br>\n%5</p></p><br><br>\n\n"
      "<span style=\" text-decoration:underline;\">Transaction Id</span></p><br>\n%6</p></p><br><br>\n\n"
      "<span style=\" text-decoration:underline;\">Transaction Private Key</span></p><br>\n%7</p><br>\n</body></html>";

    m_ui->m_detailsBrowser->setHtml(
      m_detailsTemplate
        // removes '+' and '-' from amount
        .arg(amountText.remove(0, 2))
        // adds commas to numbers
        .arg(QString("%1").arg(QLocale(QLocale::English).toString(numberOfConfirmations)))
        .arg(index.sibling(index.row(), TransactionsModel::COLUMN_DATE).data().toString())
        .arg(index.sibling(index.row(), TransactionsModel::COLUMN_ADDRESS).data().toString())
        .arg(feeText)
        .arg(index.sibling(index.row(), TransactionsModel::COLUMN_HASH).data().toString().toLower())
        .arg(transactionKey.toLower())
    );
  }
  else
  {

    // Incoming transaction

    m_detailsTemplate = 
      "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
      "</style></head><body style=\" font-family:'Cantarell'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
      "<span style=\" font-size:40px;\">You received %1</span></p></p><br><br>\n\n"
      "<span style=\" text-decoration:underline;\">Block Confirmations</span></p><br>\n%2</p></p><br><br>\n\n"
      "<span style=\" text-decoration:underline;\">Date</span></p><br>\n%3</p></p><br><br>\n\n"
      "<span style=\" text-decoration:underline;\">Received From</span></p><br>\n%4</p></p><br><br>\n\n"
      "<span style=\" text-decoration:underline;\">Fee</span></p><br>\n%5</p></p><br><br>\n\n"
      "<span style=\" text-decoration:underline;\">Transaction Id</span></p><br>\n%6</p><br>\n</body></html>";

    m_ui->m_detailsBrowser->setHtml(
      m_detailsTemplate
        // removes '+' and '-' from amount
        .arg(amountText.remove(0, 2))
        // adds commas to numbers
        .arg(QString("%1").arg(QLocale(QLocale::English).toString(numberOfConfirmations)))
        .arg(index.sibling(index.row(), TransactionsModel::COLUMN_DATE).data().toString().toLower())
        .arg(QString("unknown"))
        .arg(feeText)
        .arg(index.sibling(index.row(), TransactionsModel::COLUMN_HASH).data().toString().toLower())
    );
  }

}

TransactionDetailsDialog::~TransactionDetailsDialog() {
}

}
