/* -*- mode: C; c-basic-offset: 4; tab-width: 4 -*- vim:et:sw=4:ts=4:sts=4 */
/*=========================================================================
 *-------------------------------------------------------------------------
 *									Interface.c
 *-------------------------------------------------------------------------
 *=========================================================================
 */

#ifndef __GLYPHA_III_EXTERNS_H__
# include "Externs.h"
#endif /* __GLYPHA_III_EXTERNS_H__ */

enum menuIDsEnum {
    kAppleMenuID = 128,
    kGameMenuID = 129,
    kOptionsMenuID = 130
};
typedef enum menuIDsEnum menuIDsEnumType;
enum gameMenuItemsEnum {
    iNewGame = 1,
    iPauseGame = 2,
    iEndGame = 3,
    iQuitGame = 5
};
typedef enum gameMenuItemsEnum gameMenuItemsEnumType;
enum optionsMenuItemsEnum {
    iHelp = 1,
    iHighScores = 3,
    iScoreReset = 4,
    iAboutSource = 6,
    iSoundItemOption = 7
};
typedef enum optionsMenuItemsEnum optionsMenuItemsEnumType;
#define kAboutPictID	132


void DoAppleMenu(AppleMenuItemsEnumType);
void DoGameMenu(gameMenuItemsEnumType);
void DoOptionsMenu(optionsMenuItemsEnumType);
void UpdateMainWindow(void);
void HandleMouseEvent(EventRecord *);
void HandleKeyEvent(EventRecord *);
void HandleUpdateEvent(EventRecord *);
void HandleOSEvent(EventRecord *);
void HandleHighLevelEvent(EventRecord *);
void DoAbout(void);
void DoAboutSource(void);
void DoScoreReset(void);

extern void CheckHighScore(void);

#ifdef __clang__
extern Rect mainWindowRect;
extern WindowPtr mainWindow;
extern MenuHandle appleMenu;
extern MenuHandle gameMenu;
extern MenuHandle optionsMenu;
extern Boolean switchedOut;
extern Boolean quitting;
extern Boolean canPlay;
extern Boolean openTheScores;
#endif /* __clang__ */
Rect		mainWindowRect;
WindowPtr	mainWindow;
MenuHandle	appleMenu, gameMenu, optionsMenu;
Boolean		switchedOut, quitting, canPlay, openTheScores;

extern	prefsInfo	thePrefs;
extern	Rect		backSrcRect, workSrcRect;
extern	GWorldPtr	backSrcMap, workSrcMap;
extern	Boolean		pausing, playing, helpOpen, scoresOpen;


/*===========================================================  Functions */
/*----------------------------------------------------  MenusReflectMode */

void MenusReflectMode(void)
{
	if (playing) {
		DisableMenuItem(gameMenu, iNewGame);
		EnableMenuItem(gameMenu, iPauseGame);
		if (pausing) {
			ShowCursor();
			SetMenuItemText(gameMenu, iPauseGame, "\pResume Game");
			SetItemCmd(gameMenu, iPauseGame, (short)'R');
		} else {
#ifdef OBSCURE_CURSOR_DURING_PLAY
			ObscureCursor();
#endif /* OBSCURE_CURSOR_DURING_PLAY */
			SetMenuItemText(gameMenu, iPauseGame, "\pPause Game");
			SetItemCmd(gameMenu, iPauseGame, (short)'P');
		}
		EnableMenuItem(gameMenu, iEndGame);
		DisableMenuItem(optionsMenu, 0);
	} else {
		EnableMenuItem(gameMenu, iNewGame);
		SetMenuItemText(gameMenu, iPauseGame, "\pPause Game");
		DisableMenuItem(gameMenu, iPauseGame);
		DisableMenuItem(gameMenu, iEndGame);
		EnableMenuItem(optionsMenu, 0);
	}
}

/*---------------------------------------------------------  DoAppleMenu */

void DoAppleMenu(AppleMenuItemsEnumType theItem)
{
	switch (theItem) {
		case iAbout:
			if ((scoresOpen) || (helpOpen)) {
				CloseWall();
				scoresOpen = FALSE;
				helpOpen = FALSE;
				CheckMenuItem(optionsMenu, (MenuItemIndex)iHelp, helpOpen);
				CheckMenuItem(optionsMenu, (MenuItemIndex)iHighScores,
                              scoresOpen);
			}
			DoAbout();
			break;
        case iQuit:
			quitting = TRUE;
			break;
        case iSoundItem:
			thePrefs.soundOff = !thePrefs.soundOff;
			CheckMenuItem(optionsMenu, (MenuItemIndex)iSoundItem,
                          thePrefs.soundOff);
			break;
		default:
			/* Apple menu item handling routines previously kept here */
            fprintf(stderr, "The Apple menu is no longer handled here.\n");
			break;
	}
}

