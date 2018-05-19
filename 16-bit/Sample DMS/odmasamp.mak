# Microsoft Visual C++ generated build script - Do not modify

PROJ = ODMASAMP
DEBUG = 0
PROGTYPE = 1
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\ODMA20\SOURCE\16-BIT\SAMPLE~1\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = DIALOGS.CPP 
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /FR /GD /Fd"ODMASAMP.PDB"
CFLAGS_R_WDLL = /nologo /G3 /FPc /W3 /ALw /O1 /D "NDEBUG" /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO /MAP:FULL
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WDLL = lafxdwd oldnames libw ldllcew compobj commdlg.lib ddeml.lib lzexpand.lib mmsystem.lib olecli.lib olesvr.lib penwin.lib scrnsave.lib shell.lib stress.lib toolhelp.lib ver.lib 
LIBS_R_WDLL = lafxdw oldnames libw ldllcew compobj commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = ODMASAMP.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WDLL)
LFLAGS = $(LFLAGS_D_WDLL)
LIBS = $(LIBS_D_WDLL)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WDLL)
LFLAGS = $(LFLAGS_R_WDLL)
LIBS = $(LIBS_R_WDLL)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = DIALOGS.SBR \
		DOCLIST.SBR \
		DOCUMENT.SBR \
		ODMASAMP.SBR \
		SAMPAPP.SBR


DIALOGS_DEP = d:\odma20\source\16-bit\sample~1\odmasamp.h


DOCLIST_DEP = d:\odma20\source\16-bit\sample~1\odmasamp.h


DOCUMENT_DEP = d:\odma20\source\16-bit\sample~1\odmasamp.h


ODMASAMP_DEP = d:\odma20\source\16-bit\sample~1\odmasamp.h


SAMPAPP_DEP = d:\odma20\source\16-bit\sample~1\odmasamp.h


all:	$(PROJ).DLL

DIALOGS.OBJ:	DIALOGS.CPP $(DIALOGS_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c DIALOGS.CPP

DOCLIST.OBJ:	DOCLIST.CPP $(DOCLIST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DOCLIST.CPP

DOCUMENT.OBJ:	DOCUMENT.CPP $(DOCUMENT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DOCUMENT.CPP

ODMASAMP.OBJ:	ODMASAMP.CPP $(ODMASAMP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ODMASAMP.CPP

SAMPAPP.OBJ:	SAMPAPP.CPP $(SAMPAPP_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c SAMPAPP.CPP

ODMASAMP.RES:	ODMASAMP.RC $(ODMASAMP_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r ODMASAMP.RC


$(PROJ).DLL::	ODMASAMP.RES

$(PROJ).DLL::	DIALOGS.OBJ DOCLIST.OBJ DOCUMENT.OBJ ODMASAMP.OBJ SAMPAPP.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
DIALOGS.OBJ +
DOCLIST.OBJ +
DOCUMENT.OBJ +
ODMASAMP.OBJ +
SAMPAPP.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
d:\msvc\lib\+
d:\msvc\mfc\lib\+
..\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) ODMASAMP.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	ODMASAMP.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) ODMASAMP.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
