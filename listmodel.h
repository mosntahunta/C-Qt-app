#ifndef LISTMODEL_H
#define LISTMODEL_H

#include <QAbstractListModel>

//
// Qt model class representing the "key/value" pairs to a list.
//
// Uses a combination of an ordered list (keys) and a hash map (key, value) for quick retrieval.
//
class ListModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum ListRoles {
        KeyRole = Qt::UserRole + 1,
        ValueRole
    };

    //
    // Constructor.
    //
    ListModel( QObject *parent = nullptr );

    //
    // Resets the model by clearing the list and the map.
    //
    void reset();

    //
    // Populate the model from a given json object.
    //
    void read(const QJsonObject &json);

    //
    // Write the contents of the model to a json object.
    //
    void write(QJsonObject &json);

    //
    // Add a (key, value) pair to the model, this function is exposed to the QML view.
    //
    Q_INVOKABLE void add( QString key, QString value );

    //
    // Remove a number of rows from a given index, also exposed to the QML view.
    //
    Q_INVOKABLE bool removeRows( int row, int count, const QModelIndex &parent = QModelIndex() ) override;

    //
    // Return the number of rows in the model.
    //
    int rowCount( const QModelIndex &parent = QModelIndex() ) const override;

    //
    // Returns the data stored under the given role for the item referred to by the index.
    //
    QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const override;

    //
    // Returns the model's role names.
    //
    QHash<int,QByteArray> roleNames() const override;

private:
    //
    // Internal interface to safely append the pair to both the keys list and the hash map.
    //
    void addToModel( QString key, QString value );

    //
    // Same as above but for removing a pair from the model.
    //
    void removeFromModel( int index );

    QList<QString> keys; // ordered list of keys for indexing

    QHash<QString, QString> map; // (key, value) hash map
};

#endif // LISTMODEL_H
