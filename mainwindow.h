#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTableView>
#include <QHeaderView>
#include "deptable.h"
#include "QStandardItemModel"
#include "QStandardItem"
#include <QMenuBar>
#include "addrecorddialog.h"
#include <QFileDialog>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QTableView *tableView;
    QStandardItemModel *model;

    DepTable *depositTable;

    void showTable(QVector<QVector<QString>> table);
public slots:
    void headerClicked(int id);
    void addRecordSlot();
    void addRecordsFromFile();
    void clearTableSlot();
    void addRecord(QString record);

    void showOnlyPension();
    void showOnlyDeposit();
    void showOnlyUrgent();
    void showAll();
    void showMoreThanAverage();
private:
    bool tableExists;
    QMenu *menu, *menu2;
    void createMenu();
    enum typeShown {pension, urgent, deposit, all};
    typeShown typeToShow;
    QLabel *averageLabel;
};

#endif // MAINWINDOW_H
