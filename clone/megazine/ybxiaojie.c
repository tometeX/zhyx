#include <ansi.h>
inherit NPC;
inherit F_DEALER;

void create()
{
	set_name(HIG "〖地狱〗杂志派送小姐" NOR, ({ "xiaojie"}) );
	set("female", "女性" );
	set("age", 21);
	set("long",
		"这是一位的美丽派送小姐，她正在派送〖地狱〗杂志,你可以向她索要(yao zazhi)。\n");
	set("combat_exp", 100);
	set("attitude", "friendly");
	set("rank_info/respect", "小姐");
       	set("inquiry", ([ 
		"zazhi": "这是我们提供给玩家的〖地狱〗杂志。\n",
		"mulu": "这是我们提供给玩家的〖地狱〗杂志。\n",
		"地狱杂志": "没看过的人一定是大傻瓜。\n"
	]) );
       	set("chat_chance", 15); 
       	set("chat_msg", ({
		"派送小姐说道：我们的〖地狱〗杂志就是好，才推出就得到了大家的认可。\n"
		"派送小姐对你说道：你没看过〖地狱〗杂志吗？那就太可惜了! \n",
		"派送小姐把手上的〖地狱〗杂志整理了一下。\n",
	}) );
	carry_object("/clone/cloth/female5-cloth")->wear();
       	setup ();
}

