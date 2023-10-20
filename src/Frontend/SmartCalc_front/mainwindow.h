#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <QWidget>

extern "C" {
#include <../../Backend/smart_calc.h>
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  double x_start = 0, x_end = 0, y_start = 0, y_end = 0, h = 0, X = 0;
  int N = 0;
  QVector<double> x, y;
  const char *errors[7] = {"SUCCESS",         "FAILURE",    "CALC_ERROR",
                           "INCORRECT_INPUT", "MALLOC_ERR", "STACK_OVERFLOW",
                           "EMPTY_STACK"};

 private slots:
  void push_btn_simple();
  void push_btn_func();
  void on_push_btn_AC();
  void on_push_btn_Delete();
  void on_push_btn_equal();
  void push_btn_graph();
  void on_pushBut_goto_graph_clicked();
  void on_pushBut_goToMain_clicked();
  void on_pushBut_credit_clicked();

  void on_pushBut_calc_credit_clicked();
};
#endif  // MAINWINDOW_H