/*----------------------------------------------------------  DoGameMenu */

void DoGameMenu(gameMenuItemsEnumType theItem)
{
	switch (theItem) {
		case iNewGame:
			if ((scoresOpen) || (helpOpen)) {
				CloseWall();
				scoresOpen = FALSE;
				helpOpen = FALSE;
				CheckMenuItem(optionsMenu, (MenuItemIndex)iHelp, helpOpen);
				CheckMenuItem(optionsMenu, (MenuItemIndex)iHighScores,
                              scoresOpen);
			}
			InitNewGame();
			MenusReflectMode();
			break;
		case iPauseGame:
			if (pausing) {
				pausing = FALSE;
				DrawFrame();
			}
			break;
		case iEndGame:
			pausing = FALSE;
			playing = FALSE;
			DrawFrame();
			PlayExternalSound(kMusicSound, kMusicPriority);
			CheckHighScore();
			ShowCursor();
			MenusReflectMode();
			FlushEvents(everyEvent, 0);
			break;
		case iQuitGame:
			quitting = TRUE;
			break;
		default:
            fprintf(stderr, "Unhandled game menu item.\n");
			break;
	}
}

/*-------------------------------------------------------  DoOptionsMenu */

void DoOptionsMenu(optionsMenuItemsEnumType theItem)
{
	switch (theItem) {
		case iScoreReset:
			if ((scoresOpen) || (helpOpen)) {
				CloseWall();
				scoresOpen = FALSE;
				helpOpen = FALSE;
				CheckMenuItem(optionsMenu, (MenuItemIndex)iHelp, helpOpen);
				CheckMenuItem(optionsMenu, (MenuItemIndex)iHighScores,
                              scoresOpen);
			}
			DoScoreReset();
			break;
		case iHelp:
			if (helpOpen) {
				CloseWall();
				helpOpen = FALSE;
			} else {
				if (scoresOpen) {
					CloseWall();
					scoresOpen = FALSE;
					CheckMenuItem(optionsMenu, (MenuItemIndex)iHighScores,
                                  scoresOpen);
				}
				OpenHelp();
			}
			CheckMenuItem(optionsMenu, (MenuItemIndex)iHelp, helpOpen);
			break;
		case iHighScores:
			if (scoresOpen) {
				CloseWall();
				scoresOpen = FALSE;
			} else {
				if (helpOpen) {
					CloseWall();
					helpOpen = FALSE;
					CheckMenuItem(optionsMenu, iHelp, helpOpen);
				}
				OpenHighScores();
			}
			CheckMenuItem(optionsMenu, iHighScores, scoresOpen);
			break;
		case iAboutSource:
			DoAboutSource();
			break;
		case iSoundItemOption:
			thePrefs.soundOff = !thePrefs.soundOff;
			CheckMenuItem(optionsMenu, (MenuItemIndex)iSoundItem,
                          thePrefs.soundOff);
			break;
		default:
            fprintf(stderr, "Unhandled options menu item.\n");
			break;
	}
}

/*--------------------------------------------------------  DoMenuChoice */

void DoMenuChoice(long menuChoice)
{
	menuIDsEnumType theMenu;
    short theItem;

	if (menuChoice == 0) {
		return;
	}

	theMenu = (menuIDsEnumType)HiWord(menuChoice);
	theItem = LoWord(menuChoice);

	switch (theMenu) {
		case kAppleMenuID:
			DoAppleMenu((AppleMenuItemsEnumType)theItem);
			break;
		case kGameMenuID:
			DoGameMenu((gameMenuItemsEnumType)theItem);
			break;
		case kOptionsMenuID:
			DoOptionsMenu((optionsMenuItemsEnumType)theItem);
			break;
		default:
            fprintf(stderr, "Unhandled menu choice.\n");
			break;
	}

	HiliteMenu(0);
}

/*----------------------------------------------------  UpdateMainWindow */

void UpdateMainWindow(void)
{
	CopyBits(GetPortBitMapForCopyBits(backSrcMap),
			 GetPortBitMapForCopyBits(GetWindowPort(mainWindow)),
			 &mainWindowRect, &mainWindowRect,
			 srcCopy, 0L);
}

