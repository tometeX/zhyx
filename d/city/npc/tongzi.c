inherit NPC;
string ask_me();
void create()
{
        set_name("天下无敌忠仆", ({ "pu ren", "pu", "ren" }));
        set("gender", "男性");
        set("age", 25);
        set("long", "一个神秘的汉子，在天下无敌日子久了，看起来很开心。\n");
         set("shen_type", 2);
        set_skill("dodge", 70);
    set("combat_exp", 100000000);
            set_skill("unarmed", 1000);
            set("force", 10000);
            set("max_qi", 1000000);
            set("qi", 1000000);
        set("jiali", 1500);   
       set("attitude","friendly");
      set("inquiry", ([
                "红包" : (: ask_me :),
                "hongbao" : (: ask_me :),
                "liwu" : (: ask_me :),
                "礼物" : (: ask_me :),
        ]) );
        set("chat_msg", ({
             "天下无敌忠仆说道："+WHT+"欢迎大家来到天下无敌。\n"NOR, 
             "欢迎来到我们的游戏。",
             "想要礼物吗？请问问我关于<liwu>的问题！",
             "希望你能成为一代天骄！",
        }) );
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
    setup();
}
string ask_me()
{
        object ob;
        if ( (int)this_player()->query("hongbao_over") == 22 )
                return RANK_D->query_respect(this_player()) + 
                "不是给你红包了吗?想乱占便宜呀！";
        if ( (int)this_player()->query("hongbao_over") == 1 )
                return RANK_D->query_respect(this_player()) + 
                "你不是已经开过红包了吗?想乱占便宜呀！";
        ob = new("/u/xgchen/hb.c");
        ob->move(this_player());
        this_player()->set("hongbao_over",22);
            message_vision("$N获得一个沉甸甸的红包。\n",this_player());

        return "希望你努力成为一代大侠。。。。";
}
