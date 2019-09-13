// Copyright (c) 2011-2015 The Cryptonote developers
// Copyright (c) 2015-2016 XDN developers
// Copyright (c) 2016 The Karbowanec developers
// Copyright (c) 2018-2019 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <QCloseEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include <QTimer>

#include <Common/Util.h>
#include <Common/StringTools.h>

#include "AboutDialog.h"
#include "AnimatedLabel.h"
#include "ChangePasswordDialog.h"
#include "CurrencyAdapter.h"
#include "ExitWidget.h"
#include "MainWindow.h"
#include "NewPasswordDialog.h"
#include "NodeAdapter.h"
#include "PasswordDialog.h"
#include "Settings.h"
#include "WalletAdapter.h"
#include "WalletEvents.h"
#include "RestoreWalletFromKeysDialog.h"
#include "PrivateKeysDialog.h"
#include "ConnectionSettings.h"
#include "CreateNewWalletDialog.h"

#include "ui_mainwindow.h"

namespace WalletGui {

MainWindow* MainWindow::m_instance = nullptr;

MainWindow& MainWindow::instance() {
  if (m_instance == nullptr) {
    m_instance = new MainWindow;
  }

  return *m_instance;
}

MainWindow::MainWindow() : QMainWindow(), m_ui(new Ui::MainWindow), m_trayIcon(nullptr), m_tabActionGroup(new QActionGroup(this)),
  m_isAboutToQuit(false), maxRecentFiles(20) {
  m_ui->setupUi(this);
  // // Trying to show main window as maximized on startup but not working
  // QMainWindow::showFullScreen();
  // QMainWindow::showMaximized();
  // m_connectionStateIconLabel = new QLabel(this);
  // m_encryptionStateIconLabel = new QLabel(this);
  // m_synchronizationStateIconLabel = new AnimatedLabel(this);

  connectToSignals();
  initUi();

  walletClosed();
}

MainWindow::~MainWindow() {
}

void MainWindow::connectToSignals() {
  connect(&WalletAdapter::instance(), &WalletAdapter::openWalletWithPasswordSignal, this, &MainWindow::askForWalletPassword, Qt::QueuedConnection);
  connect(&WalletAdapter::instance(), &WalletAdapter::changeWalletPasswordSignal, this, &MainWindow::encryptWallet, Qt::QueuedConnection);
  connect(&WalletAdapter::instance(), &WalletAdapter::walletSynchronizationProgressUpdatedSignal,
    this, &MainWindow::walletSynchronizationInProgress, Qt::QueuedConnection);
  connect(&WalletAdapter::instance(), &WalletAdapter::walletSynchronizationCompletedSignal, this, &MainWindow::walletSynchronized
    , Qt::QueuedConnection);
  connect(&WalletAdapter::instance(), &WalletAdapter::walletStateChangedSignal, this, &MainWindow::setStatusBarText);
  connect(&WalletAdapter::instance(), &WalletAdapter::walletInitCompletedSignal, this, &MainWindow::walletOpened);
  connect(&WalletAdapter::instance(), &WalletAdapter::walletCloseCompletedSignal, this, &MainWindow::walletClosed);
  connect(&NodeAdapter::instance(), &NodeAdapter::peerCountUpdatedSignal, this, &MainWindow::peerCountUpdated, Qt::QueuedConnection);
  connect(m_ui->m_exitAction, &QAction::triggered, qApp, &QApplication::quit);
}

void MainWindow::initUi() {
  setWindowTitle(QString("Cash2 Wallet 5.1.1"));
#ifdef Q_OS_WIN32
  if (QSystemTrayIcon::isSystemTrayAvailable()) {
    m_trayIcon = new QSystemTrayIcon(QPixmap(":images/cryptonote"), this);
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::trayActivated);
  }
#endif
  m_ui->m_aboutCryptonoteAction->setText(QString(tr("About")));

  m_ui->m_overviewFrame->hide();
  m_ui->m_sendFrame->hide();
  // m_ui->m_receiveFrame->hide();
  m_ui->m_transactionsFrame->hide();
  // m_ui->m_addressBookFrame->hide();

