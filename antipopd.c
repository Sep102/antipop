#include <stdio.h>
#include <unistd.h>

#include <AudioToolbox/AudioServices.h>
#include <CoreFoundation/CFString.h>

int IsNum(int c)
{
    return c >= '0' && c <= '9';
}

typedef int (*FFPred)(int);
int FindFirstOf(FILE *file, FFPred pred)
{
    if(!file || !pred)
    {
	return -1;
    }
    
    while(!feof(file))
    {
	int c = fgetc(file);
	if(pred(c))
	{
	    return c;
	}
    }

    return -1;
}

int main()
{
    /* Should be a single integer in the file:
     * 1 = AC only
     * !1 = AC or Battery
     */
    FILE *ac_file = fopen("/usr/local/share/antipop/ac_only", "r");
    int ac_only = 0;
    if(ac_file)
    {
	ac_only = FindFirstOf(ac_file, IsNum);
	fclose(ac_file);
    }

    if(ac_only != 1)
    {
	SystemSoundID soundID;
	AudioServicesCreateSystemSoundID(CFURLCreateWithString(NULL, CFSTR("silent.aiff"), NULL), &soundID);
	while(1)
	{
	    AudioServicesPlaySystemSound(soundID);
	    sleep(10);
	}
	AudioServicesDisposeSystemSoundID(soundID);
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
