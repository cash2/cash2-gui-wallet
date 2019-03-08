// Copyright (c) 2011-2015 The Cryptonote developers
// Copyright (c) 2015-2016 XDN developers
// Copyright (c) 2016 The Karbowanec developers
// Copyright (c) 2018-2019 The Cash2 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

#include <QDir>
#include <QJsonObject>
#include <QObject>

namespace WalletGui {

class CommandLineParser;

class Settings : public QObject {
  Q_OBJECT
  Q_DISABLE_COPY(Settings)

public:
  static Settings& instance();

  void setCommandLineParser(CommandLineParser* _cmd_line_parser);
  void load();

  bool hasAllowLocalIpOption() const;
  bool hasHideMyPortOption() const;
  bool isTestnet() const;
  QDir getDataDir() const;
  QString getP2pBindIp() const;
  quint16 getLocalRpcPort() const;
  quint16 getP2pBindPort() const;
  quint16 getP2pExternalPort() const;
  QStringList getExclusiveNodes() const;
  QStringList getPeers() const;
  QStringList getPriorityNodes() const;
  QStringList getSeedNodes() const;

  QString getWalletFile() const;
  QStringList getRecentWalletsList() const;
  // QString getAddressBookFile() const;
  bool isEncrypted() const;
  QString getVersion() const;
  bool isStartOnLoginEnabled() const;
#ifdef Q_OS_WIN
  bool isMinimizeToTrayEnabled() const;
  bool isCloseToTrayEnabled() const;
#endif

  void setWalletFile(const QString& _file);
  void setEncrypted(bool _encrypted);
  void setCurrentTheme(const QString& _theme);
  void setStartOnLoginEnabled(bool _enable);
#ifdef Q_OS_WIN
  void setMinimizeToTrayEnabled(bool _enable);
  void setCloseToTrayEnabled(bool _enable);
#endif

  QString getConnection() const;
  QStringList getRpcNodesList() const;
  quint16 getCurrentLocalDaemonPort() const;
  QString getCurrentRemoteNode() const;

  void setConnection(const QString& _connection);
  void setRpcNodesList(const QStringList& _RpcNodesList);
  void setCurrentLocalDaemonPort(const quint16& _daemonPort);
  void setCurrentRemoteNode(const QString& _remoteNode);

private:
  QJsonObject m_settings;
  // QString m_addressBookFile;
  CommandLineParser* m_cmdLineParser;

  Settings();
  ~Settings();

  void saveSettings() const;
};

}
