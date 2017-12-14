#include "fademanager.h"
#include <QtDebug>

 //Primarily used for groups
FadeManager::FadeManager(QObject *parent)
    : QObject(parent)
    , a_duration(300)
    , a_deleteWhenFinished(false)
{

}

FadeManager::FadeManager(QWidget *target, FadeManager::FadeMode mode,
                                 int msecs, FadeManager::AnimationSequenceType sequence, QObject *parent)
    : QObject(parent)
    , a_target(target)
    , a_mode(mode)
    , a_duration(msecs)
    , a_sequenceType(sequence)
    , a_deleteWhenFinished(false)
{

}

FadeManager::FadeManager(QWidget *target, int msecs, QObject *parent, FadeManager::FadeMode mode)
    : QObject(parent)
    , a_target(target)
    , a_duration(msecs)
    , a_mode(mode)
    , a_deleteWhenFinished(false)
{

}

FadeManager::FadeManager(QWidget *target, QObject *parent)
    : QObject(parent)
    , a_target(target)
    , a_duration(300)
    , a_deleteWhenFinished(false)
{

}

FadeManager::FadeManager(FadeManager::FadeMode mode, QObject *parent)
    : QObject(parent)
    , a_mode(mode)
    , a_duration(300)
    , a_deleteWhenFinished(false)
{

}

//Will set the entire group to fade out
//It is used when using fadeOutGroup();
void FadeManager::setGroupToFadeOut(FadeManager::AnimationSequenceType typeToChange)
{
    if(typeToChange == Sequential)
    {
        const int groupSize = a_sequentialAnimations.animationCount();
        for (int i(0); i < groupSize; i++)
        {
            auto *anim = (QPropertyAnimation*) a_sequentialAnimations.animationAt(i);
            anim->setStartValue(1.0);
            anim->setEndValue(0.0);
        }
    }
    else
    {
        const int groupSize = a_parallelAnimations.animationCount();
        for (int i(0); i < groupSize; i++)
        {
            auto *anim = (QPropertyAnimation*) a_parallelAnimations.animationAt(i);
            anim->setStartValue(1.0);
            anim->setEndValue(0.0);
        }
    }
}

//Will set the entire group to fade in
//It is used when using fadeInGroup();
void FadeManager::setGroupToFadeIn(FadeManager::AnimationSequenceType typeToChange)
{
    if(typeToChange == Sequential)
    {
        const int groupSize = a_sequentialAnimations.animationCount();
        for (int i(0); i < groupSize; i++)
        {
            auto *anim = (QPropertyAnimation*) a_sequentialAnimations.animationAt(i);
            anim->setStartValue(0.0);
            anim->setEndValue(1.0);
        }
    }
    else
    {
        const int groupSize = a_parallelAnimations.animationCount();
        for (int i(0); i < groupSize; i++)
        {
            auto *anim = (QPropertyAnimation*) a_parallelAnimations.animationAt(i);
            anim->setStartValue(0.0);
            anim->setEndValue(1.0);
        }
    }
}

//Used whenever we have to iterate over groups to search
QAbstractAnimation *FadeManager::searchTarget(QWidget *target, AnimationSequenceType inWhichGroup)
{
    if(inWhichGroup == Parallel)
    {
        const int groupSize = a_parallelAnimations.animationCount();
        for (int i(0); i < groupSize; i++)
        {
            if(a_parallelAnimations.animationAt(i)->objectName() == target->objectName())
            {
                return a_parallelAnimations.animationAt(i);
            }
        }
    }
    else
    {
        const int groupSize = a_sequentialAnimations.animationCount();
        for (int i(0); i < groupSize; i++)
        {
            if(a_sequentialAnimations.animationAt(i)->objectName() == target->objectName())
            {
                return a_sequentialAnimations.animationAt(i);
            }
        }
    }
    //We get here only if we didn't find anything
    qWarning() << "Couldn't find target " << target->objectName() << "in the specified group !";
    return nullptr;
}

void FadeManager::addToParallel(QAbstractAnimation *animation)
{
    a_parallelAnimations.addAnimation(animation);
}

void FadeManager::addToSequential(QAbstractAnimation *animation)
{
    a_sequentialAnimations.addAnimation(animation);
}

void FadeManager::addTarget(QWidget *target, FadeManager::FadeMode mode)
{
    QGraphicsOpacityEffect *effectContainer;
    effectContainer = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *anim;
    anim = new QPropertyAnimation(effectContainer, "opacity", this);
    target->setGraphicsEffect(effectContainer);
    anim->setDuration(a_duration);
    setMode(anim, mode, effectContainer);

    anim->setObjectName(target->objectName()); //To find them later on by set or delete
    a_parallelAnimations.addAnimation(anim);

}

