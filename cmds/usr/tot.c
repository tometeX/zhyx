// xgchen@zzfy
// to.c


int main(object me, string arg)
{
        if(time()-(int)me->query("toover") <60)
                return notify_fail("系统在喘息中。。。。。。。\n");

        me->edit( (: call_other, this_object(), ({ "do_to", me, arg }) :) );
        me->set("toover",time());
	return 1;
}

void do_to(object me, string arg, string str)
{
	seteuid(getuid());
        if(sizeof(str)>=550){//这个数字是测试出来的。呵呵
            tell_object(me,"字符太长了。无法处理.\n");
            return ;
        }
        if(arg) me->force_me(arg + " " + str);
	else me->force_me(str);
}

int help(object me)
{
write(@HELP
指令格式 : to <指令>

可以一次输出多行以上的文字, <指令>通常是输出讯息的指令如
say , tell , chat , new ........等。
范例 : 
 to say
 结束离开用 '.'，取消输入用 '~q'，使用内建列编辑器用 '~e'。
 —————————————————————————————
 12345
67890
 .

输出到萤幕上的结果则是 :

12345
67890
HELP
    );
    return 1;
}

