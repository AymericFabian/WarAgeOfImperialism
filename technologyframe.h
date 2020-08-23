#ifndef TECHNOLOGYFRAME_H
#define TECHNOLOGYFRAME_H

#include <QFrame>

namespace Ui {
class TechnologyFrame;
}

class TechnologyFrame : public QFrame
{
    Q_OBJECT

public:
    explicit TechnologyFrame(QWidget *parent = nullptr);
    ~TechnologyFrame();

    void setName(QString name);

private:
    Ui::TechnologyFrame *ui;
};

#endif // TECHNOLOGYFRAME_H
