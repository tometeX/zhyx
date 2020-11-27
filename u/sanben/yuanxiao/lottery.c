
// 一等奖(1个) 奖励 神佑果 一个 (可以给指定id获得特殊属性,成功率100%)
// 二等奖(2个) 奖励 神兵卡一张 (可换取十级兵器一把)
// 三等奖(3个) 奖励 环宇天晶一个 (高级兵器铸造材料)
// 参与奖 (其他所有参加抽奖者均有) 奖励 春节大礼包一个 

#include <ansi.h>

#define FILE_PATH       "/data/lot/lot_machine.o"
#define CARD            __DIR__"lot_card"
#define FIRST_PRIZE     "/u/sanben/obj/shenyou"
#define SECOND_PRIZE    "/u/sanben/obj/weapon_card"
#define THIRD_PRIZE     "/d/death/obj/tianjing"
#define NORMAL_PRIZE    "/u/sanben/spr_gift"
#define MAX_NUM         300
#define TIME            200702


inherit ITEM;

void create()
{
        set_name(HIG "抽奖机" NOR, ({ "lot machine", "lot", "machine"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG 
"     ┏━━━━━━━━━━━━━━━━━━━━━━━━┓\n"+
"     ┃  ┌────────────────────┐  ┃\n"+
"     ┃  │           欢迎参加抽奖活动             │  ┃\n" +
"     ┃  │             插卡口  |===|              │  ┃\n" +
"     ┃  │             (insert card)              │  ┃\n" +
"     ┃  │                                        │  ┃\n" +
"     ┃  │      @            @          @         │  ┃\n" +
"     ┃  │    @ 1 @        @ 2 @      @ 3 @       │  ┃\n" +
"     ┃  │      @            @          @         │  ┃\n" +
"     ┃  │  查询参加者   查询获奖者   领奖        │  ┃\n" +
"     ┃  │          (push 1 or 2 or 3)            │  ┃\n" +
"     ┃  │                                        │  ┃\n" +
"     ┃  └────────────────────┘  ┃\n"+
"     ┗━━━━━━━━━━━━━━━━━━━━━━━━┛\n"NOR);
                set("unit", "台");
                set("value", 10000);
                set("weight", 3000);
                set("material", "wood");
		  set("no_get",1);
		  set("no_drop",1);		  		  
             }	         
        setup();
}

void init()
{
	add_action("do_insert","insert");
	add_action("do_push","push");
	add_action("do_open","open");
	add_action("do_reset","reset");
}
		
int do_insert( string arg )
{   
    int num, i;
    object me, ob, *obj;
    string space;	    
	    
    me = this_player();
    ob = this_object();
    space = "";

    if ( ! arg || ( arg != "card" && arg != "lot card") )
       return notify_fail("您要插入什么？\n");
       
    if (! present("lot card", me))
       return notify_fail("对不起，您没有抽奖卡呀！\n");

    if ( me->query("lot_number/" + TIME))
       return notify_fail("对不起，您已经有一个幸运号码了！\n");	

   // if ( me->query("combat_exp") < 500000 )
   //    return notify_fail("对不起，经验小于五十万的不能参加抽奖！\n");		    
	    
			
    restore_object( FILE_PATH, 1 );

    if (ob->query("open_lot") == 1 )	
	return notify_fail("现在已经开过奖了，不能再参加抽奖了！\n");
				
    if ( ob->query("number") >= MAX_NUM )
       return notify_fail("对不起，抽奖机已经满额了！\n");			

    obj = all_inventory(me);
    for(i=0; i<sizeof(obj); i++) 
    {
	if (base_name(obj[i]) == CARD)
	{
          destruct(obj[i]);
          break;
       }			     
    }	
		
    ob->add("number",1);
    num = ob->query("number");			
    me->set("lot_number/" + TIME, num);	
       	
    ob->set("id_record/" + num, me->query("id"));
    ob->set("name_record/" + num, me->query("name"));

    if ( num < 10 )  space = "       ";    	           
    else 
    if ( num < 100 ) space = "      ";
    else space = "     ";   

   save_object( FILE_PATH,1 );	
			
   message_vision(HIW"$N从怀里拿出一张抽奖卡，插入了机器的插卡孔内。\n"NOR, me);

   tell_object(me, "\n只见抽奖机的屏幕上显示到:\n"+
	     HBRED + HIW"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"+ 
	      "$$                                     $$\n"+
	      "$$" + HIY"  您好，您获得的幸运号码是:"HIG + num + HIY"号" 
                  + space + HIW"$$\n"+
	      "$$                                     $$\n"+
	      "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n"NOR);
   return 1;
}



int do_push( string arg )
{	
       int i;
	object me, ob, prize;		
	string name, space1, space2;
		
	me = this_player();
	ob = this_object();
	name = "";
	space1 = "               ";
	space2 = "     ";

       if ( ! arg || (arg != "1" && arg != "2" && arg != "3") )
       {
          tell_object(me, HIR "请选push 1 或 push 2 或push 3\n" NOR);
          return 1;
       }

	if (! wizardp(me) && time() - me->query_temp("last_push_machine") < 10)
       {
          write("这是瞎三笨做的烂机器，老按会按坏的，还是等会儿吧!\n");
	   return 1;
       }

       me->set_temp("last_push_machine", time());
       
	restore_object(FILE_PATH, 1);

	message_vision(HIW"只听“啪嗒”一声" + "$N按下了第" +
                      chinese_number(atoi(arg)) + "个按钮。\n"NOR, me);
		
	if (arg == "1")	
       {
	   for(i=1; i<sizeof(ob->query("name_record"))+1; i++) 
         {								
		name += ob->query("name_record/"+i) + "(" + 
                      ob->query("id_record/"+i) +
			 ")" + "幸运号码:" + i + "号|"; 
             if ( i%2 == 0 ) name += "\n";			
         }	
		
	  tell_object(me, HIY"目前共有"+ ob->query("number") + 
				"人参加抽奖:\n"HBGRN HIC+ name +"\n"NOR);			
	  return 1;
	}

	if (arg == "2")
	{	

	    if ( ! ob->query("open_lot") )	
	    { 
              write("现在还没开奖呀！\n");
              return 1;
           }		
	
               if  (ob->query("/prize/"+"1") < 10 ) { space1 += " "; }
		 if  (ob->query("/prize/"+"2") > 9 )  { space2 = "    "; }
		 if  (ob->query("/prize/"+"3") < 10 ) { space2 += " "; }

tell_object(me,
HIG 
"     ┏━━━━━━━━━━━━━━━━━━━━━━━━┓\n"+
"     ┃  ┌────────────────────┐  ┃\n"+
"     ┃  │" + MAG"            获奖者名单" + HIG"                  │  ┃\n" +
"     ┃  │              " + HIM HBWHT"一等奖"NOR HIG + "                    │  ┃\n" +
"     ┃  │" + space1 + MAG +     ob->query("/prize/"+"1") +
		 "号"HIG + "                    │  ┃\n" +
"     ┃  │                                        │  ┃\n" +
"     ┃  │              "+ HIY HBWHT"二等奖"NOR HIG +"                    │  ┃\n" +
"     ┃  │           "HIY + ob->query("/prize/"+"2") + "号" + space2 +
			ob->query("/prize/"+"3")+"号    "HIG + "             │  ┃\n" +
"     ┃  │                                        │  ┃\n" +
"     ┃  │              "+ HIB HBWHT"三等奖"NOR HIG +"                    │  ┃\n" +
"     ┃  │      "HIB + ob->query("/prize/"+"4") + "号    " +ob->query("/prize/"+"5")+
	"号    " + ob->query("/prize/"+"6") + "号"HIG +"           │  ┃\n" +
"     ┃  │                                        │  ┃\n" +
"     ┃  │   请获奖者速来领取奖品，三日内有效     │  ┃\n" +
"     ┃  └────────────────────┘  ┃\n"+
"     ┗━━━━━━━━━━━━━━━━━━━━━━━━┛\n"NOR);
		return 1;
			
       }	

	if (arg == "3")
	{				
	   if ( ! ob->query("open_lot") )	
	   { 
             write("现在还没开奖呀！\n");
             return 1;
          }			
			   
	   if( ! me->query("lot_number/" + TIME))
	   {
             write("咦，您没参加抽奖呀！\n");
             return 1;
          }

          message_vision(HIW"抽奖机里掉出一件奖品来。\n" +
				"$N“嗖”的一声就把奖品放进了兜里。\n"NOR, me);

 	   if ( me->query("lot_number/" + TIME ) == ob->query("prize/"+ "1"))
	   { 
             prize = new(FIRST_PRIZE); 
             prize->move(me);
	      write(HIG"恭喜您获得了一等奖，奖励已给您兑现!\n"NOR);	
             me->delete("lot_number/" + TIME);
             return 1;               
          } 

          if ( me->query("lot_number/" + TIME) == ob->query("prize/"+ "2") 
               || me->query("lot_number/" + TIME) == ob->query("prize/"+ "3"))
	   { 
             prize = new(SECOND_PRIZE); 
             prize->move(me);				    
	      write(HIY"恭喜您获得了二等奖，奖励已给您兑现!\n"NOR);
             me->delete("lot_number/" + TIME);
             return 1;               	     
          }     

	   if( me->query("lot_number/" + TIME ) == ob->query("prize/"+ "4")
              || me->query("lot_number/" + TIME ) == ob->query("prize/"+ "5")
              || me->query("lot_number/" + TIME ) == ob->query("prize/"+ "6"))
	   { 
              prize = new(THIRD_PRIZE); 
              prize->move(me);
		write(YEL"恭喜您获得了三等奖，奖励已给您兑现!\n"NOR);
              me->delete("lot_number/" + TIME);
              return 1;               		
          }
	  
             write("您获得了鼓励奖，祝你玩得开心！\n");
	      prize = new(NORMAL_PRIZE); 
             prize->move(me);	     
             me->delete("lot_number/" + TIME);
             return 1; 
        		       
     }
}

int do_open(string arg)
{    
    object ob;
    int num, i, ii, *prize, same;

    prize = ({});		
    ob = this_object();

    if ( ! arg || arg != "lot" || ! wizardp(this_player()) )
       return 0;			
		
    restore_object(FILE_PATH, 1);			

    if (ob->query("open_lot"))
	 return notify_fail("已经开过奖了呀！\n");
		
    for (i = 0; i < 6; i++)
    {	 
        same = 0;
    	 num = random(query("number"))+ 1;

	 for (ii = 0; ii < i; ii++)
	 {					
	      if ( prize[ii] == num ) { same = 1;}				
	 }
			
	 if (same == 1) {i=i-1;}
	 else   
        {
           ob->set("/prize/"+(i+1), num);
           prize += ({num});
        }
    }				
    ob->set("open_lot",1);
    save_object(FILE_PATH, 1);
			
    i = 10;
    message( "story", HIC"【开奖信息】瞎三笨[Sanben]: 同志们好，大家准备好拿礼物了吗？\n" +
			    "【开奖信息】瞎三笨[Sanben]: 现在俺来给大家开奖喽!\n" NOR, users() );
              remove_call_out("count_down");
              call_out("count_down", 5, i);			
	       return 1;					
}		     
	  
		
int do_reset(object me,object ob)
{	
       int i;
		
	me = this_player();
	ob = this_object();

	if ( ! wizardp(me) ) return 0;
          
	ob->delete("name_record");	
	ob->delete("id_record");			     

	ob->delete("open_lot");
	ob->delete("number");

	tell_object(me, HBMAG"抽奖机数据回复初始状态！\n"NOR);

	save_object( FILE_PATH, 1 );

	return 1;
		
}

void count_down(int i)
{
       message( "story", HIG"【开奖信息】春节抽奖结果马上就要公布，请大家做好准备!" +
		chinese_number(i) + "秒倒计时开始......\n"NOR, users() );
	i = i-1;

	if (i > 0 ) 
	{	
	   remove_call_out("count_down");
          call_out("count_down", 1, i);
	}
	else 
	{	message( "story", "\n", users() );
		message( "story", HIG"【开奖信息】" + HIY"现在公布获奖名单!\n"NOR, users() );
		remove_call_out("announce");
              call_out("announce", 2, i);
	}
}

void announce(int i)
{	
       object ob = this_object();

	restore_object(FILE_PATH,1 );
		
	i = i + 1;
	if ( i == 1 ) 
       {
	   message( "story", HIG"【开奖信息】" + BLINK HIM"一等奖：" +
	   ob->query("/prize/"+ i) + "号\n"NOR, users() );
       }
	if ( i == 2 ) 
       {
	   message( "story", HIG"【开奖信息】"NOR + BLINK YEL"二等奖：" +
	   ob->query("/prize/"+ i) + "号   " +
	   ob->query("/prize/"+ (i+1)) + "号\n"NOR, users() );
       }
	if ( i == 3) 
       {
	   message( "story", HIG"【开奖信息】" + BLINK HIC"三等奖：" +
	   ob->query("/prize/"+ (i+1)) + "号  " +
          ob->query("/prize/"+ (i+2)) + "号  " +
	   ob->query("/prize/"+ (i+3)) + "号\n"NOR, users() );
       }

	if (i < 3 ) 
	{	
	   remove_call_out("annouce");
          call_out("announce", 2, i);
	}
	else 
	{  	 
          remove_call_out("ending");
          call_out("ending", 2);
	}

}

void ending()
{	
       string msg;
	message( "vision", HIG"【开奖信息】" + HIY"其他参加者均有鼓励奖，三日内有效。\n" + 			
		  HIG"【开奖信息】" + HIY"祝大家新春快乐，万事如意！\n"NOR, users() );

       msg = HIG"【开奖信息】放焰火时间到!\n " + YEL"
                     | 
                  \   *  ./ 
                .  * * * . 
               -=*  POP! *=-               
               .  .* * *  . 
                /    *  .\ 
                     |          
     　　　/\~~~~~~~~~~~~~\　　　▓　　^*^　　　☆　　  $$　 .☆  
     　　./　\~~~▓~　 ~~~~\ ◆　　新春 .快乐　 *　   $◢◣$　 *  
     　　/ ^^ \ ══════\.◆　　　 *　*　　*　   $◢★◣$　 *  
     　..▎[]　▎田　田 ▎ |┃◆　 .　　　　　*　 $◢■■◣$　 *  
     　&&▎　　▎　　　 ▎'|'▎ @　　　　　　　* $◢■■■◣$ *  
     ＃ ■■■■■■■■■■〓▄▃▂▁祝你新春快乐︸︸||︸︸ \n"NOR; 
             msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL); 
             msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL); 
             msg = replace_string(msg,"*",({"HIG","HIY","HIC",})[random(3)]+"*"NOR YEL); 
             msg = replace_string(msg,"新",NOR HIY"新"NOR YEL); 
             msg = replace_string(msg,"春",NOR HIY"春"NOR YEL); 
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
		
	message("vision",msg,users() ); 
}
