#ifndef MYNEWGUIDEFACADE_H
#define MYNEWGUIDEFACADE_H

#include "GLDNewGuideFacade.h"

class CustomNewGuideFacade : public GLDNewGuideFacade
{
public:
    CustomNewGuideFacade(QWidget *parent = 0);
    ~CustomNewGuideFacade();
    static void execute(QWidget *parent);

protected:
    virtual void registerNewGuideInfo();
    virtual void doAfterShow();
};

#endif