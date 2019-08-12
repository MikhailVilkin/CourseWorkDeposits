#include "addrecorddialog.h"

AddRecordDialog::AddRecordDialog(QWidget *parent) : QDialog(parent)
{    
    this->setGeometry(this->pos().x() + 200, this->pos().y() + 100, 400, 270);
    this->setWindowTitle("Добавление записи");
    this->show();

    idLabel = new QLabel(this);
    idLabel->setGeometry(20, 20, 100, 30);
    idLabel->setText("id: ");
    idLabel->show();
    idGetter = new QLineEdit(this);
    idGetter->setGeometry(140, 20, 200, 30);
    idGetter->show();

    nameLabel = new QLabel(this);
    nameLabel->setGeometry(20, 70, 100, 30);
    nameLabel->setText("ФИО: ");
    nameLabel->show();
    nameGetter = new QLineEdit(this);
    nameGetter->setGeometry(140, 70, 200, 30);
    nameGetter->show();

    typeLabel = new QLabel(this);
    typeLabel->setGeometry(20, 120, 100, 30);
    typeLabel->setText("Вид вклада: ");
    typeLabel->show();
    typeGetter = new QLineEdit(this);
    typeGetter->setGeometry(140, 120, 200, 30);
    typeGetter->show();

    sumLabel = new QLabel(this);
    sumLabel->setGeometry(20, 170, 100, 30);
    sumLabel->setText("Сумма вклада: ");
    sumLabel->show();
    sumGetter = new QLineEdit(this);
    sumGetter->setGeometry(140, 170, 200, 30);
    sumGetter->show();

    okButton = new QPushButton(this);
    okButton->setGeometry(30, 220, 100, 30);
    okButton->setText("OK");
    okButton->show();
    connect(okButton, &QPushButton::clicked, this, &AddRecordDialog::okButtonPushed);

    applyButton = new QPushButton(this);
    applyButton->setGeometry(150, 220, 100, 30);
    applyButton->setText("Apply");
    applyButton->show();
    connect(applyButton, &QPushButton::clicked, this, &AddRecordDialog::applyButtonPushed);

    cancelButton = new QPushButton(this);
    cancelButton->setGeometry(270, 220, 100, 30);
    cancelButton->setText("Cancel");
    cancelButton->show();
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::close);
}

void AddRecordDialog::okButtonPushed() {
    QString record;
    record = getRecord();
    if (record == "") {
        return;
    }
    emit addReordSignal(record);

    this->close();
}

void AddRecordDialog::applyButtonPushed() {
    QString record;
    record = getRecord();
    if (record == "") {
        return;
    }
    emit addReordSignal(record);

    idGetter->clear();
    nameGetter->clear();
    typeGetter->clear();
    sumGetter->clear();
}

QString AddRecordDialog::getRecord() {
    QRegExp regExpNumbers("\\d+"), regExpName("[а-яА-Я]+\\s+[а-яА-Я]{1}.\\s+[а-яА-Я]{1}.");
    bool flag = false;
    if(!regExpNumbers.exactMatch(idGetter->text())) {
        idGetter->setText("WRONG!");
        flag = true;
    }
    if(!regExpNumbers.exactMatch(sumGetter->text())) {
        sumGetter->setText("WRONG!");
        flag = true;
    }
    if(typeGetter->text() != "пенсионный" && typeGetter->text() != "срочный" && typeGetter->text() != "депозит") {
        typeGetter->setText("WRONG!");
        flag = true;
    }
    if(!regExpName.exactMatch(nameGetter->text())) {
        nameGetter->setText("WRONG!");
        flag = true;
    }

    if(flag) {
        return "";
    }

    QString record;
    record = idGetter->text() + ", " + nameGetter->text() +  ", " + typeGetter->text() +  ", " + sumGetter->text();
    return record;
}

void AddRecordDialog::clearTableSlot(){
    emit clearTableSignal();
}
