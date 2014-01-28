/*
mvh 20001106: Use memcpy instead of ByteCopy
ljz 20001128: Removed two warnings
ljz 20030122: Fixed initialization of AAssociateRQ
mvh 20060618: Added definition of min()
mvh 20080203: Added experimental ConfigPadAEWithZeros
ljz 20080313: Removed some warnings
bcb 20100619: Fix gcc4 warnings and improve speed.
mvh 20100717: Merged
*/

/****************************************************************************
          Copyright (C) 1995, University of California, Davis

          THIS SOFTWARE IS MADE AVAILABLE, AS IS, AND THE UNIVERSITY
          OF CALIFORNIA DOES NOT MAKE ANY WARRANTY ABOUT THE SOFTWARE, ITS
          PERFORMANCE, ITS MERCHANTABILITY OR FITNESS FOR ANY PARTICULAR
          USE, FREEDOM FROM ANY COMPUTER DISEASES OR ITS CONFORMITY TO ANY
          SPECIFICATION. THE ENTIRE RISK AS TO QUALITY AND PERFORMANCE OF
          THE SOFTWARE IS WITH THE USER.

          Copyright of the software and supporting documentation is
          owned by the University of California, and free access
          is hereby granted as a license to use this software, copy this
          software and prepare derivative works based upon this software.
          However, any distribution of this software source code or
          supporting documentation or derivative works (source code and
          supporting documentation) must include this copyright notice.
****************************************************************************/

/***************************************************************************
 *
 * University of California, Davis
 * UCDMC DICOM Network Transport Libraries
 * Version 0.1 Beta
 *
 * Technical Contact: mhoskin@ucdavis.edu
 *
 ***************************************************************************/

#	include	"dicom.hpp"

#ifndef min
#define min(a, b) ((a)<(b)?(a):(b))
#endif

/*************************************************************************
 *
 * Application Context Class
 *
 ************************************************************************/
ApplicationContext	::	ApplicationContext()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x10),
Reserved1(0),
Length(0),
ApplicationContextName() {}
#else
	{
	ItemType = 0x10;
	Reserved1 = 0;
	}
#endif

ApplicationContext	::	ApplicationContext(UID	&uid)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x10),
Reserved1(0),
Length(0),
ApplicationContextName()
	{
#else
	{
	ItemType = 0x10;
	Reserved1 = 0;
#endif
	ApplicationContextName = uid;
	}

ApplicationContext	:: ApplicationContext(BYTE	*name)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x10),
Reserved1(0),
Length(0),
ApplicationContextName()
	{
#else
	{
	ItemType = 0x10;
	Reserved1 = 0;
#endif
	ApplicationContextName.Set(name);
	}

ApplicationContext	::	~ApplicationContext()
	{
	// nothing to de-allocate specifically

	}

void	ApplicationContext	::	Set(UID	&uid)
	{
	ApplicationContextName = uid;
	}

void	ApplicationContext	::	Set(BYTE	*name)
	{
	ApplicationContextName.Set(name);
	}

BOOL	ApplicationContext	::	Write(Buffer	&Link)
	{
	Link << ItemType;	//Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link << Reserved1;	//Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;		//Link.Write((BYTE *) &Length, sizeof(UINT16));
	Link.Write((BYTE *) ApplicationContextName.GetBuffer(Length), Length);
	Link.Flush();
	return ( TRUE );
	}

BOOL	ApplicationContext	::	Read(Buffer	&Link)
	{
	Link >> ItemType;	//Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return ( this->ReadDynamic(Link) );
	}

BOOL	ApplicationContext	::	ReadDynamic(Buffer	&Link)
	{
	Link >> Reserved1;	//Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;		//Link.Read((BYTE *) &Length, sizeof(UINT16));
	Link.Read((BYTE *) ApplicationContextName.GetBuffer(Length), Length);
	ApplicationContextName.GetBuffer(Length)[Length] = '\0';
	ApplicationContextName.SetLength(Length);
	return ( TRUE );
	}

UINT32	ApplicationContext	::	Size()
	{
	Length = ApplicationContextName.GetSize();
	return ( sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT16) + Length );
	}

/*************************************************************************
 *
 * Abstract Syntax Class
 *
 ************************************************************************/