  m_tabActionGroup->addAction(m_ui->m_overviewAction);
  m_tabActionGroup->addAction(m_ui->m_sendAction);
  // m_tabActionGroup->addAction(m_ui->m_receiveAction);
  m_tabActionGroup->addAction(m_ui->m_transactionsAction);
  // m_tabActionGroup->addAction(m_ui->m_addressBookAction);

  m_ui->m_overviewAction->toggle();
  encryptedFlagChanged(false);
  // statusBar()->addPermanentWidget(m_connectionStateIconLabel);
  // statusBar()->addPermanentWidget(m_encryptionStateIconLabel);
  // statusBar()->addPermanentWidget(m_synchronizationStateIconLabel);
  // qobject_cast<AnimatedLabel*>(m_synchronizationStateIconLabel)->setSprite(QPixmap(":icons/sync_sprite"), QSize(16, 16), 5, 24);
  // m_connectionStateIconLabel->setPixmap(QPixmap(":icons/disconnected").scaled(16, 16, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));

  // recent wallets
  m_ui->menuRecent_wallets->setVisible(false);
  QAction* recentWalletAction = 0;
  for(int i = 0; i < maxRecentFiles; ++i){
    recentWalletAction = new QAction(this);
    recentWalletAction->setVisible(false);
    QObject::connect(recentWalletAction, SIGNAL(triggered()), this, SLOT(openRecent()));
    recentFileActionList.append(recentWalletAction);
  }
  for(int i = 0; i < maxRecentFiles; ++i)
  {
     m_ui->menuRecent_wallets->addAction(recentFileActionList.at(i));
  }

  updateRecentActionList();

#ifdef Q_OS_MAC
  installDockHandler();
#endif

#ifndef Q_OS_WIN
  // m_ui->m_minimizeToTrayAction->deleteLater();
  // m_ui->m_closeToTrayAction->deleteLater();
#endif
}

#ifdef Q_OS_WIN
void MainWindow::minimizeToTray(bool _on) {
  if (_on) {
    hide();
    m_trayIcon->show();
  } else {
    showNormal();
    activateWindow();
    m_trayIcon->hide();
  }
}
#endif

void MainWindow::scrollToTransaction(const QModelIndex& _index) {
  m_ui->m_transactionsAction->setChecked(true);
  m_ui->m_transactionsFrame->scrollToTransaction(_index);
}

void MainWindow::quit() {
  if (!m_isAboutToQuit && WalletAdapter::instance().isOpen()) {
    ExitWidget* exitWidget = new ExitWidget(nullptr);
    exitWidget->show();
    m_isAboutToQuit = true;
    close();
  }
}

#ifdef Q_OS_MAC
void MainWindow::restoreFromDock() {
  if (m_isAboutToQuit) {
    return;
  }

  showNormal();
}
#endif

void MainWindow::closeEvent(QCloseEvent* _event) {
#ifdef Q_OS_WIN
  if (m_isAboutToQuit) {
    QMainWindow::closeEvent(_event);
    return;
  } else if (Settings::instance().isCloseToTrayEnabled()) {
    minimizeToTray(true);
    _event->ignore();
  } else {
    QApplication::quit();
    return;
  }
#elif defined(Q_OS_LINUX)
  if (!m_isAboutToQuit) {
    QApplication::quit();
    return;
  }
#endif
  QMainWindow::closeEvent(_event);

}

#ifdef Q_OS_WIN
void MainWindow::changeEvent(QEvent* _event) {
  QMainWindow::changeEvent(_event);
  if (!QSystemTrayIcon::isSystemTrayAvailable()) {
    QMainWindow::changeEvent(_event);
    return;
  }

  switch (_event->type()) {
  case QEvent::WindowStateChange:
    if(Settings::instance().isMinimizeToTrayEnabled()) {
      minimizeToTray(isMinimized());
    }
    break;
  default:
    break;
  }

  QMainWindow::changeEvent(_event);
}
#endif

bool MainWindow::event(QEvent* _event) {
  switch (static_cast<WalletEventType>(_event->type())) {
    case WalletEventType::ShowMessage:
    showMessage(static_cast<ShowMessageEvent*>(_event)->messageText(), static_cast<ShowMessageEvent*>(_event)->messageType());
    return true;
  }

  return QMainWindow::event(_event);
}

