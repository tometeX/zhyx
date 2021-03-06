// murong-jiafa 慕容剑法
// by Lonely

inherit SKILL;

string *action_msg = ({
        "$N剑尖下指，一式「洗耳恭听」，双脚后退三步，剑尖直点$n腿部",
        "$N踏前数步，避虚就实，右手使一式「明察秋毫」直刺$n的右肋",
        "$N一招「甜言蜜语」，剑尖抖起五朵剑花，分别刺向$n的左脸和右耳",
        "$N剑身横摆，剑尖指向$n的脸部，一招「望尘莫及」，宛若万马千军一般，横扫$n的$l",
        "$N双脚离地，使出草上飞，身行直奔$n，一招「骑虎难下」，剑出中宫，平削$n的$l",
        "$N长笑一声，横剑斜削，一招「抛砖引玉」，剑风逼向$n的$l",
});


int valid_enable(string usage) { return (usage == "sword") || (usage == "parry"); }
int valid_learn(object me)
{
        if ((int)me->query("max_neili") < 100)
                return notify_fail("你的内力不够。\n");
        if ((int)me->query_skill("shenyuan-gong", 1) < 20)
                return notify_fail("你的神元功火候太浅。\n");
        if ((int)me->query_skill("parry", 1) < 10)
                return notify_fail("你的基本招架火候太浅。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))],
                "damage": 120 + random(50),
                "attack": 60 + random(10),
                "dodge" : 60 + random(10),
                "parry" : 60 + random(10),
                "damage_type" : random(2)?"刺伤":"割伤",
        ]);
}

int practice_skill(object me)
{
        object weapon;

        if (!objectp(weapon = me->query_temp("weapon"))
        || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");
        if ((int)me->query("qi") < 70)
                return notify_fail("你的体力不够练慕容剑法。\n");
        if ((int)me->query("neili") < 70)
                return notify_fail("你的内力不够练慕容剑法。\n");
        me->receive_damage("qi", 60);
        me->add("neili", -60);
        return 1;
}
           
string perform_action_file(string action)
{
        return __DIR__"murong-jianfa/" + action;
}

