#include <QApplication>
#include <QMainWindow>
#include <QPushButton>
#include <QTimer>

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    QPushButton* button = new QPushButton("Quit", &mainWindow);

    QTimer* timer = new QTimer(&mainWindow);
    timer->setInterval(1000);

    QObject::connect(button, &QPushButton::clicked, timer, static_cast<void (QTimer::*)()>(&QTimer::start));

    QObject::connect(timer, &QTimer::timeout, []()
    {
        qApp->quit();
    });

	mainWindow.show();
    return app.exec();
}

