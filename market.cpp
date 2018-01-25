#include "market.h"
#include <QDebug>
#include <set>

Market::Market(QVector<QPair<int, int> >* data)
{
    for (QPair<int, int>& point : *data){
        add_action(new TimePoint(point));
        m_data.insert(new QPair<int, int>(point.first, point.second));
    }
}

void Market::add_action(TimePoint* action)
{
    m_actions.push_back(action);
    qDebug().noquote() << "Added: time: "<< action->time << " value: "<< action->value();
}

void Market::optimize()
{
    qWarning().noquote() << "Optimizing... data size: " << m_data.size();
    while (m_data.size() > 1) {
        std::pair<std::set<QPair<int,int>*,QPair<int,int>*>::iterator,
                std::set<QPair<int,int>*,QPair<int,int>*>::iterator> mm = std::minmax_element(m_data.cbegin(), m_data.cend(), [](QPair<int, int>* a, QPair<int, int>* b) {
            return a->second < b->second;
        });

        QPair<int, int>* min = *mm.first;
        QPair<int, int>* max = *mm.second;

        m_actions.at(min->first)->make_buy();
        m_actions.at(max->first)->make_sell(m_actions.at((*(mm.first))->first));

        m_data.erase(min);
        m_data.erase(max);
        qDebug().noquote() << "left: " << m_data.size();
    }
    if (!m_data.empty()) {
        QPair<int, int>* last = *m_data.begin();
        if (last->first < m_actions.last()->m_value) {
            m_actions.at(last->first)->make_buy();
            m_actions.last()->make_sell_all();
        }
    }
}

void Market::run()
{
    optimize();

    for (TimePoint* action: m_actions) {
        m_balance += action->execute(m_actions_count);
        this->current_time++;
        qDebug().noquote() << "BALANCE: " << m_balance;
    }

}
