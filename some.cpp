#include "changedata.h"
#include "ui_changedata.h"

#include <struct.h>
#include <functions.h>

int numberOfWorkers = 0;

changeData::changeData(QWidget *parent, void** &start1) :
    QDialog(parent),
    ui(new Ui::changeData), Start(start1)
{
    ui->setupUi(this);
}

changeData::~changeData()
{
    delete ui;
}

void changeData::on_addElement_clicked()
{
    if(Start == NULL){
        InitArray(Start);
    }
    if(ui->radioButton->isChecked()){
        TOtdel * pnew;
        pnew = new TOtdel;
        InitArray(pnew->sublev);

        pnew->kod = ui->enterCode1->text();
        pnew->name = ui->EnterName1->text();
        pnew->fioNachalnika = ui->enterFIO1->text();
        pnew->nTelefona = ui->enterTelNum1->text();
        if (pnew->name == NULL || pnew->name == "")
            return;

        int posFndEl;
        bool findOK;
        QString key = ui->EnterName1->text();
        FindElList(Start, key, posFndEl, findOK, cmpOtdel);
        addToSort(Start, pnew, posFndEl);
        ui->comOtdel->clear();
    }
    if(ui->radioButton_2->isChecked()){
        int posFndEl;
        int posFndEl_1;
        bool findOK;
        TSector* pnew;
        pnew = new TSector;
        InitArray(pnew->sublevR);
        InitArray(pnew->sublevS);

        pnew->name = ui->enterName2->text();
        pnew->fioNachalnika = ui->enterFIO2->text();
        pnew->nTelefona = ui->enterTelNum2->text();
        if (pnew->name == NULL || pnew->name == "")
            return;

        QString key = ui->comOtdel->currentText();
        QString key2 = ui->enterName2->text();
        FindElList(Start, key, posFndEl, findOK, cmpOtdel);
        void **sect = ((TOtdel*)Start[posFndEl])->sublev;
        FindElList(sect, key2, posFndEl_1, findOK, cmpSector);
        addToSort(sect, pnew, posFndEl_1);

        ((TOtdel*)Start[posFndEl])->sublev = sect;
        ui->comSector->clear();
    }

    if(ui->radioButton_3->isChecked()){
        int posFndEl_1;
        int posFndEl_2;
        int posFndEl_3;
        bool findOK;
        TSluzhazhie* pnew;
        pnew = new TSluzhazhie;

        pnew->tabelNomer = ui->enterTabNum3->text();
        pnew->name = ui->enterFIO3->text();
        pnew->address = ui->enterAdr3->text();
        pnew->dolzhnost = ui->enterDolzhn3->text();
        pnew->oklad = ui->enterFee3->text();
        if (pnew->name == NULL || pnew->name == "")
            return;

        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        QString key3 = ui->enterFIO3->text();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        ((TOtdel*)Start[posFndEl_1])->kolichestvoSotrudnikov = QString::number(++numberOfWorkers);
        void **sect = ((TOtdel*)Start[posFndEl_1])->sublev;
        FindElList(sect, key2, posFndEl_2, findOK, cmpSector);
        void **sluzh = ((TSector*)sect[posFndEl_2])->sublevS;

        FindElList(sluzh, key3, posFndEl_3, findOK, cmpSluzhashie);
        addToSort(sluzh, pnew, posFndEl_3);
        ((TSector*)sect[posFndEl_2])->sublevS = sluzh;
    }

    if(ui->radioButton_4->isChecked()){
        int posFndEl_1;
        int posFndEl_2;
        int posFndEl_3;
        bool findOK;
        TRabochie* pnew = new TRabochie;

        pnew->tabelNomer = ui->enterTabNum4->text();
        pnew->name = ui->enterFIO4->text();
        pnew->address = ui->enterAdr4->text();
        pnew->professiia = ui->enterProf4->text();
        pnew->razriad = ui->enterRazr4->text();
        pnew->tarif = ui->enterFee4->text();
        if (pnew->name == NULL || pnew->name == "")
            return;
        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        QString key3 = ui->enterFIO4->text();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        ((TOtdel*)Start[posFndEl_1])->kolichestvoSotrudnikov = QString::number(++numberOfWorkers);
        void **sect = ((TOtdel*)Start[posFndEl_1])->sublev;
        FindElList(sect, key2, posFndEl_2, findOK, cmpSector);
        void **rabch = (((TSector*)sect[posFndEl_2])->sublevR);
        FindElList(rabch, key3, posFndEl_3, findOK, cmpRabochie);
        addToSort(rabch, pnew, posFndEl_3);
        (((TSector*)sect[posFndEl_2])->sublevR) = rabch;
    }

    ui->enterCode1->clear();
    ui->EnterName1->clear();
    ui->enterFIO1->clear();
    ui->enterTelNum1->clear();

    ui->enterName2->clear();
    ui->enterFIO2->clear();
    ui->enterTelNum2->clear();

    ui->enterTabNum3->clear();
    ui->enterFIO3->clear();
    ui->enterAdr3->clear();
    ui->enterDolzhn3->clear();
    ui->enterFee3->clear();

    ui->enterTabNum4->clear();
    ui->enterFIO4->clear();
    ui->enterAdr4->clear();
    ui->enterProf4->clear();
    ui->enterRazr4->clear();
    ui->enterFee4->clear();

    ui->comOtdel->clear();
    ui->comSector->clear();
    ui->comSluzhashie->clear();
    ui->comRabochie->clear();
    for(int i = 0; i < ((int*)Start)[POS_CNT]; i++){
        ui->comOtdel->addItem(((TOtdel*)Start[i])->name);
    }
}


