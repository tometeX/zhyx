#include <ansi.h> 
#include <mudlib.h>

inherit ITEM;

int top_list(object ob1, object ob2);
int get_score(object ob);

void create()
{
        set_name(HIG "十大富翁排行榜" NOR, ({ "rich wall", "rich"}));
        set_weight(500000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\n这是一面由整块墨玉雕琢而成的十大富翁排行榜。上面"
                            "刻着当今武林中\n家产最为富有的十大超级富翁，你"
                            "可以通过(view)来查阅排名。\n" NOR);
                set("no_get", "好家伙，连墙都想抗起来。\n");
                set("unit", "面");
                set("value", 1000000);
                set("material", "stone");
        }
        setup();
        move("/d/city/beidajie1");
}

void init()
{
        add_action("do_view", "view");
}

int do_view(string arg)
{
        object *list, *ob, me;
        int i;
        string msg;

        me = this_player();

        if (arg != "heros wall" && arg != "heros" && arg != "wall")
                return notify_fail("你打算阅读什么？\n");

        // 防止系统资源消耗过大，限时浏览。
        if (! wizardp(me) && time() - me->query_temp("last_view") < 100)
                return notify_fail(HIW "\n突然间英雄壁上一道光华闪过，使你"
                                   "难以辨清壁上的字迹。\n" NOR);

        ob = filter_array(objects(), (: userp($1) && ! wizardp($1) :));

        list = sort_array(ob, (: top_list :));

        msg =  HIW "\n            ┏━━『" HIG " 富 翁 榜 " HIW "』━━┓\n";
        msg += "┏━━━┯━┻━━━━━━━━┯━━┻━┯━━━━┓\n";
        msg += "┃ " HIG "排名" HIW " │    " HIG "姓        氏" HIW
               "    │ " HIG "门  派" HIW " │ " HIG "评  价" HIW " ┃\n";
        msg += "┠───┴──────────┴────┴────┨\n";

        for (i = 0; i < 10; i++)
        {
                if (i >= sizeof(list))
                {
                        msg += HIW "┃暂时空缺。 \n" NOR;
                        continue;
                }
                msg += sprintf(HIW "┃" HIG "  %-5s %-22s%-10s %5d  " HIW "┃\n" NOR,
                        chinese_number(i + 1),
                        list[i]->query("name") + "(" +
                        capitalize(list[i]->query("id")) + ")",
                        list[i]->query("family") ?
                        list[i]->query("family/family_name") : "一介平民",
                        get_score(list[i]));
        }
        msg += HIW "┗━━━━━━━━━━━━━━━━━━━━━━━━┛\n" NOR;
        msg += HIG + NATURE_D->game_time() + "记。\n" NOR;
        msg += WHT "英雄壁下面有一行小字刻着：" + me->query("name") + "，目前评价：" +
               get_score(me) + "。\n\n" NOR;

        write(msg);
        me->set_temp("last_view", time());
        return 1;

}

int top_list(object ob1, object ob2)
{
        int score1, score2;

        score1 = get_score(ob1);
        score2 = get_score(ob2);

        return score2 - score1;
}

int get_score(object ob)
{
        int i, score;

        reset_eval_cost();

        score = ob->query("balance") / 10000;
        return score;
}
