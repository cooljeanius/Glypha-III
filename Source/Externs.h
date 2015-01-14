
/*=========================================================================
 *-------------------------------------------------------------------------
 *									Externs.h
 *-------------------------------------------------------------------------
 *=========================================================================
 */

#ifndef __GLYPHA_III_EXTERNS_H__
#define __GLYPHA_III_EXTERNS_H__ 1

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif /* HAVE_CONFIG_H */

#if (defined(__x86_64) || defined(__x86_64__)) && !defined(TARGET_CPU_X86)
# define TARGET_CPU_X86 64
#endif /* (__x86_64 || __x86_64__) && !TARGET_CPU_X86 */
#if (defined(__ppc64) || defined(__ppc64__)) && !defined(TARGET_CPU_PPC)
# define TARGET_CPU_PPC 64
#endif /* (__ppc64 || __ppc64__) && !TARGET_CPU_PPC */
#ifndef SIGDIGLEN
# define SIGDIGLEN 36 /* what it is for TARGET_CPU_PPC || TARGET_CPU_X86 */
#endif /* !SIGDIGLEN */
#if defined(__LP64__) && !defined(__LP64_SAVED__) && 0
# define __LP64_SAVED__ 1
# undef __LP64__
# ifdef __MACHINEEXCEPTIONS__
#  undef __MACHINEEXCEPTIONS__ /* just so we can re-define it */
# endif /* __MACHINEEXCEPTIONS__ */
# define __MACHINEEXCEPTIONS__ 1
# ifndef AreaID
/* Some basic declarations used throughout the kernel */
typedef struct OpaqueAreaID* AreaID;
# endif /* !AreaID */
#endif /* __LP64__ && !__LP64_SAVED__ && !TARGET_CPU_X86 */

#if !defined(__MWERKS__) || defined(HAVE_CARBON_CARBON_H)
# include <Carbon/Carbon.h>
#else
# if defined(__MWERKS__) || defined(HAVE_CARBON_H)
#  include <Carbon.h>
# else
#  error "cannot figure out how to include proper Carbon umbrella header."
# endif /* __MWERKS__ || HAVE_CARBON_H */
#endif /* !__MWERKS__ || HAVE_CARBON_CARBON_H */

#if defined(__LP64_SAVED__) && !defined(__LP64__)
# define __LP64__ 1
#endif /* __LP64_SAVED__ && !__LP64__ */

#ifndef __LP64__
# pragma options align=mac68k
#endif /* !__LP64__ */

#ifndef ATTRIBUTE_NORETURN
# define ATTRIBUTE_NORETURN __attribute__ ((__noreturn__))
#endif /* ATTRIBUTE_NORETURN */

/*
 * FIXME:
 * When compiling with Xcode 3.2.6 (gcc-4.2) on Snow Leopard, there are
 * warnings that the following headers indirectly included by
 * <Carbon/Carbon.h> use deprecated APIs:
 *
 * - CarbonCore/Files.h
 * - CarbonCore/MacMemory.h
 * - CarbonCore/OSUtils.h
 * - CarbonSound/Sound.h
 * - HIToolbox/Events.h
 * - HIToolbox/MacWindows.h
 * - HIToolbox/Menus.h
 * - QD/QuickdrawAPI.h
 *
 * TODO: either move to non-deprecated APIs, or restrict the maximum OS
 * version that this can be built on. In the meantime...
 */
/* these things are not normally available for 64-bit, so copy them here
 * manually */
