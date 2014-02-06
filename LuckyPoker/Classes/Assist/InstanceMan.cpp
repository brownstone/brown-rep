#include "InstanceMan.h"

MainLogic* InstanceMan::mainLogic = NULL;

void InstanceMan::Create()
{
    mainLogic = MainLogic::GetInstance();
}

void InstanceMan::Destroy()
{
    MainLogic::FreeInstance();
}

