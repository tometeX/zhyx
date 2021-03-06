//creat by wsw 2005 1 20
//wangxy.c
//开心词典主持人：唐小丫

#include <ansi.h>

#define FILE 	__DIR__+"kxcd.txt"  //题库文件名称
#define LINES	19000				//题库文件最大行数
#define TIME	30					//回答一题的时间限制（秒）

inherit NPC;

string name = HIY"【开心词典】"NOR+HIM"唐小丫"NOR;
int do_start();
int start_chuti();
void announce (string str);
void finish(object who);
int    filter_listener(object ob);
object *listeners ;

void create()
{
                  set_name(HIM"唐小丫"NOR, ({ "tang xiaoya","xiaoya" }));
                  set("shen_type", 1);
				  set("title", HIY"【开心词典】"NOR);
                  set("gender", "女性");
                  set("age", 36);
                  set("per",36);
                  set("long",
"她是大唐开心词典的主持人，虽然徐娘半老，但是风韵犹存。\n只见其含笑如春桃，玉唇含香,纤纤细腰,婀娜多姿，
虽说衣着不艳丽，但不掩其清秀，实乃人间绝色。\n"
);
                  set("attitude", "friendly");
                  set("inquiry", ([
    "开心词典":  WHT"\n开心词典是一种休闲的娱乐游戏。
    	start		开始游戏
    	kxcd		检查自己的成绩\n"NOR
                  ]));


                  setup();
              carry_object("/d/city/obj/cloth")->wear(); 


}




void init()
{
         add_action("do_start", "start");
         add_action("do_check", "kxcd");
}


int do_start()
{
	object me,who;
	string str;
	
	me = this_object();
	who = this_player();
	
	if (!who) return 1;

	if (time() - who->query_temp("kxcd/last_time")   < 60 ) {
		return notify_fail("不要急，慢慢来。\n");
	}
	
	if (me->query_temp("kxcd/doing") =="yes")   //正在进行
		return notify_fail("不要急，一个一个来。\n");
		
	who->delete("env/no_story");
		
	listeners = filter_array(users(), (: filter_listener :));	
	
	str = name+"："+HIY+who->query("name")+"("+who->query("id")+")参加【开心词典】大赛。\n"+NOR;
	announce (str);
	
	me->set_temp("kxcd/doing","yes");
	
	who->set_temp("kxcd/last_time",time());
	
	
	who->set_temp("kxcd/score",0);//本轮得分
	who->set_temp("kxcd/num",0);//本轮次数
	
	start_chuti();

	return 1;	
}

int start_chuti()
{
	string arg, quest, key_n, key_str, *choose, level;
	int i, k;
	
	object me = this_object();
	object who = this_player();
	
	arg = read_file(FILE,random(LINES),1);
	
	choose = allocate(6);	
	k = sscanf(arg, "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n", quest, key_n, key_str, 
		choose[0],choose[1],choose[2], choose[3], choose[4], choose[5],  level);
	
	arg = quest+"\n";
	for (i=0;i<6;i++) 
		if (sizeof(choose[i]) > 0)  arg += HIR"（"+ (i+1) +"）、"NOR+HIW+choose[i];	
	arg += HIR"（"+replace_string(level," ","")+"）"+ "\n"NOR;
	announce (name+HIW+"："+arg+NOR);
	
	who->set_temp("kxcd/start_time",time());
	
	write(HIG"请在30秒以内用选择（数字）：\n"NOR);
	input_to("get_num", 1, replace_string(key_n," ",""), replace_string(level," ",""));	
	
	remove_call_out("finish");
    call_out("finish",TIME,who);		
		
	return 1;
	
}

void get_num(string str, string key_n, string level)
{
	object who = this_player();
	float score;
	int time;
	
	remove_call_out("finish");
	
	if (str != key_n) {
		write (HIG+"回答错误。正确答案应该是："+key_n+"。\n"NOR);
		finish(who);
		return;			
	}
		
	
	time =TIME - time() + who->query_temp("kxcd/start_time");
	
	if (time<0) {
		write (HIG"你想得太久了。\n"NOR);
		return;
	}
	
	who->add_temp("kxcd/num",1);//本轮次数加1
		
	score = (int)(time/10)*0.5; //时间加分:10秒内1分，20秒内0.5，30秒内不加分
	
	if (level=="高级") score += 3;
	else if (level=="中级") score += 2;
	if (level=="低级") score += 1;
	
	who->add_temp("kxcd/score",score);//本轮得分
	
	write(HIG"回答正确！得分："+sprintf("%1.1f",score)+"。\n"NOR);
		
	//start_chuti();
	remove_call_out("start_chuti");
    call_out("start_chuti",1);
    
    return;
			

}


void finish(object who)
{
	string str;
	
	this_object()->delete_temp("kxcd");
	if (!who->query_temp("kxcd/num")) return;
	
	//计算得分
	str =  name+HIW+"："+who->query("name")+"共回答正确了"+chinese_number(who->query_temp("kxcd/num"))+"道题，获得了"
		+sprintf("%3.1f",who->query_temp("kxcd/score")) +"分。\n";
		
	announce(str);
	
	who->add("kxcd/num",1); 
	if (who->query_temp("kxcd/score") > who->query("kxcd/score"))
		who->set("kxcd/score",who->query_temp("kxcd/score"));
		
	who->delete_temp("kxcd");//清除本次记录
	who->set_temp("kxcd/last_time",time()+60); //一分钟以内不得参加
	
	return;
		
	
}

int do_check()
{
	string str;
	object who = this_player();
	
	if ( who->query("kxcd/score")) 
		str= "你共参加了"+	chinese_number(who->query("kxcd/num"))+"次测试，最高分为"+
			sprintf("%3.1f",who->query("kxcd/score"))+"分。\n";
	else str = "你还没有参加过开心词典测试。\n";
	write(HIG+str+NOR);
	return 1;
}

void announce (string str)
{
  //command_function ("chat "+str);
  //tell_room(environment(this_object()),str);
  message("story", str, listeners);
}

int filter_listener(object ob)
{
        if (ob->query("env/no_story")) return 0;
        return 1;
}