AbstractSyntax	::	AbstractSyntax()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x30),
Reserved1(0),
Length(0),
AbstractSyntaxName() {}
#else
	{
	ItemType = 0x30;
	Reserved1 = 0;
	}
#endif
		
AbstractSyntax	::	AbstractSyntax(UID	&uid)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x30),
Reserved1(0),
Length(0),
AbstractSyntaxName()
	{
#else
	{
	ItemType = 0x30;
	Reserved1 = 0;
#endif
	AbstractSyntaxName = uid;
	}

AbstractSyntax	:: AbstractSyntax(BYTE	*name)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x30),
Reserved1(0),
Length(0),
AbstractSyntaxName()
	{
#else
	{
	ItemType = 0x30;
	Reserved1 = 0;
#endif
	AbstractSyntaxName.Set(name);
	}

AbstractSyntax	::	~AbstractSyntax()
	{
	// nothing to de-allocate specifically

	}

void	AbstractSyntax	::	Set(UID	&uid)
	{
	AbstractSyntaxName = uid;
	}

void	AbstractSyntax	::	Set(BYTE	*name)
	{
	AbstractSyntaxName.Set(name);
	}

BOOL	AbstractSyntax	::	Write(Buffer	&Link)
	{
	Link << ItemType;	//Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link << Reserved1;	//Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;		//Link.Write((BYTE *) &Length, sizeof(UINT16));
	Link.Write((BYTE *) AbstractSyntaxName.GetBuffer(Length), Length);
	Link.Flush();
	return ( TRUE );
	}

BOOL	AbstractSyntax	::	Read(Buffer	&Link)
	{
	Link >> ItemType;	//Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return ( this->ReadDynamic(Link) );
	}

BOOL	AbstractSyntax	::	ReadDynamic(Buffer	&Link)
	{
	Link >> Reserved1;	//Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;		//Link.Read((BYTE *) &Length, sizeof(UINT16));
	Link.Read((BYTE *) AbstractSyntaxName.GetBuffer(Length), Length);
	AbstractSyntaxName.GetBuffer(Length)[Length] = '\0';
	AbstractSyntaxName.SetLength(Length);
	return ( TRUE );
	}

UINT32	AbstractSyntax	::	Size()
	{
	Length = AbstractSyntaxName.GetSize();
	return ( sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT16) + Length );
	}

/************************************************************************
 *
 * Transfer Syntax
 *
 ************************************************************************/

TransferSyntax	::	TransferSyntax()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x40),
Reserved1(0),
Length(0),
TransferSyntaxName(),
EndianType(LITTLE_ENDIAN) {}
#else
	{
	ItemType = 0x40;
	Reserved1 = 0;
	}
#endif

TransferSyntax	::	TransferSyntax(UID	&uid)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x40),
Reserved1(0),
Length(0),
TransferSyntaxName(),
EndianType(LITTLE_ENDIAN)
{
#else
	{
	ItemType = 0x40;
	Reserved1 = 0;
#endif
	TransferSyntaxName = uid;
	}

TransferSyntax	:: TransferSyntax(BYTE	*name)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x40),
Reserved1(0),
Length(0),
TransferSyntaxName(),
EndianType(LITTLE_ENDIAN)
	{
#else
	{
	ItemType = 0x40;
	Reserved1 = 0;
#endif
	TransferSyntaxName.Set(name);
	}

TransferSyntax	::	~TransferSyntax()
	{
	// nothing to de-allocate specifically

	}

void	TransferSyntax	::	Set(UID	&uid)
	{
	TransferSyntaxName = uid;
	}

void	TransferSyntax	::	Set(BYTE	*name)
	{
	TransferSyntaxName.Set(name);
	}

BOOL	TransferSyntax	::	Write(Buffer	&Link)
	{
//	fprintf(stderr, "Writing Transfer Syntax: %d ItemType\n", ItemType);
//	fprintf(stderr, "Length = %d\n", Length);
//	fprintf(stderr, "UID: %s\n", TransferSyntaxName.GetBuffer(Length));

	Link << ItemType;	//Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link << Reserved1;	//Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;		//Link.Write((BYTE *) &Length, sizeof(UINT16));
	Link.Write((BYTE *) TransferSyntaxName.GetBuffer(Length), Length);
	Link.Flush();
	return ( TRUE );
	}

BOOL	TransferSyntax	::	Read(Buffer	&Link)
	{
	Link >> ItemType;	//Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	//fprintf(stderr, "Reading Transfter Syntax Magic Code: %x\n", ItemType);
	return ( this->ReadDynamic(Link) );
	}

BOOL	TransferSyntax	::	ReadDynamic(Buffer	&Link)
	{
	Link >> ItemType;	//Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
 	Link >> Length;		//Link.Read((BYTE *) &Length, sizeof(UINT16));
	Link.Read((BYTE *) TransferSyntaxName.GetBuffer(Length), Length);
	TransferSyntaxName.GetBuffer(Length)[Length] = '\0';
	TransferSyntaxName.SetLength(Length);
	return ( TRUE );
	}

UINT32	TransferSyntax	::	Size()
	{
	Length = TransferSyntaxName.GetSize();
	return ( sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT16) + Length );
	}



