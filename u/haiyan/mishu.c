// mishu.c 

inherit NPC;
inherit F_GUARDER;
#include <ansi.h> 

void create()
{
        set_name("芳芳", ({ "fang fang", "fang" }));
        set("title", HIY "海燕的女秘书" NOR);
        set("long", "芳芳是海燕的小秘。\n");
        set("gender", "女性");
        set("age", 20);
        set("shen_type", 1);
        set("str", 18);
        set("int", 30);
        set("con", 25);
        set("dex", 20);
        set("per", 40);
        
        set("max_qi", 500);
        set("max_jing", 200);
        set("neili", 100);
        set("max_neili", 100);
        set("combat_exp", 2000);
        set("score", 200);

        set_skill("force", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);
        set_skill("unarmed", 20);

        set("chat_chance", 2);
        set("chat_msg", ({
              "芳芳端来一杯热气腾腾的咖啡，抿嘴笑道：“累了吧？喝杯咖啡吧！”\n",
              "芳芳轻轻地捶着海燕的背：“不要太辛苦喔！早点睡吧。”\n",
              "芳芳拿来一只烤鸡腿：“不要老吃方便面，啃只鸡腿吧。”\n",
        })); 

        set("inquiry", ([ 
          "海燕":"他是我的……嘻嘻，你问这干嘛？",
          "haiyan":"他是我的……嘻嘻，你问这干嘛？",
          "name":"我叫芳芳，是海燕的小秘，你看我的身材好吗？",
        ])); 

        setup();
        carry_object(__DIR__"bijini")->wear(); 
}


void relay_emote(object ob, string verb) 
{ 
     ob = this_player();
     switch(verb) 
     { 
         case "kiss": 
              command("shy"); 
              break; 
         case "love":
              command("protect1"); 
              break; 
         case "love1": 
              command("pei " + ob->query("id")); 
              break; 
         case "love2": 
              command("noway"); 
              break; 
         case "love3": 
              command("hammer " + ob->query("id")); 
              break; 
         case "fang": 
              command("kick2 " + ob->query("id")); 
              break; 
         case "chaxie": 
              ob->set_temp("desk_open",1);
              command("xixi " + ob->query("id")); 
              break; 
         default:
              command(verb + " " + ob->query("id")); 
              break; 
     }
}

void init() 
{ 
     object ob = this_player();
     ::init();
     if (wizardp(ob))
     {
        if ((string)ob->query("id") != "haiyan") 
        {
           message_vision("芳芳对$N说道：“欢迎$N来海燕家做客。有什么需要尽管吩咐。”\n",ob);
           return;
        }
        else
        {
           message_vision("芳芳对$N说道：“您回来啦！累了吧！先洗个澡，我给您按摩按摩！”\n",ob);
           return;
        } 
     }
     else
     {
        message_vision("芳芳杏目圆睁，对$N大怒道：“哪里来的丑八怪，竟敢闯到这里！\n",ob);
//        ob->move("/d/city/wumiao");
        return;
     }
}

