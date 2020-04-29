// Copyright (c) 2019 The COVID19 developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef COINCONTROLCOV19WIDGET_H
#define COINCONTROLCOV19WIDGET_H

#include <QDialog>

namespace Ui {
class CoinControlCov19Widget;
}

class CoinControlCov19Widget : public QDialog
{
    Q_OBJECT

public:
    explicit CoinControlCov19Widget(QWidget *parent = nullptr);
    ~CoinControlCov19Widget();

private:
    Ui::CoinControlCov19Widget *ui;
};

#endif // COINCONTROLCOV19WIDGET_H
