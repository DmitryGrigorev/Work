#include "mainwindow.h"
#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QTextCodec>
#include <ui_mainwindow.h>

QList<QAction *> *action_list;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  status_label = new QLabel();
  status_label->setObjectName("statusLabel");
  ui->statusBar->insertWidget(0, status_label);
  InitToolBars();
  codec = QTextCodec::codecForName("Windows-1251");
  file_dialog = new QFileDialog(this, codec->toUnicode("Открыть файл отгрузки"),
                                "\\", codec->toUnicode("Файл отгрузки(*.GRF)"));
  status_label->setText(codec->toUnicode("Статус работы программы"));
  settings = new Settings();
  action_list = new QList<QAction *>();

  settings->LoadRecentFilesList(action_list);
  ui->menu->insertActions(ui->actionExit, *action_list);
  ui->menu->insertSeparator(
      ui->menu->actions().at(ui->menu->actions().count() - 1));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::InitToolBars() {
  left_toolbar = new QToolBar();
  left_toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  left_toolbar->insertAction(NULL, ui->actionExit);
  left_toolbar->insertAction(NULL, ui->actionUnitNumber);
  left_toolbar->insertSeparator(NULL);
  left_toolbar->insertAction(NULL, ui->actionCreateFile);
  left_toolbar->insertAction(NULL, ui->actionOpenFile);
  left_toolbar->insertAction(NULL, ui->actionFileSave);
  left_toolbar->insertSeparator(NULL);
  left_toolbar->insertAction(NULL, ui->actionReadDataBPI);
  left_toolbar->insertAction(NULL, ui->actionClearBPI);
  left_toolbar->insertAction(NULL, ui->actionResetPortBPI);
  left_toolbar->insertSeparator(NULL);
  left_toolbar->insertAction(NULL, ui->actionDelete);
  left_toolbar->insertAction(NULL, ui->actionEdit);
  left_toolbar->insertAction(NULL, ui->actionSelectAll);
  left_toolbar->insertSeparator(NULL);
  left_toolbar->insertAction(NULL, ui->actionRemoveGraph);
  left_toolbar->insertAction(NULL, ui->actionAddGraph);
  left_toolbar->setIconSize(QSize(20, 20));
  left_toolbar->show();
  ui->bar_frame->layout()->addWidget(left_toolbar);

  right_toolbar = new QToolBar();
  right_toolbar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  right_toolbar->insertAction(NULL, ui->actionClearCanvas);
  right_toolbar->insertAction(NULL, ui->actionCopyGraph);
  right_toolbar->insertAction(NULL, ui->actionRemoveSelGraph);
  right_toolbar->insertSeparator(NULL);
  right_toolbar->insertAction(NULL, ui->actionGraphArrange);
  right_toolbar->insertAction(NULL, ui->actionMaximizeToCanvas);
  right_toolbar->insertAction(NULL, ui->actionScaleHorizontal);
  right_toolbar->insertAction(NULL, ui->actionScaleVertical);
  right_toolbar->insertAction(NULL, ui->actionStretchHorizontal);
  right_toolbar->insertAction(NULL, ui->actionStretchVertical);
  right_toolbar->insertAction(NULL, ui->actionFitInView);
  right_toolbar->insertSeparator(NULL);
  right_toolbar->insertAction(NULL, ui->actionPreviewShow);
  right_toolbar->insertAction(NULL, ui->actionPrint);
  right_toolbar->setIconSize(QSize(20, 20));
  right_toolbar->show();
  ui->bar_frame_right->layout()->addWidget(right_toolbar);
}

QDataStream &operator>>(QDataStream &in, char *v) {
  in.readRawData(v, sizeof(v));
  return in;
}

QDataStream &operator>>(QDataStream &in, DWord &val) {
  unsigned short t = 0;
  in.readRawData((char *)&t, sizeof(t));
  val = t;
  return in;
}

/*!
 * \brief UnixStartDate
 */
