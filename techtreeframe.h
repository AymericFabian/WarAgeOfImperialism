#ifndef TECHTREEFRAME_H
#define TECHTREEFRAME_H

#include <QFrame>

#include "player.h"
#include "arrow.h"

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

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::TechTreeFrame *ui;

    Arrow* arrow;
};

#endif // TECHTREEFRAME_H
