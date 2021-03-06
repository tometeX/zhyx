// getaway.c  金蝉脱壳
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return YEL "金蝉脱壳" NOR; }

int perform(object me)
{        	
        int lvl;

        if (! me->query("reborn"))        
            return notify_fail("你尚未转世重生，无法使用此技能！\n");
        if ( ! me->is_busy())
            return notify_fail("你现在无需使用此项特技！\n");
        if ( ! me->is_fighting() )
            return notify_fail("金蝉脱壳只能在战斗中使用！\n"); 

        if ( time() - me->query("la_sp_tm/getaway") < 2 )        
            return notify_fail("你刚刚用过此技能，过些时候再用吧！\n");

        me->set("la_sp_tm/getaway", time());        

        lvl = me->query_int();
        if ( lvl < me->query_dex() ) lvl = me->query_dex();

        if (random(100 - lvl) == 0)
        { 
            message_vision(HIG "\n$N" HIG "忽然浑身一阵扭动，"
                           "顿时行动自如。\n\n" NOR, me);
            me->interrupt_me();
        } else
            message_vision(CYN "\n$N" CYN "试图冲破受制，"
                           "但是毫无作用。\n\n" NOR, me);   
       return 1;
}