/*----------------------------------------------------  HandleMouseEvent */

void HandleMouseEvent(EventRecord *theEvent)
{
	WindowPtr	whichWindow;
	BitMap		screenbits;
	long		menuChoice;
	short		thePart;

	thePart = FindWindow(theEvent->where, &whichWindow);

	switch (thePart) {
		case inMenuBar:
			menuChoice = MenuSelect(theEvent->where);
			if (canPlay) {
				DoMenuChoice(menuChoice);
			}
			break;

		case inDrag:
			GetQDGlobalsScreenBits(&screenbits);
			DragWindow(whichWindow, theEvent->where, &screenbits.bounds);
			break;

		case inGoAway:
		case inGrow:
		case inZoomIn:
		case inZoomOut:
			break;

		case inContent:
			GlobalToLocal(&(theEvent->where));
			FlashObelisks(TRUE);
			LogNextTick(3);
			GenerateLightning(theEvent->where.h, theEvent->where.v);
			StrikeLightning();
			WaitForNextTick();
			StrikeLightning();
			LogNextTick(2);
			WaitForNextTick();
			PlayExternalSound(kLightningSound, kLightningPriority);
			LogNextTick(3);
			GenerateLightning(theEvent->where.h, theEvent->where.v);
			StrikeLightning();
			WaitForNextTick();
			StrikeLightning();
			LogNextTick(2);
			WaitForNextTick();
			LogNextTick(3);
			GenerateLightning(theEvent->where.h, theEvent->where.v);
			StrikeLightning();
			WaitForNextTick();
			StrikeLightning();
			LogNextTick(2);
			WaitForNextTick();
			PlayExternalSound(kLightningSound, kLightningPriority);
			LogNextTick(3);
			GenerateLightning(theEvent->where.h, theEvent->where.v);
			StrikeLightning();
			WaitForNextTick();
			StrikeLightning();
			LogNextTick(2);
			WaitForNextTick();
			FlashObelisks(FALSE);
			break;

		default:
			break;
	}
}

/*------------------------------------------------------  HandleKeyEvent */

void HandleKeyEvent(EventRecord *theEvent)
{
	char	theChar;
	Boolean	commandDown;

	theChar = (char)(theEvent->message & charCodeMask);
	commandDown = ((theEvent->modifiers & cmdKey) != 0);

	if ((commandDown) && (theEvent->what == keyDown)) {
		if (canPlay) {
			DoMenuChoice(MenuKey(theChar));
		}
	} else {
		if (helpOpen) {
			if (theChar == kUpArrowKeyASCII) {
				if (theEvent->what == autoKey) {
					ScrollHelp(-3);
				} else {
					ScrollHelp(-1);
				}
			} else if (theChar == kDownArrowKeyASCII) {
				if (theEvent->what == autoKey) {
					ScrollHelp(3);
				} else {
					ScrollHelp(1);
				}
			} else if (theChar == kPageDownKeyASCII) {
				ScrollHelp(199);
			} else if (theChar == kPageUpKeyASCII) {
				ScrollHelp(-199);
			} else if ((theChar == kHelpKeyASCII) && (!playing)) {
				CloseWall();
				helpOpen = FALSE;
				CheckMenuItem(optionsMenu, iHelp, helpOpen);
			}
		} else if ((theChar == kHelpKeyASCII) && (!playing)) {
			if (scoresOpen) {
				CloseWall();
				scoresOpen = FALSE;
				CheckMenuItem(optionsMenu, iHighScores, scoresOpen);
			}
			OpenHelp();
			CheckMenuItem(optionsMenu, iHelp, helpOpen);
		}
	}
}

/*---------------------------------------------------  HandleUpdateEvent */

void HandleUpdateEvent (EventRecord *theEvent)
{
	if ((WindowPtr)theEvent->message == mainWindow) {
		SetPortWindowPort(mainWindow);
		BeginUpdate(mainWindow);
		UpdateMainWindow();
		EndUpdate(mainWindow);
		canPlay = TRUE;
	}
}

/*-------------------------------------------------------  HandleOSEvent */

void HandleOSEvent (EventRecord *theEvent)
{
	if (theEvent->message & 0x01000000)	{ /* suspend or resume event */
		if (theEvent->message & 0x00000001) { /* resume event */
			switchedOut = FALSE;
		} else { /* suspend event */
			switchedOut = TRUE;
		}
	}
}

/*------------------------------------------------  HandleHighLevelEvent */