double UnixStartDate = 25569.0;
/*!
 * \brief fromTDateTime
 * \param tDateTime
 * \return
 */
time_t fromTDateTime(double &tDateTime) {
  time_t tm = ((time_t)(tDateTime - UnixStartDate)) * 86400;
  return tm;
}

void MainWindow::on_actionOpenFile_triggered() {
  file_dialog->setAcceptMode(QFileDialog::AcceptOpen);
  if (file_dialog->exec() != QDialog::Accepted) {
    ;
    ; // Error
  } else {
    reader = new GRF_Reader(file_dialog->selectedFiles().first());
    reader->SetParentWidgetPointer(this);
    reader->BeginReading(this);
    QString s = file_dialog->selectedFiles().at(0);
    settings->AddNextFileName(s);
  }
}

void MainWindow::on_actionExit_triggered() { this->close(); }

void MainWindow::on_tableWidget_itemChanged(QTableWidgetItem *item) {
  Q_UNUSED(item);
}

int k = 0;
void MainWindow::SetTable(Record *record) {

  QTableWidgetItem *name = new QTableWidgetItem(codec->toUnicode(record->name)),
                   *date = new QTableWidgetItem(record->data_),
                   *time = new QTableWidgetItem(record->time_),
                   *weld_id =
                       new QTableWidgetItem(QString::number(record->svar)),
                   *unit_id =
                       new QTableWidgetItem(QString::number(record->detal)),
                   *duration = new QTableWidgetItem(
                       QString::number((float)record->count * 0.1f));

  ui->tableWidget->insertRow(k);
  ui->tableWidget->setItem(k, 0, name);
  ui->tableWidget->setItem(k, 1, weld_id);
  ui->tableWidget->setItem(k, 2, unit_id);
  ui->tableWidget->setItem(k, 3, duration);
  ui->tableWidget->setItem(k, 4, time);
  ui->tableWidget->setItem(k, 5, date);
  ui->tableWidget->update();

  k++;
}

int l = 0;
void MainWindow::SetTable(NewRecord *record) {
  QTableWidgetItem *name = new QTableWidgetItem(codec->toUnicode(record->name)),
                   *date = new QTableWidgetItem(record->data_),
                   *time = new QTableWidgetItem(record->time_),
                   *weld_id =
                       new QTableWidgetItem(QString::number(record->svar)),
                   *unit_id =
                       new QTableWidgetItem(QString::number(record->detal)),
                   *duration = new QTableWidgetItem(
                       QString::number((float)record->count * 0.1f));

  ui->tableWidget->insertRow(l);
  ui->tableWidget->setItem(l, 0, name);
  ui->tableWidget->setItem(l, 1, weld_id);
  ui->tableWidget->setItem(l, 2, unit_id);
  ui->tableWidget->setItem(l, 3, duration);
  ui->tableWidget->setItem(l, 4, time);
  ui->tableWidget->setItem(l, 5, date);
  ui->tableWidget->update();

  l++;
}

void MainWindow::SetTable(OldRecord *record) {
  QTableWidgetItem *name = new QTableWidgetItem(codec->toUnicode(record->name)),
                   *date = new QTableWidgetItem(record->data_),
                   *time = new QTableWidgetItem(record->time_),
                   *weld_id =
                       new QTableWidgetItem(QString::number(record->svar)),
                   *unit_id =
                       new QTableWidgetItem(QString::number(record->detal)),
                   *duration = new QTableWidgetItem(
                       QString::number((float)record->count * 0.1f));

  ui->tableWidget->insertRow(k);
  ui->tableWidget->setItem(k, 0, name);
  ui->tableWidget->setItem(k, 1, weld_id);
  ui->tableWidget->setItem(k, 2, unit_id);
  ui->tableWidget->setItem(k, 3, duration);
  ui->tableWidget->setItem(k, 4, time);
  ui->tableWidget->setItem(k, 5, date);
  ui->tableWidget->update();

  k++;
}
