#include <ansi.h>
#include <combat.h>

#define JQJY "「" HIB "绝情"HIW"绝义" NOR "」"
#define JQ "【" HIR "绝情" NOR "】"
#define JY "【" RED "绝义" NOR "】"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill = (int)me->query_skill("yinyang-ren", 1), i;
        string type1, type2, msg, nextmsg, edmsg,name;
        object weapon1, weapon2, equipment;
        int ap, dp, damage, j, count;

        if (me->query("dex") < 54)                
        return notify_fail("你的先天身法太低，难以施展出" JQJY "。\n");

        if (me->query_skill("yinyang-ren", 1) < 450)
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(JQJY "只能对战斗中的对手使用。\n");

        weapon1 = me->query_temp("weapon");
        weapon2 = me->query_temp("handing");

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("你没有同时装备刀剑，难以施展" JQJY "。\n");

        if (weapon2->query("consistence") <= 0)
                return notify_fail("你的" + weapon2->name() + "已经严重"
                                   "损坏，无法继续使用了。\n");

        type1 = weapon1->query("skill_type");
        type2 = weapon2->query("skill_type");

        if ((type1 != "sword" && type1 != "blade")
           || (type2 != "sword" && type2 != "blade"))
                return notify_fail("你所使用的武器不对，难以施展" JQJY "。\n");

        if ((type1 == "sword" && type2 != "blade")
           || (type1 == "blade" && type2 != "sword"))
                return notify_fail("你没有同时装备刀剑，难以施展" JQJY "。\n");

        if (me->query_skill_mapped("sword") != "yinyang-ren"
           || me->query_skill_mapped("blade") != "yinyang-ren")
                return notify_fail("你没有激发阴阳刃，难以施展" JQJY "。\n");

    if ((int)me->query_skill("yinyang-ren", 1) < 800)
        return notify_fail("以你阴阳刃的修为来看，还不足以运用"JQJY"。\n");

    if ((int)me->query_skill("fenxin-jue", 1) < 500)
        return notify_fail("以你焚心诀的修为来看，还不足以运用"JQJY"。\n");

    if (me->query("max_neili") < 10000)
        return notify_fail("你的内力修为不够运用"JQJY"所需！\n");

    if (me->query("neili") < 2000)
        return notify_fail("你的内力不够运用"JQJY"所需！\n");

    if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
    
  
    msg =WHT "$N剑收背后，刀横胸前义正辞严" YEL "「望门投止思张俭，忍死须臾待杜根。我自横刀向天笑，去留肝胆两昆仑！」" WHT "。\n"
                     "$n心想，此诗荡气回肠，此人慷慨激昂，应该不是那卑鄙无耻之徒,于是放松的警惕，顿时门户大开。\n"
                     "$N身形逆转使出了"NOR""JQJY"之"JY""WHT"式，刹那间天空阴云密布。\n"
                     "$n的心脏几乎停止了跳动，呆呆的望着$N。$N的眼中能看见的只有无数碎裂的" RED "【义】" WHT "！\n"NOR;

        ap = me->query_skill("yinyang-ren", 1) + me->query_skill("blade") + me->query_skill("sword") + me->query_skill("force"); 
        dp = target->query_skill("dodge") + target->query_skill("parry");

        if (ap * 3 / 5 + random(ap) > dp)
        {
        	 me->add("neili",-800);
            damage = ap*2 + random(ap)*2;
            msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
              BLU "$n没想到$N会突然出手偷袭，方寸大乱。$N手中"+weapon1->name()+
              RED "如同成千上万破碎的情义，让$n避无可避！\n" NOR);  
			
			   if (objectp(equipment = target->query_temp("weapon")))
			   {
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += HIR "“锵”的一声脆响，$n" HIR "手"
										"持的" + name + HIR "被$N" HIR "刀剑横飞划得"
										"七零八落，碎的满地皆是。\n" NOR;  			 
                           }
        } else
        {
           me->add("neili",-500);
            msg += HIG "然而$n" HIG "识得此招厉害，早有准备，将$N" HIG
            "的攻势一一化解。\n" NOR;
        } 
         message_vision(msg, me, target);
  
        nextmsg =HIM "$N目光呆滞，口中呢喃" HIC "「问世间，情为何物？直教生死相许。天南地北双飞客，老翅几回寒暑。\n"
                                 "欢乐趣，离别苦，就中更有痴儿女。君应有语。渺万里层云，千山暮雪，只影为谁去。」" HIM "\n"
                                 "唱完上阙，便引剑自刎。$n想到自己的爱人，感到同病相怜，向前一步，准备救下$N。\n"
                                 "" HIG "突然$N身形一转眨眼间使用阴阳刃的终极绝招----"NOR""JQJY""HIM"之"NOR""JQ"式。\n"
                                 "" HIG "$N眼神莹然有光，似乎进入了" HIR "【绝情】" HIG "的境界。\n"
                                 "$N手中" + weapon2->name() + "化做无数幻影攻向$n。\n";
                
        if (ap * 3 / 4 + random(ap) > dp)
        {
             // 转移武器
                weapon1->move(me, 1);
                weapon2->wield();

        	 me->add("neili",-800);
            damage += random(ap) ;
            nextmsg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 120,
              HIY "$n只觉「情义」害人不浅，$N如同死神一般，势必要取$n性命！\n" NOR);    
                	
	      // 转移回初始状态
                weapon2->move(me, 1);
                weapon1->wield();
                me->set_temp("handing", weapon2);
								
			if (objectp(equipment = target->query_temp("armor/armor")) && random(3)==1)
			{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += HIR "“噼噼啪啪”的一阵脆响，$n" HIR "身"
										"着的" + name + HIR "被$N" HIR "刀剑横飞划得"
										"七零八落，碎的满地皆是。\n" NOR; 
			}
			if (objectp(equipment = target->query_temp("armor/cloth")) && random(3)==1)
			{
					name = equipment->name();                                                        
					equipment->set("consistence", 0);									 
					equipment->move(environment(me));
					msg += HIR "“噼噼啪啪”的一阵脆响，$n" HIR "身"
										"着的" + name + HIR "被$N" HIR "刀剑横飞划得"
										"七零八落，碎的满地皆是。\n" NOR;   
			}
        } else
        {
           me->add("neili", -500);
            nextmsg += HIG "$n早知此人卑鄙无耻，留有后着，将$N" HIG
            "的攻势一一化解。\n" NOR;
        }
                message_vision(nextmsg, me, target);



       edmsg = HIW "$N见奸计被人识破，心想绝不能留下活口，于是手中" + weapon1->name() + HIW "蓦地一抖"
              "，将阴阳刃连环施出。霎时寒光点点，犹如夜陨划空，铺天盖地罩向$n。\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                edmsg += HIW "$n" HIW "只见无数刀光剑影向自己逼"
                       "来，顿感眼花缭乱，心底寒意油然而生。\n" NOR;
                count = ap / 6;
                me->set_temp("yinyang-ren/max_pfm", 1);
        } else
        {
                edmsg += HIG "$n" HIG "突然发现自己四周皆被刀光"
                      "剑影所包围，心知不妙，急忙小心招架。\n" NOR;
                count = ap / 12;
        }
        message_combatd(edmsg, me, target);

       me->add("neili", -600);
       me->add_temp("apply/attack", count);       
       me->add_temp("apply/damage", count * 1 / 3);

        for (j = 0; j < 6; j++)
       {
               if (! me->is_fighting(target))
                        break;
          COMBAT_D->do_attack(me, target, weapon1, 0);
        }
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count * 1 / 3);
     me->delete_temp("yinyang-ren/max_pfm");
        me->start_busy( 2 + random(7));      
        return 1;
}

                


