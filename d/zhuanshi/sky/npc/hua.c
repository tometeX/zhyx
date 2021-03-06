#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("华英雄", ({ "hua yingxiong", "hua", "yingxiong"}));
        set("long", "一个俊俏的中年男子，衣着长衫，他就是华英雄。\n"
                    "传说他命犯天煞孤星，一生漂泊，落于异地。尔后\n"
                    "习得一身绝技，兼修炼「中华傲决」，大败「东洋\n"
                    "战神」无敌。\n"); 
        set("nickname", HIW "中华英雄" NOR);
        set("title", HIY "大宗师" NOR);
        set("gender", "男性");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 120);
        set("int", 120);
        set("con", 120);
        set("dex", 120);
        set("per", 120);

        set("max_qi", 55000);
        set("max_jing", 20000);
        set("max_neili", 65000);
        set("neili", 65000);
        set("jiali", 200);
        set("combat_exp", 80000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: perform_action, "sword.aoqi" :),
                (: perform_action, "sword.jianqi" :),
				(: perform_action, "strike.zhangzhen" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

		
        set_skill("dodge", 700);
        set_skill("strike", 700);
        set_skill("parry", 700);
        set_skill("unarmed", 700);
        set_skill("force", 700);
        set_skill("sword", 800);
        set_skill("siji-jianfa", 700);
        set_skill("china-aojue", 800);
        set_skill("idle-force", 700);
        set_skill("literate", 200);

        map_skill("force", "china-aojue");
        map_skill("sword", "china-aojue");
        map_skill("dodge", "china-aojue");
        map_skill("parry", "china-aojue");
        map_skill("strike", "china-aojue");
        map_skill("unarmed", "china-aojue");
		
	    set_temp("apply/damage", 350);
		set_temp("apply/unarmed_damage", 350);
        set_temp("apply/armor", 300);
        set("apply/dodge", 400); 

        prepare_skill("strike", "china-aojue");       

        setup();

        carry_object(__DIR__"obj/cloth3")->wear();
        carry_object(__DIR__"obj/chijian")->wield();        
}


void greeting(object ob)
{
     object me;
     me=this_player();
     if (!ob || !present(ob, environment())) return;
     command("look " + me->query("id"));
     command("say 打赢我才能上去！");     
     return ;
}


int accept_fight(object ob)
{
        if (is_fighting())
        {
                message_vision(CYN "$N" CYN "对$n" CYN "叫道：你先别急"
                               "，我打完这架就来领教你的。\n" NOR,
                               this_object(), ob);
                return -1;
        }       

        if (query("qi") < 20000 ||
            query("jing") < 5000 ||
            query("neili") < 25000)
        {
                message_vision(CYN "$N" CYN "摇摇头对$n" CYN "道：我现"
                               "在太累了，待我歇会儿再说吧。\n" NOR,
                               this_object(), ob);
                return -1;
        }
  

        message_vision(HIW "$N" HIW "大喜道：好好好！我正手痒痒，咱们"
                       "来比划比划！\n" NOR, this_object(), ob);

        competition_with(ob);
        return -1;
}


void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(CYN "$N" CYN "看了看$n" CYN "，嘿嘿笑道：你的水"
                       "平太菜了，要好好练功，好好练功。\n" NOR,
                       this_object(), ob);
        ::win();
}


void lost()
{
	object *inv;
	int n;
	object ob,room;
         if (! objectp(ob = query_competitor()))
                return; 

	inv = deep_inventory(ob);

	for (n = 0; n < sizeof(inv); n++)
        {
                if (! playerp(inv[n])) continue;
                else
                {
                	command("say 你背的是谁？还不快快放下！");
                  return;
                }
        }
	if (living(this_object()) && present("zhuanshi tongzhi", ob))
	{
		command("gongxi " + ob->query("id"));
		room = find_object("/d/zhuanshi/sky/sky4");
		if (! room) room = load_object("/d/zhuanshi/sky/sky4");
		ob->move(room);	
        }else	command("say 你把转世通知书弄丢了？赶快去找回来！");

        ::lost();
}

void unconcious()
{
        say( HIC"华英雄说道：“想搞我没那么容易。”说完就从怀里拿出一颗天王保命丸塞进嘴里嚼了起来。\n"NOR);
        say( HIC"片刻之间，华英雄又恢复了精神，“嘿嘿”奸笑了两声。\n"NOR);
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
	remove_all_enemy(1);
	lost();
}
void die()
{
        unconcious();
}


