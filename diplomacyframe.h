#ifndef DIPLOMACYFRAME_H
#define DIPLOMACYFRAME_H

#include <QFrame>

#include "diplomacytablemodel.h"

namespace Ui {
class DiplomacyFrame;
}

class DiplomacyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit DiplomacyFrame(QWidget *parent = nullptr);
    ~DiplomacyFrame();

private:
    Ui::DiplomacyFrame *ui;
    void init();

    DiplomacyTableModel* diploTableModel;
};

#endif // DIPLOMACYFRAME_H
