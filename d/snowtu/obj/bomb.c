#include <ansi.h>
#include <combat.h>
inherit ITEM;

void setup(){ }

void create()
{
set_name(HIR"鞭炮"NOR,({"bian pao","pao zhu","pao"}));
set_weight(5000);
if( clonep() )
        set_default_object(__FILE__);
else    {
        set("unit", "个");
        set("long", HIR"过年时常点的爆竹，点(dian)着后要记得丢(diu)出去哦。\n"NOR);
        set("material", "paper");
        set("value",1000);
        }
setup();
}

int init()
{
//add_action("do_dian", "dian");
//add_action("do_drop", "diu");
}

int do_dian(string arg)
{
object ob = this_object();
object me = environment(ob);
if ( !arg || !id(arg) )
        return notify_fail("你要点什么？\n");
if ( ob->query("burn") )
        return notify_fail("已经点着了！"HIR"噼里啪啦 =^-^=\n"NOR);
if ( me->is_busy() )
        return notify_fail("你正忙着呢。\n");

message_vision("$N贼兮兮的掏出个$n，拿火引点着了...\n"NOR,me,ob);
me->start_busy(1);
ob->set("burn",1);
ob->set("num",1+random(6));
ob->save();
call_out("check",1,ob);
return 1;
}

int do_drop(string arg)
{
object ob = this_object();
object me = environment(ob);
if ( !arg || !id(arg) )
        return notify_fail("你要丢什么？\n");
if ( me->is_busy() )
        return notify_fail("你正忙着呢。\n");
if (ob->query("burn") == 1)
{
message_vision("$N拿着$n战战兢兢的，不由将$n丢了出去...\n"NOR,me,ob);
me->start_busy(1);
ob->move(environment(me));
call_out("dismiss",60,ob);
return 1;
}
else {
return notify_fail("没点干吗要扔啊！\n");
}
}

void dismiss(object ob)
{
if ( !ob ) return;
if ( living(environment(ob)) ) return;
message("vision","一个捡垃圾的过来，见到"+ob->name()+"不由喜不自禁，将它拣走了....\n",environment(ob),ob);
destruct(ob);
return;
}

void check(object ob)
{
int num;
string msg;
object who = environment(ob);
if ( !ob || !who )
        return;
message("vision",YEL+ob->name()+YEL"的火药线哧哧直响....\n"NOR,who,ob);
ob->add("num",-1);
ob->save();
if ( num=ob->query("num")<=0 )
        {
        msg = YEL"“轰”的一声，"+ob->name()+YEL"炸开来了，在半空中绽出五颜六色。\n\n
               |
           \   *  ./
          .  * * * .
         -=*  POP! *=-              
         .  .* * *  .
          /    *  .\
               |  
               .     

　　　/\~~~~~~~~~~~~~\　　　▓　　^*^　　　☆　　$$　 .☆ 
　　./　\~~~▓~　 ~~~~\ ◆　　圣诞 .快乐　 *　 $◢◣$　 * 
　　/ ^^ \ ══════\.◆　　　 *　*　　*　 $◢★◣$　 * 
　..▎[]　▎田　田 ▎ |┃◆　 .　　　　　*　 $◢■■◣$　 * 
　&&▎　　▎　　　 ▎'|'▎ @　　　　　　　* $◢■■■◣$ * 
＃ ■■■■■■■■■■〓▄▃▂▁愿你圣诞快乐︸︸||︸︸ \n"NOR;
        msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL);
        msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL);
        msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL);
        msg = replace_string(msg,"圣",NOR HIY"圣"NOR YEL);
        msg = replace_string(msg,"诞",NOR HIY"诞"NOR YEL);
        msg = replace_string(msg,"快",NOR HIY"快"NOR YEL);
        msg = replace_string(msg,"乐",NOR HIY"乐"NOR YEL);
        msg = replace_string(msg,"◣",NOR HIG"◣"NOR YEL);
        msg = replace_string(msg,"■",NOR HIG"■"NOR YEL);
        msg = replace_string(msg,"★",NOR HIR"★"NOR YEL);
        msg = replace_string(msg,"◢",NOR HIG"◢"NOR YEL);
        msg = replace_string(msg,"◆",NOR HIR"◆"NOR YEL);
        msg = replace_string(msg,"☆",NOR BLINK HIY"☆"NOR YEL);
        msg = replace_string(msg,"HIG",HIG);
        msg = replace_string(msg,"HIC",HIC);
        msg = replace_string(msg,"HIY",HIY);
        message("vision",msg,environment(ob),ob);
        if ( living(environment(ob)) )
                {
                message("vision",HIR"爆竹在手中炸开，"+environment(ob)->name()+"哪里躲得了，给炸了个正着！\n"NOR,environment(ob),ob);
                num = 40+random(100);
                }
        destruct(ob);
        }
else    {
        remove_call_out("check");
        call_out("check",1,ob);
        }
return;
}


