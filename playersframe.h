#ifndef PLAYERSFRAME_H
#define PLAYERSFRAME_H

#include <QFrame>
#include <QTableView>

#include "playerstablemodel.h"

namespace Ui {
class PlayersFrame;
}

class PlayersFrame : public QFrame
{
    Q_OBJECT

public:
    explicit PlayersFrame(QWidget *parent = nullptr);
    ~PlayersFrame();

private:
    Ui::PlayersFrame *ui;

    PlayersTableModel* playersTableModel;
};

#endif // PLAYERSFRAME_H
