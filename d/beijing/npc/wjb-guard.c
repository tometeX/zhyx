
inherit NPC; 

#include <ansi.h> 

int ask_wjb(object me, object ob); 
void create() 
{ 
     set_name("守卫",({"shou wei","guard"}) ); 
     set("long","这是一位的无极帮的守卫。\n"); 
     set("title","无极帮帮众"); 
     set("gender","男性"); 
     set("age",20); 
     set("combat_exp",100000); 
     set_skill("dodge",150); 
     set_skill("force",150); 
     set_skill("literate",150); 
     set_skill("unarmed",150); 
     set("inquiry",([ 
          "无极帮" : (: ask_wjb :), 
     ]) ); 
     setup(); 
} 

int ask_wjb(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     if (me->query("bang_good/name")!="无极帮" && (int)me->query("shen") >= 0 ) 
     { 
           command("famours " + me->query("id")); 
           tell_object(me,"守卫笑眯眯地对你说：“是想加入咱们无极帮吧？请进请进。”\n"); 
           me->set_temp("good_wjb2",1); 
           return 1; 
     } 
     if( me->query("bang_bad") || (int)me->query("shen") < 0 ) 
     { 
           ob->command("say 哪里来的邪魔歪道，找打么？\n"); 
           return 1; 
     } 

     tell_object(me,"守卫奇怪道：“同为本帮兄弟，你何出此言啊？”\n"); 
     return 1; 
} 

