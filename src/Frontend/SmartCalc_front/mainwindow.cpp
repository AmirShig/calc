#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->result_show->setFocus();

  // Клавиши цифр
  connect(ui->pushBut_0, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_1, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_2, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_3, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_4, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_5, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_6, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_7, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_8, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_9, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_x, SIGNAL(clicked()), this, SLOT(push_btn_simple()));

  // Клавиши    точка, скобки
  connect(ui->pushBut_dot, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_Cl_Br, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_Op_Br, SIGNAL(clicked()), this, SLOT(push_btn_simple()));

  // Клавиши операторов
  connect(ui->pushBut_div, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_mult, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_plus, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_minus, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_mod, SIGNAL(clicked()), this, SLOT(push_btn_simple()));
  connect(ui->pushBut_pow, SIGNAL(clicked()), this, SLOT(push_btn_simple()));

  // Клавиши функций
  connect(ui->pushBut_sin, SIGNAL(clicked()), this, SLOT(push_btn_func()));
  connect(ui->pushBut_cos, SIGNAL(clicked()), this, SLOT(push_btn_func()));
  connect(ui->pushBut_tan, SIGNAL(clicked()), this, SLOT(push_btn_func()));
  connect(ui->pushBut_asin, SIGNAL(clicked()), this, SLOT(push_btn_func()));
  connect(ui->pushBut_acos, SIGNAL(clicked()), this, SLOT(push_btn_func()));
  connect(ui->pushBut_atan, SIGNAL(clicked()), this, SLOT(push_btn_func()));
  connect(ui->pushBut_log, SIGNAL(clicked()), this, SLOT(push_btn_func()));
  connect(ui->pushBut_ln, SIGNAL(clicked()), this, SLOT(push_btn_func()));
  connect(ui->pushBut_sqrt, SIGNAL(clicked()), this, SLOT(push_btn_func()));

  // Клавиши очистки поля
  connect(ui->pushBut_AC, SIGNAL(clicked()), this, SLOT(on_push_btn_AC()));
  connect(ui->pushBut_Del, SIGNAL(clicked()), this, SLOT(on_push_btn_Delete()));

  // Клавиша произведения расчетов
  connect(ui->pushBut_equal, SIGNAL(clicked()), this,
          SLOT(on_push_btn_equal()));
  connect(ui->pushBut_calc_credit, SIGNAL(clicked()), this,
          SLOT(on_pushBut_calc_credit_clicked()));

  // Клавиши для работы с графиком функций
  connect(ui->pushBut_crGraph, SIGNAL(clicked()), this, SLOT(push_btn_graph()));
  connect(ui->pushBut_clear_graph, SIGNAL(clicked()), this,
          SLOT(on_push_btn_AC()));

  // Клавиши для перехода между страницами
  connect(ui->pushBut_graph, SIGNAL(clicked()), this,
          SLOT(on_pushBut_goto_graph_clicked()));
  connect(ui->pushBut_credit, SIGNAL(clicked()), this,
          SLOT(on_pushBut_credit_clicked()));
  connect(ui->pushBut_goToMain, SIGNAL(clicked()), this,
          SLOT(on_pushBut_goToMain_clicked()));
  connect(ui->pushBut_goToMain_2, SIGNAL(clicked()), this,
          SLOT(on_pushBut_goToMain_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::push_btn_simple() {
  QPushButton *button = (QPushButton *)sender();

  std::string text_label = ui->result_show->text().toStdString();

  if (text_label == "0" || text_label == "CALC_ERROR" ||
      text_label == "INCORRECT_INPUT") {
    if (button->text() == '.') {
      text_label = "0" + button->text().toStdString();
    } else {
      text_label = button->text().toStdString();
    }
  } else {
    text_label += button->text().toStdString();
  }

  ui->result_show->setText(QString::fromStdString(text_label));
}

void MainWindow::push_btn_func() {
  QPushButton *button = (QPushButton *)sender();
  QString button_text = button->text() + "(";
  QString new_label = ui->result_show->text();
  if (new_label == "0" || new_label == "CALC_ERROR" ||
      new_label == "INCORRECT_INPUT") {
    new_label = button_text;
  } else {
    new_label += button_text;
  }
  ui->result_show->setText(new_label);
}

void MainWindow::on_push_btn_AC() {
  QPushButton *button = (QPushButton *)sender();
  if (button->text() == "AC") {
    ui->result_show->setText("0");  // установить пустой вывод
  }
  ui->graph_field->clearPlottables();
  ui->graph_field->replot();
}

void MainWindow::on_push_btn_Delete() {
  QString text = ui->result_show->text();
  if (text == "CALC_ERROR" || text == "INCORRECT_INPUT") {
    ui->result_show->setText("0");
  } else if (!text.isEmpty() && text != "0") {
    text.chop(1);
    if (text == "") text = "0";
    ui->result_show->setText(text);
  }
}

void MainWindow::on_push_btn_equal() {
  errnum error_code = SUCCESS;
  std::string expression = ui->result_show->text().toStdString();
  char *expression_ptr = &expression[0];
  double result = 0.0, x = ui->x_value->value();

  error_code = entrance(expression_ptr, &result, x);

  if (error_code == SUCCESS) {
    QString new_label = QString::number(result, 'g', 15);
    ui->result_show->setText(new_label);
  } else {
    ui->result_show->setText(errors[error_code]);
  }
}

void MainWindow::push_btn_graph() {
  errnum error_code = SUCCESS;
  h = 0.1;
  double result = 0.0;
  std::string expression = ui->result_show->text().toStdString();
  char *expression_ptr = &expression[0];

  ui->graph_field->clearPlottables();
  ui->graph_field->replot();

  x_start = ui->x_start->value();
  x_end = ui->x_end->value();

  y_start = ui->y_start->value();
  y_end = ui->y_end->value();

  ui->graph_field->xAxis->setRange(x_start, x_end);
  ui->graph_field->yAxis->setRange(y_start, y_end);

  N = (x_end + h - x_start) / h + 2;

  for (X = x_start; X <= (x_end + h) && !error_code; X += h) {
    error_code = entrance(expression_ptr, &result, X);
    if (error_code == SUCCESS) {
      y.push_back(result);
      x.push_back(X);
    } else {
      ui->result_show->setText(errors[error_code]);
      ui->graph_function->setText(errors[error_code]);
    }
  }

  ui->graph_field->addGraph();
  ui->graph_field->graph(0)->addData(x, y);
  ui->graph_field->replot();

  x.clear();
  y.clear();
}

void MainWindow::on_pushBut_goto_graph_clicked() {
  ui->stackedWidget->setCurrentIndex(1);
  ui->graph_function->setText(ui->result_show->text());
}

void MainWindow::on_pushBut_goToMain_clicked() {
  ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushBut_credit_clicked() {
  ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_pushBut_calc_credit_clicked() {
  errnum error_code = SUCCESS;
  ui->m_payment->clear();
  ui->m_payment_last->clear();
  ui->total_payment->clear();
  ui->interest_paid->clear();
  ui->error_show->clear();
  // Переменные для полученной инф-ии по кредиту
  double loan_amount = ui->loan_amount_show->value();
  int loan_term = ui->loan_term->value();
  double interest_rate = ui->interest_rate_show->value();

  char cred_type = 0;

  // Переменные для вывода результата
  cred_info result = {0, 0, 0, 0};
  if (loan_amount == 0 || interest_rate == 0 || loan_term == 0) {
    error_code = FAILURE;
    ui->error_show->setText("Ошибка! Заполните все поля.");
  }

  if (ui->annuity->isChecked()) {
    cred_type = 'A';
  } else if (ui->differentiated->isChecked()) {
    cred_type = 'D';
  } else {
    error_code = FAILURE;
    ui->error_show->setText("Ошибка! Выберите тип платежа по кредиту.");
  }
  if (ui->time_type->currentText() == "Лет") {
    if (loan_term <= 50) {
      loan_term *= 12;
    } else {
      error_code = FAILURE;
      ui->error_show->setText("Ошибка! Максимальный срок займа - 50 лет.");
    }
  }
  if (error_code == SUCCESS) {
    result = credit(loan_amount, loan_term, interest_rate, cred_type);
    ui->m_payment->setText(QString::number(result.monthly_payment, 'f', 2));
    if (cred_type == 'A') {
      ui->first_pay->setText("Ежемесячный платеж");
      ui->last_pay->clear();
    } else if (cred_type == 'D') {
      ui->first_pay->setText("Платеж за первый месяц");
      ui->last_pay->setText("Платеж за последний месяц");
      ui->m_payment_last->setText(
          QString::number(result.last_monthly_payment, 'f', 2));
    }
    ui->total_payment->setText(QString::number(result.total_payment, 'f', 2));
    ui->interest_paid->setText(
        QString::number(result.total_interest_paid, 'f', 2));
  }
}