/************************************************************************
 *
 *  Implementation Class
 *
 ************************************************************************/

ImplementationClass	::	ImplementationClass()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x52),
Reserved1(0),
Length(0),
ImplementationName(),
EndianType(LITTLE_ENDIAN) {}
#else
	{
	ItemType = 0x52;
	Reserved1 = 0;
	}
#endif
		
ImplementationClass	::	ImplementationClass(UID	&uid)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x52),
Reserved1(0),
Length(0),
ImplementationName(),
EndianType(LITTLE_ENDIAN)
	{
#else
	{
	ItemType = 0x52;
	Reserved1 = 0;
#endif
	ImplementationName = uid;
	}

ImplementationClass	:: ImplementationClass(BYTE	*name)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x52),
Reserved1(0),
Length(0),
ImplementationName(),
EndianType(LITTLE_ENDIAN)
	{
#else
	{
	ItemType = 0x52;
	Reserved1 = 0;
#endif
	ImplementationName.Set(name);
	}

ImplementationClass	::	~ImplementationClass()
	{
	// nothing to de-allocate specifically

	}

void	ImplementationClass	::	Set(UID	&uid)
	{
	ImplementationName = uid;
	}

void	ImplementationClass	::	Set(BYTE	*name)
	{
	ImplementationName.Set(name);
	}

BOOL	ImplementationClass	::	Write(Buffer	&Link)
	{
	Link << ItemType;	//Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link << Reserved1;	//Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;		//Link.Write((BYTE *) &Length, sizeof(UINT16));
	Link.Write((BYTE *) ImplementationName.GetBuffer(Length), Length);
	Link.Flush();
	return ( TRUE );
	}

BOOL	ImplementationClass	::	Read(Buffer	&Link)
	{
	Link >> ItemType;	//Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return ( this->ReadDynamic(Link) );
	}

BOOL	ImplementationClass	::	ReadDynamic(Buffer	&Link)
	{
	Link >> Reserved1;	//Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;		//Link.Read((BYTE *) &Length, sizeof(UINT16));
	Link.Read((BYTE *) ImplementationName.GetBuffer(Length), Length);
	ImplementationName.GetBuffer(Length)[Length] = '\0';
	ImplementationName.SetLength(Length);
	return ( TRUE );
	}

UINT32	ImplementationClass	::	Size()
	{
	Length = ImplementationName.GetSize();
	return ( sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT16) + Length );
	}


/************************************************************************
 *
 *  Implementation Class
 *
 ************************************************************************/

ImplementationVersion	::	ImplementationVersion()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x55),
Reserved1(0),
Length(0),
Version(),
EndianType(LITTLE_ENDIAN) {}
#else
	{
	ItemType = 0x55;
	Reserved1 = 0;
	}
#endif
		
ImplementationVersion	::	ImplementationVersion(UID	&uid)
#ifdef __GNUC__ //The GCC way
:ItemType(0x55),
Reserved1(0),
Length(0),
Version(uid),
EndianType(LITTLE_ENDIAN) {}
#else
	{
	ItemType = 0x55;
	Reserved1 = 0;
	Version = uid;
	}
#endif

