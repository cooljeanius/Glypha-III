/* -*- mode: C; c-basic-offset: 4; tab-width: 4 -*- vim:et:sw=4:ts=4:sts=4 */
/*=========================================================================
 *-------------------------------------------------------------------------
 *									Utilities.c
 *-------------------------------------------------------------------------
 *=========================================================================
 */

#ifndef __GLYPHA_III_EXTERNS_H__
# include "Externs.h"
#endif /* __GLYPHA_III_EXTERNS_H__ */

extern WindowPtr mainWindow;
extern Boolean pausing;

#ifndef kActive
# define kActive	0
#endif /* !kActive */
#define kInactive	255

#ifdef __clang__
extern long tickNext;
#endif /* __clang__ */
long tickNext = 0L;


/*===========================================================  Functions */
/*-----------------------------------------------------------  RandomInt */

short RandomInt(short range)
{
	register long rawResult;

	rawResult = Random();
	if (rawResult < 0L) {
		rawResult *= -1L;
	}
	rawResult = ((rawResult * (long)range) / 32768L);

	return ((short)rawResult);
}

/*------------------------------------------------------------  RedAlert */

void ATTRIBUTE_NORETURN RedAlert(const StringPtr theStr)
{
#define kRedAlertID 128
	short whoCares;

	ParamText(theStr, "\p", "\p", "\p");
	whoCares = Alert((SInt16)kRedAlertID, 0L);
	/* dummy condition to use value stored to 'whoCares': */
	if (whoCares == (DialogItemIndex)0) {
		;
	}
	ExitToShell();
#ifndef __clang__
    /*NOTREACHED*/
    exit(0);
#endif /* !__clang__ */
}

/*---------------------------------------------------------  LoadGraphic */

void LoadGraphic(short resID)
{
	Rect		bounds;
	PicHandle	thePicture;
	short		theSizeForThePic;

	thePicture = GetPicture(resID);
	if ((thePicture == NULL) || (thePicture == 0L)) {
		RedAlert((const StringPtr)"\pA Graphic Could NOT Be Loaded");
		/* RedAlert() calls ExitToShell(), so we should be skipping out of
         * here, but clang's static analyzer does not seem to know that: */
#if defined(__clang_analyzer__)
		fprintf(stderr, "LoadGraphic(): Forcing exit due to failure\n");
		exit(1);
#endif /* __clang_analyzer__ */
	}

	HLock((Handle)thePicture);
	printf("LoadGraphic(): Attempting to draw thePicture for resId '%i'...\n",
		   resID);
	bounds = (*thePicture)->picFrame; /* set a breakpoint here to debug */
	theSizeForThePic = (*thePicture)->picSize; /* or here (but not both) */
	printf("LoadGraphic(): thePicture should have size '%i'"
#ifdef _PRINT_GRAPHICS_DEBUGGING_MESSAGES
		   "and the following dimensions:\n"
		   " top:    '%i'\n"
		   " left:   '%i'\n"
		   " bottom: '%i'\n"
		   " right:  '%i'\n"
#endif /* _PRINT_GRAPHICS_DEBUGGING_MESSAGES */
		   "%s",
		   theSizeForThePic,
#ifdef _PRINT_GRAPHICS_DEBUGGING_MESSAGES
		   bounds.top, bounds.left, bounds.bottom, bounds.right,
#endif /* _PRINT_GRAPHICS_DEBUGGING_MESSAGES */
		   "\n");
	HUnlock((Handle)thePicture);
	OffsetRect(&bounds, -bounds.left, -bounds.top);
	DrawPicture(thePicture, &bounds);

	ReleaseResource((Handle)thePicture);
}

/*------------------------------------------------------  ZeroRectCorner */

void ZeroRectCorner(Rect *theRect)		/* Offset rect to (0, 0) */
{
	theRect->right -= theRect->left;
	theRect->bottom -= theRect->top;
	theRect->left = 0;
	theRect->top = 0;
}

/*---------------------------------------------------------  LogNextTick */

void LogNextTick(long howMany)
{
	tickNext = (long)(TickCount() + (UInt32)howMany);
}

