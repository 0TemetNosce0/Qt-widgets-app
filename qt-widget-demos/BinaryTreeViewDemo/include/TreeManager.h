#ifndef TREEMANAGER_H_
#define TREEMANAGER_H_

#include <QObject>

class TreeScene;
class Node;

class TreeManager : public QObject
{
    Q_OBJECT;

public:
    TreeManager();

    bool addValue(int value);
    bool removeValue(int value);
    bool deleteSelected();
    void rotateSelectedLeft();
    void rotateSelectedRigth();
    int valueByIndex(int index);

    int treeSize();
    bool isEmpty();
    TreeScene* scene();

private slots:
    void updateScene();
    void updateSceneRect();

signals:
    void treeChanged();

private:
    enum ChildType { LeftChild, RightChild };

    void deleteNode(Node *node);
    Node* searchValue(int value);
    int subTreeHeight(Node *node);

    Node* searchDFS(Node *cur, int val);
    int subTreeHeightDFS(Node *cur);
    void recalcRelPos();
    void recalcAbsPos();
    qreal recalcRelPosDFS(Node *node, ChildType type);
    void recalcAbsPosDFS(Node *node);

    int valueByIndexDFS(Node *node, int index);

    void setRoot(Node *node);

    TreeScene *m_scene;
    Node *m_root;
    int m_treeSize;
};

#endif /* TREEMANAGER_H */
