#ifndef TRADEACTION_H
#define TRADEACTION_H

#include <QObject>

class TimePoint
{
public:
    enum Action {
        BUY,
        SELL,
        SELL_ALL,
        IDLE
    } action;

    int time = -1;
    int profit = 0;
    int m_value = 0;
    TimePoint(QPair<int, int> pair = QPair<int, int>(0, 0));
    void make_sell(TimePoint* other);
    void make_sell_all();
    void make_buy();
    int execute(int& counter);
    int getProfit();
    int value();
private:
    TimePoint* sell_what = nullptr;
};

#endif // TRADEACTION_H