ImplementationVersion	:: ImplementationVersion(BYTE	*name)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x55),
Reserved1(0),
Length(0),
Version(),
EndianType(LITTLE_ENDIAN)
	{
#else
	{
	ItemType = 0x55;
	Reserved1 = 0;
#endif
	Version.Set(name);
	}

ImplementationVersion	::	~ImplementationVersion()
	{
	// nothing to de-allocate specifically

	}

void	ImplementationVersion	::	Set(UID	&uid)
	{
	Version = uid;
	}

void	ImplementationVersion	::	Set(BYTE	*name)
	{
	Version.Set(name);
	}

BOOL	ImplementationVersion	::	Write(Buffer	&Link)
	{
	Link << ItemType;	//Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link << Reserved1;	//Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;		//Link.Write((BYTE *) &Length, sizeof(UINT16));
	Link.Write((BYTE *) Version.GetBuffer(Length), Length);
	Link.Flush();
	return ( TRUE );
	}

BOOL	ImplementationVersion	::	Read(Buffer	&Link)
	{
	Link >> ItemType;	//Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return ( this->ReadDynamic(Link) );
	}

BOOL	ImplementationVersion	::	ReadDynamic(Buffer	&Link)
	{
	Link >> Reserved1;	//Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;		//Link.Read((BYTE *) &Length, sizeof(UINT16));
	Link.Read((BYTE *) Version.GetBuffer(Length), Length);
	Version.GetBuffer(Length)[Length] = '\0';
	Version.SetLength(Length);
	return ( TRUE );
	}

UINT32	ImplementationVersion	::	Size()
	{
	Length = Version.GetSize();
	return ( sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT16) + Length );
	}

/************************************************************************
 *
 * Presentation Context
 *
 ************************************************************************/

PresentationContext	::	PresentationContext()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x20),
Reserved1(0),
Length(0),
PresentationContextID(uniq8odd()),
Reserved2(0),
Reserved3(0),
Reserved4(0),
AbsSyntax(),
TrnSyntax()
	{
#else
	{
	ItemType = 0x20;
	Reserved1 = 0;
	PresentationContextID = uniq8odd();
	Reserved2 = 0;
	Reserved3 = 0;
	Reserved4 = 0;
#endif
//	fprintf(stderr, "Creating PresentationContext / %d\n",
//		TrnSyntax.ClearType);
	}

PresentationContext	::	PresentationContext(
	AbstractSyntax	&Abs, 
	TransferSyntax	&Tran)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x20),
Reserved1(0),
Length(0),
PresentationContextID(uniq8odd()),
Reserved2(0),
Reserved3(0),
Reserved4(0),
AbsSyntax(Abs),
TrnSyntax()
	{
	TrnSyntax.Add ( Tran );
#else
	{
	AbsSyntax = Abs;
	TrnSyntax.Add ( Tran );
	ItemType = 0x20;
	Reserved1 = 0;
	PresentationContextID = uniq8odd();
	Reserved2 = 0;
	Reserved3 = 0;
	Reserved4 = 0;
#endif
	}

PresentationContext	::	~PresentationContext()
	{
//	fprintf (stderr, "~PresentationContext ClearType=%d\n", TrnSyntax.ClearType);
	//TrnSyntax.FreeData ( FALSE );
	}

void	PresentationContext	::	SetAbstractSyntax(AbstractSyntax	&Abs)
	{
	AbsSyntax = Abs;
	}

void	PresentationContext	::	AddTransferSyntax(TransferSyntax	&Tran)
	{
	TrnSyntax.Add ( Tran );
	}

BOOL	PresentationContext	::	Write ( Buffer	&Link )
	{
	UINT	Index;

	Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved1, sizeof(BYTE));	
	Link << Length;	//Link.Write((BYTE *) &Length, sizeof(UINT16));
	Link.Write((BYTE *) &PresentationContextID, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved2, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved3, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved4, sizeof(BYTE));
	AbsSyntax.Write(Link);
	Link.Flush();
	Index = 0;
	while ( Index < TrnSyntax.GetSize() )
		{
		TrnSyntax[ Index ].Write(Link);
		++Index;
		}
	if ( Index )
		return ( TRUE );
	return ( FALSE );
	}

BOOL	PresentationContext	::	Read (Buffer	&Link)
	{
	Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return ( this->ReadDynamic(Link) );
	}