#if defined(__LP64__) && __LP64__
/* from CarbonCore/Files.h: */
# if !defined(__FILES__) || (defined(MAC_OS_X_VERSION_MIN_REQUIRED) && (MAC_OS_X_VERSION_MIN_REQUIRED >= MAC_OS_X_VERSION_10_5))
struct HFileParam {
	QElemPtr        qLink;        /* queue link in header */
	SInt16          qType;        /* type byte for safety check */
	SInt16          ioTrap;       /* FS: the Trap */
	Ptr             ioCmdAddr;    /* FS: address to dispatch to */
	IOCompletionUPP ioCompletion; /* completion routine addr (0 for synch calls) */
	volatile OSErr  ioResult;     /* result code */
	StringPtr       ioNamePtr;    /* ptr to Vol:FileName string */
	FSVolumeRefNum  ioVRefNum; /* volume refnum (DrvNum for Eject and MountVol) */
	FSIORefNum      ioFRefNum;
	SInt8           ioFVersNum;
	SInt8           filler1;
	SInt16          ioFDirIndex;
	SInt8           ioFlAttrib;
	SInt8           ioFlVersNum;
	FInfo           ioFlFndrInfo;
	SInt32          ioDirID;
	UInt16          ioFlStBlk;
	SInt32          ioFlLgLen;
	SInt32          ioFlPyLen;
	UInt16          ioFlRStBlk;
	SInt32          ioFlRLgLen;
	SInt32          ioFlRPyLen;
	UInt32          ioFlCrDat;
	UInt32          ioFlMdDat;
};
typedef struct HFileParam HFileParam;
struct HIOParam {
	QElemPtr        qLink;        /* queue link in header */
	short           qType;        /* type byte for safety check */
	short           ioTrap;       /* FS: the Trap */
	Ptr             ioCmdAddr;    /* FS: address to dispatch to */
	IOCompletionUPP ioCompletion; /* completion routine addr (0 for synch calls) */
	volatile OSErr  ioResult;     /* result code */
	StringPtr       ioNamePtr;    /* ptr to Vol:FileName string */
	short           ioVRefNum; /* volume refnum (DrvNum for Eject and MountVol) */
	short           ioRefNum;
	SInt8           ioVersNum;
	SInt8           ioPermssn;
	Ptr             ioMisc;
	Ptr             ioBuffer;
	long            ioReqCount;
	long            ioActCount;
	short           ioPosMode;
	long            ioPosOffset;
};
typedef struct HIOParam HIOParam;
struct HVolumeParam {
	QElemPtr        qLink;        /* queue link in header */
	short           qType;        /* type byte for safety check */
	short           ioTrap;       /* FS: the Trap */
	Ptr             ioCmdAddr;    /* FS: address to dispatch to */
	IOCompletionUPP ioCompletion; /* completion routine addr (0 for synch calls) */
	volatile OSErr  ioResult;     /* result code */
	StringPtr       ioNamePtr;    /* ptr to Vol:FileName string */
	short           ioVRefNum; /* volume refnum (DrvNum for Eject and MountVol) */
	long            filler2;
	short           ioVolIndex;
	unsigned long   ioVCrDate;
	unsigned long   ioVLsMod;
	short           ioVAtrb;
	unsigned short  ioVNmFls;
	unsigned short  ioVBitMap;
	unsigned short  ioAllocPtr;
	unsigned short  ioVNmAlBlks;
	unsigned long   ioVAlBlkSiz;
	unsigned long   ioVClpSiz;
	unsigned short  ioAlBlSt;
	unsigned long   ioVNxtCNID;
	unsigned short  ioVFrBlk;
	unsigned short  ioVSigWord;
	short           ioVDrvInfo;
	short           ioVDRefNum;
	short           ioVFSID;
	unsigned long   ioVBkUp;
	short           ioVSeqNum;
	unsigned long   ioVWrCnt;
	unsigned long   ioVFilCnt;
	unsigned long   ioVDirCnt;
	long            ioVFndrInfo[8];
};
typedef struct HVolumeParam HVolumeParam;
struct AccessParam {
	QElemPtr        qLink;        /*queue link in header*/
	short           qType;        /*type byte for safety check*/
	short           ioTrap;       /*FS: the Trap*/
	Ptr             ioCmdAddr;    /*FS: address to dispatch to*/
	IOCompletionUPP ioCompletion; /*completion routine addr (0 for synch calls)*/
	volatile OSErr  ioResult;     /*result code*/
	StringPtr       ioNamePtr;    /*ptr to Vol:FileName string*/
	short           ioVRefNum; /*volume refnum (DrvNum for Eject and MountVol)*/
	short           ioRefNum;     /* <- , ioRefNum ( use to be filler3 ) */
	short           ioDenyModes; /*access rights data*/
	short           filler4;
	SInt8           filler5;
	SInt8           ioACUser;     /*access rights for directory only*/
	long            filler6;
	long            ioACOwnerID;  /*owner ID*/
	long            ioACGroupID;  /*group ID*/
	long            ioACAccess;   /*access rights*/
	long            ioDirID;
};
typedef struct AccessParam AccessParam;
struct ObjParam {
	QElemPtr        qLink;        /*queue link in header*/
	short           qType;        /*type byte for safety check*/
	short           ioTrap;       /*FS: the Trap*/
	Ptr             ioCmdAddr;    /*FS: address to dispatch to*/
	IOCompletionUPP ioCompletion; /*completion routine addr (0 for synch calls)*/
	volatile OSErr  ioResult;     /*result code*/
	StringPtr       ioNamePtr;    /*ptr to Vol:FileName string*/
	short           ioVRefNum; /*volume refnum (DrvNum for Eject and MountVol)*/
	short           filler7;
	short           ioObjType;    /*function code*/
	StringPtr       ioObjNamePtr; /*ptr to returned creator/group name*/
	long            ioObjID;      /*creator/group ID*/
};
typedef struct ObjParam                 ObjParam;
struct CopyParam {
	QElemPtr        qLink;        /*queue link in header*/
	short           qType;        /*type byte for safety check*/
	short           ioTrap;       /*FS: the Trap*/
	Ptr             ioCmdAddr;    /*FS: address to dispatch to*/
	IOCompletionUPP ioCompletion; /*completion routine addr (0 for synch calls)*/
	volatile OSErr  ioResult;     /*result code*/
	StringPtr       ioNamePtr;    /*ptr to Vol:FileName string*/
	short           ioVRefNum; /*volume refnum (DrvNum for Eject and MountVol)*/
	short           ioDstVRefNum; /*destination vol identifier*/
	short           filler8;
	StringPtr       ioNewName;    /*ptr to destination pathname*/
	StringPtr       ioCopyName;   /*ptr to optional name*/
	long            ioNewDirID;   /*destination directory ID*/
	long            filler14;
	long            filler15;
	long            ioDirID;
};
typedef struct CopyParam CopyParam;
struct WDParam {
	QElemPtr        qLink;        /*queue link in header*/
	short           qType;        /*type byte for safety check*/
	short           ioTrap;       /*FS: the Trap*/
	Ptr             ioCmdAddr;    /*FS: address to dispatch to*/
	IOCompletionUPP ioCompletion; /*completion routine addr (0 for synch calls)*/
	volatile OSErr  ioResult;     /*result code*/
	StringPtr       ioNamePtr;    /*ptr to Vol:FileName string*/
	short           ioVRefNum; /*volume refnum (DrvNum for Eject and MountVol)*/
	short           ioWDCreated;
	short           ioWDIndex;
	long            ioWDProcID;
	short           ioWDVRefNum;
	short           filler10;
	long            filler11;
	long            filler12;
	long            filler13;
	long            ioWDDirID;
};
typedef struct WDParam                  WDParam;
struct FIDParam {
	QElemPtr        qLink;         /*queue link in header*/
	short           qType;         /*type byte for safety check*/
	short           ioTrap;        /*FS: the Trap*/
	Ptr             ioCmdAddr;     /*FS: address to dispatch to*/
	IOCompletionUPP ioCompletion;  /*completion routine addr (0 for synch calls)*/
	volatile OSErr  ioResult;      /*result code*/
	StringPtr       ioNamePtr;     /*ptr to Vol:FileName string*/
	short           ioVRefNum; /*volume refnum (DrvNum for Eject and MountVol)*/
	long            filler14;
	StringPtr       ioDestNamePtr; /* dest file name */
	long            filler15;
	long            ioDestDirID;   /* dest file's directory id */
	long            filler16;
	long            filler17;
	long            ioSrcDirID;    /* source file's directory id */
	short           filler18;
	long            ioFileID;      /* file ID */
};
typedef struct FIDParam FIDParam;
struct ForeignPrivParam {
	QElemPtr        qLink;        /*queue link in header*/
	short           qType;        /*type byte for safety check*/
	short           ioTrap;       /*FS: the Trap*/
	Ptr             ioCmdAddr;    /*FS: address to dispatch to*/
	IOCompletionUPP ioCompletion; /*completion routine addr (0 for synch calls)*/
	volatile OSErr  ioResult;     /*result code*/
	StringPtr       ioNamePtr;    /*ptr to Vol:FileName string*/
	short           ioVRefNum; /*volume refnum (DrvNum for Eject and MountVol)*/
	long            ioFiller21;
	long            ioFiller22;
	Ptr             ioForeignPrivBuffer;
	long            ioForeignPrivActCount;
	long            ioForeignPrivReqCount;
	long            ioFiller23;
	long            ioForeignPrivDirID;
	long            ioForeignPrivInfo1;
	long            ioForeignPrivInfo2;
	long            ioForeignPrivInfo3;
	long            ioForeignPrivInfo4;
};
typedef struct ForeignPrivParam         ForeignPrivParam;
struct HFileInfo {
	QElemPtr        qLink;        /*queue link in header*/
	short           qType;        /*type byte for safety check*/
	short           ioTrap;       /*FS: the Trap*/
	Ptr             ioCmdAddr;    /*FS: address to dispatch to*/
	IOCompletionUPP ioCompletion; /*completion routine addr (0 for synch calls)*/
	volatile OSErr  ioResult;     /*result code*/
	StringPtr       ioNamePtr;    /*ptr to Vol:FileName string*/
	short           ioVRefNum; /*volume refnum (DrvNum for Eject and MountVol)*/
	short           ioFRefNum;
	SInt8           ioFVersNum;
	SInt8           filler1;
	short           ioFDirIndex;
	SInt8           ioFlAttrib;
	SInt8           ioACUser;
	FInfo           ioFlFndrInfo;
	long            ioDirID;
	unsigned short  ioFlStBlk;
	long            ioFlLgLen;
	long            ioFlPyLen;
	unsigned short  ioFlRStBlk;
	long            ioFlRLgLen;
	long            ioFlRPyLen;
	unsigned long   ioFlCrDat;
	unsigned long   ioFlMdDat;
	unsigned long   ioFlBkDat;
	FXInfo          ioFlXFndrInfo;
	long            ioFlParID;
	long            ioFlClpSiz;
};
typedef struct HFileInfo                HFileInfo;
struct DirInfo {
	QElemPtr        qLink;        /*queue link in header*/
	short           qType;        /*type byte for safety check*/
	short           ioTrap;       /*FS: the Trap*/
	Ptr             ioCmdAddr;    /*FS: address to dispatch to*/
	IOCompletionUPP ioCompletion; /*completion routine addr (0 for synch calls)*/
	volatile OSErr  ioResult;     /*result code*/
	StringPtr       ioNamePtr;    /*ptr to Vol:FileName string*/
	short           ioVRefNum; /*volume refnum (DrvNum for Eject and MountVol)*/
	short           ioFRefNum;
	SInt8           ioFVersNum;
	SInt8           filler1;
	short           ioFDirIndex;
	SInt8           ioFlAttrib;
	SInt8           ioACUser;
	DInfo           ioDrUsrWds;
	long            ioDrDirID;
	unsigned short  ioDrNmFls;
	short           filler3[9];
	unsigned long   ioDrCrDat;
	unsigned long   ioDrMdDat;
	unsigned long   ioDrBkDat;
	DXInfo          ioDrFndrInfo;
	long            ioDrParID;
};
typedef struct DirInfo DirInfo;
union CInfoPBRec {
	HFileInfo           hFileInfo;
	DirInfo             dirInfo;
};
typedef union CInfoPBRec                CInfoPBRec;
typedef CInfoPBRec *                    CInfoPBPtr;
struct CSParam {
	QElemPtr        qLink;           /*queue link in header*/
	short           qType;           /*type byte for safety check*/
	short           ioTrap;          /*FS: the Trap*/
	Ptr             ioCmdAddr;       /*FS: address to dispatch to*/
	IOCompletionUPP ioCompletion; /*completion routine addr (0 for synch calls)*/
	volatile OSErr  ioResult;        /*result code*/
	StringPtr       ioNamePtr;       /*ptr to Vol:FileName string*/
	short           ioVRefNum; /*volume refnum (DrvNum for Eject and MountVol)*/
	FSSpecPtr       ioMatchPtr;      /* match array */
	long            ioReqMatchCount; /* maximum allowable matches */
	long            ioActMatchCount; /* actual match count */
	long            ioSearchBits;    /* search criteria selector */
	CInfoPBPtr      ioSearchInfo1; /* search values and range lower bounds */
	CInfoPBPtr      ioSearchInfo2; /* search values and range upper bounds */
	long            ioSearchTime;    /* length of time to run search */
	CatPositionRec  ioCatPosition;   /* current position in the catalog */
	Ptr             ioOptBuffer; /* optional performance enhancement buffer */
	long            ioOptBufSize; /* size of buffer pointed to by ioOptBuffer */
};
typedef struct CSParam CSParam;
union HParamBlockRec {
	HIOParam            ioParam;
	HFileParam          fileParam;
	HVolumeParam        volumeParam;
	AccessParam         accessParam;
	ObjParam            objParam;
	CopyParam           copyParam;
	WDParam             wdParam;
	FIDParam            fidParam;
	CSParam             csParam;
	ForeignPrivParam    foreignPrivParam;
};
typedef union HParamBlockRec HParamBlockRec;
typedef HParamBlockRec *HParmBlkPtr;
# endif /* !__FILES__ || 10.5+ */
/* from CarbonSound/Sound.h: */
# if !defined(__SOUND__)
struct SndCommand {
	unsigned short cmd;
	short          param1;
	long           param2;
};
typedef struct SndCommand SndCommand;
typedef struct SndChannel SndChannel;
typedef SndChannel *SndChannelPtr;
#  if !defined(CALLBACK_API)
#   define CALLBACK_API(_type, _name)  _type(* _name)
#  endif /* !CALLBACK_API */
typedef CALLBACK_API(void, SndCallBackProcPtr)(SndChannelPtr chan, SndCommand *cmd);
#  if !defined(STACK_UPP_TYPE)
#   define STACK_UPP_TYPE(name) name
#  endif /* !STACK_UPP_TYPE */
typedef STACK_UPP_TYPE(SndCallBackProcPtr) SndCallBackUPP;
/* command numbers for SndDoCommand() and SndDoImmediate(): */
enum {
	nullCmd                = 0,
	quietCmd               = 3,
	flushCmd               = 4,
	reInitCmd              = 5,
	waitCmd                = 10,
	pauseCmd               = 11,
	resumeCmd              = 12,
	callBackCmd            = 13,
	syncCmd                = 14,
	availableCmd           = 24,
	versionCmd             = 25,
	volumeCmd              = 46,   /* sound manager 3.0 or later only */
	getVolumeCmd           = 47,   /* sound manager 3.0 or later only */
	clockComponentCmd      = 50,   /* sound manager 3.2.1 or later only */
	getClockComponentCmd   = 51,   /* sound manager 3.2.1 or later only */
	scheduledSoundCmd      = 52,   /* sound manager 3.3 or later only */
	linkSoundComponentsCmd = 53,   /* sound manager 3.3 or later only */
	soundCmd               = 80,
	bufferCmd              = 81,
	rateMultiplierCmd      = 86,
	getRateMultiplierCmd   = 87
};
/* synthesizer numbers for SndNewChannel(): */
enum {
	sampledSynth           = 5     /* sampled sound synthesizer */
};
enum {
	initChanLeft           = 0x0002, /* left stereo channel */
	initChanRight          = 0x0003, /* right stereo channel */
	initNoInterp           = 0x0004, /* no linear interpolation */
	initNoDrop             = 0x0008, /* no drop-sample conversion */
	initMono               = 0x0080, /* monophonic channel */
	initStereo             = 0x00C0, /* stereo channel */
	initMACE3              = 0x0300, /* MACE 3:1 */
	initMACE6              = 0x0400, /* MACE 6:1 */
	initPanMask            = 0x0003, /* mask for right/left pan values */
	initSRateMask          = 0x0030, /* mask for sample rate values */
	initStereoMask         = 0x00C0, /* mask for mono/stereo values */
	initCompMask           = 0xFF00  /* mask for compression IDs */
};
# endif /* !__SOUND__ */
/* from QD/QuickdrawTypes.h, or QD/Quickdraw.h, depending on SDK: */
# if !defined(__QUICKDRAWTYPES__) && !defined(__QUICKDRAW__)
enum {
	blackColor             = 33,   /* colors expressed in these mappings */
	whiteColor             = 30,
	redColor               = 205,
	greenColor             = 341,
	blueColor              = 409,
	cyanColor              = 273,
	magentaColor           = 137,
	yellowColor            = 69
};
# endif /* !__QUICKDRAWTYPES__ && !__QUICKDRAW__ */
/* from HIToolbox/Menus.h: */
# if !OPAQUE_TOOLBOX_STRUCTS
struct MenuInfo {
	MenuID menuID;      /* in Carbon use Get/SetMenuID*/
	short  menuWidth;   /* in Carbon use Get/SetMenuWidth*/
	short  menuHeight;  /* in Carbon use Get/SetMenuHeight*/
	Handle menuProc;    /* not supported in Carbon*/
	long   enableFlags; /* in Carbon use Enable/DisableMenuItem, IsMenuItemEnable*/
	Str255 menuData;    /* in Carbon use Get/SetMenuTitle*/
};
typedef struct MenuInfo MenuInfo;
typedef MenuInfo *MenuPtr;
typedef MenuPtr *MenuHandle;
# else
typedef struct OpaqueMenuRef* MenuRef;
/* MenuHandle is old name for MenuRef: */
typedef MenuRef MenuHandle;
# endif  /* !OPAQUE_TOOLBOX_STRUCTS */
#endif /* __LP64__ */
/* do prototypes that are not normally available for 64-bit in a separate
 * ifdef, because prototypes are a __STDC__ thing: */
