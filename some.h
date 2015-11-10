#ifndef CHANGEDATA_H
#define CHANGEDATA_H

#include <QDialog>


namespace Ui {
class changeData;
}

class changeData : public QDialog
{
    Q_OBJECT

public:
    explicit changeData(QWidget *parent, void ** &start1);
    ~changeData();

private slots:
    void on_addElement_clicked();

    void on_changeElement_clicked();

    void on_deleteElement_clicked();

    void on_exit_clicked();

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_radioButton_3_clicked();

    void on_radioButton_4_clicked();

    void on_comOtdel_activated(const QString &arg1);

    void on_comSector_activated(const QString &arg1);

    void on_comSluzhashie_activated(const QString &arg1);

    void on_comRabochie_activated(const QString &arg1);

private:
    Ui::changeData *ui;
    void** &Start;
};

#endif // CHANGEDATA_H
