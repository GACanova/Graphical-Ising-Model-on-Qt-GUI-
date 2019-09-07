#ifndef SPINWINDOW_H
#define SPINWINDOW_H

#include <QDialog>
#include <QPaintEvent>
#include "spinpainter.h"
#include "types.h"
#include<vector>

namespace Ui {
class SpinWindow;
}

class SpinWindow : public QDialog
{
    Q_OBJECT
private:
    Ui::SpinWindow *ui;
    SpinPainter *painterObject{nullptr};
    unsigned number{0},size;
    std::vector<spin> data;

public:
    explicit SpinWindow(QWidget *parent = 0);
    ~SpinWindow();
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *e);
    void updateData(std::vector<spin> Data, uint Size);

private:
    void CreateDestroySpins(int n);

private slots:

public slots:

};

#endif // SPINWINDOW_H
