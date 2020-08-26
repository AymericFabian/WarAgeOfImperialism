#ifndef COUNTRIESFRAME_H
#define COUNTRIESFRAME_H

#include <QFrame>
#include <QTableView>

#include "countriestablemodel.h"

namespace Ui {
class CountriesFrame;
}

class CountriesFrame : public QFrame
{
    Q_OBJECT

public:
    explicit CountriesFrame(QWidget *parent = nullptr);
    ~CountriesFrame();

private:
    Ui::CountriesFrame *ui;

    CountriesTableModel* countriesTableModel;
};

#endif // COUNTRIESFRAME_H
