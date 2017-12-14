#pragma once

#include <QWidget>

class QUrl;

class FileSystemView : public QWidget
{
    Q_OBJECT

public:
    explicit FileSystemView(QWidget *parent = 0);
    ~FileSystemView();

public Q_SLOTS:
    void openLink(const QUrl&);

private:

};


