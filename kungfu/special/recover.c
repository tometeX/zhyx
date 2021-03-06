// recover.c  破元大法
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "破元大法" NOR; }

int perform(object me)
{        	
	 mapping my;
        string *cnds;
        mapping conditions;
        int i;


        if (! me->query("reborn"))        
            return notify_fail("你尚未转世重生，无法使用此技能！\n");

        if ( time() - me->query("la_sp_tm/recover") < 300 )        
            return notify_fail("你刚刚用过此技能，过些时候再用吧！\n");

        me->set("la_sp_tm/recover", time());

	 my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"];
        my["jingli"] = my["eff_jingli"] = my["max_jingli"];
        my["qi"]     = my["eff_qi"]     = my["max_qi"];
        my["neili"]  = my["max_neili"] * 2;
        my["food"]   = me->max_food_capacity();
        my["water"]  = me->max_water_capacity();

       conditions = me->query_condition(); 
        if (conditions)
        { 
           cnds = keys(conditions);

           for( i = 0; i < sizeof(cnds); i++ )
           {
               if ( me->dispel_condition(me, cnds[i]))           
                 me->clear_condition(cnds[i]);  
           }
        }
        message_vision(HIW "$N" HIW "瞬间运用真气突破七经八脉，"
                       "顿时气色饱满，神采奕奕。\n" NOR, me);
   
       return 1;
}

