
#include <ansi.h>

inherit NPC;
inherit F_DEALER;

int ask_tiaozhan();

void create()

{
    set_name(HIG"狼神"NOR, ({"dgdg_boss"}));
    set("title", HIR"［"HIW"神农守护者"HIR"］"NOR);
    set("gender", "男性");
        set("str", 35);
        set("int", 13);
        set("con", 34);
        set("dex", 32);
        set("per", 40);

    set("vendor_goods", ({         
                "/u/dgdg/fuben/obj/tongxingzheng", 
        }));
    set("max_qi", 2000000);
        set("max_jing", 2000000);
        set("neili", 2000000);
        set("max_neili", 2000000);
        set("jiali", 1500);

        set("combat_exp", 2000000000);
        set_skill("unarmed", 2000);
        set_skill("sword", 2000);
        set_skill("claw", 2000);
        set_skill("strike", 2000);
        set_skill("hand", 2000);
        set_skill("cuff", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
        set_skill("force", 2000);
        set_skill("yunv-xinjing", 2000);
        set_skill("zhuangzi-wu", 2000);
        set_skill("suxin-jian", 2000);
        set_skill("lonely-sword", 2000);
        set_skill("qiankun-danuoyi", 2000);
        set_skill("yinyang-shiertian", 2000);
        set_skill("martial-cognize", 2000);
        set_skill("zuoyou-hubo", 400);

        map_skill("parry", "qiankun-danuoyi");
        map_skill("force", "yunv-xinjing");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("unarmed", "yinyang-shiertian");
        map_skill("sword", "lonely-sword");
        map_skill("strike", "liuyang-zhang");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("unarmed", "yinyang-shiertian");   
        
        set("inquiry", ([     
					"挑战神农" : (: ask_tiaozhan :),
                ]));      
        
        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
	        (: command("perform sword.luo") :),
	        (: command("perform sword.liao") :),	
	        (: command("perform unarmed.tian") :),       
	        (: exert_function, "recover" :),
	        (: exert_function, "powerup" :),	       
        }));
        
        set_temp("apply/attack", 5000);
        set_temp("apply/defense", 3000);
        set_temp("apply/damage", 5000);
        set_temp("apply/unarmed_damage", 3000);
        set_temp("apply/armor", 3000);

  
    setup();
   
    carry_object("/clone/weapon/green_sword")->wield();
   
}


void init()
{
     object me;
     ::init();

        add_action("do_list", "list");
        add_action("do_buy", "buy");
        
        if( interactive(me = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }

}



int ask_tiaozhan()
{
	  int n;
    object me;
    object *inv;
    object room;
    me = this_player();
   
    inv = deep_inventory(me);
    command("look " + me->query("id"));
 
           for (n = 0; n < sizeof(inv); n++)
        {
                if (! playerp(inv[n])) continue;
                else
                {
                	command("say 你背的是谁？还不快快放下！");
                  return 1;
                }
        }

	if (living(this_object()) && present("tongxing zheng", me))
	{
		room = find_object("/u/dgdg/fuben/room/sncave");
	        if (! room) room = load_object("/u/dgdg/fuben/room/sncave");
	        me->move(room);
                command("chat 又一位探险者进入了神农洞!");
	} else
	{
                command("grin");
                command("say 你得有通行证才能进得去，我给你会员价，卖一个给你如何？");
	}	

    return 1;
}


     varargs int receive_damage(string type, int n, object who) 
     { 
             if (! objectp(who) || ! interactive(who) || who == this_object()) 
                     return 0; 
      
             tell_object(who, HIR "你发现" + name() + 
                         HIR "诡秘一笑，忽然觉得一阵心悸，神智一阵恍惚。\n" NOR); 
             return who->receive_damage(type, n, this_object()); 
     } 
      
     varargs int receive_wound(string type, int n, object who) 
     { 
             if (! objectp(who) || ! interactive(who) || who == this_object()) 
                     return 0; 
      
             tell_object(who, RED "你忽见" + name() + 
                         RED "桀桀怪笑，只觉得浑身都是一痛，直入骨髓深处。\n" NOR); 
             return who->receive_wound(type, n, this_object()); 
     } 