#if defined(__LP64__) && __LP64__ && defined(__STDC__) && (__STDC__)
/* (the check against '__STDC__' should really be against the value that
 * '__STDC_VERSION__' has when compiling for C99) */
# if !defined(CopyBits)
extern void CopyBits(const BitMap *srcBits, const BitMap *dstBits,
					 const Rect *srcRect, const Rect *dstRect, short mode,
					 RgnHandle maskRgn);
# endif /* !CopyBits */
extern const BitMap *GetPortBitMapForCopyBits(CGrafPtr port);
extern CGrafPtr GetWindowPort(WindowRef window);
extern void QDFlushPortBuffer(CGrafPtr port, RgnHandle region);
extern void MacSetPort(GrafPtr port);
extern WindowRef GetNewWindow(short windowID, void *wStorage, WindowRef behind);
extern DialogRef GetNewDialog(SInt16 dialogID, void *dStorage, WindowRef behind);
# if defined(TARGET_OS_MAC) && TARGET_OS_MAC && !defined(MacGetMenu)
#  define MacGetMenu GetMenu
# endif /* TARGET_OS_MAC */
extern MenuRef MacGetMenu(short resourceID);
extern void MoveTo(short h, short v);
extern RgnHandle NewRgn(void);
extern PicHandle GetPicture(short pictureID);
# if defined(TARGET_OS_MAC) && TARGET_OS_MAC && !defined(MacSetPort)
#  define MacSetPort SetPort
# endif /* TARGET_OS_MAC */
extern void MacSetPort(GrafPtr port);
extern void PaintRect(const Rect * r);
extern void GetForeColor(RGBColor * color);
extern void TextFont(short font);
extern void TextSize(short size);
extern void TextFace(StyleParameter face);
extern void Index2Color(long index, RGBColor *aColor);
extern void RGBForeColor(const RGBColor *color);
extern void DrawString(ConstStr255Param s);
extern void NumToString(long theNum, Str255 theString);
extern short StringWidth(ConstStr255Param s);
extern void SetPortWindowPort(WindowRef window);
extern void PenSize(short width, short height);
extern void PenMode(short mode);
# if defined(TARGET_OS_MAC) && TARGET_OS_MAC && !defined(MacLineTo)
#  define MacLineTo LineTo
# endif /* TARGET_OS_MAC */
extern void MacLineTo(short h, short v);
extern void PenNormal(void);
extern void CopyMask(const BitMap *srcBits, const BitMap *maskBits,
					 const BitMap *dstBits, const Rect *srcRect,
					 const Rect *maskRect, const Rect *dstRect);
