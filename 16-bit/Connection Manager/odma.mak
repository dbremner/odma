# Microsoft Visual C++ generated build script - Do not modify

PROJ = ODMA
DEBUG = 0
PROGTYPE = 1
CALLER = C:\Project\ODMA\multODMA\test16.exe
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG 
R_RCDEFINES = /dNDEBUG 
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = C:\PROJECT\ODMA\CONMAN\
USEMFC = 0
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = 
CUSEPCHFLAG = 
CPPUSEPCHFLAG = 
FIRSTC =             
FIRSTCPP = CLIENT.CPP  
RC = rc
CFLAGS_D_WDLL = /nologo /G2 /W3 /Zi /ALw /Od /D "_DEBUG" /FR /Zn /GD /Fd"ODMA.PDB"
CFLAGS_R_WDLL = /nologo /G3 /FPc /W3 /ALw /O1 /D "NDEBUG" /GD 
LFLAGS_D_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WDLL = /NOLOGO /NOD /NOE /PACKC:61440 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WDLL = oldnames libw ldllcew compobj commdlg.lib olecli.lib olesvr.lib shell.lib 
LIBS_R_WDLL = oldnames libw ldllcew compobj commdlg.lib olecli.lib olesvr.lib shell.lib 
RCFLAGS = /nologo 
RESFLAGS = /nologo 
RUNFLAGS = 
DEFFILE = ODMA.DEF
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
SBRS = CLIENT.SBR \
		INIT.SBR \
		ODMAENT.SBR \
		ODMDMS.SBR \
		REGISTRY.SBR


CLIENT_DEP = c:\project\odma\conman\odma.h \
	c:\project\odma\conman\conman.h \
	c:\project\odma\conman\odmacom.h \
	c:\project\odma\conman\odmlist.h


INIT_DEP = c:\project\odma\conman\conman.h \
	c:\project\odma\conman\odmacom.h \
	c:\project\odma\conman\odma.h \
	c:\project\odma\conman\odmlist.h


ODMAENT_DEP = c:\project\odma\conman\conman.h \
	c:\project\odma\conman\odmacom.h \
	c:\project\odma\conman\odma.h \
	c:\project\odma\conman\odmlist.h


ODMDMS_DEP = c:\project\odma\conman\conman.h \
	c:\project\odma\conman\odmacom.h \
	c:\project\odma\conman\odma.h \
	c:\project\odma\conman\odmlist.h


REGISTRY_DEP = c:\project\odma\conman\conman.h \
	c:\project\odma\conman\odmacom.h \
	c:\project\odma\conman\odma.h \
	c:\project\odma\conman\odmlist.h


all:	$(PROJ).DLL

CLIENT.OBJ:	CLIENT.CPP $(CLIENT_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c CLIENT.CPP

INIT.OBJ:	INIT.CPP $(INIT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c INIT.CPP

ODMAENT.OBJ:	ODMAENT.CPP $(ODMAENT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ODMAENT.CPP

ODMDMS.OBJ:	ODMDMS.CPP $(ODMDMS_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ODMDMS.CPP

REGISTRY.OBJ:	REGISTRY.CPP $(REGISTRY_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c REGISTRY.CPP

ODMA.RES:	ODMA.RC $(ODMA_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r ODMA.RC


$(PROJ).DLL::	ODMA.RES

$(PROJ).DLL::	CLIENT.OBJ INIT.OBJ ODMAENT.OBJ ODMDMS.OBJ REGISTRY.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
CLIENT.OBJ +
INIT.OBJ +
ODMAENT.OBJ +
ODMDMS.OBJ +
REGISTRY.OBJ +
$(OBJS_EXT)
$(PROJ).DLL
$(MAPFILE)
C:\MSVC\LIB\+
C:\MSVC\MFC\LIB\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) ODMA.RES $@
	@copy $(PROJ).CRF MSVC.BND
	implib /nowep $(PROJ).LIB $(PROJ).DLL

$(PROJ).DLL::	ODMA.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) ODMA.RES $@

run: $(PROJ).DLL
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