void FadeManager::addTarget(QWidget *target)
{
    QGraphicsOpacityEffect *effectContainer;

    effectContainer = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *anim;
    anim = new QPropertyAnimation(effectContainer, "opacity", this);
    target->setGraphicsEffect(effectContainer);
    anim->setDuration(a_duration);
    setMode(anim, FadeIn, effectContainer);

    anim->setObjectName(target->objectName()); //To find them later on by set or delete
    a_parallelAnimations.addAnimation(anim);
}

void FadeManager::addTarget(QWidget *target, FadeManager::FadeMode mode,
                                FadeManager::AnimationSequenceType sequence)
{
    QGraphicsOpacityEffect *effectContainer;
    effectContainer = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *anim;
    anim = new QPropertyAnimation(effectContainer, "opacity", this);
    target->setGraphicsEffect(effectContainer);
    anim->setDuration(a_duration);
    setMode(anim, mode, effectContainer);

    anim->setObjectName(target->objectName()); //To find them later on by set or delete
    if(sequence == Parallel)
        a_parallelAnimations.addAnimation(anim);
    else
        a_sequentialAnimations.addAnimation(anim);

}

void FadeManager::addTarget(QWidget *target, int msecs)
{
    QGraphicsOpacityEffect *effectContainer;
    effectContainer = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *anim;
    anim = new QPropertyAnimation(effectContainer, "opacity", this);
    target->setGraphicsEffect(effectContainer);
    anim->setDuration(msecs);
    setMode(anim, FadeIn, effectContainer);
    anim->setObjectName(target->objectName()); //To find them later on by set or delete
    a_parallelAnimations.addAnimation(anim);
}

void FadeManager::addTarget(QWidget *target, FadeManager::FadeMode mode,
                                int msecs, FadeManager::AnimationSequenceType sequence)
{
    QGraphicsOpacityEffect *effectContainer;
    effectContainer = new QGraphicsOpacityEffect(this);
    QPropertyAnimation *anim;
    anim = new QPropertyAnimation(effectContainer, "opacity", this);
    target->setGraphicsEffect(effectContainer);
    anim->setDuration(msecs);
    setMode(anim, mode, effectContainer);

    anim->setObjectName(target->objectName()); //To find them later on by set or delete
    if(sequence == Parallel)
        a_parallelAnimations.addAnimation(anim);
    else
        a_sequentialAnimations.addAnimation(anim);
}

void FadeManager::deleteTarget(QWidget *targetToDelete, FadeManager::AnimationSequenceType fromWhichGroup)
{
    if(fromWhichGroup == Parallel)
    {
        auto animToRemove =  searchTarget(targetToDelete, Parallel);
        if(animToRemove == nullptr)
            return;
        a_parallelAnimations.removeAnimation(animToRemove);
    }
    else
    {
        auto animToRemove =  searchTarget(targetToDelete, Sequential);
        if(animToRemove == nullptr)
            return;
        a_sequentialAnimations.removeAnimation(animToRemove);
    }
}

void FadeManager::editTarget(QWidget *targetToModify, FadeManager::FadeMode mode, FadeManager::AnimationSequenceType fromWhichGroup)
{
    if(fromWhichGroup == Parallel)
    {
        auto animToModify =  searchTarget(targetToModify, Parallel);
        if(animToModify == nullptr)
            return;
        auto *anim = (QPropertyAnimation*) animToModify;
        auto *container = (QGraphicsOpacityEffect*) anim->targetObject();
        setMode(anim, mode, container);
    }
    else
    {
        auto animToModify =  searchTarget(targetToModify, Sequential);
        if(animToModify == nullptr)
            return;
        auto *anim = (QPropertyAnimation*) animToModify;
        auto *container = (QGraphicsOpacityEffect*) anim->targetObject();
        setMode(anim, mode, container);
    }
}

void FadeManager::changeTargetGroup(QWidget *targetToModify, FadeManager::AnimationSequenceType fromWhichGroup)
{
    if(fromWhichGroup == Parallel)
    {
        auto animToModify =  searchTarget(targetToModify, Parallel);
        if(animToModify == nullptr)
            return;
        auto *anim = (QPropertyAnimation*) animToModify;
        a_parallelAnimations.removeAnimation(anim);
        a_sequentialAnimations.addAnimation(anim);

    }
    else
    {
        auto animToModify =  searchTarget(targetToModify, Sequential);
        if(animToModify == nullptr)
            return;
        auto *anim = (QPropertyAnimation*) animToModify;
        a_sequentialAnimations.removeAnimation(anim);
        a_parallelAnimations.addAnimation(anim);
    }
}

