#include <stdio.h>
#include <unistd.h>
#include <sys/cdefs.h>

#include <AudioToolbox/AudioServices.h>
#include <CoreFoundation/CoreFoundation.h>

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

int OnAC()
{
    CFTypeRef blob = (CFTypeRef)IOPSCopyPowerSourcesInfo();
    CFArrayRef ps = (CFTypeRef)IOPSCopyPowerSourcesList(blob);
        
    CFDictionaryRef theDict = (CFDictionaryRef)IOPSGetPowerSourceDescription(blob, CFArrayGetValueAtIndex(ps, 0));
    CFStringRef isCharging = CFDictionaryGetValue(theDict, CFSTR("Power Source State" ));
        
    CFRelease(ps);
    CFRelease(blob);

    return CFStringCompare(isCharging, CFSTR("AC Power"), 0) == 0;
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
	ac_only = FindFirstOf(ac_file, IsNum) - '0';
	fclose(ac_file);
    }

    SystemSoundID soundID;
    AudioServicesCreateSystemSoundID
	    ( CFURLCreateWithString(NULL, CFSTR("/Extra/share/antipop/silent.aiff"), NULL)
	    , &soundID );

    if(ac_only != 1)
    {
	while(1)
	{
	    AudioServicesPlaySystemSound(soundID);
	    sleep(10);
	}
    }
    else
    {
	while(1)
	{
	    if(OnAC())
	    {
		AudioServicesPlaySystemSound(soundID);
	    }

	    sleep(10);
	}
    }

    AudioServicesDisposeSystemSoundID(soundID);
}