void changeData::on_changeElement_clicked()
{
    if(ui->radioButton->isChecked()){
        int posFndEl_1, posFndEl;
        bool findOK;
        TOtdel * pnew;
        pnew = new TOtdel;

        QString key1 = ui->comOtdel->currentText();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        pnew->sublev = ((TOtdel*)Start[posFndEl_1])->sublev;
        Delete(Start,posFndEl_1);

        pnew->kod = ui->enterCode1->text();
        pnew->name = ui->EnterName1->text();
        pnew->fioNachalnika = ui->enterFIO1->text();
        pnew->nTelefona = ui->enterTelNum1->text();

        QString key = ui->EnterName1->text();
        FindElList(Start, key, posFndEl, findOK, cmpOtdel);
        addToSort(Start, pnew, posFndEl);
        ui->comOtdel->clear();
    }
    if(ui->radioButton_2->isChecked()){
        int posFndEl_1;
        int posFndEl_2;
        bool findOK;
        TSector* pnew;
        pnew = new TSector;

        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        void **sect = ((TOtdel*)Start[posFndEl_1])->sublev;
        FindElList(sect, key2, posFndEl_2, findOK, cmpSector);
        pnew->sublevR = ((TSector*)sect[posFndEl_2])->sublevR;
        pnew->sublevS = ((TSector*)sect[posFndEl_2])->sublevS;
        Delete(sect, posFndEl_2);

        pnew->name = ui->enterName2->text();
        pnew->fioNachalnika = ui->enterFIO2->text();
        pnew->nTelefona = ui->enterTelNum2->text();

        QString key3 = ui->enterName2->text();

        FindElList(sect, key3, posFndEl_1, findOK, cmpSector);
        addToSort(sect, pnew, posFndEl_1);
        ui->comSector->clear();
    }
    if(ui->radioButton_3->isChecked()){        
        int posFndEl_1;
        int posFndEl_2;
        int posFndEl_3;
        bool findOK;
        TSluzhazhie* pnew;
        pnew = new TSluzhazhie;

        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        QString key3 = ui->comSluzhashie->currentText();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        ((TOtdel*)Start[posFndEl_1])->kolichestvoSotrudnikov = QString::number(--numberOfWorkers);
        void **sect = ((TOtdel*)Start[posFndEl_1])->sublev;
        FindElList(sect, key2, posFndEl_2, findOK, cmpSector);
        void **sluzh = ((TSector*)sect[posFndEl_2])->sublevS;
        FindElList(sluzh, key3, posFndEl_3, findOK, cmpSluzhashie);
        Delete(sluzh, posFndEl_3);

        pnew->tabelNomer = ui->enterTabNum3->text();
        pnew->name = ui->enterFIO3->text();
        pnew->address = ui->enterAdr3->text();
        pnew->dolzhnost = ui->enterDolzhn3->text();
        pnew->oklad = ui->enterFee3->text();

        QString key4 = ui->enterFIO3->text();
        FindElList(sluzh, key4, posFndEl_3, findOK, cmpSluzhashie);
        addToSort(sluzh, pnew, posFndEl_3);


    }
    if(ui->radioButton_4->isChecked()){
        int posFndEl_1;
        int posFndEl_2;
        int posFndEl_3;
        bool findOK;
        TRabochie* pnew = new TRabochie;

        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        QString key3 = ui->comRabochie->currentText();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        ((TOtdel*)Start[posFndEl_1])->kolichestvoSotrudnikov = QString::number(--numberOfWorkers);
        void **sect = ((TOtdel*)Start[posFndEl_1])->sublev;
        FindElList(sect, key2, posFndEl_2, findOK, cmpSector);
        void **rabch = ((TSector*)sect[posFndEl_2])->sublevR;
        FindElList(rabch, key3, posFndEl_3, findOK, cmpRabochie);
        Delete(rabch, posFndEl_3);

        pnew->tabelNomer = ui->enterTabNum4->text();
        pnew->name = ui->enterFIO4->text();
        pnew->address = ui->enterAdr4->text();
        pnew->professiia = ui->enterProf4->text();
        pnew->razriad = ui->enterRazr4->text();
        pnew->tarif = ui->enterFee4->text();

        QString key4 = ui->enterFIO4->text();
        FindElList(rabch, key4, posFndEl_3, findOK, cmpRabochie);
        addToSort(rabch, pnew, posFndEl_3);
    }

    ui->enterCode1->clear();
    ui->EnterName1->clear();
    ui->enterFIO1->clear();
    ui->enterTelNum1->clear();

    ui->enterName2->clear();
    ui->enterFIO2->clear();
    ui->enterTelNum2->clear();

    ui->enterTabNum3->clear();
    ui->enterFIO3->clear();
    ui->enterAdr3->clear();
    ui->enterDolzhn3->clear();
    ui->enterFee3->clear();

    ui->enterTabNum4->clear();
    ui->enterFIO4->clear();
    ui->enterAdr4->clear();
    ui->enterProf4->clear();
    ui->enterRazr4->clear();
    ui->enterFee4->clear();

    ui->comOtdel->clear();
    ui->comSector->clear();
    ui->comSluzhashie->clear();
    ui->comRabochie->clear();
    for(int i = 0; i < ((int*)Start)[POS_CNT]; i++){
        ui->comOtdel->addItem(((TOtdel*)Start[i])->name);
    }
}

