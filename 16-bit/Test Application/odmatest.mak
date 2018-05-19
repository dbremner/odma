# Microsoft Visual C++ generated build script - Do not modify

PROJ = ODMATEST
DEBUG = 0
PROGTYPE = 0
CALLER = 
ARGS = 
DLLS = 
D_RCDEFINES = /d_DEBUG
R_RCDEFINES = /dNDEBUG
ORIGIN = MSVC
ORIGIN_VER = 1.00
PROJPATH = D:\ODMA20\SOURCE\16-BIT\TESTAP~1\
USEMFC = 1
CC = cl
CPP = cl
CXX = cl
CCREATEPCHFLAG = 
CPPCREATEPCHFLAG = /YcSTDAFX.H
CUSEPCHFLAG = 
CPPUSEPCHFLAG = /YuSTDAFX.H
FIRSTC =             
FIRSTCPP = STDAFX.CPP  
RC = rc
CFLAGS_D_WEXE = /nologo /G2 /W3 /Zi /AL /Od /D "_DEBUG" /FR /GA /Fd"ODMATEST.PDB" 
CFLAGS_R_WEXE = /nologo /Gs /G3 /FPc /W3 /AL /O2 /D "NDEBUG" /GA 
LFLAGS_D_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:20480 /ALIGN:16 /ONERROR:NOEXE /CO  
LFLAGS_R_WEXE = /NOLOGO /NOD /PACKC:61440 /STACK:16384 /ALIGN:16 /ONERROR:NOEXE  
LIBS_D_WEXE = lafxcwd oldnames libw llibcew odma commdlg.lib shell.lib 
LIBS_R_WEXE = lafxcw oldnames libw llibcew odma commdlg.lib shell.lib 
RCFLAGS = /nologo /z
RESFLAGS = /nologo /t
RUNFLAGS = 
DEFFILE = ODMATEST.DEF
OBJS_EXT = 
LIBS_EXT = 
!if "$(DEBUG)" == "1"
CFLAGS = $(CFLAGS_D_WEXE)
LFLAGS = $(LFLAGS_D_WEXE)
LIBS = $(LIBS_D_WEXE)
MAPFILE = nul
RCDEFINES = $(D_RCDEFINES)
!else
CFLAGS = $(CFLAGS_R_WEXE)
LFLAGS = $(LFLAGS_R_WEXE)
LIBS = $(LIBS_R_WEXE)
MAPFILE = nul
RCDEFINES = $(R_RCDEFINES)
!endif
!if [if exist MSVC.BND del MSVC.BND]
!endif
SBRS = STDAFX.SBR \
		DMSOPT.SBR \
		DMSQUERY.SBR \
		DOCFRMT.SBR \
		MAINFRM.SBR \
		ODMATEST.SBR \
		TESTDOC.SBR \
		TESTVIEW.SBR


ODMA_DEP = 

STDAFX_DEP = d:\odma20\source\16-bit\testap~1\stdafx.h


DMSOPT_DEP = d:\odma20\source\16-bit\testap~1\stdafx.h \
	d:\odma20\source\16-bit\testap~1\odmatest.h \
	d:\odma20\source\16-bit\testap~1\testdoc.h \
	d:\odma20\source\16-bit\testap~1\dmsopt.h


DMSQUERY_DEP = d:\odma20\source\16-bit\testap~1\stdafx.h \
	d:\odma20\source\16-bit\testap~1\odmatest.h \
	d:\odma20\source\16-bit\testap~1\testdoc.h \
	d:\odma20\source\16-bit\testap~1\dmsquery.h


DOCFRMT_DEP = d:\odma20\source\16-bit\testap~1\stdafx.h \
	d:\odma20\source\16-bit\testap~1\odmatest.h \
	d:\odma20\source\16-bit\testap~1\docfrmt.h


MAINFRM_DEP = d:\odma20\source\16-bit\testap~1\stdafx.h \
	d:\odma20\source\16-bit\testap~1\odmatest.h \
	d:\odma20\source\16-bit\testap~1\mainfrm.h


