#ifndef FADEMANAGER_H
#define FADEMANAGER_H

#include <QObject>
#include <QWidget>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>


/*   Convenience class to fade in or out any QWidget,
 *   The class manages internally groups for you, making code cleaner.
 *   Created by Horoneru the 31/03/15
 *   V1.1.3 (updated 13/05/15)
*/

class FadeManager : public QObject
{
    Q_OBJECT

public:
    enum FadeMode
    {
        FadeOut, FadeIn
    };

    enum AnimationSequenceType
    {
        Parallel, Sequential
    };

    //Constructors
    explicit FadeManager(QObject *parent = 0);
    FadeManager(QWidget *target, FadeMode mode , int msecs, AnimationSequenceType sequence, QObject *parent);
    FadeManager(QWidget *target, int msecs, QObject *parent, FadeMode mode = FadeIn);
    FadeManager(QWidget *target, QObject *parent);
    FadeManager(FadeMode mode, QObject *parent);
    ~FadeManager();

    inline void setDefaultDuration(int msecs)
    {
        a_duration = msecs;
    }

    inline const int getDefaultDuration()
    {
        return a_duration;
    }

    void addToParallel(QAbstractAnimation *animation);
    void addToSequential(QAbstractAnimation *animation);

    void setSingleTarget(QWidget *target)
    {
        a_target = target;
    }

    void addTarget(QWidget *target);
    void addTarget(QWidget *target, FadeMode mode);
    void addTarget(QWidget *target, FadeMode mode,
                   AnimationSequenceType sequence);
    void addTarget(QWidget *target, int msecs);
    void addTarget(QWidget *target, FadeMode mode,
                   int msecs, AnimationSequenceType sequence);

    /* Those Use the target names and calls searchTarget(); to iterate */
    void deleteTarget(QWidget *targetToDelete, AnimationSequenceType fromWhichGroup);

    void editTarget(QWidget *targetToModify, FadeMode mode, AnimationSequenceType fromWhichGroup = Parallel);
    void editTarget(QWidget *targetToModify, int msecs, AnimationSequenceType fromWhichGroup = Parallel);
    void editTarget(QWidget *targetToModify, FadeMode mode, int msecs, AnimationSequenceType fromWhichGroup = Parallel);

    void changeTargetGroup(QWidget *targetToModify, AnimationSequenceType fromWhichGroup = Parallel);

    void clearGroup(AnimationSequenceType whichGroup);

    void start(bool deleteWhenFinished = true); //Start one animation with the arguments specified on constructor
    void startGroup(AnimationSequenceType typeToStart, bool deleteWhenFinished = true); //Starts the animations in the group started
    void fadeOutGroup(AnimationSequenceType typeToStart, bool deleteWhenFinished = true); //Sets the entire group to FadeOut
    void fadeInGroup(AnimationSequenceType typeToStart, bool deleteWhenFinished = true); //Sets the entire group to FadeIn

signals:
    void finished(FadeManager::AnimationSequenceType); //When finished, you will be notified, and know which group finished.

public slots:

    inline void parallelFinished()
    {
        if(a_deleteWhenFinished)
        {
            a_parallelAnimations.clear();
            a_deleteWhenFinished = false;
        }

        emit finished(FadeManager::Parallel);
    }

    inline void sequentialFinished()
    {
        if(a_deleteWhenFinished)
        {
            a_sequentialAnimations.clear();
            a_deleteWhenFinished = false;
        }
        emit finished(FadeManager::Sequential);
    }

private:
    void setMode(QPropertyAnimation *anim, FadeMode mode, QGraphicsOpacityEffect *container);
    void setGroupToFadeOut(AnimationSequenceType typeToChange);
    void setGroupToFadeIn(AnimationSequenceType typeToChange);
    QAbstractAnimation* searchTarget(QWidget *target, AnimationSequenceType inWhichGroup);

    //Attributes
    int a_duration; //Duration in ms
    QWidget *a_target; //Used when starting only one animation
    QGraphicsOpacityEffect *a_effectContainer; //Used when starting only one animation
    QSequentialAnimationGroup a_sequentialAnimations;
    QParallelAnimationGroup a_parallelAnimations;
    bool a_deleteWhenFinished;
    FadeMode a_mode; //FadeIn or FadeOut
    AnimationSequenceType a_sequenceType; //Parallel or Sequential
};

#endif // FADEMANAGER
