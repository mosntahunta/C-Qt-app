#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "serializer.h"
#include "deserializer.h"
#include "listmodel.h"

int main( int argc, char *argv[] )
{
    ListModel model;

    Serializer serializer(model);
    Deserializer deserializer(model);

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("listmodel", &model);
    engine.rootContext()->setContextProperty("serializer", &serializer);
    engine.rootContext()->setContextProperty("deserializer", &deserializer);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app, [url](QObject *obj, const QUrl &objUrl)
    {
        if ( !obj && url == objUrl )
        {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}