extern void SysBeep(short duration);
extern void GetIndString(Str255 theString, short strListID, short index);
# if defined(__FILES__)
extern OSErr PBDirCreateAsync(HParmBlkPtr paramBlock);
extern OSErr PBDirCreateSync(HParmBlkPtr paramBlock);
# endif /* __FILES__ */
extern void DisableMenuItem(MenuRef theMenu, MenuItemIndex item);
# if defined(TARGET_OS_MAC) && TARGET_OS_MAC && !defined(MacEnableMenuItem)
#  define MacEnableMenuItem EnableMenuItem
# endif /* TARGET_OS_MAC */
extern void MacEnableMenuItem(MenuRef theMenu, MenuItemIndex item);
# if defined(TARGET_OS_MAC) && TARGET_OS_MAC && !defined(MacCheckMenuItem)
#  define MacCheckMenuItem CheckMenuItem
# endif /* TARGET_OS_MAC */
extern void MacCheckMenuItem(MenuRef theMenu, MenuItemIndex item,
							 Boolean checked);
# if defined(TARGET_OS_MAC) && TARGET_OS_MAC && !defined(MacShowCursor)
#  define MacShowCursor ShowCursor
# endif /* TARGET_OS_MAC */
extern void MacShowCursor(void);
extern void ObscureCursor(void);
extern void SetMenuItemText(MenuRef theMenu, MenuItemIndex item,
							ConstStr255Param itemString);
