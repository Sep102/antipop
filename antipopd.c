#include <stdio.h>
#include <unistd.h>

int main()
{
    int ac_only = 0;

    FILE *ac_file = fopen("/usr/local/share/antipop/ac_only", "r");
    if(ac_file)
    {
	/* Should be a single integer in the file:
	 * 1 = AC only
	 * !1 = AC or Battery
	 */
	ac_only = fgetc(ac_file);
	fclose(ac_file);
    }

    if(ac_only != 1)
    {
	while(1)
	{
	    system("say ' '");
	    sleep(10);
	}
    }
    else
    {
	while(1)
	{
	    FILE *ac_check_proc = popen("pmset -g | grep \"AC Power.*\\*\"", "r");
	    if(ac_check_proc && fgetc(ac_check_proc) > 0)
	    {
		system("say ' '");
		pclose(ac_check_proc);
	    }

	    sleep(10);
	}
    }
}
