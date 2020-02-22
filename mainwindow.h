#pragma once

#include <QKeyEvent>
#include <QMainWindow>
#include "data.h"
#include "whitelist.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void keyPressEvent(QKeyEvent *event) Q_DECL_OVERRIDE;

  private slots:
    void Next();

  private:
    Ui::MainWindow *ui;
    class Whitelist *whitelist;
};