void changeData::on_deleteElement_clicked()
{
    if(ui->radioButton->isChecked()){
        int posFndEl_1;
        bool findOK;
        QString key1 = ui->comOtdel->currentText();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        Delete(Start,posFndEl_1);
    }
    if(ui->radioButton_2->isChecked()){
        int posFndEl_1;
        int posFndEl_2;
        bool findOK;
        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        void **sect = ((TOtdel*)Start[posFndEl_1])->sublev;
        FindElList(sect, key2, posFndEl_2, findOK, cmpSector);
        Delete(sect, posFndEl_2);
    }
    if(ui->radioButton_3->isChecked()){
        int posFndEl_1;
        int posFndEl_2;
        int posFndEl_3;
        bool findOK;
        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        QString key3 = ui->comSluzhashie->currentText();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        ((TOtdel*)Start[posFndEl_1])->kolichestvoSotrudnikov = QString::number(--numberOfWorkers);
        void **sect = ((TOtdel*)Start[posFndEl_1])->sublev;
        FindElList(sect, key2, posFndEl_2, findOK, cmpSector);
        void **sluzh = ((TSector*)sect[posFndEl_2])->sublevS;
        FindElList(sluzh, key3, posFndEl_3, findOK, cmpSluzhashie);
        Delete(sluzh, posFndEl_3);
    }
    if(ui->radioButton_4->isChecked()){
        int posFndEl_1;
        int posFndEl_2;
        int posFndEl_3;
        bool findOK;
        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        QString key3 = ui->comRabochie->currentText();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        ((TOtdel*)Start[posFndEl_1])->kolichestvoSotrudnikov = QString::number(--numberOfWorkers);
        void **sect = ((TOtdel*)Start[posFndEl_1])->sublev;
        FindElList(sect, key2, posFndEl_2, findOK, cmpSector);
        void **rabch = ((TSector*)sect[posFndEl_2])->sublevR;
        FindElList(rabch, key3, posFndEl_3, findOK, cmpRabochie);
        Delete(rabch, posFndEl_3);
    }
    ui->enterCode1->clear();
    ui->EnterName1->clear();
    ui->enterFIO1->clear();
    ui->enterTelNum1->clear();

    ui->enterName2->clear();
    ui->enterFIO2->clear();
    ui->enterTelNum2->clear();

    ui->enterTabNum3->clear();
    ui->enterFIO3->clear();
    ui->enterAdr3->clear();
    ui->enterDolzhn3->clear();
    ui->enterFee3->clear();

    ui->enterTabNum4->clear();
    ui->enterFIO4->clear();
    ui->enterAdr4->clear();
    ui->enterProf4->clear();
    ui->enterRazr4->clear();
    ui->enterFee4->clear();

    ui->comOtdel->clear();
    ui->comSector->clear();
    ui->comSluzhashie->clear();
    ui->comRabochie->clear();
    for(int i = 0; i < ((int*)Start)[POS_CNT]; i++){
        ui->comOtdel->addItem(((TOtdel*)Start[i])->name);
    }
}