void FadeManager::clearGroup(FadeManager::AnimationSequenceType whichGroup)
{
    if(whichGroup == Parallel)
        a_parallelAnimations.clear();
    else
        a_sequentialAnimations.clear();
}

void FadeManager::editTarget(QWidget *targetToModify, int msecs, FadeManager::AnimationSequenceType fromWhichGroup)
{
    if(fromWhichGroup == Parallel)
    {
        auto animToModify =  searchTarget(targetToModify, Parallel);
        if(animToModify == nullptr)
            return;
        auto *anim = (QPropertyAnimation*) animToModify;
        anim->setDuration(msecs);
    }
    else
    {
        auto animToModify =  searchTarget(targetToModify, Sequential);
        if(animToModify == nullptr)
            return;
        auto *anim = (QPropertyAnimation*) animToModify;
        anim->setDuration(msecs);
    }
}

void FadeManager::editTarget(QWidget *targetToModify, FadeManager::FadeMode mode, int msecs, FadeManager::AnimationSequenceType fromWhichGroup)
{
    if(fromWhichGroup == Parallel)
    {
        auto animToModify =  searchTarget(targetToModify, Parallel);
        if(animToModify == nullptr)
            return;
        auto *anim = (QPropertyAnimation*) animToModify;
        auto *container = (QGraphicsOpacityEffect*) anim->targetObject();
        setMode(anim, mode, container);
        anim->setDuration(msecs);
    }
    else
    {
        auto animToModify =  searchTarget(targetToModify, Sequential);
        if(animToModify == nullptr)
            return;
        auto *anim = (QPropertyAnimation*) animToModify;
        auto *container = (QGraphicsOpacityEffect*) anim->targetObject();
        setMode(anim, mode, container);
        anim->setDuration(msecs);
    }
}

void FadeManager::start(bool deleteWhenFinished)
{
    //TODO : Clean up ressources when finished and add similiar logic to groups
    QPropertyAnimation *anim;
    a_effectContainer = new QGraphicsOpacityEffect(this);
    anim = new QPropertyAnimation(a_effectContainer, "opacity", this);
    a_target->setGraphicsEffect(a_effectContainer);
    anim->setDuration(a_duration);
    setMode(anim, a_mode, a_effectContainer);
    if(deleteWhenFinished)
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    else
        anim->start();
}

void FadeManager::setMode(QPropertyAnimation *anim, FadeMode mode, QGraphicsOpacityEffect *container)
{
    if(mode == FadeIn)
    {
        container->setOpacity(0.0);
        anim->setStartValue(0.0);
        anim->setEndValue(1.0);
    }
    else //Fade out
    {
        container->setOpacity(1.0);
        anim->setStartValue(1.0);
        anim->setEndValue(0.0);
    }
}

void FadeManager::startGroup(FadeManager::AnimationSequenceType typeToStart, bool deleteWhenFinished)
{
    if(typeToStart == Sequential)
    {
        if(a_sequentialAnimations.state() == QAbstractAnimation::Running)
            a_sequentialAnimations.stop();
        if(deleteWhenFinished)
            a_deleteWhenFinished = true;
        connect(&a_sequentialAnimations, SIGNAL(finished()), this, SLOT(sequentialFinished()));
        a_sequentialAnimations.start();
    }
    else
    {
        if(a_parallelAnimations.state() == QAbstractAnimation::Running)
            a_parallelAnimations.stop();
        if(deleteWhenFinished)
            a_deleteWhenFinished = true;
        connect(&a_parallelAnimations, SIGNAL(finished()), this, SLOT(parallelFinished()));
        a_parallelAnimations.start();
    }
}

void FadeManager::fadeOutGroup(FadeManager::AnimationSequenceType typeToStart, bool deleteWhenFinished)
{
    setGroupToFadeOut(typeToStart);
    startGroup(typeToStart, deleteWhenFinished);
}

void FadeManager::fadeInGroup(FadeManager::AnimationSequenceType typeToStart, bool deleteWhenFinished)
{
    setGroupToFadeIn(typeToStart);
    startGroup(typeToStart, deleteWhenFinished);
}

FadeManager::~FadeManager()
{
    a_target = nullptr;
    if(a_parallelAnimations.animationCount()) //If it's not 0 (false), then there's something
        clearGroup(Parallel);
    if(a_sequentialAnimations.animationCount())
        clearGroup(Sequential);
    if(!a_effectContainer) //if pointer not null
        delete a_effectContainer;
    else
        a_effectContainer = nullptr;
}
