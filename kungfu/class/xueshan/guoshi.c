// /kungfu/class/xueshan/guoshi.c  贡唐仓国师
// by secret
// Update by haiyan

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "xueshan.h"

string ask_for_join();

void create()
{
        set_name("贡唐仓国师", ({ "gongtangcang guoshi", "guoshi" }));
        set("long",@LONG
贡唐仓国师是雪山寺中地位较高的喇嘛。
身穿一件青色袈裟，头戴僧帽。
LONG
        );
        set("title", HIY "大喇嘛" NOR);
        set("nickname", HIG "国师" NOR);
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 24);
        set("int", 28);
        set("con", 26);
        set("dex", 25);

        set("max_qi", 1500);
        set("max_jing", 500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 20);
        set("combat_exp", 120000);

        //密宗可以学习
        set_skill("literate", 120); 
        set_skill("force", 100);
        set_skill("necromancy", 100);
        set_skill("mizong-neigong", 100);
        set_skill("dodge", 100);
        set_skill("shenkong-xing", 80);
        set_skill("parry", 70);
        set_skill("staff", 80);
        set_skill("xiangmo-chu", 80 );
        set_skill("sword",50);
        set_skill("mingwang-jian",40);
        set_skill("cuff", 90);
        set_skill("yujiamu-quan", 80);
        set_skill("hand", 90);
        set_skill("dashou-yin", 90);

        //其它可以学习
        set_skill("lamaism", 200);
        set_skill("sanscrit", 200);
        set_skill("buddhism", 200); 

        map_skill("force", "mizong-neigong");
        map_skill("dodge", "shenkong-xing");
        map_skill("cuff", "yujiamu-quan");
        map_skill("parry", "xiangmo-chu");
        map_skill("staff", "xiangmo-chu");
        map_skill("sword", "mingwang-jian");

        prepare_skill("cuff", "yujiamu-quan");
        prepare_skill("hand", "dashou-yin");

        create_family("雪山寺", 4, "大喇嘛");
        set("class", "bonze");

        set("inquiry",([
                "剃度"  : (: ask_for_join :),
                "出家"  : (: ask_for_join :),
                "知识" :       "我只能传授你 密宗心法(lamaism)、禅宗心法(buddhism)和梵文 (sanscrit)，其\n它的找你的师父学习吧。\n", 
                "传授" :       "我只能传授你 密宗心法(lamaism)、禅宗心法(buddhism)和梵文 (sanscrit)，其\n它的找你的师父学习吧。\n", 
                "技能" :       "我只能传授你 密宗心法(lamaism)、禅宗心法(buddhism)和梵文 (sanscrit)，其\n它的找你的师父学习吧。\n", 
        ]));

        setup();

        carry_object("/d/shaolin/obj/chanzhang")->wield();
        carry_object("/d/xueshan/obj/c-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",100);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;
 
        if ((string)ob->query("gender") != "男性")
        {
                command("say 修习密宗内功需要纯阳之体。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "还是请回吧！");
                return;
        }

        if ((string)ob->query("class") != "bonze")
        {
                command("say 我佛门的清规戒律甚多。");
                ob->set_temp("pending/join_bonze", 1);
                command("say 施主若真心皈依我佛，请跪下(kneel)受戒。\n");
                return;
        }

        if ((string)ob->query("family/family_name") != "雪山寺"
                && ob->query("family/family_name") != "血刀门")
        {
                command("say 这位" + RANK_D->query_respect(ob) +
                        "既非我密宗弟子，还是请回吧！");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 40)
        {
                command("say 入我雪山寺，修习密宗心法是首要的。");
                command("say 这位" + RANK_D->query_respect(ob) +
                        "是否还应该多多钻研本门的心法？");
                return;
        }

        command("say 好，就传你一些武功吧！");
        command("recruit " + ob->query("id"));

        ob->set("title",HIY "喇嘛" NOR);
}

void init()
{
        add_action("do_kneel", "kneel");
        add_action("do_say", "say");
}

string ask_for_join()
{
        object me;

        me = this_player();

        if( (string)me->query("class")=="bonze" )
                return "阿弥陀佛！ 你已经是出家人了，何故跟贫僧开这等玩笑？\n";

        if( (string)me->query("gender") != "男性" )
                return "施主若真心向佛，真是可喜可贺，可惜本寺只收男徒。\n";

        me->set_temp("pending/join_bonze", 1);

        return "阿弥陀佛！善哉！善哉！施主若真心皈依"
               "我佛，请跪下(kneel)受戒。\n";
}

int do_kneel()
{
        object me = this_player();

        if (! me->query_temp("pending/join_bonze"))
                return 0;

        message_vision("$N双手合十，恭恭敬敬地跪了下来。\n\n"
                       "$n伸出手掌，在$N头顶轻轻地摩挲了几下，将"
                       "$N的头发尽数剃去。\n\n", me, this_object());

        me->set("class", "bonze");
        me->set("title",HIY "喇嘛" NOR);      

        command("smile");
        command("say 好，就传你一些武功吧！");
        command("recruit " + me->query("id"));

        return 1;
}

int do_say(string arg)
{

        object me = this_player();

        if (! arg || arg == "") return 0;

        if (arg == "法轮常转")
        {
                me->move("/d/xueshan/guangchang");
                return 1;
        }
}

int recognize_apprentice(object me, string skill)
{
        if (me->query("shen") > 0)
        {
                command("say 老衲与施主并非同道中人，施主还是快请离开吧，免遭无谓之灾！");
                return -1;
        }

        if (skill != "lamaism" && skill != "sanscrit" && skill != "buddhism")
        {
                command("say 这些还是向你的师父学吧，我能传授一些知识给你。");
                return -1;
        }
        return 1;
}

