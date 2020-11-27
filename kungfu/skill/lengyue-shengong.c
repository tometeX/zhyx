inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }


int valid_force(string force)
{
        return force == "miaojia-neigong" ||              
               force == "lengyue-shengong";
}


int query_neili_improve(object me)
{
    int lvl;

    lvl = (int)me->query_skill("lengyue-shengong", 1);
    return lvl * lvl * 15 * 12 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("lenyue-shengong", 1);

        if ( me->query("gender") == "无性" && lvl > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的冷月神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
    return notify_fail("冷月神功只能用学(learn)的来增加熟练度。\n");
}

string exert_function_file(string func)
{
    return __DIR__"lengyue-shengong/" + func;
}