extern void SetItemCmd(MenuRef theMenu, MenuItemIndex item,
					   CharParameter cmdChar);
extern void HiliteMenu(MenuID menuID);
extern BitMap *GetQDGlobalsScreenBits(BitMap * screenBits);
# if defined(TARGET_OS_MAC) && TARGET_OS_MAC && !defined(MacFindWindow)
#  define MacFindWindow FindWindow
# endif /* TARGET_OS_MAC */
extern WindowPartCode MacFindWindow(Point thePoint, WindowRef *window);
extern long MenuSelect(Point startPt);
extern void DragWindow(WindowRef window, Point startPt, const Rect *boundsRect);
extern void GlobalToLocal(Point *pt);
extern long MenuKey(CharParameter ch);
extern void BeginUpdate(WindowRef window);
extern void EndUpdate(WindowRef window);
extern Boolean WaitNextEvent(EventMask eventMask, EventRecord *theEvent,
							 UInt32 eventSleep, RgnHandle mouseRgn);
#endif /* __LP64__ && __STDC__ */

/*-------------------------------------------------------------  Defines */
#define	kPutInFront			(WindowPtr)-1L
#define	kNormalUpdates		TRUE

#define kHelpKeyASCII		0x05
#define kPageUpKeyASCII		0x0B
#define kPageDownKeyASCII	0x0C
#define	kUpArrowKeyASCII	0x1E
#define kDownArrowKeyASCII	0x1F


