#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "graphdatamodel.h"
#include "chart.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);


    GraphDataModel model;

    model.registerFunction("linear",new Linear);
    model.registerFunction("sinusoid",new Sinusoid);
    model.registerFunction("logarithm",new Logarithm);
    model.registerFunction("exponential",new Exponential);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty( "graphData", &model);
    qmlRegisterType<Chart>("Sachi.Chart", 1, 0, "Chart");

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
