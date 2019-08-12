#ifndef ADDRECORDDIALOG_H
#define ADDRECORDDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class AddRecordDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddRecordDialog(QWidget *parent = nullptr);
signals:
    void clearTableSignal();
    void addReordSignal(QString);
public slots:
    void clearTableSlot();
    void okButtonPushed();
    void applyButtonPushed();
private:
    QLabel *idLabel;
    QLineEdit *idGetter;
    QLabel *nameLabel;
    QLineEdit *nameGetter;
    QLabel *typeLabel;
    QLineEdit *typeGetter;
    QLabel *sumLabel;
    QLineEdit *sumGetter;
    QPushButton *okButton;
    QPushButton *applyButton;
    QPushButton *cancelButton;
    QString getRecord();
};

#endif // ADDRECORDDIALOG_H