void changeData::on_exit_clicked()
{
    this->hide();
}

void changeData::on_radioButton_clicked()
{
    ui->comOtdel->setEnabled(true);
    ui->comSector->setEnabled(false);
    ui->comSluzhashie->setEnabled(false);
    ui->comRabochie->setEnabled(false);

    ui->enterCode1->setEnabled(true);
    ui->EnterName1->setEnabled(true);
    ui->enterFIO1->setEnabled(true);
    ui->enterTelNum1->setEnabled(true);

    ui->enterName2->setEnabled(false);
    ui->enterFIO2->setEnabled(false);
    ui->enterTelNum2->setEnabled(false);

    ui->enterTabNum3->setEnabled(false);
    ui->enterFIO3->setEnabled(false);
    ui->enterAdr3->setEnabled(false);
    ui->enterDolzhn3->setEnabled(false);
    ui->enterFee3->setEnabled(false);

    ui->enterTabNum4->setEnabled(false);
    ui->enterFIO4->setEnabled(false);
    ui->enterAdr4->setEnabled(false);
    ui->enterProf4->setEnabled(false);
    ui->enterRazr4->setEnabled(false);
    ui->enterFee4->setEnabled(false);

    if(Start!=NULL){
        ui->comOtdel->clear();
        for(int i = 0; i < ((int*)Start)[POS_CNT]; i++){
            ui->comOtdel->addItem(((TOtdel*)Start[i])->name);
            }
    }
}


void changeData::on_radioButton_2_clicked()
{
    ui->comOtdel->setEnabled(true);
    ui->comSector->setEnabled(true);
    ui->comSluzhashie->setEnabled(false);
    ui->comRabochie->setEnabled(false);

    ui->enterCode1->setEnabled(false);
    ui->EnterName1->setEnabled(false);
    ui->enterFIO1->setEnabled(false);
    ui->enterTelNum1->setEnabled(false);

    ui->enterName2->setEnabled(true);
    ui->enterFIO2->setEnabled(true);
    ui->enterTelNum2->setEnabled(true);

    ui->enterTabNum3->setEnabled(false);
    ui->enterFIO3->setEnabled(false);
    ui->enterAdr3->setEnabled(false);
    ui->enterDolzhn3->setEnabled(false);
    ui->enterFee3->setEnabled(false);

    ui->enterTabNum4->setEnabled(false);
    ui->enterFIO4->setEnabled(false);
    ui->enterAdr4->setEnabled(false);
    ui->enterProf4->setEnabled(false);
    ui->enterRazr4->setEnabled(false);
    ui->enterFee4->setEnabled(false);

    if(Start!=NULL){
        ui->comOtdel->clear();
        for(int i = 0; i < ((int*)Start)[POS_CNT]; i++){
            ui->comOtdel->addItem(((TOtdel*)Start[i])->name);
            }
    }
}

