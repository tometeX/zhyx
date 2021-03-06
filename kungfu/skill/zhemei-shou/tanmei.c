// feilong.c 逍遥折梅手【弹梅.落雪.散花香】

#include <ansi.h>
#include <combat.h>

#define TANMEI "" HIG "【" HIM "弹梅." HIW "落雪." HIY "散花香" HIG "】" NOR ""

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, pp, fp, bp;


        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TANMEI "只能在战斗中对对手使用。\n");

        if ((int)me->query_skill("zhemei-shou", 1) < 800)
                return notify_fail("你逍遥折梅手不够娴熟，无法施展" TANMEI "。\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 500)
                return notify_fail("你八荒六合唯我独尊功不够娴熟，无法施展" TANMEI "。\n");

        if (me->query("dex") < 40)
                return notify_fail("你先天身法不足，无法施展" TANMEI "。\n");

        if (me->query("con") < 40)
                return notify_fail("你先天根骨不足，无法施展" TANMEI "。\n");

	if (! me->query("reborn"))        
		return notify_fail("你尚未转世重生，无法领会此绝招！\n");
      
        if( (int)me->query("max_neili") < 12000 )
                return notify_fail("你的内力修为太差，无法施展" TANMEI "。\n"); 

        if ((int)me->query("neili") < 1000)
                return notify_fail("你现在真气不够，无法施展" TANMEI "！\n");

        if (me->query_skill_mapped("hand") != "zhemei-shou")
                return notify_fail("你没有激发逍遥折梅手，无法使用" TANMEI "。\n");

        if (me->query_skill_prepared("hand") != "zhemei-shou")
                return notify_fail("你没有准备逍遥折梅手，难以施展" TANMEI "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        me->add("neili", -800);

        ap = me->query_skill("bahuang-gong", 1) + me->query_skill("zhemei-shou", 1) + me->query_skill("qimen-wuxing", 1) + me->query("jiali");
        dp = target->query_skill("dodge") + target->query_skill("qimen-wuxing", 1);
        pp = target->query_skill("parry") + target->query_skill("qimen-wuxing", 1);
        fp = target->query_skill("force") + target->query_skill("qimen-wuxing", 1);
        bp = dp + pp + fp;
        
        msg = HIM "                                          【弹 梅】\n"NOR;
        msg += HIM "$N微微一笑吟出" HIC "「耐得人间雪与霜，百花头上尔先香」" HIM "的同时，左手向$n轻轻弹出，好像是要弹去梅花上面的露珠！\n" NOR;
        if (ap * 3 / 5 + random(ap) > dp)
        {       damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50 + random(10),
                                           HIM "$n" HIM "被眼前的景象迷住了，竟然忘记了后退，躲避不及，被$N"
                                           HIM "震得口吐鲜血，也浑然不知。\n" NOR);
        }
        else
                msg += CYN "$n" CYN "识破了$N的意图，微微斜身躲过这一击。\n" NOR;

        msg += HIW "                                          【落 雪】\n"NOR; 
        msg += HIW "$N双手急挥，左右摇摆，幻出漫天梅花，飞雪似的向$n落来！\n" NOR;
        if (ap * 3 / 5 + random(ap) > pp)
        {       damage += random(ap);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70 + random(10),
                                           HIW "飞雪漫天，正是" HIG "「飘风骤雨惊飒飒，落花飞雪何茫茫」" HIW "，$n" HIW "哪里来得及闪"
                                           "避招架？只见$N" HIW "身中数下，$n"
                                           HIW "鼻孔流血！\n" NOR);
        }
        else
                msg += CYN "$n" CYN "判断出了梅花的方向向，向后轻轻一退，避过了飞雪般的梅花。\n" NOR;                

        msg += YEL "                                          【散花香】\n"NOR;
        msg += YEL "$n突然闻到一股若有若无的香味，心猿意马之中$N的双手已向$n胸口拍来！\n" NOR;
        if (ap / 2 + random(ap) > fp)
        {       damage += random(ap);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + random(10),
                                           YEL "$n" YEL "如痴如醉,$N口中吟道" WHT "「冰雪林中著此身，不同桃李混芳尘。」" YEL ",一击即中。\n"
                                           "$n" YEL "七窍流血，却也不知不觉。$N口中继续吟道" WHT "「忽然一夜清香发，散作乾坤万里春」" YEL "！\n" NOR);
        
        }
        else
                msg += CYN "$n" CYN "心之不妙，双手护胸，硬接下了这一击。\n" NOR;
       
        msg += HIC "$N" HIC "将奇门五行之术融入折梅手之中，双手幻出漫天手影，宛若朵朵梅花，将$n笼罩在一片梅海之中！\n" NOR;
        if (ap * 3 / 2 + random(ap) > bp)
        {       damage += random(ap);
                 msg += HIM "只听$n" HIM "一声尖啸，$N" HIM "的五色梅"
                               "花已尽数击中$p" HIM "身体，顿时将$p" HIM "割"
                               "为一个血人。\n" NOR;
                 target->receive_damage("qi", damage, me);
                 target->receive_wound("qi", damage / 2, me);
                 target->receive_damage("jing", damage / 3, me);
                 target->receive_wound("jing", damage / 4, me);
                 target->start_busy(2);
        } else
        {
                msg += CYN "可是$p" CYN "的看破了$P" CYN "的企图，丝"
                      "毫不为所动，让$P" CYN "的虚招没有起得任何作用。\n" NOR;
                me->start_busy(2);
        }


        me->start_busy( 1 + random(3));
        message_combatd(msg, me, target);
        return 1;
}
