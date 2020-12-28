#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "graphdatamodel.h"
#include "chart.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    GraphDataModel model;

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<GraphDataModel>();
    engine.rootContext()->setContextProperty("graphData", &model);

    qmlRegisterType<Chart>("Sachi.Chart", 1, 0, "Chart");
    qmlRegisterType<GraphDataModel>("Sachi.Chart", 1, 0, "GraphDataModel");


    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
