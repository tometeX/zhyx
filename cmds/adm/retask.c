#include <ansi.h>

int main(object me)
        {
          if( !wizardp(me) )
                return notify_fail("you are not wiz!!\n");  
          TASK_D->init_dynamic_quest(1);
        }
                
 int help(object me)
{
  write(@HELP

refresh 命令是用来重新布所有（完成和没完成）的使命（ｔａｓｋｓ）

HELP
    );
return 1;
}
