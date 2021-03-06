#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "bingcan_duzhang"; }

string chinese_name() { return "冰蚕寒毒"; }

string update_msg_others()
{
       return HIW "$N" HIW "惨嚎一声，脸色铁青，全身浮现出一层寒气，不住的颤抖。\n" NOR;
}

string update_msg_self()
{
        return HIW "你只觉极寒攻心，全身肌肉快要冻结一般。\n" NOR;
}

string die_msg_others()
{
        return HIW "$N" HIW "冻成一尊僵硬的雕塑一般，突然"
               "间“砰”的一声碎成了一地的冰块。\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] * 1;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] * 2;
}

string die_reason()
{
        return "冰蚕寒毒发作，被活活冻死了";
}


int dispel(object me, object ob, mapping cnd)
{
        if ((me->query_skill("jiuyang-shengong", 1) > 1000 && 
             me->query_skill_mapped("force") == "jiuyang-shengong") ||
             (me->query_skill("freezing-force", 1) > 200 &&
              me->query_skill_mapped("force") == "freezing-force") || 
             (me->query_skill("yijinjing", 1) > 1000 &&
              me->query_skill_mapped("force") == "yijinjing"))
        {
               me->add_temp("apply/dispel-poison", 1000);
               me->set_temp("add_dispel", 1); 
               call_out("clear_dispel", 2, me);
        }

        return ::dispel(me, ob, cnd);

}


void clear_dispel(object me)
{
       if (me->query_temp("apply/dispel-poison") && 
           me->query_temp("add_dispel"))
       {
                me->delete_temp("add_dispel");
                me->add_temp("apply/dispel-poison", -1000);
                return;
       }
               
}