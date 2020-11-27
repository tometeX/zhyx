// Code of JHSH
// yiyang.c 一阳指力注入武器

#include <ansi.h>

inherit F_SSERVER;

private int remove_effect(object me, object weapon);

int perform(object me, object target)
{
        object weapon;
        int skill, skill1, damage;

        if (me->query_skill_mapped("force") != "kurong-changong" &&
            me->query_skill_mapped("force") != "duanshi-xinfa")
                return notify_fail("你所用得内功心法不对，无法运用一阳指。\n");

        if (me->query_temp("yiyang"))
                return notify_fail("你已运一阳指指力于武器上了！\n");

        if (me->query_skill("force",1)<100
                || (me->query_skill("kurong-changong",1)<100 &&
                    me->query_skill("duanshi-xinfa",1)<100)
                || me->query_skill("duanjia-sword",1)<100
                || me->query_skill("sun-finger",1)<120)
                return notify_fail("你的功力不够，无法运用一阳指指力于武器上！\n");

        if (!objectp(weapon = me->query_temp("weapon")) || weapon->query("skill_type")!="sword")
                return notify_fail("你没有使用正确的武器，无法运一阳指力于其上。\n");

        if (weapon->query_temp("yiyang"))
                return notify_fail("该武器已经注满了一阳指指力！\n");

        if (me->query("neili") <= 300)
                return notify_fail("你的内力不够运一阳指力！\n");

        if (me->query("jingli") <= 100)
                return notify_fail("你的精力不够运一阳指力！\n");

        if (weapon->query("weapon_prop/damage")>=500)
                return notify_fail("你发现这件武器打造的精致无比，巧夺天功，无法灌注内力于其上！\n");

        message("vision", HIY "\n"+me->query("name")+"紧握"+weapon->query("name")+"凝神运气片刻。\n\n" NOR, environment(me), me);
        tell_object(me, HIY "\n你凝神运气，把一阳指指力灌注到"+weapon->query("name")+"上。\n\n" NOR);

        skill = me->query_skill("force");

        me->set_temp("yiyang", 25+skill/10);

        skill = me->query_skill("sun-finger",1) + me->query_skill("kurong-changong",1);
	skill /= 3;
        weapon->set_temp("rig", weapon->query("weapon_prop/damage"));
        weapon->set_temp("yiyang", 1);

        if (weapon->query("weapon_prop/damage") < 100 )
		damage = 300 + skill;
        else if ( weapon->query("weapon_prop/damage") < 300 )
		damage = 200 + skill;
        else if ( weapon->query("weapon_prop/damage") < 500 )
		damage = 100 + skill;

        weapon->add("weapon_prop/damage", damage);
	me->add_temp("apply/damage", damage);
        call_out("checking", 1, me, weapon);
        me->add("neili", -200);
        me->add("jingli", -50);

        return 1;
}

void checking(object me, object weapon)
{
        if (!me) {
		if (!weapon) return;
                weapon->set("weapon_prop/damage", weapon->query_temp("rig"));
                weapon->delete_temp("yiyang");
                weapon->delete_temp("rig");
                return;
        }
        if (me->query_temp("yiyang")) {
	   if (!weapon)
	   {
               	remove_effect(me, weapon);
	        tell_object(me, HIY "\n你把一阳指指力收了回来。\n\n" NOR);
                return;
	   }
           else if (environment(weapon)!= me || weapon!=me->query_temp("weapon")) {
               	remove_effect(me, weapon);
	        tell_object(me, HIY "\n你把一阳指指力从"+weapon->name()+"上收了回来。\n\n" NOR);
                return;
           }
           else if (weapon->query("weapon_prop") == 0) {
                remove_effect(me, weapon);
                tell_object(me, HIY "\n你的"+weapon->name()+"已毁，不得不收回灌注于其上的一阳指指力。\n\n" NOR);
                return;
           }
           else if (me->query_skill_mapped("force") != "kurong-changong" &&
                    me->query_skill_mapped("force") != "duanshi-xinfa") {
                remove_effect(me, weapon);
                tell_object(me, HIY "\n你感到内息不畅，无法保持灌注在"+weapon->name()+"上的一阳指指力。\n\n" NOR);
                return;
           }

           me->add_temp("yiyang", -1);
           call_out("checking", 1, me, weapon);
        }
        else {
           remove_effect(me, weapon);
        tell_object(me, HIY "\n你感到内息混浊，不得不换气运功，从"+weapon->name()+"上收回灌注的一阳指指力。\n\n" NOR);
        }
}       

private int remove_effect(object me, object weapon)
{
	if (weapon)
	{
		if (me->query_temp("weapon") &&
        	    me->query_temp("weapon") == weapon)
		    me->add_temp("apply/damage", -weapon->query("weapon_prop/damage") + weapon->query_temp("rig"));
	        weapon->set("weapon_prop/damage", weapon->query_temp("rig"));
        	weapon->delete_temp("yiyang");
	        weapon->delete_temp("rig");
	}
        me->delete_temp("yiyang");
        return 1;
}
