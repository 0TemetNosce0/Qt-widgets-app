#ifndef QDOCKCOMMON_H
#define QDOCKCOMMON_H

enum DockStatus
{
    AutoHide,
    Docked,
    Floating,
};

enum DockArea
{
    NoneArea = 0,
    LeftArea = 1,
    TopArea = 1 << 2,
    RightArea = 1 << 3,
    BottomArea = 1 << 4,
    CenterArea = 1 << 5,
    CenterLeftArea = 1 << 6,
    CenterTopArea = 1 << 7,
    CenterRightArea = 1 << 8,
    CenterBottomArea = 1 << 9
};

#endif // QDOCKCOMMON_H