void MainWindow::createNewWallet() {
  CreateNewWalletDialog dlg(this);
  if (dlg.exec() == QDialog::Accepted) {
    QString filePath = dlg.getFilePath();
    QString passwordQString = dlg.getPasswordString().trimmed();
    QString passwordConfirmQString = dlg.getPasswordConfirmString().trimmed();
    
    if (filePath.isEmpty() || passwordQString.isEmpty() || passwordConfirmQString.isEmpty())
    {
      return;
    }

    std::string password = passwordQString.toStdString();
    std::string passwordConfirm = passwordConfirmQString.toStdString();

    if (password != passwordConfirm)
    {
      return;
    }

    if (!filePath.isEmpty() && !filePath.endsWith(".wallet")) {
      filePath.append(".wallet");
    }

    if (!filePath.isEmpty() && !QFile::exists(filePath)) {
      if (WalletAdapter::instance().isOpen()) {
        WalletAdapter::instance().close();
      }

      WalletAdapter::instance().setWalletFile(filePath);
      WalletAdapter::instance().open(passwordQString);
      showPrivateKeys();
    }
  }
}

void MainWindow::openWallet() {
  QString filePath = QFileDialog::getOpenFileName(this, tr("Open .wallet/.keys file"),
#ifdef Q_OS_WIN
    QApplication::applicationDirPath(),
#else
    QDir::homePath(),
#endif
    tr("Wallet (*.wallet *.keys)"));

  if (!filePath.isEmpty()) {
    if (WalletAdapter::instance().isOpen()) {
      WalletAdapter::instance().close();
    }

    WalletAdapter::instance().setWalletFile(filePath);
    WalletAdapter::instance().open("");
  }
}

void MainWindow::restoreWalletFromKeys() {
  RestoreWalletFromKeysDialog dlg(this);
  if (dlg.exec() == QDialog::Accepted) {
    QString filePath = dlg.getFilePath();
    QString spendSecretKeyQString = dlg.getSpendSecretKeyString().trimmed();
    QString viewSecretKeyQString = dlg.getViewSecretKeyString().trimmed();
    QString passwordQString = dlg.getPasswordString().trimmed();
    QString passwordConfirmQString = dlg.getPasswordConfirmString().trimmed();
    
    if (spendSecretKeyQString.isEmpty() || viewSecretKeyQString.isEmpty() || passwordQString.isEmpty() || passwordConfirmQString.isEmpty() || filePath.isEmpty()) {
      return;
    }

    std::string password = passwordQString.toStdString();
    std::string passwordConfirm = passwordConfirmQString.toStdString();

    if (password != passwordConfirm)
    {
      return;
    }

    if (!filePath.endsWith(".wallet")) {
      filePath.append(".wallet");
    }

    /////////////////////////

    std::string spendSecretKeyStr = spendSecretKeyQString.toStdString();
    std::string viewSecretKeyStr = viewSecretKeyQString.toStdString();

    Crypto::SecretKey spendSecretKey;
    Crypto::SecretKey viewSecretKey;

    size_t size;
    if (!Common::fromHex(spendSecretKeyStr, &spendSecretKey, sizeof(spendSecretKey), size) || size != sizeof(spendSecretKey)) {
      QMessageBox::warning(this, tr("Spend private key is not valid"), tr("The spend private key you entered is not valid."), QMessageBox::Ok);
      return;
    }

    if (!Common::fromHex(viewSecretKeyStr, &viewSecretKey, sizeof(viewSecretKey), size) || size != sizeof(viewSecretKey)) {
      QMessageBox::warning(this, tr("View private key is not valid"), tr("The view private key you entered is not valid."), QMessageBox::Ok);
      return;
    }

    //////////////////////////

    CryptoNote::AccountKeys keys;

    keys.spendSecretKey = spendSecretKey;
    Crypto::secret_key_to_public_key(keys.spendSecretKey,keys.address.spendPublicKey);
    keys.viewSecretKey = viewSecretKey;
    Crypto::secret_key_to_public_key(keys.viewSecretKey,keys.address.viewPublicKey);

    if (WalletAdapter::instance().isOpen()) {
      WalletAdapter::instance().close();
    }

    WalletAdapter::instance().setWalletFile(filePath);
    WalletAdapter::instance().createWithKeys(keys, password);


    // if(Crypto::ElectrumWords::words_to_bytes(mnemonicString.toStdString(), keys.spendSecretKey, seed_language)) {
      // Crypto::secret_key_to_public_key(keys.spendSecretKey,keys.address.spendPublicKey);
      // Crypto::SecretKey second;
      // keccak((uint8_t *)&keys.spendSecretKey, sizeof(Crypto::SecretKey), (uint8_t *)&second, sizeof(Crypto::SecretKey));
      // Crypto::generate_deterministic_keys(keys.address.viewPublicKey,keys.viewSecretKey,second);

      // if (WalletAdapter::instance().isOpen()) {
        // WalletAdapter::instance().close();
      // }
      // WalletAdapter::instance().setWalletFile(filePath);
      // WalletAdapter::instance().createWithKeys(keys);
    // } else {
      // QMessageBox::critical(nullptr, tr("Mnemonic seed is not correct"), tr("There must be an error in mnemonic seed. Make sure you entered it correctly."), QMessageBox::Ok);
      // return;
    // }
  }
}