/*-----------------------------------------------------  WaitForNextTick */

void WaitForNextTick(void)
{
	if (tickNext > (long)TickCount()) {
		RunCurrentEventLoop((tickNext - (long)TickCount()) / 60.0f);
	}
}
/*-----------------------------------------------  CreateOffScreenPixMap */

void CreateOffScreenPixMap(Rect *theRect, GWorldPtr *offScreen)
{
	if (NewGWorld(offScreen, 0, theRect, 0, GetGDevice(), noNewDevice)) {
		RedAlert((const StringPtr)"\pGWorld could not be successfully created.");
	}
	SetPort(*offScreen); /* HERE */
}

/*-----------------------------------------------  CreateOffScreenBitMap */

void CreateOffScreenBitMap(Rect *theRect, GWorldPtr *offScreen)
{
	if (NewGWorld(offScreen, 0, theRect, 0, GetGDevice(), noNewDevice)) {
		RedAlert((const StringPtr)"\pGWorld could not be successfully created.");
	}
	SetPort(*offScreen); /* HERE */
}

/*---------------------------------------------------------  CenterAlert */

void CenterAlert(short alertID)
{
	AlertTHndl	alertHandle;
	Rect		theScreen, alertRect;
	short		horiOff, vertOff;
	Byte		wasState;
	BitMap		screenBits;

	GetQDGlobalsScreenBits(&screenBits);
	theScreen = screenBits.bounds;
	theScreen.top += 20;

	/* ignore warning about multi-character constant, this is the proper
	 * context to use them in: */
	alertHandle = (AlertTHndl)GetResource('ALRT', alertID);
	if (alertHandle != 0L) {
		wasState = (Byte)HGetState((Handle)alertHandle);
		HLock((Handle)alertHandle);

		alertRect = (**alertHandle).boundsRect;
		OffsetRect(&alertRect, -alertRect.left, -alertRect.top);

		horiOff = (((theScreen.right - theScreen.left) - alertRect.right) / 2);
		vertOff = (((theScreen.bottom - theScreen.top) - alertRect.bottom) / 3);

		OffsetRect(&alertRect, horiOff, (short)(vertOff + 20));

		(**alertHandle).boundsRect = alertRect;
		HSetState((Handle)alertHandle, (SInt8)wasState);
	}
}

/*------------------------------------------------------------  RectWide */

short RectWide(Rect *theRect)
{
	return (theRect->right - theRect->left);
}

/*------------------------------------------------------------  RectTall */

short RectTall(Rect *theRect)
{
	return (theRect->bottom - theRect->top);
}

/*----------------------------------------------------  CenterRectInRect */

void CenterRectInRect(Rect *rectA, Rect *rectB)
{
	short widthA, tallA;

	widthA = RectWide(rectA);
	tallA = RectTall(rectA);

	rectA->left = (rectB->left + (RectWide(rectB) - widthA) / 2);
	rectA->right = rectA->left + widthA;

	rectA->top = (rectB->top + (RectTall(rectB) - tallA) / 2);
	rectA->bottom = (rectA->top + tallA);
}

/*-------------------------------------------------------  PasStringCopy */

void PasStringCopy(StringPtr p1, StringPtr p2)
{
	register short stringLength;

	stringLength = *p2++ = *p1++;
	while (--stringLength >= 0) {
		*p2++ = *p1++;
	}
}

/*--------------------------------------------------------  CenterDialog */

void CenterDialog(short dialogID)
{
	DialogTHndl	dlogHandle;
	Rect		theScreen, dlogBounds;
	short		hPos, vPos;
	Byte		wasState;
	BitMap		screenBits;

	GetQDGlobalsScreenBits(&screenBits);
	theScreen = screenBits.bounds;
	theScreen.top += 20;

	/* ignore warning about multi-character constant, this is the proper
	 * context to use them in: */
	dlogHandle = (DialogTHndl)GetResource('DLOG', dialogID);
	if (dlogHandle != 0L) {
		wasState = (Byte)HGetState((Handle)dlogHandle);
		HLock((Handle)dlogHandle);

		dlogBounds = (**dlogHandle).boundsRect;
		OffsetRect(&dlogBounds, -dlogBounds.left, -dlogBounds.top);

		hPos = (((theScreen.right - theScreen.left) - dlogBounds.right) / 2);
		vPos = (((theScreen.bottom - theScreen.top) - dlogBounds.bottom) / 3);

		OffsetRect(&dlogBounds, hPos, (short)(vPos + 20));

		(**dlogHandle).boundsRect = dlogBounds;
		HSetState((Handle)dlogHandle, (SInt8)wasState);
	}
}

