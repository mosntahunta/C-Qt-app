#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "deserializer.h"

Deserializer::Deserializer( ListModel &list_model )
: model(list_model)
{

}

bool
Deserializer::load( QUrl url )
{
    // Read from file
    QString path = url.toLocalFile();
    QFile file(path);

    if ( !file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        qWarning("Couldn't open save file.");
        return false;
    }
    QJsonParseError JsonParseError;
    QJsonDocument JsonDocument = QJsonDocument::fromJson(file.readAll(), &JsonParseError);
    file.close();

    // Update model
    QJsonObject object = JsonDocument.object();
    model.read(object);

    return true;
}