void MainWindow::openRecent(){
  QAction *action = qobject_cast<QAction *>(sender());
  if (action) {
    QString filePath = action->data().toString();
    if (!filePath.isEmpty() && QFileInfo(filePath).exists()) {
      if (WalletAdapter::instance().isOpen()) {
        WalletAdapter::instance().close();
      }
      WalletAdapter::instance().setWalletFile(filePath);
      WalletAdapter::instance().open("");
    }
  }
}

// void MainWindow::backupWallet() {
  // QString filePath = QFileDialog::getSaveFileName(this, tr("Backup wallet to..."),
  // #ifdef Q_OS_WIN
      // QApplication::applicationDirPath(),
  // #else
      // QDir::homePath(),
  // #endif
      // tr("Wallets (*.wallet)")
      // );
    // if (!filePath.isEmpty() && !filePath.endsWith(".wallet")) {
      // filePath.append(".wallet");
    // }

    // if (!filePath.isEmpty() && !QFile::exists(filePath)) {
      // WalletAdapter::instance().backup(filePath);
    // }
// }

void MainWindow::showPrivateKeys() {
  PrivateKeysDialog dlg(this);
  dlg.walletOpened();
  dlg.exec();
}

void MainWindow::encryptWallet() {
  if (Settings::instance().isEncrypted()) {
    bool error = false;
    do {
      ChangePasswordDialog dlg(this);
      if (dlg.exec() == QDialog::Rejected) {
        return;
      }

      QString oldPassword = dlg.getOldPassword();
      QString newPassword = dlg.getNewPassword();
      error = !WalletAdapter::instance().changePassword(oldPassword, newPassword);
    } while (error);
  } else {
    NewPasswordDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
      QString password = dlg.getPassword();
      if (password.isEmpty()) {
        return;
      }

      encryptedFlagChanged(WalletAdapter::instance().changePassword("", password));
    }
  }
}

void MainWindow::closeWallet() {
  if (WalletAdapter::instance().isOpen()) {
    WalletAdapter::instance().close();
  }
}

void MainWindow::updateRecentActionList(){
  QStringList recentFilePaths = Settings::instance().getRecentWalletsList();
  if(recentFilePaths.isEmpty())
  {
    m_ui->menuRecent_wallets->setVisible(false);
  }

  if(recentFilePaths.size() != 0)
  {
    int itEnd = 0;

    if(recentFilePaths.size() <= maxRecentFiles)
    {
      itEnd = recentFilePaths.size();
    }
    else
    {
      itEnd = maxRecentFiles;
    }

    for (int i = 0; i < itEnd; ++i)
    {
      QString strippedName = QFileInfo(recentFilePaths.at(i)).absoluteFilePath();
      recentFileActionList.at(i)->setText(strippedName);
      recentFileActionList.at(i)->setData(recentFilePaths.at(i));
      recentFileActionList.at(i)->setVisible(true);
    }

    for (int i = itEnd; i < maxRecentFiles; ++i)
    {
      recentFileActionList.at(i)->setVisible(false);
    }
  }
  else
  {
    m_ui->menuRecent_wallets->setVisible(false);
  }
}

