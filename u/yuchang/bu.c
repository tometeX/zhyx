#include <ansi.h>
inherit NPC;
void consider();
void create()
{
    set_name("步惊云", ({"bu jingyun", "bu", "jingyun"}));
    set("nickname", HIY "不哭死神" NOR );
    set("gender", "男性");
    set("age", 25);
    set("long", 
        "他就是天下会云堂堂主步经云，江湖上人称「不哭死神」。\n");
    set("attitude", "peaceful");
    
    set("str", 100);
    set("int", 80);
    set("con", 86);
    set("dex", 240);
    set("chat_chance", 1);
    set("chat_msg", ({
        "步经云叹了口气道：“唉 …… 我的令牌哪里去了 ……”\n",
        "步经云低头沉思，悠然不语。\n",
    }));
    set("inquiry", ([
        "令牌"     : "谁能帮我找到令牌，我什么事都答应他! \n",
        "绝世好剑" : "嘿嘿，当今天下只有我知道这个秘密。\n",
    ]));
    set("qi", 20000);
   set("max_qi", 20000);
    set("jing", 5000);
    set("max_jing", 5000);
    set("max_jingli", 3000);

    set("jingli", 3000);
    set("neili", 6000);
    set("max_neili", 20000);
    set("jiali", 300);
    
     set("combat_exp", 60000000);
     
  set_skill("force", 900);
    set_skill("bibo-shengong", 890);
     set_skill("tanzhi-shentong", 900);
   set_skill("unarmed", 1000);
    set_skill("luoying-shenzhang", 860);
     set_skill("dodge", 1100);
    set_skill("anying-fuxiang", 800);
    set_skill("parry", 900);
   set_skill("sword", 900);
    set_skill("qimen-wuxing",800);
    set_skill("literate",550);           // 读书识字
     set_skill("literate",1100);
    map_skill("force"  , "bibo-shengong");
    map_skill("unarmed", "tanzhi-shentong");
    map_skill("dodge"  , "anying-fuxiang");
    map_skill("parry"  , "luoying-shenzhang");
    
    create_family("天下会", 1, "堂主");


	setup();
    
    carry_object("/d/taohua/obj/bupao")->wear();

    
}

int accept_object(object who, object ob)
{
    
    if ( (string) ob->query("id") =="ling pai" ) {
        if (!(int)who->query_temp("tmark/ling")) who->set_temp("tmark/ling", 0);
        message_vision("步经云看了看$N送来的令牌，点了点头，说道：\n"
                               "难得你将令牌送回。你送我的东西我就收下了。\n"
                               "作为补偿,我可以告诉你点秘密。\n", who);
        who->set("tmark/ling", 1);
        return 1;
    }
    return 0;
}
