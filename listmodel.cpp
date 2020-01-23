#include "listmodel.h"

#include <QJsonArray>
#include <QJsonObject>

ListModel::ListModel( QObject *parent )
    : QAbstractListModel(parent)
{
}

void
ListModel::reset()
{
    beginResetModel();
    map.clear();
    keys.clear();
    endResetModel();
}

void ListModel::read( const QJsonObject &json )
{
    if ( json.contains("keys") && json["keys"].isArray() && json.contains("values") && json["values"].isArray() )
    {
        reset();

        QJsonArray keyArray = json["keys"].toArray();
        QJsonArray valueArray = json["values"].toArray();

        Q_ASSERT(keyArray.size() == valueArray.size());

        beginInsertRows(QModelIndex(), 0, keyArray.size() - 1);
        for ( int keyIndex = 0; keyIndex < keyArray.size(); ++keyIndex )
        {
            QString key = keyArray[keyIndex].toString();
            QString value = valueArray[keyIndex].toString();

            if ( map.find(key) == map.end() )
            {
                addToModel(key, value);
            }
        }
        endInsertRows();
    }
    else
    {
        qWarning("Json object could not be parsed into the list model.");
    }
}

void ListModel::write( QJsonObject &json )
{
    QJsonArray keyArray;
    QJsonArray valueArray;

    for( QString key : keys )
    {
        keyArray.append(key);
        valueArray.append(map[key]);
    }

    Q_ASSERT(keyArray.size() == valueArray.size());

    json["keys"] = keyArray;
    json["values"] = valueArray;
}

void
ListModel::add( QString key, QString value )
{
    if ( map.find(key) == map.end() )
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        addToModel(key, value);
        endInsertRows();
    }
}

bool
ListModel::removeRows( int row, int count, const QModelIndex &parent )
{
    int final_row_to_remove = row + count - 1;
    if( final_row_to_remove >= keys.size() && row >= 0 )
    {
        qWarning("Rows to remove cannot be out of range of the list.");
        return false;
    }

    beginRemoveRows(QModelIndex(), row, final_row_to_remove);
    for ( int keyIndex = row; keyIndex <= final_row_to_remove; keyIndex++ )
    {
        removeFromModel(keyIndex);
    }
    endRemoveRows();

    return true;
}

int
ListModel::rowCount( const QModelIndex &parent ) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if ( parent.isValid() )
    {
        return 0;
    }

    return keys.count();
}

QVariant
ListModel::data( const QModelIndex &index, int role ) const
{
    if ( index.isValid() )
    {
        if ( role == KeyRole )
        {
            QString key = keys[index.row()];
            return QVariant::fromValue(key);
        }
        else if ( role == ValueRole )
        {
            QString value = map[keys[index.row()]];
            return QVariant::fromValue(value);
        }
    }

    return QVariant();
}

QHash<int,QByteArray>
ListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[KeyRole] = "key";
    roles[ValueRole] = "value";
    return roles;
}

void
ListModel::addToModel( QString key, QString value )
{
    Q_ASSERT(map.size() == keys.size());

    keys.append(key);
    map[key] = value;
}

void
ListModel::removeFromModel( int index )
{
    if ( index >= 0  && index < keys.size() )
    {
        QString key = keys[index];
        Q_ASSERT(map.find(key) != map.end());
        Q_ASSERT(map.size() == keys.size());

        keys.removeAt(index);
        map.remove(key);
    }
}
