#ifndef TECHNOLOGYFRAME_H
#define TECHNOLOGYFRAME_H

#include <QFrame>

#include "player.h"

namespace Ui {
class TechnologyFrame;
}

class TechnologyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit TechnologyFrame(QWidget *parent = nullptr);
    ~TechnologyFrame();

    void init(Player::Technology techno, int level);

    void updateStatus(int player, Player::Technology techno, int level, bool researched);
private:
    Ui::TechnologyFrame *ui;

    Player::Technology techno;
    int level;

private slots:
    void technoToggled(bool);

signals:
    // player, techno, level, isResearched
    void researched(int, Player::Technology, int, bool);
};

#endif // TECHNOLOGYFRAME_H