BOOL	PresentationContext	::	ReadDynamic (Buffer	&Link)
	{
	INT32			Count;
	TransferSyntax	Tran;

	Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;	//Link.Read((BYTE *) &Length, sizeof(UINT16));
	Link.Read((BYTE *) &PresentationContextID, sizeof(BYTE));
	Link.Read((BYTE *) &Reserved2, sizeof(BYTE));
	Link.Read((BYTE *) &Reserved3, sizeof(BYTE));
	Link.Read((BYTE *) &Reserved4, sizeof(BYTE));

	Count = Length - sizeof(BYTE) - sizeof(BYTE) - sizeof(BYTE) - sizeof(BYTE);
//	fprintf(stderr, "Pres Context Length: %d\n", Length);
//	fprintf(stderr, "Reading Abstract Syntax\n");
	AbsSyntax.Read(Link);
	Count = Count - AbsSyntax.Size();
	while ( Count > 0)
		{
//		fprintf(stderr, "Reading Transfer Syntax Count = %d\n", Count);
		Tran.Read ( Link );
		Count = Count - Tran.Size();
		TrnSyntax.Add ( Tran );
		}
//	fprintf(stderr, "Read Presentation Context, ClearType = %d\n", 
//		TrnSyntax.ClearType);
	if ( !Count)
		return ( TRUE );
	return ( FALSE );
	}

UINT32	PresentationContext	::	Size()
	{
	UINT	Index;
	Length = sizeof(BYTE) + sizeof(BYTE) + sizeof(BYTE) + sizeof(BYTE);
	Length += AbsSyntax.Size();
	Index = 0;
	while(Index < TrnSyntax.GetSize() )
		{
		Length += TrnSyntax.Get(Index).Size();
		++Index;
		}
	return ( Length + sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT16));
	}

/************************************************************************
 *
 * Maximum Sub Length
 *
 ************************************************************************/

MaximumSubLength	::	MaximumSubLength()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x51),
Reserved1(0),
Length(0),
MaximumLength(0) {}
#else
	{
	ItemType = 0x51;
	Reserved1 = 0;
	}
#endif
		
MaximumSubLength	::	MaximumSubLength(UINT32	Max)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x51),
Reserved1(0),
Length(0),
MaximumLength(Max) {}
#else
	{
	ItemType = 0x51;
	Reserved1 = 0;
	MaximumLength = Max;
	}
#endif

MaximumSubLength	::	~MaximumSubLength()
	{
	// nothing to de-allocate
	}

void	MaximumSubLength	::	Set(UINT32	Max)
	{
	MaximumLength = Max;
	}

UINT32	MaximumSubLength	::	Get()
	{
	return ( MaximumLength );
	}

BOOL	MaximumSubLength	::	Write(Buffer	&Link)
	{
	Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;	//Link.Write((BYTE *) &Length, sizeof(UINT16));
	Link << MaximumLength; //Link.Write((BYTE *) &MaximumLength, sizeof(UINT32));
	Link.Flush();
	return ( TRUE );
	}

BOOL	MaximumSubLength	::	Read(Buffer	&Link)
	{
	Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return ( this->ReadDynamic(Link) );
	}

BOOL	MaximumSubLength	::	ReadDynamic(Buffer	&Link)
	{
	Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;	//Link.Read((BYTE *) &Length, sizeof(UINT16));
	Link >> MaximumLength; //Link.Read((BYTE *) &MaximumLength, sizeof(UINT32));

	return ( TRUE );
	}

UINT32	MaximumSubLength	::	Size()
	{
	Length = sizeof(UINT32);
	return ( Length + sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT16));
	}



/******** SCP / SCU Role Select ***********/


SCPSCURoleSelect	::	SCPSCURoleSelect()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x54),
Reserved1(0),
Length(0),
uid(),
SCURole(),
SCPRole() {}
#else
	{
	ItemType = 0x54;
	Reserved1 = 0;
	}
#endif

SCPSCURoleSelect	::	~SCPSCURoleSelect()
	{
	// nothing to de-allocate
	}


BOOL	SCPSCURoleSelect	::	Write(Buffer	&Link)
	{
	UINT16	TL;

	ItemType = 0x54;
	
	Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;	//Link.Write((BYTE *) &Length, sizeof(UINT16));
	TL = uid.GetSize();
	Link << TL; //Link.Write((BYTE *) &MaximumLength, sizeof(UINT32));
	Link.Write((BYTE *) uid.GetBuffer(1), TL);
	Link << SCURole;
	Link << SCPRole;
	Link.Flush();
	return ( TRUE );
	}

