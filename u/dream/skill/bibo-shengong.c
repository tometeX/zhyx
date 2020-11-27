// bibo-shengong.c 碧波神功
// by Lonely

inherit FORCE;

int valid_force(string force) { return 1; }

int valid_enable(string usage) { return usage == "force"; }

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bibo-shengong", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

int valid_learn(object me)
{
        int lvl = (int)me->query_skill("bibo-shengong", 1);

        if (me->query("gender") == "无性" && lvl > 49)
                return notify_fail("你无根无性，阴阳不调，难以领会高深的碧波神功。\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("碧波神功只能用学增加熟练度。\n");
}

string exert_function_file(string func)
{
        return __DIR__"bibo-shengong/" + func;
}

mapping exercise_msg(object me)
{
        return ([
                "start_self"   : "盘腿坐下，双目微闭，双手掌心相向成虚握太极，天人合一，练气入虚。\n",
                "start_other"  : "盘腿坐下，双目微闭，双手掌心相向成虚握太极。轻风吹过，" + me->name() + 
                                 "身上的衣袍竟然不为所动。\n",
                "finish_self"  : "将内息又运了一个小周天，缓缓导入丹田，双臂一震，站了起来。\n",
                "finish_other" : "脸上红光乍现，又立刻隐去。随即双臂一震，站了起来。\n"
        ]);
}
