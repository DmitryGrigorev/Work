#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "data.h"
#include "grf_reader.h"
#include "settings.h"
#include <QFileDialog>
#include <QLabel>
#include <QMainWindow>
#include <QTableWidgetItem>
#include <QToolBar>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
  void InitToolBars();
  void setStatusLabelText(const char *text);
  void SetTable(Record *record);
  void SetTable(NewRecord *record);
  void SetTable(OldRecord *record);
private slots:
  void on_actionOpenFile_triggered();
  void on_actionExit_triggered();
  void on_tableWidget_itemChanged(QTableWidgetItem *item);

private:
  Ui::MainWindow *ui;
  QToolBar *left_toolbar, *right_toolbar;
  QLabel *status_label;
  QTextCodec *codec;
  QFileDialog *file_dialog;
  GRF_Reader *reader;
  Settings *settings;
};

#endif // MAINWINDOW_H
