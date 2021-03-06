inherit FORCE;

int valid_enable(string usage) { return usage == "force"; }

int valid_force(string force)
{
        return force == "shenlong-xinfa" ||
               force == "xuanming-shengong" ||
               force == "minggu-xinfa" ;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("huaxue-shengong", 1);
        return lvl * lvl * 15 * 16 / 100 / 200;
}

int valid_learn(object me)
{
        if (me->query("gender") == "无性"
           && (int)me->query_skill("huaxue-shengong", 1) > 99)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的化血神功。\n");

        if ((int)me->query_skill("force", 1) < 100)
                return notify_fail("你的基本内功火候还不够。\n");

        if ((int)me->query_skill("shenlong-xinfa", 1) < 100)
                return notify_fail("你对神龙心法领悟的太浅，无法理解化血神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("化血神功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"huaxue-shengong/" + func;
}
