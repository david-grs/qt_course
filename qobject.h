#pragma once

#include <QObject>
#include <QString>
#include <QDebug>

class Item : public QObject
{
    Q_OBJECT  

public:
    explicit Item(const QString& name, QObject* parent = nullptr) :
        QObject(parent)
    {
        setObjectName(name);
    }

    ~Item() 
    {
       qDebug() << "destroying" << objectName(); 
    }
};

