//by xiner 2009-07-05用于special查询
#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object* users;
        int count, i, j;
        
        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

//        users = all_interactive();
	users = users();

        if (wiz_level(me) < 4)
                return 0;
  
        if (! str)
                return notify_fail("你要统计什么特技？\n");

        if (file_size("/kungfu/special/" + str + ".c") == -1)
                return notify_fail("没有这个特技存在！\n");

        count = sizeof(users);

        j = 0;
        write(HIW "\n以下为本MUD中掌握 " + HIM + CHINESE_D->chinese(str) + HIW + " 的玩家。\n" NOR);
        write(HIY "-------------------------------------------------------------------------\n" NOR);
        for (i = 0; i < count; i ++)
        {
             if (users[i]->query("special_skill/" + str))
             {
                  write(HIC + users[i]->name() + "(" + users[i]->query("id") + ") \t\t" NOR);
                  write(HIC "年龄：" + users[i]->query("age") + "\t" NOR);
                  write(HIC "所属门派：" + users[i]->query("family/family_name") + "\t" NOR);
                  write(HIC "等级：" + users[i]->query(str) + "\n" NOR);
                  j ++;
             }
         
        }
        write(HIW "\n总共 " HIR + j + HIW " 位玩家具有" + HIM + CHINESE_D->chinese(str) + HIW +" 的特殊技能。\n" NOR);
        write(HIY "-------------------------------------------------------------------------\n" NOR);

        return 1;
}

