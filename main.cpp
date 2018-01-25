#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#include "market.h"

#define SEP ","
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QFile csv(":/WunderFund_data.csv");

    if (!csv.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "Couldn't open data file!";
        return 1;
    }

    QVector<QPair<int, int>>* chart_data = new QVector<QPair<int, int>>;

    QTextStream in(&csv);
    QString headers = in.readLine();
    qDebug().noquote() << headers.split(SEP);
    while (!in.atEnd()){
        QStringList pair = in.readLine().split(SEP);
        //qDebug().noquote() << pair;
        if (pair.size() == 2){
            chart_data->append(qMakePair(pair.at(0).toInt(),
                                        pair.at(1).toInt())
                              );
        }
    }

    Market market(chart_data);
    market.run();

    return 0;

    return a.exec();
}