#define kDownArrowKeyMap	122		/* key map offset for down arrow */
#define kRightArrowKeyMap	123		/* key map offset for right arrow */
#define kLeftArrowKeyMap	124		/* key map offset for left arrow */

#define kAKeyMap			7
#define	kEKeyMap			9
#define	kPKeyMap			36
#define	kQKeyMap			11
#define kSKeyMap			6
#define kColonMap			0x2E
#define kQuoteMap			0x20
#define	kCommandKeyMap		48
#define	kEscKeyMap			50
#define kSpaceBarMap		54

/* defines ending in "Priority" get an extra tab so that they align
 * separately from the ones ending in "Sound": */
#define kBirdSound			1
#define kBirdPriority			80
#define kBonusSound			2
#define kBonusPriority			85
#define kBoom1Sound			3
#define kBoom1Priority			115
#define kBoom2Sound			4
#define kBoom2Priority			110
#define kSplashSound		5
#define kSplashPriority			75
#define kFlapSound			6
#define kFlapPriority			70
#define kGrateSound			8
#define kGratePriority			40
#define kLightningSound		9
#define kLightningPriority		100
#define kMusicSound			10
#define kMusicPriority			120
#define kScreechSound		12
#define kScreechPriority		50
#define kSpawnSound			13
#define kSpawnPriority			90
#define kWalkSound			14
#define kWalkPriority			30
#define kFlap2Sound			15
#define kFlap2Priority			20
#define kScrape2Sound		16
#define kScrape2Priority		10

