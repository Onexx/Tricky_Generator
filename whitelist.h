#pragma once

#include <QWidget>
#include "data.h"
#include "generator.h"

namespace Ui {
class Whitelist;
}

class Whitelist : public QWidget {
    Q_OBJECT

  public:
    explicit Whitelist(QWidget *parent = nullptr, int studentsAmount = 0,
                       int tasksAmount = 0);
    ~Whitelist();

  private slots:
    void Next();
    void CellDoubleClicked(int row, int column);
    void CellClicked(int row, int column);

  private:
    void Parser(std::vector<std::vector<int>> &possibleTasks);
    Ui::Whitelist *ui;
    class Generator *generator;
    int studentsAmount = 0;
    int tasksAmount = 0;
};