void changeData::on_radioButton_3_clicked()
{
    ui->comOtdel->setEnabled(true);
    ui->comSector->setEnabled(true);
    ui->comSluzhashie->setEnabled(true);
    ui->comRabochie->setEnabled(false);

    ui->enterCode1->setEnabled(false);
    ui->EnterName1->setEnabled(false);
    ui->enterFIO1->setEnabled(false);
    ui->enterTelNum1->setEnabled(false);

    ui->enterName2->setEnabled(false);
    ui->enterFIO2->setEnabled(false);
    ui->enterTelNum2->setEnabled(false);

    ui->enterTabNum3->setEnabled(true);
    ui->enterFIO3->setEnabled(true);
    ui->enterAdr3->setEnabled(true);
    ui->enterDolzhn3->setEnabled(true);
    ui->enterFee3->setEnabled(true);

    ui->enterTabNum4->setEnabled(false);
    ui->enterFIO4->setEnabled(false);
    ui->enterAdr4->setEnabled(false);
    ui->enterProf4->setEnabled(false);
    ui->enterRazr4->setEnabled(false);
    ui->enterFee4->setEnabled(false);

    if(Start!=NULL){
        ui->comOtdel->clear();
        for(int i = 0; i < ((int*)Start)[POS_CNT]; i++){
            ui->comOtdel->addItem(((TOtdel*)Start[i])->name);
            }
    }

}

void changeData::on_radioButton_4_clicked()
{
    ui->comOtdel->setEnabled(true);
    ui->comSector->setEnabled(true);
    ui->comSluzhashie->setEnabled(false);
    ui->comRabochie->setEnabled(true);


    ui->enterCode1->setEnabled(false);
    ui->EnterName1->setEnabled(false);
    ui->enterFIO1->setEnabled(false);
    ui->enterTelNum1->setEnabled(false);

    ui->enterName2->setEnabled(false);
    ui->enterFIO2->setEnabled(false);
    ui->enterTelNum2->setEnabled(false);

    ui->enterTabNum3->setEnabled(false);
    ui->enterFIO3->setEnabled(false);
    ui->enterAdr3->setEnabled(false);
    ui->enterDolzhn3->setEnabled(false);
    ui->enterFee3->setEnabled(false);

    ui->enterTabNum4->setEnabled(true);
    ui->enterFIO4->setEnabled(true);
    ui->enterAdr4->setEnabled(true);
    ui->enterProf4->setEnabled(true);
    ui->enterRazr4->setEnabled(true);
    ui->enterFee4->setEnabled(true);

    if(Start!=NULL){
        ui->comOtdel->clear();
        for(int i = 0; i < ((int*)Start)[POS_CNT]; i++){
            ui->comOtdel->addItem(((TOtdel*)Start[i])->name);
            }
    }
}

void changeData::on_comOtdel_activated(const QString &arg1)
{
    if(ui->radioButton->isChecked()){
        int pos; bool ok;
        FindElList(Start, arg1,pos,ok,cmpOtdel);
        ui->EnterName1->setText(((TOtdel*)Start[pos])->name);
        ui->enterFIO1->setText(((TOtdel*)Start[pos])->fioNachalnika);
        ui->enterCode1->setText(((TOtdel*)Start[pos])->kod);
        ui->enterTelNum1->setText(((TOtdel*)Start[pos])->nTelefona);
    }
    if(ui->radioButton_2->isChecked()||ui->radioButton_3->isChecked()||ui->radioButton_4->isChecked()){
        ui->comSector->clear();
        int posFndEl;
        bool findOK;
        QString key = ui->comOtdel->currentText();
        FindElList(Start, key, posFndEl, findOK, cmpOtdel);
        void **sect = ((TOtdel*)Start[posFndEl])->sublev;
        for(int j = 0; j < ((int*)sect)[POS_CNT]; j++){
            ui->comSector->addItem(((TSector*)sect[j])->name);
        }
    }
}

