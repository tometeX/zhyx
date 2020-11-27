// smith.c

#include <ansi.h>

inherit "/inherit/char/b_npc.c";    

mixed ask_back();

void create()
{
        set_name("铁老板", ({ "tie boss", "tie", "boss" }));
         set("title", "铁匠铺后台老板");
	 set("shen_type", 1);

        set("gender", "男性" );
        set("age", 33);
        set("long", "他就是铁匠铺的真正老板。\n");

        set("combat_exp", 400);
	 set("attitude", "friendly");
        set("vendor_goods",({
                "/clone/weapon/changjian",
                "/clone/weapon/hammer",
                "/clone/weapon/tudao",
		  "/clone/weapon/dagger",
                "/clone/weapon/tiegun",
                "/clone/weapon/changbian",
                "/clone/weapon/gangdao",
                "/clone/cloth/tiejia",
                "/d/item/obj/jingtie",
                "/clone/weapon/arrow",
                "/clone/weapon/wolfarrow",
                "/clone/weapon/bow",
                "/clone/weapon/longbow",
                "/clone/weapon/qimeigun",
        }));

        set("inquiry", ([
//                "工作" : (: ask_me :),
//                "job"  : (: ask_me :),
//                "血海无边" : (: ask_back :),
        ]));

	setup();

	carry_object("/clone/misc/cloth")->wear();
}






