#ifndef __INSTANCE_MAN_H__
#define __INSTANCE_MAN_H__

#include "Model/MainLogic.h"


class InstanceMan
{
public:
    static void Create();
    static void Destroy();

public:
    static MainLogic* mainLogic;
};


#endif // __INSTANCE_MAN_H__
