// Copyright (c) 2011-2015 The Cryptonote developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "CurrencyAdapter.h"
#include "OverviewFrame.h"
// #include "RecentTransactionsModel.h"
#include "WalletAdapter.h"
#include "Settings.h"
#include "MainWindow.h"

#include "ui_overviewframe.h"

namespace WalletGui {

// class RecentTransactionsDelegate : public QStyledItemDelegate {
  // Q_OBJECT

// public:
  // RecentTransactionsDelegate(QObject* _parent) : QStyledItemDelegate(_parent) {
  // }

  // ~RecentTransactionsDelegate() {
  // }

  // QWidget* createEditor(QWidget* _parent, const QStyleOptionViewItem& _option, const QModelIndex& _index) const Q_DECL_OVERRIDE {
    // if (!_index.isValid()) {
      // return nullptr;
    // }

    // return new TransactionFrame(_index, _parent);
  // }

  // QSize sizeHint(const QStyleOptionViewItem& _option, const QModelIndex& _index) const Q_DECL_OVERRIDE {
    // return QSize(346, 64);
  // }
// };

OverviewFrame::OverviewFrame(QWidget* _parent) : QFrame(_parent), m_ui(new Ui::OverviewFrame)/*, m_transactionModel(new RecentTransactionsModel)*/ {
  m_ui->setupUi(this);

  connect(&WalletAdapter::instance(), &WalletAdapter::walletActualBalanceUpdatedSignal, this, &OverviewFrame::updateActualBalance, Qt::QueuedConnection);
  connect(&WalletAdapter::instance(), &WalletAdapter::walletPendingBalanceUpdatedSignal, this, &OverviewFrame::updatePendingBalance, Qt::QueuedConnection);
  connect(&WalletAdapter::instance(), &WalletAdapter::walletCloseCompletedSignal, this, &OverviewFrame::reset, Qt::QueuedConnection);
  // connect(m_transactionModel.data(), &QAbstractItemModel::rowsInserted, this, &OverviewFrame::transactionsInserted);
  // connect(m_transactionModel.data(), &QAbstractItemModel::layoutChanged, this, &OverviewFrame::layoutChanged);
  connect(&WalletAdapter::instance(), &WalletAdapter::updateWalletAddressSignal, this, &OverviewFrame::updateWalletAddress);
  connect(&WalletAdapter::instance(), &WalletAdapter::updateWalletNameSignal, this, &OverviewFrame::updateWalletName);

  // m_ui->m_tickerLabel1->setText(CurrencyAdapter::instance().getCurrencyTicker().toUpper());
  // m_ui->m_tickerLabel2->setText(CurrencyAdapter::instance().getCurrencyTicker().toUpper());

  // m_ui->m_recentTransactionsView->setItemDelegate(new RecentTransactionsDelegate(this));
  // m_ui->m_recentTransactionsView->setModel(m_transactionModel.data());

  reset();
}

OverviewFrame::~OverviewFrame() {
}

// void OverviewFrame::transactionsInserted(const QModelIndex& _parent, int _first, int _last) {
  // for (quint32 i = _first; i <= _last; ++i) {
    // QModelIndex recentModelIndex = m_transactionModel->index(i, 0);
    // m_ui->m_recentTransactionsView->openPersistentEditor(recentModelIndex);
  // }
// }

// void OverviewFrame::layoutChanged() {
  // for (quint32 i = 0; i <= m_transactionModel->rowCount(); ++i) {
    // QModelIndex recent_index = m_transactionModel->index(i, 0);
    // m_ui->m_recentTransactionsView->openPersistentEditor(recent_index);
  // }
// }

void OverviewFrame::updateActualBalance(quint64 _balance) {
  // m_ui->m_actualBalanceLabel->setText(CurrencyAdapter::instance().formatAmount(_balance));
  quint64 pendingBalance = WalletAdapter::instance().getPendingBalance();
  m_ui->m_totalBalanceLabel->setText(CurrencyAdapter::instance().formatAmount(_balance + pendingBalance));
}

void OverviewFrame::updatePendingBalance(quint64 _balance) {
  m_ui->m_pendingBalanceLabel->setText(CurrencyAdapter::instance().formatAmount(_balance));
  quint64 actualBalance = WalletAdapter::instance().getActualBalance();
  m_ui->m_totalBalanceLabel->setText(CurrencyAdapter::instance().formatAmount(_balance + actualBalance));
}

void OverviewFrame::reset() {
  updateActualBalance(0);
  updatePendingBalance(0);
  clearAddress();
  clearWalletName();
}

void OverviewFrame::updateWalletAddress(const QString& _address) {
  m_ui->m_addressEdit->setText(_address);
  
  // makes address box have no border
  m_ui->m_addressEdit->setStyleSheet("QLineEdit { qproperty-frame: false }");
  
  // makes address box have a transparent background
  m_ui->m_addressEdit->setStyleSheet("background:transparent;");

  // makes cursor an I beam
  m_ui->m_addressEdit->setCursor(Qt::IBeamCursor);
}

void OverviewFrame::clearAddress() {
  m_ui->m_addressEdit->clear();
}

void OverviewFrame::clearWalletName() {
  m_ui->m_walletName->clear();
}

void OverviewFrame::updateWalletName() {
  // get wallet name
  QString filePath = Settings::instance().getWalletFile();
  QFileInfo fileInfo(filePath);
  QString walletName = fileInfo.baseName();
  m_ui->m_walletName->setText(walletName);
}

}

#include "OverviewFrame.moc"
