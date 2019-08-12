#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{    
    tableExists = false;
    depositTable = new DepTable;

    createMenu();

    typeToShow = all;

    averageLabel = new QLabel(this);
    averageLabel->setGeometry(10,20,500,30);
}

void MainWindow::createMenu() {
    menu = menuBar()->addMenu(tr("&меню"));

    QAction *addRecordAction = new QAction(tr("&Добавить запись"), this);
    addRecordAction->setShortcuts(QKeySequence::AddTab);
    connect(addRecordAction, &QAction::triggered, this, &MainWindow::addRecordSlot);
    menu->addAction(addRecordAction);

    QAction *addRecordfromFileAction = new QAction(tr("&Добавить записи из файла"), this);
    addRecordfromFileAction->setShortcuts(QKeySequence::Find);
    connect(addRecordfromFileAction, &QAction::triggered, this, &MainWindow::addRecordsFromFile);
    menu->addAction(addRecordfromFileAction);

    QAction *clearTableAction = new QAction(tr("&Очистить таблицу"), this);
    connect(clearTableAction, &QAction::triggered, this, &MainWindow::clearTableSlot);
    menu->addAction(clearTableAction);

    menu2 = menuBar()->addMenu(tr("&Показать"));

    QAction *showPensionAction = new QAction(tr("&Показать только пенсионный"), this);
    connect(showPensionAction, &QAction::triggered, this, &MainWindow::showOnlyPension);
    menu2->addAction(showPensionAction);

    QAction *showDepositAction = new QAction(tr("&Показать только депозит"), this);
    connect(showDepositAction, &QAction::triggered, this, &MainWindow::showOnlyDeposit);
    menu2->addAction(showDepositAction);

    QAction *showUrgentAction = new QAction(tr("&Показать только срочный"), this);
    connect(showUrgentAction, &QAction::triggered, this, &MainWindow::showOnlyUrgent);
    menu2->addAction(showUrgentAction);

    QAction *showAllAction = new QAction(tr("&Показать все"), this);
    connect(showAllAction, &QAction::triggered, this, &MainWindow::showAll);
    menu2->addAction(showAllAction);

    QAction *showMoreAverageAction = new QAction(tr("&Показать у кого больше среднего"), this);
    connect(showMoreAverageAction, &QAction::triggered, this, &MainWindow::showMoreThanAverage);
    menu2->addAction(showMoreAverageAction);
}

void MainWindow::addRecordSlot() {
    AddRecordDialog *addRecordDialog = new AddRecordDialog;
    addRecordDialog->show();
    connect(addRecordDialog, &AddRecordDialog::clearTableSignal, this, &MainWindow::clearTableSlot);
    connect(addRecordDialog, SIGNAL(addReordSignal(QString)), this, SLOT(addRecord(QString)));
}

void MainWindow::addRecord(QString record) {
    try {
        depositTable->addRecord(record);

    }catch(int ex) {
        qDebug() << ex;
    }
    showTable(depositTable->getTable());
}

void MainWindow::addRecordsFromFile() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      QDir::homePath(),
                                                      tr("TextFiles (*.txt)"));
    QFile file(filePath);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly))) {
        while(!file.atEnd()) {
            QString string;
            string = file.readLine();
            string = string.trimmed();
            addRecord(string);
        }
    }
}

void MainWindow::clearTableSlot(){
    model->clear();
    tableView->setModel(model);
    tableExists = false;
    depositTable->deleteTable();
}

void MainWindow::showTable(QVector<QVector<QString>> table) {
    if(tableExists) {
        model->clear();
        tableView->setModel(model);
        tableExists = false;
        averageLabel->hide();
    }

    averageLabel->setText("Среднее значение суммы выплат через год - " + QString::number(depositTable->getAverageSum()));
    averageLabel->show();

    model = new QStandardItemModel;
    QStandardItem *item;

    QStringList headers;
    headers << "ID" << "ФИО" << "Вид вклада" << "Сумма вклада" << "Годовой\nпроцент" <<
            "Сумма\nпо процентам\nза месяц" << "Сумма\nк выплате";
    model->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < table.size(); i++)
        for (int j = 0; j < headers.size(); j++)
        {
            item = new QStandardItem(QString(table[i][j]));
            item->setTextAlignment(Qt::AlignCenter);
            model->setItem(i, j, item);
        }

    tableView = new QTableView(this);
    tableView->setModel(model);

    tableView->setGeometry(0,50,745, this->height() - 50);
    tableView->setColumnWidth(0, tableView->columnWidth(0) - 20);
    tableView->setColumnWidth(1, tableView->columnWidth(1) + 20);
    tableView->resizeRowsToContents();
    tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tableView->horizontalHeader()->setSectionsClickable(true);
    tableView->show();
    connect(tableView->horizontalHeader(), SIGNAL(sectionPressed(int)), this, SLOT(headerClicked(int)));
    tableExists = true;

    switch (typeToShow) {
    case pension:
        showOnlyPension();
        break;
    case deposit:
        showOnlyDeposit();
        break;
    case urgent:
        showOnlyUrgent();
        break;
    case all:
        break;
    }
}

void MainWindow::showOnlyPension() {
    QVector<QVector<QString>> onlyPension;
    QVector<QVector<QString>> full = depositTable->getTable();
    for(int i = 0; i < full.size(); i++) {
        if(full[i][2] == "пенсионный") {
            onlyPension << full[i];
        }
    }
    typeToShow = all;
    showTable(onlyPension);
    typeToShow = pension;
}

void MainWindow::showOnlyDeposit() {
    QVector<QVector<QString>> onlyDeposit;
    QVector<QVector<QString>> full = depositTable->getTable();
    for(int i = 0; i < full.size(); i++) {
        if(full[i][2] == "депозит") {
            onlyDeposit << full[i];
        }
    }
    typeToShow = all;
    showTable(onlyDeposit);
    typeToShow = deposit;
}

void MainWindow::showOnlyUrgent() {
    QVector<QVector<QString>> onlyUrgent;
    QVector<QVector<QString>> full = depositTable->getTable();
    for(int i = 0; i < full.size(); i++) {
        if(full[i][2] == "срочный") {
            onlyUrgent << full[i];
        }
    }
    typeToShow = all;
    showTable(onlyUrgent);
    typeToShow = urgent;
}

void MainWindow::showAll() {
    typeToShow = all;
    showTable(depositTable->getTable());
}

void MainWindow::showMoreThanAverage() {
    typeToShow = all;
    int average = depositTable->getAverageSum();

    QVector<QVector<QString>> onlyMoreThanAverage;
    QVector<QVector<QString>> full = depositTable->getTable();
    for(int i = 0; i < full.size(); i++) {
        if(full[i][6].toInt() > average) {
            onlyMoreThanAverage << full[i];
        }
    }
    showTable(onlyMoreThanAverage);
}

void MainWindow::headerClicked(int id) {
    depositTable->clickedToSort(id);
    showTable(depositTable->getTable());
}

MainWindow::~MainWindow()
{

}
