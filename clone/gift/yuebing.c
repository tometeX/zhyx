#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "中秋月饼" NOR, ({ "yuebing" }) );
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一块“天下无敌”巫师组发放的中秋月饼。\n"
                                "月饼散发着诱人的香味，你禁不住想去吃一口。\n" NOR);
                set("value", 500000);
                set("unit", "块");
                set("no_give",1);
                set("no_drop",1);
                set("no_sell",1);
                set("only_do_effect", 1);
        }
}

int do_effect(object me)
{
        string mapsk;
        int effect;
        int neili;

        log_file("static/yuebing", sprintf("%s(%s) eat 月饼 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

        effect = 0;

                if (me->query("/txwd/gift/zhongqiu2004_eated")){
            message_vision("你都吃过了，还吃，赶紧交给巫师要不你麻烦了！",me);
            return 1;}
                message_vision(HIW "$N" HIW "一仰脖，吞下了一块月饼，只见$P"
                               HIW "浑身一颤，七窍都冒出白烟来。\n" NOR, me);

                me->add("combat_exp", 200000 + random(100000));
                me->add("magic_points", 3000);
                me->add("potential", 30000);

                mapsk = me->query_skill_mapped("force");
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force", 1500000);

                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);
                if (stringp(mapsk) && me->can_improve_skill(mapsk))
                        me->improve_skill(mapsk, 1500000);

                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);

                me->improve_neili(800);
                me->improve_jingli(500);
                me->set("/txwd/gift/zhongqiu2004_eated", 1);
        destruct(this_object());
        return 1;
}


