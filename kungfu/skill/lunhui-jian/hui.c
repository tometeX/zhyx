//Updated by Kasumi.
#include <ansi.h>
#include <combat.h>

#define HUI "「" HIR "真·六道轮回" NOR "」"

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);
string attack3(object me, object target, int damage);
string attack4(object me, object target, int damage);
string attack5(object me, object target, int damage);
string attack6(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        string wn, msg;
        object sroom, room;
        int ap, dp, damage;

        if (userp(me) && ! me->query("can_perform/lunhui-jian/rendao")&&! me->query("can_perform/lunhui-jian/tiandao")&& ! me->query("can_perform/lunhui-jian/eguidao") && ! me->query("can_perform/lunhui-jian/chushengdao") && ! me->query("can_perform/lunhui-jian/diyudao")&&! me->query("can_perform/lunhui-jian/xiuluodao"))
                return notify_fail("六道轮回你一道都没领悟，无法施展。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" HUI "。\n");

        if ((int)me->query_skill("force") < 550)
                return notify_fail("你的内功修为不够，难以施展" HUI "。\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("你的内力修为不够，难以施展" HUI "。\n");

        if ((int)me->query_skill("buddhism", 1) < 500)
                return notify_fail("你对禅宗心法参悟不够，难以施展" HUI "。\n");

        if ((int)me->query_skill("lunhui-jian", 1) < 200)
                return notify_fail("你释迦轮回剑火候不够，难以施展" HUI "。\n");

        if (me->query_skill_mapped("sword") != "lunhui-jian")
                return notify_fail("你没有激发释迦轮回剑，难以施展" HUI "。\n");

        if ((int)me->query("neili") < 1000)
                return notify_fail("你现在真气不够，难以施展" HUI "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        wn = weapon->name();

        message_combatd(HIW "$N" HIW "面露拈花之意，祭起手中" + wn +
                        HIW "，霎时碧波流转，华光万丈，说不尽的祥和。"
                        "\n" NOR, me, target);

        //  记录下最初的房间
        if (! objectp(sroom = environment(me)))
                return 1;

        ap = me->query_skill("lunhui-jian",1) +
             me->query_skill("buddhism", 1);

        

		//人间道
		
		dp = target->query_skill("force",1) +
             target->query_skill("buddhism", 1);

        damage = ap + random(2*ap);
		 if (me->query("can_perform/lunhui-jian/rendao"))
		 {
        
             room = find_object("/d/special/liudaolunhui/rendao");
             if (! room) room = load_object("/d/special/liudaolunhui/rendao");

             me->move(room);
             target->move(room);

             message_vision(HIY "\n$N" HIY "左手轻轻一拨，右手所持的" + wn +
                            HIY "叮呤做响，剑姿说不出的潇洒妙曼。\n" NOR, me, target);

             if (ap *2 / 3 + random(ap) > dp)
             {
                    msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                               (: attack1, me, target, damage :));
             } else
             {
                 msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
              }
              message_vision(msg, me, target);
			  me->add("neili", -150 - random(100));
		 }

        // 畜生道
        
        dp = target->query_skill("force",1) +
             target->query_skill("buddhism", 1);

        damage = ap + random(2*ap);
		  if (me->query("can_perform/lunhui-jian/chushengdao"))
		  {
              room = find_object("/d/special/liudaolunhui/chushengdao");
              if (! room) room = load_object("/d/special/liudaolunhui/chushengdao");

               me->move(room);
               target->move(room);

               message_vision(HIY "\n却见$N" HIY "面无表情，将手中" + wn +
                       HIY "猛的往前一递，犹如毒蛇般噬向$n" HIY "。\n"
                       NOR, me, target);

               if (ap * 2 / 3  + random(ap) > dp)
               {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
                                           (: attack2, me, target, damage :));
               } else
               {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
               }
                message_vision(msg, me, target);
				 me->add("neili", -150 - random(100));
		  }

        // 饿鬼道
        dp = target->query_skill("dodge",1) +
             target->query_skill("buddhism", 1);

        damage = ap + random(2*ap);
	   if (me->query("can_perform/lunhui-jian/eguidao"))
	   {
           room = find_object("/d/special/liudaolunhui/eguidao");
           if (! room) room = load_object("/d/special/liudaolunhui/eguidao");

            me->move(room);
            target->move(room);

            message_vision(HIY "\n$N" HIY "一声长叹，左手捏着剑诀，忽闻" +
                       wn + HIY "上血腥之气渐浓，朝$n" HIY "迎头斩落。\n"
                       NOR, me, target);

            if (ap * 2 / 3  + random(ap) > dp)
            {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 110,
                                           (: attack3, me, target, damage :));
            } else
            {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
             }
             message_vision(msg, me, target);
			  me->add("neili", -150 - random(100));
	   }

        // 修罗道
        dp = target->query_skill("dodge",1) +
             target->query_skill("buddhism", 1);

        damage = ap + random(2*ap);
	    if (me->query("can_perform/lunhui-jian/xiuluodao"))
		{
            room = find_object("/d/special/liudaolunhui/xiuluodao");
            if (! room) room = load_object("/d/special/liudaolunhui/xiuluodao");

            me->move(room);
            target->move(room);

            message_vision(HIY "\n忽见$N" HIY "身形微晃，顿时幻出十数个身"
                       "影，十数柄" + wn + HIY "齐向$n" HIY "刺去。"
                       "\n" NOR, me, target);

            if (ap * 2 / 3  + random(ap) > dp)
            {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 130,
                                           (: attack4, me, target, damage :));
            } else
            {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
            }
            message_vision(msg, me, target);
			 me->add("neili", -150 - random(100));
		}

        // 地狱道
        dp = target->query_skill("parry",1) +
             target->query_skill("buddhism", 1);

        damage = ap + random(3*ap);
		 if (me->query("can_perform/lunhui-jian/diyudao"))
		 {
              room = find_object("/d/special/liudaolunhui/diyudao");
              if (! room) room = load_object("/d/special/liudaolunhui/diyudao");

              me->move(room);
              target->move(room);

              message_vision(HIY "\n紧接着$N" HIY + wn + HIY "一颤，有若龙吟"
                       "，剑身腾起一道滔天寒流，向四周扩散开去。\n" NOR,
                       me, target);

              if (ap *3/ 4 + random(ap) > dp)
              {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 150,
                                           (: attack5, me, target, damage :));
               } else
               {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
               }
               message_vision(msg, me, target);
			    me->add("neili", -150 - random(100));
		 }

        // 六道轮回之天极道
        
        dp = target->query_skill("parry",1) +
             target->query_skill("buddhism", 1);

        damage = ap *2 + random(5*ap);
		if (me->query("can_perform/lunhui-jian/tiandao"))
		{
            room = find_object("/d/special/liudaolunhui/tiandao");
            if (! room) room = load_object("/d/special/liudaolunhui/tiandao");

            me->move(room);
            target->move(room);

             message_vision(HIY "\n$N" HIY "身外化身，剑外化剑，手中" + wn +
                       HIY "便似蛟龙腾空，拨云见日，天地为之失色。\n"
                       NOR, me, target);

            if (ap *3/ 4 + random(ap) > dp)
            {
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 170,
                                           (: attack6, me, target, damage :));
            } else
            {
                msg = CYN "可是$n" CYN "收敛心神，奋力招"
                      "架，将剑招卸于无形。\n" NOR;
             }
             message_vision(msg, me, target);
			  me->add("neili", -150 - random(100));
		}

        me->start_busy(3 + random(3));
       

       
        tell_object(me, "\n\n");
        tell_object(target, "\n\n");

        // 转移回最初的房间
        me->move(sroom);
        target->move(sroom);

        // 不能通过断线来保命
        //if (target->query("qi") < 0)
        //        target->die(me);

        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$n" HIR "只觉心头一阵凄苦，竟忍不住要落"
              "下泪来，喉咙一甜，呕出一口鲜血。\n" NOR;
        if (random(5) > 2)
		{
        if (! target->query_temp("rendao"))
        {
                msg += WHT "$p忽然察觉到全身的力气竟似一丝"
                       "丝远离自己而去，无助之极。\n" NOR;

                target->add_temp("apply/attack", -500);
                target->add_temp("apply/parry", -500);
                target->add_temp("apply/dodge", -500);
                target->set_temp("rendao", 1);
				call_out("rendao_end", 10 + random(5), me, target);
        }
		
		}
        return msg;
		
}

