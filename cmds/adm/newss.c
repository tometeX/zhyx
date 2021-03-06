inherit F_CLEAN_UP;

#ifndef ADV_D
#define ADV_D          "/adm/daemons/advd"
#endif

int main(object me, string arg)
{
        if (! arg || arg == "" || arg == "all")
        {
                ADV_D->show_advs(me, (arg != "all") ? 1 : 0);
                return 1;
        }

	if (arg == "start")
	{
		ADV_D->start_adv();
		write("广告系统启动！\n");
		return 1;	
	}
	
	if (arg == "stop")
	{
		ADV_D->stop_adv();
		write("广告系统停止！\n");
		return 1;
	}
	
        if (sscanf(arg, "discard %s", arg))
        {
                ADV_D->do_discard(me, arg);
                return 1;
        }

        if (sscanf(arg, "post %s", arg))
        {
                ADV_D->do_post(me, arg);
                return 1;
        }
        
	ADV_D->do_read(me, arg);
	
        return 1;
}

int help(object me)
{
	write(@HELP
指令格式 : adv [<all> || <num>] || [post 标题] || [discard num]
		|| start || stop

这条指令让巫师发布广告。

使用 all 参数可以让你查看系统目前所有的广告，指定数字可以查看该
条广告的详细内容。

adv post <标题>来发布广告。
adv discard来删除广告。
adv start 启动广告系统。
adv stop  停止广告系统。

注意：广告的标题是为了巫师阅读和管理的方便，广告播送的时候只播送
      具体的内容。
HELP );
    return 1;
}
