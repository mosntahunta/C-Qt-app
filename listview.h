#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QAbstractListModel>

class ListView : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ListRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };
    explicit ListView(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:

};

#endif // LISTVIEW_H
