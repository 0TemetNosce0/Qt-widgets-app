#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QFont>
#include <QMutex>
#include <QLabel>
#include <QObject>
#include <QPushButton>
#include <QApplication>
#include <QFontDatabase>

class IconHelper : public QObject
{

private:
    QFont iconFont;
    explicit IconHelper(QObject *parent = 0);
    static IconHelper *_instance;

public:
    static IconHelper *Instance()
    {
        static QMutex mutex;
        if (!_instance)
        {
            QMutexLocker locker(&mutex);
            if (!_instance)
            {
                _instance = new IconHelper;
            }
        }
        return _instance;
    }

    void SetIcon(QLabel *lab, QChar c, int size = 10);
    void SetIcon(QPushButton *btn, QChar c, int size = 10);

};

#endif // ICONHELPER_H
