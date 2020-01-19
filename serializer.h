#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <QUrl>

#include "listmodel.h"

//
// Serialize the list model into a json file.
//
class Serializer : public QObject
{
    Q_OBJECT
public:
    //
    // Constructor, takes a reference to the list model.
    //
    Serializer(ListModel &list_model);

    //
    // Save the model to a file at a given location, create a new file if it doesn't exist.
    //
    Q_INVOKABLE bool save(QUrl url);

private:
    ListModel &model;
};

#endif // SERIALIZER_H
