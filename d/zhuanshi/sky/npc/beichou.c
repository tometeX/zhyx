#include <ansi.h>
inherit NPC;

void create()
{
        set_name("北丑", ({ "bei chou", "bei", "chou", "xizi" }) );
        set("nickname", HIW "北戏子" NOR);
        set("title", HIC "武林泰斗" NOR);
        set("gender", "男性" );
        set("age", 68);
        set("long", HIC "这是一个身着戏子打扮的瘦小老头，长得尖\n"
                        "嘴猴腮，天生一副奸相。这便是当今武林中\n"
                        "号称「" HIR "南贤北丑" HIC "」戏子北丑。"
                        "\n" NOR);
        set("attitude", "friendly");
        set("max_jing", 50000);
        set("max_qi", 55000);
        set("max_jingli", 50000);
        set("jingli", 50000);
        set("max_neili", 60000);
        set("neili", 60000);
        set("jiali", 200);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);
        set("combat_exp", 200000000);

        set_skill("dodge", 850);
        set_skill("unarmed", 850);
        set_skill("force", 850);
        set_skill("parry", 850);
        set_skill("sword", 850);
        set_skill("poison", 850);
        set_skill("medical", 850);
        set_skill("hand", 850);
        set_skill("strike", 850);
        set_skill("staff", 850);
        set_skill("finger", 850);
        set_skill("claw", 850);
        set_skill("blade", 850);
        set_skill("pixie-jian", 850);
        set_skill("literate", 850);
//      set_skill("taoism", 850);
	set_skill("count", 90);
        set_skill("buddhism", 850);
        set_skill("jiuyang-shengong", 850);
        set_skill("lingbo-weibu", 850);
        set_skill("qiankun-danuoyi", 850);
        set_skill("xuanming-zhang", 850);
        set_skill("jiuyin-baiguzhao", 850);
        set_skill("dugu-jiujian", 850);
        set_skill("liumai-shenjian", 850);
        set_skill("qianzhu-wandushou", 850);
        set_skill("ranmu-daofa", 850);
        set_skill("dagou-bang", 850);
        set_skill("shaolin-yishu", 850);
        set_skill("wudu-qishu", 850);
        set_skill("throwing", 850);
        set_skill("mantian-xing", 850);
        set_skill("idle-force", 850);

        map_skill("unarmed", "pixie-jian");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "lingbo-weibu");
        map_skill("parry", "qiankun-danuoyi");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("strike", "xuanming-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("finger", "liumai-shenjian");
        map_skill("sword", "dugu-jiujian");
        map_skill("blade", "ranmu-daofa");
        map_skill("staff", "dagou-bang");
        map_skill("throwing", "mantian-xing");
        map_skill("poison", "wudu-qishu");
        map_skill("medical", "shaolin-yishu");
		
	set_temp("apply/damage", 400);
	set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 800);
        set("apply/dodge", 400); 

        prepare_skill("finger", "liumai-shenjian");

        create_family("逍遥派", 0, "武林泰斗");

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({               
                (: perform_action, "parry.nuoyi" :),
                (: perform_action, "dodge.lingbo" :),               
                (: perform_action, "hand.zhugu" :),  
                (: perform_action, "finger.zong" :),               
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),              
        }) );

        setup();
        carry_object("d/city/obj/cloth")->wear();
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

        if (query("qi") < 25000 ||
            query("jing") < 20000 ||
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
		room = find_object("/d/zhuanshi/sky/heaven");
		if (! room) room = load_object("/d/zhuanshi/sky/heaven");
		ob->move(room);	
        }else	command("say 你把转世通知书弄丢了？赶快去找回来！");

        ::lost();
}

void unconcious()
{
        say( HIC"北丑说道：“想搞我没那么容易。”说完就从怀里拿出一颗天王保命丸塞进嘴里嚼了起来。\n"NOR);
        say( HIC"片刻之间，北丑又恢复了精神，“嘿嘿”奸笑了两声。\n"NOR);
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