ODMATEST_DEP = d:\odma20\source\16-bit\testap~1\stdafx.h \
	d:\odma20\source\16-bit\testap~1\odmatest.h \
	d:\odma20\source\16-bit\testap~1\mainfrm.h \
	d:\odma20\source\16-bit\testap~1\childfrm.h \
	d:\odma20\source\16-bit\testap~1\testdoc.h \
	d:\odma20\source\16-bit\testap~1\testview.h \
	d:\odma20\source\16-bit\testap~1\dmsopt.h \
	d:\odma20\source\16-bit\testap~1\dmsquery.h


TESTDOC_DEP = d:\odma20\source\16-bit\testap~1\stdafx.h \
	d:\odma20\source\16-bit\testap~1\odmatest.h \
	d:\odma20\source\16-bit\testap~1\cntritem.h \
	d:\odma20\source\16-bit\testap~1\testdoc.h \
	d:\odma20\source\16-bit\testap~1\docfrmt.h


TESTVIEW_DEP = d:\odma20\source\16-bit\testap~1\stdafx.h \
	d:\odma20\source\16-bit\testap~1\odmatest.h \
	d:\odma20\source\16-bit\testap~1\testdoc.h \
	d:\odma20\source\16-bit\testap~1\testview.h


ODMATEST_RCDEP = d:\odma20\source\16-bit\testap~1\res\odmatest.ico \
	d:\odma20\source\16-bit\testap~1\res\testdoc.ico \
	d:\odma20\source\16-bit\testap~1\res\odmatest.rc2


all:	$(PROJ).EXE

STDAFX.OBJ:	STDAFX.CPP $(STDAFX_DEP)
	$(CPP) $(CFLAGS) $(CPPCREATEPCHFLAG) /c STDAFX.CPP

DMSOPT.OBJ:	DMSOPT.CPP $(DMSOPT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DMSOPT.CPP

DMSQUERY.OBJ:	DMSQUERY.CPP $(DMSQUERY_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DMSQUERY.CPP

DOCFRMT.OBJ:	DOCFRMT.CPP $(DOCFRMT_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c DOCFRMT.CPP

MAINFRM.OBJ:	MAINFRM.CPP $(MAINFRM_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c MAINFRM.CPP

ODMATEST.OBJ:	ODMATEST.CPP $(ODMATEST_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c ODMATEST.CPP

TESTDOC.OBJ:	TESTDOC.CPP $(TESTDOC_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TESTDOC.CPP

TESTVIEW.OBJ:	TESTVIEW.CPP $(TESTVIEW_DEP)
	$(CPP) $(CFLAGS) $(CPPUSEPCHFLAG) /c TESTVIEW.CPP

ODMATEST.RES:	ODMATEST.RC $(ODMATEST_RCDEP)
	$(RC) $(RCFLAGS) $(RCDEFINES) -r ODMATEST.RC


$(PROJ).EXE::	ODMATEST.RES

$(PROJ).EXE::	STDAFX.OBJ DMSOPT.OBJ DMSQUERY.OBJ DOCFRMT.OBJ MAINFRM.OBJ ODMATEST.OBJ \
	TESTDOC.OBJ TESTVIEW.OBJ $(OBJS_EXT) $(DEFFILE)
	echo >NUL @<<$(PROJ).CRF
STDAFX.OBJ +
DMSOPT.OBJ +
DMSQUERY.OBJ +
DOCFRMT.OBJ +
MAINFRM.OBJ +
ODMATEST.OBJ +
TESTDOC.OBJ +
TESTVIEW.OBJ +
$(OBJS_EXT)
$(PROJ).EXE
$(MAPFILE)
d:\msvc\lib\+
d:\msvc\mfc\lib\+
..\lib\+
$(LIBS)
$(DEFFILE);
<<
	link $(LFLAGS) @$(PROJ).CRF
	$(RC) $(RESFLAGS) ODMATEST.RES $@
	@copy $(PROJ).CRF MSVC.BND

$(PROJ).EXE::	ODMATEST.RES
	if not exist MSVC.BND 	$(RC) $(RESFLAGS) ODMATEST.RES $@

run: $(PROJ).EXE
	$(PROJ) $(RUNFLAGS)


$(PROJ).BSC: $(SBRS)
	bscmake @<<
/o$@ $(SBRS)
<<