void MainWindow::aboutQt() {
  QMessageBox::aboutQt(this);
}

void MainWindow::setStartOnLogin(bool _on) {
  Settings::instance().setStartOnLoginEnabled(_on);
  // m_ui->m_startOnLoginAction->setChecked(Settings::instance().isStartOnLoginEnabled());
}

void MainWindow::setMinimizeToTray(bool _on) {
#ifdef Q_OS_WIN
  Settings::instance().setMinimizeToTrayEnabled(_on);
#endif
}

void MainWindow::setCloseToTray(bool _on) {
#ifdef Q_OS_WIN
  Settings::instance().setCloseToTrayEnabled(_on);
#endif
}

void MainWindow::about() {
  AboutDialog dlg(this);
  dlg.exec();
}

void MainWindow::setStatusBarText(const QString& _text, const QString& _textColor) {
  statusBar()->showMessage(_text);
  statusBar()->setStyleSheet("border-top: 1px solid #C8C8C8; color:" + _textColor + ";");
}

void MainWindow::showMessage(const QString& _text, QtMsgType _type) {
  switch (_type) {
  case QtCriticalMsg:
    QMessageBox::critical(this, tr("Wallet error"), _text);
    break;
  case QtDebugMsg:
    QMessageBox::information(this, tr("Wallet"), _text);
    break;
  default:
    break;
  }
}

void MainWindow::askForWalletPassword(bool _error) {
  PasswordDialog dlg(_error, this);
  if (dlg.exec() == QDialog::Accepted) {
    QString password = dlg.getPassword();
    WalletAdapter::instance().open(password);
  }
}

void MainWindow::encryptedFlagChanged(bool _encrypted) {
  // m_ui->m_encryptWalletAction->setEnabled(!_encrypted);
  // m_ui->m_changePasswordAction->setEnabled(_encrypted);
  // QString encryptionIconPath = _encrypted ? ":icons/encrypted" : ":icons/decrypted";
  // QPixmap encryptionIcon = QPixmap(encryptionIconPath).scaled(16, 16, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  // m_encryptionStateIconLabel->setPixmap(encryptionIcon);
  // QString encryptionLabelTooltip = _encrypted ? tr("Encrypted") : tr("Not encrypted");
  // m_encryptionStateIconLabel->setToolTip(encryptionLabelTooltip);
}

void MainWindow::peerCountUpdated(quint64 _peerCount) {
  // QString connectionIconPath = _peerCount > 0 ? ":icons/connected" : ":icons/disconnected";
  // QPixmap connectionIcon = QPixmap(connectionIconPath).scaled(16, 16, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  // m_connectionStateIconLabel->setPixmap(connectionIcon);
  // m_connectionStateIconLabel->setToolTip(QString(tr("%1 peers").arg(_peerCount)));
}

void MainWindow::walletSynchronizationInProgress() {
  // qobject_cast<AnimatedLabel*>(m_synchronizationStateIconLabel)->startAnimation();
  // m_synchronizationStateIconLabel->setToolTip(tr("Synchronization in progress"));

  // allow sending only after wallet is synchronized
  m_ui->m_sendAction->setEnabled(false);
}

void MainWindow::walletSynchronized(int _error, const QString& _error_text) {
  // QPixmap syncIcon = QPixmap(":icons/synced").scaled(16, 16, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
  // qobject_cast<AnimatedLabel*>(m_synchronizationStateIconLabel)->stopAnimation();
  // m_synchronizationStateIconLabel->setPixmap(syncIcon);
  // QString syncLabelTooltip = _error > 0 ? tr("Not synchronized") : tr("Synchronized");
  // m_synchronizationStateIconLabel->setToolTip(syncLabelTooltip);
  
  // allow sending only after wallet is synchronized
  m_ui->m_sendAction->setEnabled(true);
}

