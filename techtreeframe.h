#ifndef TECHTREEFRAME_H
#define TECHTREEFRAME_H

#include <QFrame>

namespace Ui {
class TechTreeFrame;
}

class TechTreeFrame : public QFrame
{
    Q_OBJECT

public:
    explicit TechTreeFrame(QWidget *parent = nullptr);
    ~TechTreeFrame();

private:
    Ui::TechTreeFrame *ui;
};

#endif // TECHTREEFRAME_H
