#ifndef DEPTABLE_H
#define DEPTABLE_H

#include <QVector>

class DepTable
{
public:
    DepTable();

    void addRecord(QString record);
    QVector<QVector<QString>> getTable();
    void deleteTable();

    int countOfRecords;
    int getAverageSum();

    void clickedToSort(int field);
private:
    QVector<QVector<QString>> records;
    const QVector<int> integers = {0, 3, 4, 5, 6};
};

#endif // DEPTABLE_H
