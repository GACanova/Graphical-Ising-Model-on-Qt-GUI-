#ifndef ENERGYWINDOW_H
#define ENERGYWINDOW_H

#include <QDialog>
#include "energypainter.h"

#define timeSteps 1000

namespace Ui {
class EnergyWindow;
}

class EnergyWindow : public QDialog
{
    Q_OBJECT
private:
    Ui::EnergyWindow *ui;
    EnergyPainter *painterObject{nullptr};
    std::list<ObsData> data;

public:
    explicit EnergyWindow(QWidget *parent = 0);
    ~EnergyWindow();
    void updateData(ObsData Data);
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *e);


signals:
    void closeWindow();
};

#endif // ENERGYWINDOW_H
