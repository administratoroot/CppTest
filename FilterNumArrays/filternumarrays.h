#ifndef FILTERNUMARRAYS_H
#define FILTERNUMARRAYS_H

#include <QtWidgets/QDialog>
#include "ui_filternumarrays.h"
#include <vector>
#include <set>
class FilterNumArrays : public QDialog
{
    Q_OBJECT

public:
    FilterNumArrays(QWidget *parent = 0);
    ~FilterNumArrays();
private slots:
    void on_pushButton_clicked();
private:
    std::vector<std::set<int>> getAllPlainTextEditText();
    bool generateSetNumbers(const QString& str, std::set<int>& setResult);
    std::set<int> calcIntersection(const std::vector<std::set<int>>& vecSets);
    bool isNumberValid(int nNumber);
private:
    Ui::FilterNumArraysClass ui;
};

#endif // FILTERNUMARRAYS_H
