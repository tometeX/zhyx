// Create by Rcwiz for Hero 2003
// Command of Voting System

#include <net/dns.h>
#include <ansi.h>

inherit F_CLEAN_UP;

#define POLL_D "/adm/daemons/polld"

int help(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
	object victim;
	string para, target, kind;
        string* kinds;
        int n;

	if (((int) me->query("age") < 18) 
          && ! wizardp(me)
          && arg != "now"
          && arg != "history" )
           	    return notify_fail("民主不是儿戏！小孩子一边玩去！\n");

    if (me->query("combat_exp") < 1000000 
        && ! wizardp(me)
        && arg != "now"
        && arg != "history" )
                return notify_fail("目前只允许实战经验在100万以上的ID投票。\n");

	if ((int) me->query("vote/deprived"))
        {
                // 是否被剥夺投票权？还没有恢复呢？
                if (time() - me->query("vote/deprived") >= 86400)
                        me->delete("vote/deprived");
                else
		        return notify_fail("你想起当初玩弄民主、被剥夺投票权的事，追悔莫及。\n");
        }
       
        if (! arg)return help(me);

        if (arg == "history")
        {
                POLL_D->show_voting(me, "history");
                return 1;
        }
        if (arg == "now")
        {
                POLL_D->show_voting(me, "now");
                return 1;               
        }
        
        if (arg == "end")
        {
                POLL_D->end_voting(me);
                return 1;
        }

        sscanf(arg, "%s %s %s", para, target, kind);

        switch (para)
        {
                case "shot":
                       sscanf(arg, "%s %s", para, kind);
                       if (! POLL_D->query_now_voting_class(kind) )
                       {
                             write(HIR "\n看清楚了再投票！\n" NOR);
                             POLL_D->show_voting(me, "now");
                             break;
                       }
                       POLL_D->shot_target(me, kind);
                       break;
               
                case "start":
                       if (sscanf(arg, "%s %s %s", para, target, kind) != 3)
                              return help(me);

                       POLL_D->start_voting(me, target, kind);
                       break;
 
                default:
                       return help(me);
        }

	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : poll shot          <种类>   ： 参与投票
                start  <目标> <种类>   ： 发起投票
                end                    ： 结束投票
                history                ： 显示历史投票记录
                now                    ： 显示当前投票信息

比如当前正在对XXX投票，投票种类为“好，一般，差”，那么
如果你要投XXX为“好”，则：

           poll shot XXX 好

巫师在使用 poll start <目标> <种类>命令时，比如开始对
“是否同意开放XXX门派”进行投票，投票种类为：“是”和“否”
则此时命令应为：

           poll start 是否同意开放XXX门派 是:否

即投票种类必须用“:”符号分开。


HELP );
    return 1;
}
