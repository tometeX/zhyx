// feng.c  风舞九天

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "风舞九天" NOR; }

int perform(object me, string skill)
{
        return notify_fail("风舞九天这项技能不需要运用。\n");
}