string attack2(object me, object target, int damage)
{
        object weapon;
        string wn, msg;

        msg = HIR "忽然间$n" HIR "感到胸口处一阵火热，剑气"
              "袭体，带出一蓬血雨。\n" NOR;

		 if (random(5) > 2)
		 {
            if (objectp(weapon = target->query_temp("weapon")))
            {
                wn = weapon->name();
                msg += WHT "忽听「锵锵锵」几声脆响，$n" WHT "的" + wn +
                       WHT "竟被$N" WHT "绞成了块块碎片。\n" NOR;

                weapon->set("consistence", 0);
                weapon->move(target);
            }
		 }
        return msg;
}

string attack3(object me, object target, int damage)
{
        int shd;
        string msg;

        msg = HIR "剑锋过处，卷起漫天血浪，$n" HIR "只感头晕目"
              "眩，四肢乏力，难以再战。\n" NOR;

		if (random(5) > 2)
		{
           if (target->query_temp("shield"))
           {
                shd = target->query_temp("apply/armor");

                target->add_temp("apply/armor", -shd);
                target->delete_temp("shield");

                msg += WHT "$N" WHT "气劲涌至，宛若刀割，顿时将$n"
                       WHT "的护体真气摧毁得荡然无存。\n" NOR;
           }
		}
        return msg;
}

