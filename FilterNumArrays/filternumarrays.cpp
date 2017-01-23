#include "filternumarrays.h"
#include <vector>
FilterNumArrays::FilterNumArrays(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    ui.plainTextEdit_00->setFocus();
}

FilterNumArrays::~FilterNumArrays()
{

}

void FilterNumArrays::on_pushButton_clicked()
{
    std::vector<std::set<int>>& vecSets =  getAllPlainTextEditText();
    std::set<int>& resultSet = calcIntersection(vecSets);
    QString sResult;
    for each(auto item in resultSet)
    {
        if (item < 10)
        {
            sResult += "00";
        }
        else if (item < 100)
        {
            sResult += "0";
        }
        sResult += QString::number(item);
        sResult += " ";
    }
    if (sResult.isEmpty())
    {
        sResult += QString::fromLocal8Bit("没有交集");
    }
    ui.plainTextEdit_Result->setPlainText(sResult);
}

std::vector<std::set<int>> FilterNumArrays::getAllPlainTextEditText()
{
    std::vector<std::set<int>> vecTextNumbers;
    int nRowCount = ui.gridLayout->rowCount();
    int nColumnCount = ui.gridLayout->columnCount();
    for (int i = 0; i < nRowCount; ++i)
    {
        for (int j = 0; j < nColumnCount; ++j)
        {
            QPlainTextEdit* pPlainTextEdit = dynamic_cast<QPlainTextEdit*>(ui.gridLayout->itemAtPosition(i, j)->widget());
            if (nullptr == pPlainTextEdit)
            {
                continue;
            }
            QString str = pPlainTextEdit->toPlainText();
            std::set<int> setNumbers;
            bool bSuccess = generateSetNumbers(str, setNumbers);
            if (!str.isEmpty())
            {
                //格子有内容
                if (!bSuccess)
                {
                    //存在输入错误，变色
                    pPlainTextEdit->setStyleSheet("border:2px solid red");
                }
                else
                {
                    //没有错误，恢复默认
                    pPlainTextEdit->setStyleSheet("");
                }
                //都是错的插入空set
                vecTextNumbers.push_back(setNumbers);
            }
            else
            {
                //恢复默认
                pPlainTextEdit->setStyleSheet("");
            }
        }
    }
    return vecTextNumbers;
}

bool FilterNumArrays::generateSetNumbers(const QString& str, std::set<int>& setResult)
{
    bool bResult = true;
    QStringList list = str.split(" ");
    for (auto it = list.begin(); it != list.end(); ++it)
    {
        QString& strItem = *it;
        if (strItem.isEmpty())
        {
            continue;
        }
        bool bOk;
        int nItem = strItem.toInt(&bOk);
        if (bOk && isNumberValid(nItem))
        {
            setResult.insert(nItem);
        }
        else
        {
            bResult = false;
        }
    }
    return bResult;
}

std::set<int> FilterNumArrays::calcIntersection(const std::vector<std::set<int>>& vecSets)
{
    std::set<int> setIntersectionResults;
    if (vecSets.empty())
    {
        return setIntersectionResults;
    }
    setIntersectionResults = vecSets.at(0);
    for (int i = 1; i < vecSets.size();++i)
    {
        const std::set<int>& curSet = vecSets.at(i);
        for (auto it = setIntersectionResults.begin(); it != setIntersectionResults.end();)
        {
            if (curSet.end() == curSet.find(*it))
            {
                //当前的数字在后面的数组中不存在
               setIntersectionResults.erase(it++);
            }
            else
            {
                ++it;
            }
        }
    }
    return setIntersectionResults;
}

bool FilterNumArrays::isNumberValid(int nNumber)
{
    if (nNumber < 0 || nNumber>999)
    {
        return false;
    }
    return true;
}
