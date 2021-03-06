#include <ansi.h>

inherit NPC;

void create()
{
        object ob;
        set_name("何太冲", ({"he taichong", "he", "taichong"}));
        set("long", @LONG
他就是名扬江湖的昆仑派第四代掌门铁琴先生
何太冲。虽然此时他年纪已大，但仍然看得出
他年轻时的英俊潇洒。
LONG);
        set("nickname", WHT "铁琴先生" NOR);
        set("gender", "男性");
        set("age", 43);
        set("attitude", "heroism");
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 150);
        set("combat_exp", 1600000);

        set_skill("force", 220);
        set_skill("kunlun-xinfa", 200);
        set_skill("liangyi-shengong", 220);
        set_skill("dodge", 200);
        set_skill("chuanyun-bu", 200);
        set_skill("hand", 200);
        set_skill("sanyin-shou", 200);
        set_skill("cuff", 200);
        set_skill("zhentian-quan", 200);
        set_skill("parry", 200);
        set_skill("sword", 220);
        set_skill("kunlun-jian", 220);
        set_skill("xunlei-jian", 220);
        set_skill("zhengliangyi-jian", 220);
        set_skill("throwing", 200);
        set_skill("kunlun-qifa", 200);
        set_skill("tanqin-jifa", 240);
        set_skill("tieqin-yin", 240);
        set_skill("literate", 220);
        set_skill("martial-cognize", 200);

        map_skill("force", "liangyi-shengong");
        map_skill("dodge", "chuanyun-bu");
        map_skill("parry", "zhengliangyi-jian");
        map_skill("sword", "kunlun-jian");
        map_skill("cuff", "zhentian-quan");
        map_skill("hand", "sanyin-shou");
        map_skill("throwing", "kunlun-qifa");
        map_skill("tanqin-jifa", "tieqin-yin");

        prepare_skill("strike", "kunlun-zhang");
        prepare_skill("cuff", "zhentian-quan");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.fanyin" :),
                (: perform_action, "throwing.liu" :),
                (: perform_action, "cuff.shi" :),
                (: perform_action, "hand.sun" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        setup();

        carry_object("clone/misc/cloth")->wear();
}

void init()
{       
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("killing");
                call_out("killing", 1, ob);
        }
}

void killing(object ob)
{       
        object me;
        object obj=this_object();

        me = this_player();
        if (! ob || environment(ob) != environment())
                return;
                switch(random(2))
        {
        case 0:
//                say(CYN "玄慈大喝道：你这魔教爪牙，还不速来受死！\n" NOR);    
        set("anti",me);
                me->kill_ob(obj);
                  kill_ob(me);
                break;
        case 1:
 //               say(CYN "玄慈大叹：哎，又一个送死的来了！\n" NOR);
                set("anti",me);
                  kill_ob(me);
                me->kill_ob(obj);
                break;
        }
}


void killed_enemy()
{
        if (objectp(query("anti")))
        {
                shout(HIR "\n【光明顶之战】" HIW "何太冲：哎！" HIC + query("anti")->name() + HIW "维护魔教，不自量力，白白送了性命！\n" NOR );

        }
}


void die()
{
        if (objectp(query("anti")))
        {
        query("anti")->set_temp("skybook/tulong/guangmingding/kunlun",1);
  
   message_vision(HIY "\n何太冲大叹一声：罢了罢了！随之带领门下弟子鱼贯离去！\n" NOR,
                                   this_object(),query("anti"));
if ( query("anti")->query_temp("skybook/tulong/guangmingding/shaolin") > 0  
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/emei") > 0
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/chengkun") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/kunlun") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/huashan") > 0 
        &&  query("anti")->query_temp("skybook/tulong/guangmingding/wudang") > 0  )
      {      
                shout(HIR "\n【光明顶之战】" HIW "明教弟子：" HIC + query("anti")->name() + HIW "在光明顶技压群雄，独力击退六大门派，救明教万千弟子于危难之中！\n" NOR );
                query("anti")->delete_temp("skybook/tulong/guangmingding");
                     query("anti")->set("skybook/tulong/winguangming",1); 
                        query("anti")->move(__DIR__"to_ding");

        }
                 destruct(this_object());
        }

::die();
}



