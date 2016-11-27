#ifndef HISTORY_H
#define HISTORY_H

#include <QAbstractListModel>

typedef QList<QPair<QString, QString>> myList;

class History : public QAbstractListModel
{
    Q_OBJECT
public:
    Q_INVOKABLE void insert(int index, const QString& first, const QString &second);
    Q_INVOKABLE void append(const QString& first, const QString &second);
    Q_INVOKABLE void remove(int index);
    Q_INVOKABLE void clear();

    // gives the size of the model
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_INVOKABLE QPair<QString, QString> get(int index);


public:
    // Define the role names to be used
    enum RoleNames {
        ExpressionRole = Qt::UserRole,
        ResultRole = Qt::UserRole+2
    };

    explicit History(QObject *parent = 0);
    ~History();

    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    int count();
protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QList<QPair<QString, QString>> m_data;
    QHash<int, QByteArray> m_roleNames;
signals:
    void countChanged(int);
};

#endif // HISTORY_H
