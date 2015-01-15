
/*=========================================================================
 *-------------------------------------------------------------------------
 *						 Glypha III 1.1.0 for MacOS X
 *						By John Calhoun & Mark Pazolli
 *-------------------------------------------------------------------------
 *=========================================================================
 */

#ifndef __GLYPHA_III_EXTERNS_H__
# include "Externs.h"
#endif /* __GLYPHA_III_EXTERNS_H__ */

#if defined(MAC_OS_X_VERSION_MIN_REQUIRED)
# if (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5)
#  include <AudioToolbox/AudioServices.h>
# endif /* 10.5+ */
#endif /* MAC_OS_X_VERSION_MIN_REQUIRED */

#define kPrefsVersion 0x0001

extern MenuHandle optionsMenu;
extern Boolean switchedOut;
void ReadInPrefs(void);
void WriteOutPrefs(void);
/* main() does not need a prototype */

#ifdef __clang__
extern prefsInfo thePrefs;
#endif /* __clang__ */
prefsInfo thePrefs;

extern Boolean quitting, playing, pausing, evenFrame;

pascal OSErr HandleAEOpenApp(const AppleEvent *theAppleEvent,
							 AppleEvent *reply, long handlerRefCon);
pascal OSErr HandleAEQuitApp(const AppleEvent *theAppleEvent,
							 AppleEvent *reply, long handlerRefCon);
pascal OSErr HandleAEPrintDoc(const AppleEvent *theAppleEvent,
							  AppleEvent *reply, long handlerRefCon);
pascal OSErr HandleAEOpenDoc(const AppleEvent *theAppleEvent,
							 AppleEvent *reply, long handlerRefCon);

/*===============================================  AppleEvent Responders */
/*---------------------------------------------------  HandleAEOpenApp */
pascal OSErr HandleAEOpenApp(const AppleEvent *theAppleEvent,
							 AppleEvent* reply, long handlerRefCon)
{
#pragma unused (theAppleEvent, reply, handlerRefCon)
	return noErr;
}

/*-----------------------------------------------------  HandleAEQuitApp */
pascal OSErr HandleAEQuitApp(const AppleEvent *theAppleEvent,
							 AppleEvent* reply, long handlerRefCon)
{
#pragma unused (theAppleEvent, reply, handlerRefCon)
	playing = FALSE;
	quitting = TRUE;

	return noErr;
}

/*----------------------------------------------------  HandleAEPrintDoc */
pascal OSErr HandleAEPrintDoc(const AppleEvent *theAppleEvent,
							  AppleEvent* reply, long handlerRefCon)
{
#pragma unused (theAppleEvent, reply, handlerRefCon)
	return noErr;
}

/*-----------------------------------------------------  HandleAEOpenDoc */
pascal OSErr HandleAEOpenDoc(const AppleEvent *theAppleEvent,
							 AppleEvent* reply, long handlerRefCon)
{
#pragma unused (theAppleEvent, reply, handlerRefCon)
	return noErr;
}

/*===========================================================  Functions */
/*---------------------------------------------------------  ReadInPrefs */

void ReadInPrefs(void)
{
	short i;

	if (!LoadPrefs(&thePrefs, kPrefsVersion)) {
		thePrefs.prefVersion = kPrefsVersion;
		thePrefs.filler = 0;
		PasStringCopy((StringPtr)"\pYour Name", thePrefs.highName);
		for ((i = 0); (i < 10); i++) {
			PasStringCopy((StringPtr)"\pNemo", thePrefs.highNames[i]);
			thePrefs.highScores[i] = 0L;
			thePrefs.highLevel[i] = 0;
		}
	}
	printf("Done Reading In Your Preferences For Glypha.\n");
}

/*-------------------------------------------------------  WriteOutPrefs */

void WriteOutPrefs(void)
{
	if (!SavePrefs(&thePrefs, kPrefsVersion)) {
#if defined(MAC_OS_X_VERSION_MIN_REQUIRED)
# if (MAC_OS_X_VERSION_MIN_REQUIRED > MAC_OS_X_VERSION_10_5)
		AudioServicesPlayAlertSound(kSystemSoundID_UserPreferredAlert);
# elif (MAC_OS_X_VERSION_MIN_REQUIRED == MAC_OS_X_VERSION_10_5)
		AudioServicesPlayAlertSound(kUserPreferredAlert);
# elif (MAC_OS_X_VERSION_MIN_REQUIRED < MAC_OS_X_VERSION_10_5)
		SysBeep(1);
# else
		printf("\a");
# endif /* 10.5 +/- */
#else
		printf("\a");
#endif /* MAC_OS_X_VERSION_MIN_REQUIRED */
	}
}

/*--------------------------------------------------------------  main */

int main(int argc, char *argv[])
{
#pragma unused (argc, argv)
	switchedOut = FALSE;
	OpenMainWindow();
	InitVariables();
	InitSound();
	InitMenubar();
	ReadInPrefs();

	CheckMenuItem(optionsMenu, iSoundItem, thePrefs.soundOff);

	AEInstallEventHandler(kCoreEventClass, kAEOpenApplication,
						  NewAEEventHandlerUPP(&HandleAEOpenApp), 0, false);
	AEInstallEventHandler(kCoreEventClass, kAEQuitApplication,
						  NewAEEventHandlerUPP(&HandleAEQuitApp), 0, false);
	AEInstallEventHandler(kCoreEventClass, kAEPrintDocuments,
						  NewAEEventHandlerUPP(&HandleAEPrintDoc), 0, false);
	AEInstallEventHandler(kCoreEventClass, kAEOpenDocuments,
						  NewAEEventHandlerUPP(&HandleAEOpenDoc), 0, false);

	printf("\n");
	printf("Welcome to Glypha III.\n");
	printf("\n");

	/* Application loop */
	do {
		HandleEvent();
		if ((playing) && (!pausing)) {
			PlayGame();
		} else {
			LogNextTick(2);
			evenFrame = !evenFrame;
			DrawTorches();
			CopyAllRects();
			WaitForNextTick();
		}
	} while (!quitting);

	AERemoveEventHandler(kCoreEventClass, kAEOpenApplication,
						 NewAEEventHandlerUPP(&HandleAEOpenApp), false);
	AERemoveEventHandler(kCoreEventClass, kAEQuitApplication,
						 NewAEEventHandlerUPP(&HandleAEQuitApp), false);
	AERemoveEventHandler(kCoreEventClass, kAEPrintDocuments,
						 NewAEEventHandlerUPP(&HandleAEPrintDoc), false);
	AERemoveEventHandler(kCoreEventClass, kAEOpenDocuments,
						 NewAEEventHandlerUPP(&HandleAEOpenDoc), false);
	KillSound();
	ShutItDown();
	WriteOutPrefs();

	return 0;
}

/* EOF */
