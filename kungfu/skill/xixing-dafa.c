#include <ansi.h>

inherit FORCE;

int valid_enable(string usage)
{
	return usage == "force";
}

int valid_force(string force)
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("xixing-dafa", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("xixing-dafa", 1);

        if (me->query("character") == "光明磊落")
                return notify_fail("你心中暗道：这种害人的武功，我学它作甚？\n");

        if (me->query("con") < 30)
                return notify_fail("你试着按照法门运转了一下内息，忽然觉得心火如"
                                   "焚，丹田却是一阵冰凉！\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功修为不足，难以修炼吸星大法。\n");

        if (! me->query("can_learn/xixing-dafa/ren")
           && me->query("max_neili")
           && lvl < 200
           && lvl >= 10)
                return notify_fail("你没有按照吸星大法的诀窍将内力散去，现在还不"
                                   "敢妄自继续修行大法。\n");

        return ::valid_learn(me);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int jiali;

        if ((int)me->query_skill("xixing-dafa", 1) < 80
           || ! living(me))
                return;

        if ((jiali = ob->query("jiali")) < 1
            || ob->query_skill_mapped("force") == "taixuan-gong")
                return;

        ap = ob->query_skill("force",1);
        dp = me->query_skill("force",1);
        if (ap / 2 + random(ap) < dp * 4 / 5)
        {
                if (me->query("neili") < me->query("max_neili") * 15 / 10)
                        me->add("neili", jiali);

                result = ([ "damage" : -damage ]);

                switch (random(4))
                {
                case 0:
                        result += ([ "msg" : HIM "$N" HIM "只觉得内力源源而泻"
                                             "，不由得大吃一惊。\n" NOR ]);
                        break;
                case 1:
                        result += ([ "msg" : HIM "$N" HIM "只觉得发出的内力犹"
                                             "如石沉大海，不知所踪。\n" NOR ]);
                        break;
                case 2:
                        result += ([ "msg" : HIM "$N" HIM "只觉得发出的内力犹"
                                             "无影无踪，浑然不知着落。\n" NOR ]);
                        break;
                default:
                        result += ([ "msg" : HIM "$N" HIM "不住催动内力，但是"
                                             "只觉得$n竟似毫不费力。\n" NOR ]);
                        break;
                }
                return result;
        }
}

int practice_skill(object me)
{
        return notify_fail("吸星大法只能用学的，或是从运用(exert)中增加熟练度。\n");
}

void check_count(object me)
{
        if (! me->query("can_learn/xixing-dafa/ren")
           && me->query("max_neili") >= 3000
           && me->query("exception/xixing-count") > 1000)
        {
                me->apply_condition("xixing-fanshi",
                        me->query_condition("xixing-fanshi") +
                        me->query("exception/xixing-count") / 10);
                me->delete("exception/xixing-count");
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;    
        lvl = me->query_skill("xixing-dafa", 1);
	

        if (lvl < 350 
		|| me->query_skill_mapped("force") != "xixing-dafa"           
	    ||me->query("neili") < 300
	    ||random(2) == 1)
		return 0;

	if (me->query_temp("xixing-dafa/xijing"))
	{				
		damage_bonus = lvl / 3 + me->query_con() * 5;
		damage_bonus += random(damage_bonus / 3);
		
        victim->receive_wound("jing", damage_bonus, me);

		if (victim->query("jing") > 0)
		    me->add("jing", damage_bonus/3);

        if (me->query("jing") > me->query("eff_jing"))
          	me->set("jing", me->query("eff_jing") );

		return HIM "$n" HIM "猛觉额角两侧如针刺般剧痛,精气被$N"+ HIM "源源不断地吸走！\n" NOR;
	} 
	
	if (me->query_temp("xixing-dafa/xiqi"))
	{		
		damage_bonus = lvl / 3 + me->query_con() * 8;
		damage_bonus += random(damage_bonus / 3);
		
        victim->receive_wound("qi", damage_bonus, me);

		if (victim->query("qi") > 0)
		    me->add("qi", damage_bonus/2);

        if (me->query("qi") > me->query("eff_qi"))
          	me->set("qi", me->query("eff_qi") );  

		return RED "$n" RED "只觉得膻中微痛,全身气血飞泄而出，为$N"RED"所吸走！\n" NOR;
	} 
	
	if (me->query_temp("xixing-dafa/xineili"))
	{    
		damage_bonus = lvl / 3 + me->query_con() * 12;
		damage_bonus += random(damage_bonus / 3);
			
        victim->add("neili", -damage_bonus);

		if ( victim->query("neili") < 0)
		    victim->set("neili",0);
		
		if (victim->query("neili") > 0)
		    me->add("neili", damage_bonus/2);

        if (me->query("neili") > me->query("max_neili")*2 - 500)
          	me->set("neili", me->query("max_neili")*2 - 500); 

		return HIG "$n" HIG "只觉得气海穴微痛,全身内力在$N"HIG"吸星大法的牵引下，如水银般循孔飞泄而出！\n" NOR;
	} 
	
	
}

void skill_improved(object me)
{
        me->add("exception/xixing-count", me->query_skill("xixing-dafa", 1) + 1);
        check_count(me);
}

string exert_function_file(string func)
{
        return __DIR__"xixing-dafa/" + func;
}
