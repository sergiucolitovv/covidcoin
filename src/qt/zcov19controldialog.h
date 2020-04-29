// Copyright (c) 2017-2020 The COVID19 developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZCOV19CONTROLDIALOG_H
#define ZCOV19CONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zcov19/zerocoin.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZCov19ControlDialog;
}

class CZCov19ControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZCov19ControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZCov19ControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZCov19ControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZCov19ControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZCov19ControlDialog(QWidget *parent);
    ~ZCov19ControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZCov19ControlDialog *ui;
    WalletModel* model;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZCov19ControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZCOV19CONTROLDIALOG_H