void HandleHighLevelEvent(EventRecord *theEvent)
{
	AEProcessAppleEvent(theEvent);
}

/*---------------------------------------------------------  HandleEvent */

void HandleEvent(void)
{
	EventRecord	theEvent;
	/* The following variable used to just be called "sleep": */
	long	eventSleep = 1L; /* renamed so it will NOT shadow unistd.h */
	Boolean	itHappened;

	itHappened = WaitNextEvent((EventMask)everyEvent, &theEvent,
                               (UInt32)eventSleep, 0L);

	if (itHappened) {
		switch (theEvent.what) {
			case mouseDown:
                printf("Mouse button clicked.\n");
				HandleMouseEvent(&theEvent);
				break;
            case mouseUp:
                printf("Mouse button released.\n");
                break;
			case keyDown:
			case autoKey:
				HandleKeyEvent(&theEvent);
				break;
			case updateEvt:
				HandleUpdateEvent(&theEvent);
				break;
			case osEvt:
				HandleOSEvent(&theEvent);
				break;
			case kHighLevelEvent:
				HandleHighLevelEvent(&theEvent);
				break;
            case activateEvt:
                printf("Window activated or deactivated.\n");
                break;
			default:
                fprintf(stderr, "Unhandled event to handle: '%u'.\n",
                        theEvent.what);
				break;
		}
	} else if (openTheScores) {
		openTheScores = FALSE;
		OpenHighScores();
	}
}

/*-------------------------------------------------------------  DoAbout */

void DoAbout(void)
{
	Rect		aboutRect;
	WindowPtr	aboutWindow;
	BitMap		screenBits;
	EventRecord theEvent;
	Boolean 	isEvent, windowDone = false;

	HiliteMenu(0);
	SetRect(&aboutRect, 0, 0, 325, 318);
	GetQDGlobalsScreenBits(&screenBits);
	CenterRectInRect(&aboutRect, &screenBits.bounds);
	aboutWindow = GetNewWindow(129, 0L, kPutInFront);
	SetPortWindowPort(aboutWindow);
	LoadGraphic(kAboutPictID);

	do {
		isEvent = WaitNextEvent(everyEvent, &theEvent, 120, 0L);
		if (isEvent) {
			switch (theEvent.what) {
				case kHighLevelEvent:
					HandleHighLevelEvent(&theEvent);
					break;
				case updateEvt:
					LoadGraphic(kAboutPictID);
					break;
				case mouseDown:
					windowDone = true;
					break;
				default:
                    fprintf(stderr, "Unhandled event for 'about'.\n");
					break;
			}
		}
	} while (windowDone == false);

	SetPortWindowPort(mainWindow);
	if (aboutWindow != 0L) {
		DisposeWindow(aboutWindow);
	}
}

/*-------------------------------------------------------  DoAboutSource */

void DoAboutSource(void)
{
#define kAboutSourceDialog 134
	DialogPtr	theDial;
	short		item;
	Boolean		leaving = false;

	HiliteMenu(0);
	theDial = GetNewDialog(kAboutSourceDialog, 0L, kPutInFront);
	SetDialogDefaultItem(theDial, 1);
	FlushEvents(everyEvent, 0);

	while (!leaving) {
		ModalDialog(0L, &item);

		switch (item) {
			case 1:
				leaving = true;
				break;
			default:
                fprintf(stderr, "Unhandled item.\n");
				break;
		}
	}

	DisposeDialog(theDial);
}

/*--------------------------------------------------------  DoScoreReset */

void DoScoreReset(void)
{
#define kScoreResetDialog 133
	DialogPtr	theDial;
	short		i, item;
	Boolean		leaving = false;

	HiliteMenu(0);
	theDial = GetNewDialog(kScoreResetDialog, 0L, kPutInFront);
	SetDialogDefaultItem(theDial, 1);
	FlushEvents(everyEvent, 0);

	while (!leaving) {
		ModalDialog(0L, &item);

		switch (item) {
			case 1:
				for ((i = 0); (i < 10); i++) {
					PasStringCopy((StringPtr)"\pNemo",
                                  thePrefs.highNames[i]);
					thePrefs.highScores[i] = 0L;
					thePrefs.highLevel[i] = 0;
					openTheScores = TRUE;
				}
				leaving = true;
				break;
			case 2:
				leaving = true;
				break;
			default:
                fprintf(stderr, "Unhandled item.\n");
				break;
		}
	}

	DisposeDialog(theDial);
}

/* EOF */
