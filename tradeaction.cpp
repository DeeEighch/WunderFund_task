#include <QDebug>
#include "tradeaction.h"
#define MINIMUM 0

TimePoint::TimePoint(QPair<int, int> pair)
    :action(IDLE), time(pair.first), m_value(pair.second)
{

}

void TimePoint::make_sell(TimePoint* other)
{
    action = SELL;
    sell_what = other;

}

void TimePoint::make_sell_all()
{
    action = SELL_ALL;
}

void TimePoint::make_buy()
{
    action = BUY;
}

int TimePoint::value(){
    return m_value;
}

int TimePoint::execute(int & counter)
{
    switch (action) {
        case TimePoint::Action::BUY:
            counter++;
            qDebug().noquote() << "[INFO]: BUY one action. current: " << counter;
            return -1 * m_value;
            break;
        case TimePoint::Action::SELL:
            if (counter < MINIMUM + 1) {
                qDebug().noquote() << "[ERROR]: Nothing to sell!";
                return 0;
            } else {
                counter--;
                profit = m_value - sell_what->m_value;
                qDebug().noquote() << "[INFO]: SELL one action. current: " << counter;
                return m_value;
            }
            break;
        case TimePoint::Action::SELL_ALL:{
            int money = 0;
            if (counter > 0) {
                 money = m_value * counter;
                 qDebug().noquote() << "[INFO]: SELL_ALL in count : " << counter << "curent: " << 0;
                counter = 0;

            }

            return money;
        }
        case TimePoint::Action::IDLE:
        default:
            qDebug().noquote() << "[INFO]: Waiting... current: " << counter;
            return 0;
            break;
    }
}

int TimePoint::getProfit()
{
    return profit;
}