BOOL	SCPSCURoleSelect	::	Read(Buffer	&Link)
	{
	Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return ( this->ReadDynamic(Link) );
	}

BOOL	SCPSCURoleSelect	::	ReadDynamic(Buffer	&Link)
	{
	UINT16	TL;
	
	Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;	//Link.Read((BYTE *) &Length, sizeof(UINT16));
	Link >> TL;
	Link.Read((BYTE*) uid.GetBuffer(TL+1), TL);
	uid.GetBuffer(Length)[Length] = '\0';
	uid.SetLength(TL);
	Link >> SCURole;
	Link >> SCPRole;
	return ( TRUE );
	}

UINT32	SCPSCURoleSelect	::	Size()
	{
	Length = sizeof(UINT16) + uid.GetSize() + sizeof(BYTE) + sizeof(BYTE);
	return ( Length + sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT16) );
	}

/************************************************************************
 *
 * User Information
 *
 ************************************************************************/

UserInformation	::	UserInformation()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x50),
Reserved1(0),
Length(0),
UserInfoBaggage(0),
MaxSubLength(0),
ImpClass(),
ImpVersion(),
SCPSCURole() {}
#else
	{
	ItemType = 0x50;
	Reserved1 = 0;
	UserInfoBaggage = 0;
	}
#endif
		
UserInformation	::	~UserInformation()
	{
	// nothing to de-allocate
	}

void	UserInformation	::	SetMax(MaximumSubLength	&Max)
	{
	MaxSubLength = Max;
	}

UINT32	UserInformation	::	GetMax()
	{
	return(MaxSubLength.Get());
	}

BOOL	UserInformation	::	Write(Buffer	&Link)
	{
 	Link << ItemType;	//Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link << Reserved1;	//Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;		//Link.Write((BYTE *) &Length, sizeof(UINT16));
	Link.Flush();
	MaxSubLength.Write(Link);
	ImpClass.Write(Link);
	ImpVersion.Write(Link);
	return ( TRUE );
	}

BOOL	UserInformation	::	Read(Buffer	&Link)
	{
	Link >> ItemType; //Link.Read((BYTE *) &ItemType, sizeof(BYTE));
	return ( this->ReadDynamic(Link) );
	}

BOOL	UserInformation	::	ReadDynamic(Buffer	&Link)
	{
	BYTE		TempByte;
	INT32		Count;

	UserInfoBaggage = 0;
	
	Link >> Reserved1;	//Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;		//Link.Read((BYTE *) &Length, sizeof(UINT16));
	Count = Length;
//	fprintf(stderr, "User Info Length: %d\n", Length);
	while(Count > 0)
		{
		Link >> TempByte;	//Link.Read((BYTE *) &TempByte, sizeof(BYTE));
		switch ( TempByte )
			{
			case	0x51:
//				fprintf(stderr, "Reading Max Sub Length Count = %d\n", Count);
				MaxSubLength.ReadDynamic(Link);
				Count = Count - MaxSubLength.Size();
				break;
			case	0x52:
//				fprintf(stderr, "Reading Implementation Class Count = %d\n", Count);
				ImpClass.ReadDynamic(Link);
				Count = Count - ImpClass.Size();
				break;
			case	0x54:	// Role selection
				SCPSCURole.ReadDynamic(Link);
				Count = Count - SCPSCURole.Size();
				UserInfoBaggage += SCPSCURole.Size();
				break;
			case	0x55:
//				fprintf(stderr, "Reading Implemenation Version Count = %d\n", Count);
				ImpVersion.ReadDynamic(Link);
				Count = Count - ImpVersion.Size();
				break;
			default:
				//fprintf(stderr, "Unknown Packet: %x, Count = %d\n", TempByte, Count);
				Link.Kill(Count-1);	// unknown user information packet
				UserInfoBaggage = Count;
				Count = -1;
			}
		}
//	fprintf(stderr, "ending User Info ReadD Count = %d\n", Count);
	if(!Count)
		return ( TRUE );
	return ( FALSE );
	}

UINT32	UserInformation	::	Size()
	{
	Length = MaxSubLength.Size();
	Length += ImpClass.Size();
	Length += ImpVersion.Size();
	return ( Length + UserInfoBaggage + sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT16));
	}

/************************************************************************
 *
 * AAssociateRQ Packet
 *
 ************************************************************************/

