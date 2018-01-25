#ifndef MARKET_H
#define MARKET_H

#include <QObject>
#include <QVector>
#include <QSet>
#include <tradeaction.h>
#include <set>
class Market
{   
public:
    Market(QVector<QPair<int, int>>* data);
    void add_action(TimePoint* action);
    void optimize();

    void run();
private:
    int m_actions_count = 0;
    int current_time = 0;

    std::set<QPair<int, int>*> m_data;
    QVector<TimePoint*> m_actions;
    int m_balance = 0;
};

#endif // MARKET_H