string attack4(object me, object target, int damage)
{
        object cloth, armor;
        string cn, an, msg;

        msg = HIR "$n" HIR "顿时大惊失色，瞬间已被$N" HIR "连中"
              "数剑，直削得血肉模糊。\n" NOR;

		 if (random(5) > 2)
		 {
            if (objectp(cloth = target->query_temp("armor/cloth")))
            {
                cn = cloth->name();
                msg += WHT "忽听轰然声大作，$n" WHT "身着的" + cn +
                       WHT "在$N" WHT "内力激荡下，竟被震得粉碎。\n"
                       NOR;

                cloth->set("consistence", 0);
                cloth->move(target);
              } else
              if (objectp(armor = target->query_temp("armor/armor")))
              {
                an = armor->name();
                msg += WHT "忽听「哧啦」一声脆响，$n" WHT "身着的" +
                       an + WHT "竟被$N" WHT "震裂，化成块块碎片。\n"
                       NOR;

                armor->set("consistence", 0);
                armor->move(target);
              }
		 }
        return msg;
}

string attack5(object me, object target, int damage)
{
        string msg;

        msg = HIR "只见$n" HIR "全身一阵抽搐，被剑锋所携的极寒气流"
              "包裹其中，刺痛难当。\n" NOR;

		 if (random(5) > 2)
		 {
           if (! target->query_condition("poison"))
           {
                target->affect_by("poison",
                	([ "level"    : damage * 2,
                           "name"     : "炼狱寒焰",
                           "id"       : me->query("id"),
                           "duration" : damage / 20 ]));

                msg += WHT "霎时间$n" WHT "忽觉一股奇寒散入七经八脉"
                       "，仿佛连血液都停止了流动。\n" NOR;
            }
		 }
        return msg;
}

string attack6(object me, object target, int damage)
{

        string msg;

        msg = HIR "$N" HIR "剑势迅猛之极，令$n" HIR "毫无招架余地，"
              "竟镇怯当场，素手待毙。\n" NOR;

		 if (random(5) > 2)
		 {
            if (! target->query_temp("no_exert")
               || ! target->query_temp("no_perform"))
            {
                target->set_temp("no_exert", 1);
                target->set_temp("no_perform", 1);

                msg += WHT "$n" WHT "只感到全身真气涣散，丹元瓦解，似"
                       "乎所有的武功竟都消逝殆尽。\n" NOR;
				call_out("tiandao_end", 10 + random(5), me, target);
            }			
		}
        return msg;
}


void rendao_end(object me, object target)
{
        if (target && target->query_temp("rendao"))
        {
                if (living(target))
                {
			    target->add_temp("apply/attack", 500);
                target->add_temp("apply/parry", 500);
                target->add_temp("apply/dodge", 500);
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                        tell_object(target, HIY "你感到气力又逐渐恢复了。\n" NOR);
                }
                target->delete_temp("rendao");
	}
	return;
}


void tiandao_end(object me, object target)
{
        if (target && target->query_temp("no_perform") && target->query_temp("no_exert"))
        {
                if (living(target))
                {
			   
                        message_combatd(HIC "$N" HIC "深深吸入一口"
                                        "气，脸色由白转红，看起来好"
                                        "多了。\n" NOR, target);

                         tell_object(target, HIY "你感到被扰乱的真气"
                                            "慢慢平静了下来。\n" NOR);
                }               
				target->delete_temp("no_perform");
				target->delete_temp("no_exert");
	}
	return;
}