#define kLavaHeight			456
#define kRoofHeight			2
#define kGravity			4

#define kIdle				-1	/* enemy & player mode */
#define kFlying				0	/* enemy & player mode */
#define kWalking			1	/* enemy & player mode */
#define kSinking			2	/* player mode */
#define kSpawning			3	/* enemy mode */
#define kFalling			4	/* enemy mode & player mode */
#define kEggTimer			5	/* enemy mode */
#define kDeadAndGone		6	/* enemy mode */
#define kBones				7	/* player mode */
#define kLurking			10	/* hand mode */
#define kOutGrabeth			11	/* hand mode */
#define kClutching			12	/* hand mode */
#define kWaiting			15	/* eye mode */
#define kStalking			16	/* eye mode */


#define kInitNumLives		5
#define kMaxEnemies			8
#define kDontFlapVel		8

#define kOwl				0
#define kWolf				1
#define kJackal				2

#define iQuit				5
#define iSoundItem			7


/*-------------------------------------------------------------  Structs */

/* playerType */
typedef struct
{
	Rect	dest, wasDest, wrap;
	short	h, v;
	short	wasH, wasV;
	short	hVel, vVel;
	short	srcNum, mode;
	short	frame;
	Boolean	facingRight, flapping;
	Boolean	walking, wrapping;
	Boolean	clutched;
    char    padding; /* 1 byte */
} playerType;

