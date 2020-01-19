#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <QString>
#include <QUrl>
#include "listmodel.h"

//
// Load and deserialize a json file and populate the list model.
//
class Deserializer : public QObject
{
    Q_OBJECT
public:
    //
    // Constructor, takes a reference to the list model.
    //
    Deserializer( ListModel &list_model );

    //
    // Load a json file from a given url.
    //
    Q_INVOKABLE bool load( QUrl url );

private:
    ListModel &model;
};

#endif // DESERIALIZER_H
