// mail.c

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

void create() { seteuid(getuid()); }

int help(object me);
private void get_mail_to(string mailto, object me, string topic);
private void get_mail_subject(string topic, object me, string mailto);

int main(object me, string arg)
{
        string mailto, topic;

        if (! arg || sscanf(arg, "%s %s", mailto, topic) != 2)
        {
                mailto = arg;
                topic = 0;
        }

        if (! mailto || mailto == "")
        {
                write("请输入你发送邮件的地址：");
                input_to("get_mail_to", me, 0);
                return 1;
        }

        get_mail_to(mailto, me, topic);
	return 1;
}

private void get_mail_to(string mailto, object me, string topic)
{
        string user, addr;

        if (! mailto || mailto == "" || sscanf(mailto, "%s@%s", user, addr) != 2 ||
            user == "" || addr == "")
        {
                tell_object(me, "你指定的发送地址格式不正确。\n");
                return;
        }

        if (topic)
        {
                get_mail_subject(topic, me, mailto);
                return;
        }

        write("清输入你信件的标题：");
        input_to("get_mail_subject", me, mailto);
}

private void get_mail_subject(string topic, object me, string mailto)
{
        if (! topic || topic == "")
                topic = "没有";

        write(sprintf(WHT "发信人：" CYN "%s  "
                      WHT "收信人：" CYN "%s  "
                      WHT "主题：" CYN "%s\n" NOR,
                      me->query("email"), mailto, topic));
        write("请输入你信件的内容。\n");
        me->edit(bind((: call_other, __FILE__, "done", me, mailto, topic :), me));
}

void done(object me, string mailto, string topic, string msg)
{
        if (! me || ! msg || msg == "")
                return;

        if (! wizardp(me) && time() - me->query_temp("last_mail") < 30)
        {
                tell_object(me, "你在三十秒钟内只能发送一封信件。\n");
                return;
        }

        me->set_temp("last_mail", time());
        if (! MAIL_D->queue_mail(me, me->query("email"),
                                 mailto, topic, msg))
        {
                tell_object(me, query_fail_msg());
                tell_object(me, "发送邮件失败。\n");
        } else
                tell_object(me, "你的邮件已经发往<" + mailto + ">了。\n");
}

int help(object me)
{
	write(@HELP
指令格式： mail [<地址>] [<主题>]

这个指令让你发信给某人。
HELP );
	return 1;
}