/* enemyType */
typedef struct
{
	Rect	dest, wasDest;
	short	h, v;
	short	wasH, wasV;
	short	hVel, vVel;
	short	srcNum, mode;
	short	kind, frame;
	short	heightSmell, targetAlt;
	short	flapImpulse, pass;
	short	maxHVel, maxVVel;
	Boolean	facingRight;
    char    padding; /* 1 byte */
} enemyType;

/* handInfo */
typedef struct
{
	Rect	dest;
	short	mode;
} handInfo;

/* eyeInfo */
typedef struct
{
	Rect	dest;
	short	mode, opening;
	short	srcNum, frame;
	Boolean	killed, entering;
} eyeInfo;

/* prefsInfo */
typedef struct
{
	short	prefVersion, filler;
	Str255	highName;
	Str15	highNames[10];
	long	highScores[10];
	short	highLevel[10];
	Boolean	soundOff;
    char    padding; /* 1 byte */
} prefsInfo;

/*----------------------------------------------------------  Prototypes */


/* The following prototypes are for functions from Enemy.c */
void GenerateEnemies(void);
void MoveEnemies(void);
void InitHandLocation(void);
void HandleHand(void);
void InitEye(void);
void KillOffEye(void);
void HandleEye(void);
void CheckPlayerEnemyCollision(void);

/* The following prototypes are for functions from Graphics.c */
void DrawPlatforms(short);
void ScrollHelp(short);
void OpenHelp(void);
void CloseWall(void);
void OpenHighScores(void);
void UpdateLivesNumbers(void);
void UpdateScoreNumbers(void);
void UpdateLevelNumbers(void);
void GenerateLightning(short h, short v);
void FlashObelisks(Boolean);
void StrikeLightning(void);
void DumpBackToWorkMap(void);
void DumpMainToWorkMap(void);
void AddToUpdateRects(Rect *);
void DrawTorches(void);
void CopyAllRects(void);
void DrawFrame(void);

/* The following prototypes are for functions from Interface.c */
void MenusReflectMode(void);
void DoMenuChoice(long);
void HandleEvent(void);

/* The following prototypes are for functions from Play.c */
void InitNewGame(void);
void PlayGame(void);

/* The following prototypes are for functions from Prefs.c */
Boolean SavePrefs(prefsInfo *, short);
Boolean LoadPrefs(prefsInfo *, short);

/* The following prototypes are for functions from SetUpTakeDown.c */
void OpenMainWindow(void);
void InitMenubar(void);
void InitVariables(void);
void ShutItDown(void);

/* The following prototypes are for functions from Sound.c */
void PlayExternalSound(short, short);
void InitSound(void);
void KillSound(void);

/* The following prototypes are for functions from Utilities.c */
short RandomInt(short);
void RedAlert(const StringPtr);
void LoadGraphic(short);
void CreateOffScreenPixMap(Rect *, GWorldPtr *);
void CreateOffScreenBitMap(Rect *, GWorldPtr *);
void ZeroRectCorner(Rect *);
void LogNextTick(long);
void WaitForNextTick(void);
Boolean DoWeHaveGestalt(void);
void CenterAlert(short);
short RectWide(Rect *);
short RectTall(Rect *);
void CenterRectInRect(Rect *, Rect *);
void PasStringCopy(StringPtr, StringPtr);
void CenterDialog(short);
void DrawDefaultButton(DialogPtr);
void PasStringCopyNum(StringPtr, StringPtr, short);
void GetDialogString(DialogPtr, short, StringPtr);
void SetDialogString(DialogPtr, short, StringPtr);
void SetDialogNumToStr(DialogPtr, short, long );
void GetDialogNumFromStr(DialogPtr, short, long *);
void CustomDisableControl(DialogPtr, short);

#ifndef __LP64__
# pragma options align=reset
#endif /* !__LP64__ */
#endif /* __GLYPHA_III_EXTERNS_H__ */

/* EOF */