/*---------------------------------------------------  DrawDefaultButton */

void DrawDefaultButton(DialogPtr theDialog)
{
	Rect	itemRect;
	Handle	itemHandle;
	short	itemType;

	GetDialogItem(theDialog, (DialogItemIndex)1, &itemType, &itemHandle,
                  &itemRect);
	InsetRect(&itemRect, (short)-4, (short)-4);
	PenSize((short)3, (short)3);
	FrameRoundRect(&itemRect, (short)16, (short)16);
	PenNormal();
}

/*----------------------------------------------------  PasStringCopyNum */

void PasStringCopyNum(StringPtr p1, StringPtr p2, short charsToCopy)
{
	short i;

	if (charsToCopy > *p1) { /* if trying to copy more chars than there are, */
		charsToCopy = *p1; /* then reduce the number of chars to copy to this size */
	}

	/* 'StringPtr' is an alias for a "pointer to an unsigned char", so
     * since we are looking at what 'p2' is pointing to, just cast to
     * 'unsigned char' instead of 'StringPtr': */
	*p2 = (unsigned char)charsToCopy;

	if (*p2++) {
        ; /* (dummy) */
    }
	if (*p1++) {
        ; /* (dummy) */
    }

	for ((i = 0); (i < charsToCopy); i++) {
		*p2++ = *p1++;
	}
}

/*-----------------------------------------------------  GetDialogString */

void GetDialogString(DialogPtr theDialog, short item, StringPtr theString)
{
	Rect	itemRect;
	Handle	itemHandle;
	short	itemType;

	GetDialogItem(theDialog, (DialogItemIndex)item, &itemType, &itemHandle,
                  &itemRect);
	GetDialogItemText(itemHandle, theString);
}

/*-----------------------------------------------------  SetDialogString */

void SetDialogString(DialogPtr theDialog, short item, StringPtr theString)
{
	Rect	itemRect;
	Handle	itemHandle;
	short	itemType;

	GetDialogItem(theDialog, (DialogItemIndex)item, &itemType, &itemHandle,
                  &itemRect);
	SetDialogItemText(itemHandle, theString);
}

/*---------------------------------------------------  SetDialogNumToStr */

void SetDialogNumToStr(DialogPtr theDialog, short item, long theNumber)
{
	Str255	theString;
	Rect	itemRect;
	Handle	itemHandle;
	short	itemType;

	NumToString(theNumber, theString);
	GetDialogItem(theDialog, (DialogItemIndex)item, &itemType, &itemHandle,
                  &itemRect);
	SetDialogItemText(itemHandle, theString);
}

/*-------------------------------------------------  GetDialogNumFromStr */

void GetDialogNumFromStr(DialogPtr theDialog, short item, long *theNumber)
{
	Str255	theString;
	Rect	itemRect;
	Handle	itemHandle;
	short	itemType;

	GetDialogItem(theDialog, (DialogItemIndex)item, &itemType, &itemHandle,
                  &itemRect);
	GetDialogItemText(itemHandle, theString);
	StringToNum(theString, theNumber);
}

/*------------------------------------------------------  DisableControl */

void CustomDisableControl(DialogPtr theDialog, short whichItem)
{
	Rect	iRect;
	Handle	iHandle;
	short	iType;

	GetDialogItem(theDialog, (DialogItemIndex)whichItem, &iType, &iHandle,
                  &iRect);
	HiliteControl((ControlHandle)iHandle, (ControlPartCode)kInactive);
}

#ifdef kActive
# undef kActive
#endif /* kActive */

/* EOF */