void changeData::on_comSector_activated(const QString &arg1)
{
    if(ui->radioButton_2->isChecked()){
        ui->enterName2->setText(arg1);
        int pos_1, pos_2; bool ok;
        QString key = ui->comOtdel->currentText();

        FindElList(Start, key, pos_1,ok,cmpOtdel);
        void **sect = ((TOtdel*)Start[pos_1])->sublev;
        FindElList(sect, arg1,pos_2,ok,cmpSector);
        ui->enterName2->setText(((TSector*)sect[pos_2])->name);
        ui->enterFIO2->setText(((TSector*)sect[pos_2])->fioNachalnika);
        ui->enterTelNum2->setText(((TSector*)sect[pos_2])->nTelefona);
    }
    if(ui->radioButton_3->isChecked()){
        ui->comSluzhashie->clear();
        int posFndEl_1;
        int posFndEl_2;
        bool findOK;
        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        void **sect = ((TOtdel*)Start[posFndEl_1])->sublev;
        FindElList(sect, key2, posFndEl_2, findOK, cmpSector);
        void **sluzh = ((TSector*)sect[posFndEl_2])->sublevS;
        for(int j = 0; j < ((int*)sluzh)[POS_CNT]; j++){
            ui->comSluzhashie->addItem(((TSluzhazhie*)sluzh[j])->name);
        }

    }
    if(ui->radioButton_4->isChecked()){
        ui->comRabochie->clear();
        int posFndEl_1;
        int posFndEl_2;
        bool findOK;
        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        FindElList(Start, key1, posFndEl_1, findOK, cmpOtdel);
        void **sect = ((TOtdel*)Start[posFndEl_1])->sublev;
        FindElList(sect, key2, posFndEl_2, findOK, cmpSector);
        void **rabt = ((TSector*)sect[posFndEl_2])->sublevR;
        for(int j = 0; j < ((int*)rabt)[POS_CNT]; j++){
            ui->comRabochie->addItem(((TRabochie*)rabt[j])->name);
        }
    }
}

void changeData::on_comSluzhashie_activated(const QString &arg1)
{
    if(ui->radioButton_3->isChecked()){
        ui->enterFIO3->setText(arg1);
        int pos1,pos2,pos3; bool ok;
        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        FindElList(Start, key1, pos1, ok, cmpOtdel);
        void **sect = ((TOtdel*)Start[pos1])->sublev;
        FindElList(sect, key2, pos2, ok, cmpSector);
        void **sluzh = ((TSector*)sect[pos2])->sublevS;
        FindElList(sluzh, arg1,pos3,ok,cmpSluzhashie);
        ui->enterFIO3->setText(((TSluzhazhie*)sluzh[pos3])->name);
        ui->enterAdr3->setText(((TSluzhazhie*)sluzh[pos3])->address);
        ui->enterDolzhn3->setText(((TSluzhazhie*)sluzh[pos3])->dolzhnost);
        ui->enterTabNum3->setText(((TSluzhazhie*)sluzh[pos3])->tabelNomer);
        ui->enterFee3->setText(((TSluzhazhie*)sluzh[pos3])->oklad);
    }
}

void changeData::on_comRabochie_activated(const QString &arg1)
{

    if(ui->radioButton_4->isChecked()){
        ui->enterFIO4->setText(arg1);
        int pos1,pos2,pos3; bool ok;
        QString key1 = ui->comOtdel->currentText();
        QString key2 = ui->comSector->currentText();
        FindElList(Start, key1, pos1, ok, cmpOtdel);
        void **sect = ((TOtdel*)Start[pos1])->sublev;
        FindElList(sect, key2, pos2, ok, cmpSector);
        void **rab = ((TSector*)sect[pos2])->sublevR;
        FindElList(rab, arg1,pos3,ok,cmpRabochie);

        ui->enterFIO4->setText(((TRabochie*)rab[pos3])->name);
        ui->enterAdr4->setText(((TRabochie*)rab[pos3])->address);
        ui->enterProf4->setText(((TRabochie*)rab[pos3])->professiia);
        ui->enterRazr4->setText(((TRabochie*)rab[pos3])->razriad);
        ui->enterTabNum4->setText(((TRabochie*)rab[pos3])->tabelNomer);
        ui->enterFee4->setText(((TRabochie*)rab[pos3])->tarif);
    }

}