BOOL ConfigPadAEWithZeros = 0;

AAssociateRQ	::	AAssociateRQ()
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x01),
Reserved1(0),
Length(0),
ProtocolVersion(0x0001),
Reserved2(0),
AppContext(),
PresContexts(),
UserInfo()
	{
#else
	{
	ItemType = 0x01;
	Reserved1 = 0;
	ProtocolVersion = 0x0001;
	Reserved2 = 0;
#endif
	SpaceMem(CalledApTitle, 16);
	if (ConfigPadAEWithZeros) memset(CalledApTitle, 0, 16);
	CalledApTitle[16] = 0;
	SpaceMem(CallingApTitle, 16);
	if (ConfigPadAEWithZeros) memset(CalledApTitle, 0, 16);
	CallingApTitle[16] = 0;
	ZeroMem(Reserved3, 32);
	}

AAssociateRQ	::	AAssociateRQ(BYTE	*CallingAp, BYTE	*CalledAp)
#ifdef __GNUC__ //Faster with member initialization.
:ItemType(0x01),
Reserved1(0),
Length(0),
ProtocolVersion(0x0001),
Reserved2(0),
AppContext(),
PresContexts(),
UserInfo()
	{
#else
	{
	ItemType = 0x01;
	Reserved1 = 0;
	ProtocolVersion = 0x0001;
	Reserved2 = 0;
#endif
	SpaceMem(CalledApTitle, 16);
	if (ConfigPadAEWithZeros) memset(CalledApTitle, 0, 16);
	CalledApTitle[16] = 0;
	SpaceMem(CallingApTitle, 16);
	if (ConfigPadAEWithZeros) memset(CalledApTitle, 0, 16);
	CallingApTitle[16] = 0;
	ZeroMem(Reserved3, 32);
	memcpy(CallingApTitle, CallingAp, min(strlen((char *)CallingAp), 16u));
	memcpy(CalledApTitle, CalledAp, min(strlen((char *)CalledAp), 16u));
	}

AAssociateRQ	::	~AAssociateRQ()
	{
	// nothing, everything should self-destruct nicely
	while(PresContexts.GetSize())
		{
		PresContexts.Get ( 0 ).TrnSyntax.ClearType = TRUE;
		PresContexts.RemoveAt ( 0 );
		}

	PresContexts.ClearType = TRUE;
//	fprintf(stderr, "~AAssociateRQ : PresContexts.ClearType = %d\n",
//		PresContexts.ClearType);
	}

void	AAssociateRQ	::	SetCalledApTitle(BYTE	*CalledAp)
	{
	SpaceMem(CalledApTitle, 16);
	if (ConfigPadAEWithZeros) memset(CalledApTitle, 0, 16);
	memcpy(CalledApTitle, CalledAp, min(strlen((char *)CalledAp), 16u));
	}

void	AAssociateRQ	::	SetCallingApTitle(BYTE	*CallingAp)
	{
	SpaceMem(CallingApTitle, 16);
	if (ConfigPadAEWithZeros) memset(CalledApTitle, 0, 16);
	memcpy(CallingApTitle, CallingAp, min(strlen((char *)CallingAp), 16u));
	}

void	AAssociateRQ	::	SetApplicationContext(ApplicationContext	&AppC)
	{
	AppContext = AppC;
	}

void	AAssociateRQ	::	SetApplicationContext(UID &uid)
	{
	AppContext.Set(uid);
	}

void	AAssociateRQ	::	AddPresentationContext(PresentationContext	&PresContext)
	{
	PresContexts.Add(PresContext);
	PresContexts.Get(PresContexts.GetSize()-1).TrnSyntax.ClearType = TRUE;
	}

void	AAssociateRQ	::	SetUserInformation(UserInformation	&User)
	{
	UserInfo = User;
	}

void	AAssociateRQ	::	ClearPresentationContexts()
	{
	while(PresContexts.GetSize())
		PresContexts.RemoveAt ( 0 );
	return;
	}

BOOL	AAssociateRQ	::	Write(Buffer	&Link)
	{
	UINT	Index;

	//fprintf(stderr, "AAssociateRQ :: Write ()\n");fflush(stderr);
	Size();
	Link << ItemType; //Link.Write((BYTE *) &ItemType, sizeof(BYTE));
	Link.Write((BYTE *) &Reserved1, sizeof(BYTE));
	Link << Length;	//Link.Write((BYTE *) &Length, sizeof(UINT32));
	Link << ProtocolVersion;	//Link.Write((BYTE *) &ProtocolVersion, sizeof(UINT16));
	Link << Reserved2;			//Link.Write((BYTE *) &Reserved2, sizeof(UINT16));
	Link.Write((BYTE *) CalledApTitle, 16);
	Link.Write((BYTE *) CallingApTitle, 16);
	Link.Write((BYTE *) Reserved3, 32);
	Link.Flush();
	AppContext.Write(Link);
	Index = 0;
	while(Index < PresContexts.GetSize())
		{
		PresContexts[Index].Write(Link);
		++Index;
		}
	UserInfo.Write(Link);
	return ( TRUE );
	}

BOOL	AAssociateRQ	::	Read(Buffer	&Link)
	{
//	fprintf(stderr, "Attempting to Read AAssociateRQ PDU\n");
	Link.Read((BYTE *) &ItemType, sizeof(BYTE));
//	fprintf(stderr, "Got ItemType: %x\n", ItemType);
	return(this->ReadDynamic(Link));
	}

BOOL	AAssociateRQ	::	ReadDynamic(Buffer	&Link)
	{
	INT			Count;
	BYTE			TempByte;
	PresentationContext	*PresContext;

	Link.Read((BYTE *) &Reserved1, sizeof(BYTE));
	Link >> Length;	//Link.Read((BYTE *) &Length, sizeof(UINT32));
	Link >> ProtocolVersion;	//Link.Read((BYTE *) &ProtocolVersion, sizeof(UINT16));
	Link >>	Reserved2;			//Link.Read((BYTE *) &Reserved2, sizeof(UINT16));
	Link.Read((BYTE *) CalledApTitle, 16);
	Link.Read((BYTE *) CallingApTitle, 16);
	Link.Read((BYTE *) Reserved3, 32);
	CalledApTitle[16] = '\0';
	CallingApTitle[16] = '\0';
//	fprintf(stderr, "Item Length: %d\n", Length);
//	fprintf(stderr, "Protocol Version: %d\n", ProtocolVersion);
//	fprintf(stderr, "CalledApTitle: %16.16s\n", CalledApTitle);
//	fprintf(stderr, "CallingApTitle: %16.16s\n", CallingApTitle);

	Count = Length - sizeof(UINT16) - sizeof(UINT16) - 16 - 16 - 32;
	while(Count > 0)
		{
		Link.Read((BYTE *) &TempByte, sizeof(BYTE));
		switch(TempByte)
			{
			case	0x50:	// user information
//				fprintf(stderr, "Reading User Information (%d)\n", Count);
				UserInfo.ReadDynamic(Link);
				Count = Count - UserInfo.Size() - UserInfo.UserInfoBaggage;
//				fprintf(stderr, "Count = %d/UserInfo = %d\n", Count,
//					UserInfo.Size());
				break;
			case	0x20:
//				fprintf(stderr, "Reading Presentation Context (%d)\n", Count);
				PresContext = new PresentationContext;
				PresContext->TrnSyntax.ClearType = TRUE;
				PresContext->ReadDynamic(Link);
				Count = Count - PresContext->Size();
				PresContexts.Add(*PresContext);
				PresContext->TrnSyntax.ClearType = FALSE;
				delete PresContext;

				break;
			case	0x10:
//				fprintf(stderr, "Reading AppContext (%d)\n", Count);
				AppContext.ReadDynamic(Link);
				Count = Count - AppContext.Size();
				break;
			default:
				//fprintf(stderr, "unknown item: %x ending\n", TempByte);
				Link.Kill(Count-1);
				Count = -1;
			}
		}
	if(!Count)
		return ( TRUE );
	return ( FALSE);
	}

UINT32	AAssociateRQ	::	Size()
	{
	UINT	Index;

	Length = sizeof(UINT16) + sizeof(UINT16) + 16 + 16 + 32;
	Length += AppContext.Size();
	Index = 0;

	while(Index < PresContexts.GetSize())
		{
		Length += PresContexts[Index].Size();
		++Index;
		}
	Length += UserInfo.Size();
	return ( Length + sizeof(BYTE) + sizeof(BYTE) + sizeof(UINT32) );
	}

