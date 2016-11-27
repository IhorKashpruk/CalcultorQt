#include "history.h"


History::History(QObject *parent)
    : QAbstractListModel(parent)
{
    m_roleNames[ExpressionRole] = "expression";
    m_roleNames[ResultRole] = "result";
}

History::~History()
{
}

int History::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant History::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const QPair<QString, QString>& ex = m_data.at(row);
    switch(role) {
    case ExpressionRole:
        return ex.first;
    case ResultRole:
        return ex.second;
    }
    return QVariant();
}

int History::count()
{
    return m_data.count();
}

QHash<int, QByteArray> History::roleNames() const
{
    return m_roleNames;
}

void History::insert(int index, const QString &first, const QString& second)
{
    if(index < 0 || index > m_data.count()) {
        return;
    }
    QPair<QString, QString> ex(first, second);

    // view protocol (begin => manipulate => end]
    emit beginInsertRows(QModelIndex(), index, index);
    m_data.insert(index, ex);
    emit endInsertRows();
    // update our count property
    emit countChanged(m_data.count());
}

void History::append(const QString &first, const QString& second)
{
    insert(m_data.size(), first, second);
}

void History::remove(int index)
{
    if(index < 0 || index >= m_data.count()) {
        return;
    }
    emit beginRemoveRows(QModelIndex(), index, index);
    m_data.removeAt(index);
    emit endRemoveRows();
    // do not forget to update our count property
    emit countChanged(m_data.count());
}

void History::clear()
{
    emit beginRemoveRows(QModelIndex(), 0, m_data.size());
    m_data.clear();
    emit endRemoveRows();
    emit countChanged(m_data.size());
}

QPair<QString,QString> History::get(int index)
{
    if(index < 0 || index >= m_data.count()) {
        return QPair<QString, QString>();
    }
    return m_data.at(index);
}
