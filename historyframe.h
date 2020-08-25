#ifndef HISTORYFRAME_H
#define HISTORYFRAME_H

#include <QFrame>

namespace Ui {
class HistoryFrame;
}

class HistoryFrame : public QFrame
{
    Q_OBJECT

public:
    explicit HistoryFrame(QWidget *parent = nullptr);
    ~HistoryFrame();

private:
    Ui::HistoryFrame *ui;
};

#endif // HISTORYFRAME_H
