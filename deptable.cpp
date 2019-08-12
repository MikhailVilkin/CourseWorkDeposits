#include "deptable.h"
#include <QDebug>

DepTable::DepTable()
{
    countOfRecords = 0;
}

void DepTable::addRecord(QString record) {

    QStringList types = record.split(", ");
    if(types.size() != 4)
        throw 210;
    foreach(QString str, types) {
        str.replace("^[a-zA-Zа-яА-Я0-9]", "");
    }

    QVector<QString> recordVector;
    for(int i = 0; i < 4; i++) {
        recordVector << types[i];
    }

    if(recordVector[2] == "пенсионный")
        recordVector << "12";
    else if(recordVector[2] == "срочный")
        recordVector << "24";
    else if(recordVector[2] == "депозит")
        recordVector << "30";
    else throw 220;

    int sumForMonth = (recordVector[3].toInt() * recordVector[4].toInt() / 100) / 12;
    recordVector << QString::number(sumForMonth);

    recordVector << QString::number(recordVector[3].toInt() + sumForMonth * 12);

    records << recordVector;
    countOfRecords++;
}

int DepTable::getAverageSum() {
    int sum = 0;
    for(int i = 0; i < countOfRecords; i++) {
        sum += records[i][6].toInt();
    }

    return sum / countOfRecords;
}

QVector<QVector<QString>> DepTable::getTable() {return records;}

void DepTable::deleteTable() {
    countOfRecords=0;
    records.clear();
}

void DepTable::clickedToSort(int field) {
    int item;
    bool changed = false;
    for(int counter = 1; counter < records.size(); counter++) {
        item = counter - 1;
        if(integers.contains(field))
        {
            while(item >= 0 && records[item][field].toInt() > records[item+1][field].toInt()) {
                std::swap(records[item+1], records[item]);
                changed = true;
                item--;
            }
        }
        else {
            while(item >= 0 && records[item][field].compare(records[item+1][field]) > 0)
            {
                std::swap(records[item+1], records[item]);
                changed = true;
                item--;
            }
        }
    }
    if(!changed)
        std::reverse(records.begin(), records.end());
}
