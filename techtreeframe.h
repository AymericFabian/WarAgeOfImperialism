#ifndef TECHTREEFRAME_H
#define TECHTREEFRAME_H

#include <QFrame>
#include "player.h"

namespace Ui {
class TechTreeFrame;
}

class TechTreeFrame : public QFrame
{
    Q_OBJECT

public:
    explicit TechTreeFrame(QWidget *parent = nullptr);
    ~TechTreeFrame();

    void reset();
public slots:
    void onResearch(int player, Player::Technology techno, int level, bool researched);

private:
    Ui::TechTreeFrame *ui;
};

#endif // TECHTREEFRAME_H
