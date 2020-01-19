#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include "serializer.h"

Serializer::Serializer( ListModel &list_model )
: model(list_model)
{

}

bool
Serializer::save( QUrl url )
{
    // Create the json document from model
    QJsonObject object;
    QJsonDocument document;
    model.write(object);
    document.setObject(object);

    // Write to file
    QString path = url.toLocalFile();
    QFile file(path);
    if ( !file.open(QFile::WriteOnly | QFile::Text | QFile::Truncate) )
    {
        qWarning("Couldn't open save file.");
        return false;
    }
    file.write(document.toJson());
    file.close();

    return true;
}