void MainWindow::walletOpened(bool _error, const QString& _error_text) {
  if (!_error) {
    // m_encryptionStateIconLabel->show();
    m_ui->toolBar->show();
    // m_synchronizationStateIconLabel->show();
    // m_ui->m_backupWalletAction->setEnabled(true);
    m_ui->m_showPrivateKeys->setEnabled(true);
    m_ui->m_closeWalletAction->setEnabled(true);
    m_ui->m_changePasswordAction->setEnabled(true);
    encryptedFlagChanged(Settings::instance().isEncrypted());

    QList<QAction*> tabActions = m_tabActionGroup->actions();
    Q_FOREACH(auto action, tabActions) {
      action->setEnabled(true);
    }

    m_ui->m_overviewAction->trigger();

    deleteStartPrompt();

    m_ui->m_overviewFrame->show();

    // allow sending only after wallet is synchronized
    m_ui->m_sendAction->setEnabled(false);

    updateRecentActionList();
  }
  else
  {
    walletClosed();
  }
}

void MainWindow::walletClosed() {
  // m_ui->m_backupWalletAction->setEnabled(false);
  m_ui->m_showPrivateKeys->setEnabled(false);
  m_ui->m_closeWalletAction->setEnabled(false);
  // m_ui->m_encryptWalletAction->setEnabled(false);
  m_ui->m_changePasswordAction->setEnabled(false);
  m_ui->m_overviewFrame->hide();
  m_ui->m_sendFrame->hide();
  m_ui->m_transactionsFrame->hide();
  m_ui->toolBar->hide();
  // m_ui->m_addressBookFrame->hide();
  // m_encryptionStateIconLabel->hide();
  // m_synchronizationStateIconLabel->hide();
  QList<QAction*> tabActions = m_tabActionGroup->actions();
  Q_FOREACH(auto action, tabActions) {
    action->setEnabled(false);
  }
  updateRecentActionList();
}

#ifdef Q_OS_WIN
void MainWindow::trayActivated(QSystemTrayIcon::ActivationReason _reason) {
  showNormal();
  m_trayIcon->hide();
}
#endif

void MainWindow::openConnectionSettings() {
    ConnectionSettingsDialog dlg(&MainWindow::instance());
    dlg.initConnectionSettings();
    dlg.setConnectionMode();
    dlg.setRemoteNode();
    dlg.setLocalDaemonPort();
    if (dlg.exec() == QDialog::Accepted) {
      QString connection = dlg.setConnectionMode();
      Settings::instance().setConnection(connection);

      QString remoteNode = dlg.setRemoteNode();
      Settings::instance().setCurrentRemoteNode(remoteNode);

      quint16 daemonPort = dlg.setLocalDaemonPort();
      Settings::instance().setCurrentLocalDaemonPort(daemonPort);

      QMessageBox::information(this, tr("Connection settings changed"), tr("Connection mode will be changed after restarting the wallet."), QMessageBox::Ok);
    }
}

// ***Will cause a crash if the element does not exist
void MainWindow::deleteStartPrompt()
{
  if (m_ui->horizontalLayout != nullptr)
  {
    delete m_ui->horizontalLayout;
    m_ui->horizontalLayout = nullptr;
  }

  if (m_ui->m_openWalletButton != nullptr)
  {
    delete m_ui->m_openWalletButton;
    m_ui->m_openWalletButton = nullptr;
  }

  if (m_ui->horizontalLayout_2 != nullptr)
  {
    delete m_ui->horizontalLayout_2;
    m_ui->horizontalLayout_2 = nullptr;
  }

  if (m_ui->m_createNewWalletButton != nullptr)
  {
    delete m_ui->m_createNewWalletButton;
    m_ui->m_createNewWalletButton = nullptr;
  }

  if (m_ui->horizontalLayout_3 != nullptr)
  {
    delete m_ui->horizontalLayout_3;
    m_ui->horizontalLayout_3 = nullptr;
  }

  if (m_ui->m_restoreWalletFromKeysButton != nullptr)
  {
    delete m_ui->m_restoreWalletFromKeysButton;
    m_ui->m_restoreWalletFromKeysButton = nullptr;
  }

  if (m_ui->m_start != nullptr)
  {
    delete m_ui->m_start;
    m_ui->m_start = nullptr;
  }
}

}
