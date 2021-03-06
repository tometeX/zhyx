
//擂台npc3

#include <ansi.h> 
inherit  __DIR__"leitai_npc";
void do_disappear();
void create()
{           
       set("level", 3);        
       set("name", "段皇爷");
       set("id", "duan huangye");       
    
    	set("long", @LONG
一灯大师乃江湖中人称“东邪西毒，南帝北丐”中
的南帝段皇爷，当年凭着段氏“一阳指”而独步武
林，罕逢敌手。但却在中年时因一段悲情而出家为
僧，之后大彻大悟，成为一位得道高僧。
LONG );
    	set("title", "大理国退位皇帝");
    	set("nickname", HIY "南帝" NOR);
    	set("gender", "男性");
    	set("age", 71);
	set("shen_type", 1);
    	set("attitude", "friendly");

    	set("str", 50);
    	set("int", 50);
    	set("con", 50);
    	set("dex", 50);

    	set("qi", 15000);
    	set("max_qi", 15000);
    	set("jing", 6000);
    	set("max_jing", 6000);
    	set("neili", 20000);
    	set("max_neili", 20000);
    	set("jiali", 400);
    	set("combat_exp", 7000000);
    	set("score", 500000);

        set_skill("force", 400);
        set_skill("xiantian-gong", 400);
        set_skill("duanshi-xinfa", 400);
        set_skill("kurong-changong", 400);
        set_skill("dodge", 400);
        set_skill("tiannan-bu", 400);
        set_skill("cuff", 400);
        set_skill("jinyu-quan", 400);
        set_skill("strike", 400);
        set_skill("wuluo-zhang", 400);
        set_skill("sword", 400);
        set_skill("staff", 400);
        set_skill("duanjia-jian", 400);
        set_skill("finger", 400);
        set_skill("qiantian-zhi", 400);
        set_skill("yiyang-zhi", 400);
        set_skill("parry", 400);
        set_skill("jingluo-xue", 400);
        set_skill("buddhism", 400);
        set_skill("literate", 400);
        set_skill("sanscrit", 400);
        set_skill("martial-cognize", 400);

        map_skill("force", "xiantian-gong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "yiyang-zhi");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("parry", "yiyang-zhi");
        map_skill("sword", "duanjia-jian");
        map_skill("staff", "yiyang-zhi");

        prepare_skill("finger", "yiyang-zhi");

        create_family("段氏皇族", 11, "传人");
     
        // npc的pfm
        set("pfm", ({
             "finger.jian", 
             "finger.qian",
             "finger.dian", 
             "finger.die",              
         }));
        //npc的兵器
        set("hand","/d/city/npc/obj/tieshou"); 


       //以下数据不变
        set("chat_chance", 200);
        set("chat_msg", ({ 
                      (: do_disappear :),                       
        }));
        set("chat_chance_combat", 200);
	 set("chat_msg_combat", ({	
           (: pfm : ),
           (: exert_function, "recover" :),       
	  }) );   
        
        restore();
        setup();  
        if (clonep()) keep_heart_beat();         
        carry_object("/d/city/npc/obj/jinsijia")->wear();        
        if ( query("weapon") )
            carry_object(query("weapon"))->wield(); 
        if ( query("hand") )
            carry_object(query("hand"))->wear();       
           
}




