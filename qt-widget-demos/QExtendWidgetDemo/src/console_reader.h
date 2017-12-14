#ifndef CONSOLE_READER_H
#define CONSOLE_READER_H

#include <QObject>
#include <QPointer>
#include <QProcess>

class console_reader : public QObject
{
    Q_OBJECT

public:
    console_reader(QObject *parent = 0);
    virtual ~console_reader();

protected:
    virtual void interpretate_console_output(QStringList & stringList) = 0;
    virtual QString QByteArray_to_QString(QByteArray & m_byteArray);
    QString::SplitBehavior internal_splitBehavior;
    QProcess m_process;

private:
    QString m_uncomplete_line;

private slots:
    void read_console_output();
};

#endif
