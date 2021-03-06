// xiyang-boji.c 西洋搏击术
#include <ansi.h>
inherit SKILL;

string *dodge_msg = ({
	"$n身子一扭，恰好躲过了$N这一招。\n",
	"可是$n突然飞身后退，敏捷的躲过了$N这一招。\n",
	"$n奋力横移，闪开了$N的追击。\n",
	"$n身随$N转动，忽快忽慢，让$N无法捕捉到$n的踪影。\n",
        "$n嗔目大喝，气势异样恢弘，$N手一软，招数全然落空。\n",
});

string *dfail_msg = ({
	"$n身子一扭企图闪躲，但是$N早已经料到这一招，$n顿时受挫。\n",
	"$n突然飞身后退，$N不紧不慢一个大步反让$n防不胜防。\n",
	"$n身随$N转动，忽快忽慢，然而$N早已算到$n的踪影，顺势变招扑前直击。\n",
        "$n嗔目大喝，气势异样恢弘，不过$N随意一招，立刻瓦解了$n的气势。\n",
});

int valid_enable(string usage) { return usage == "dodge"; }

int valid_learn(object me) { return 1; }

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        string msg;
        int ap, dp, mp;

	if ((int) me->query_skill("xiyang-boji", 1) < 300 ||
            me->query_skill_mapped("dodge") != "xiyang-boji" ||
            ! living(me))
		return;

	mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("xiyang-boji", 1) + me->query_skill("dodge", 1) / 2;

        if (ap / 2 + random(ap) < dp)
        {
                msg = dodge_msg[random(sizeof(dodge_msg))];
                msg = replace_string(msg, "$N", "$N" HIW);
                msg = replace_string(msg, "$n", "$n" HIW);
                msg = HIW + msg + NOR;

                result = ([ "damage": -damage,
                            "msg"   : msg ]);

                return result;
        } else
        if (mp >= 100)
        {
                msg = dfail_msg[random(sizeof(dfail_msg))];
                msg = replace_string(msg, "$N", "$N" HIG);
                msg = replace_string(msg, "$n", "$n" HIG);
                msg = HIG + msg + NOR;
                COMBAT_D->set_bhinfo(msg);
        }
}

int practice_skill(object me)
{
        if( (int)me->query("qi") < 50 )
                return notify_fail("你的体力太差了，无法练习西洋搏击术。\n");

        me->receive_damage("qi", 40);
        return 1;
}
