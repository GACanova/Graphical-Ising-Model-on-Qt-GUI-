#ifndef SPINSWINDOW_H
#define SPINSWINDOW_H

#include <QDialog>

namespace Ui {
class SpinsWindow;
}

class SpinsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SpinsWindow(QWidget *parent = 0);
    ~SpinsWindow();

private:
    Ui::SpinsWindow *ui;
};

#endif // SPINSWINDOW_H
