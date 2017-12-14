#ifndef QDOCKNODE_H
#define QDOCKNODE_H

#include <QSplitter>

class QDockNode : public QSplitter
{
    Q_OBJECT

public:
    QDockNode(QWidget *parent);
    ~QDockNode();
private:

};

#endif // QDOCKNODE_H
