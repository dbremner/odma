# Microsoft Developer Studio Generated NMAKE File, Based on ODMATest32.dsp
!IF "$(CFG)" == ""
CFG=ODMATest32 - Win32 Debug
!MESSAGE No configuration specified. Defaulting to ODMATest32 - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "ODMATest32 - Win32 Release" && "$(CFG)" !=\
 "ODMATest32 - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ODMATest32.mak" CFG="ODMATest32 - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ODMATest32 - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ODMATest32 - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

OUTDIR=.\..\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\..\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ODMATest32.exe"

!ELSE 

ALL : "$(OUTDIR)\ODMATest32.exe"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\CntrItem.obj"
	-@erase "$(INTDIR)\DMSOpt.obj"
	-@erase "$(INTDIR)\DMSQuery.obj"
	-@erase "$(INTDIR)\DOCFrmt.obj"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\ODMATest.obj"
	-@erase "$(INTDIR)\ODMATest32.pch"
	-@erase "$(INTDIR)\ODMATest32.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\TestDoc.obj"
	-@erase "$(INTDIR)\TestView.obj"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(OUTDIR)\ODMATest32.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /I "..\Include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\ODMATest32.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ODMATest32.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ODMATest32.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=..\lib/ODMA32.lib /nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\ODMATest32.pdb" /machine:I386 /out:"$(OUTDIR)\ODMATest32.exe" 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\CntrItem.obj" \
	"$(INTDIR)\DMSOpt.obj" \
	"$(INTDIR)\DMSQuery.obj" \
	"$(INTDIR)\DOCFrmt.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ODMATest.obj" \
	"$(INTDIR)\ODMATest32.res" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestDoc.obj" \
	"$(INTDIR)\TestView.obj" \
	"..\lib\ODMA32.lib"

"$(OUTDIR)\ODMATest32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

OUTDIR=.\..\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\..\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\ODMATest32.exe" "$(OUTDIR)\ODMATest32.bsc"

!ELSE 

ALL : "$(OUTDIR)\ODMATest32.exe" "$(OUTDIR)\ODMATest32.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\ChildFrm.obj"
	-@erase "$(INTDIR)\ChildFrm.sbr"
	-@erase "$(INTDIR)\CntrItem.obj"
	-@erase "$(INTDIR)\CntrItem.sbr"
	-@erase "$(INTDIR)\DMSOpt.obj"
	-@erase "$(INTDIR)\DMSOpt.sbr"
	-@erase "$(INTDIR)\DMSQuery.obj"
	-@erase "$(INTDIR)\DMSQuery.sbr"
	-@erase "$(INTDIR)\DOCFrmt.obj"
	-@erase "$(INTDIR)\DOCFrmt.sbr"
	-@erase "$(INTDIR)\MainFrm.obj"
	-@erase "$(INTDIR)\MainFrm.sbr"
	-@erase "$(INTDIR)\ODMATest.obj"
	-@erase "$(INTDIR)\ODMATest.sbr"
	-@erase "$(INTDIR)\ODMATest32.pch"
	-@erase "$(INTDIR)\ODMATest32.res"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\TestDoc.obj"
	-@erase "$(INTDIR)\TestDoc.sbr"
	-@erase "$(INTDIR)\TestView.obj"
	-@erase "$(INTDIR)\TestView.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(OUTDIR)\ODMATest32.bsc"
	-@erase "$(OUTDIR)\ODMATest32.exe"
	-@erase "$(OUTDIR)\ODMATest32.ilk"
	-@erase "$(OUTDIR)\ODMATest32.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\ODMATest32.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\ODMATest32.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\ODMATest32.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\ChildFrm.sbr" \
	"$(INTDIR)\CntrItem.sbr" \
	"$(INTDIR)\DMSOpt.sbr" \
	"$(INTDIR)\DMSQuery.sbr" \
	"$(INTDIR)\DOCFrmt.sbr" \
	"$(INTDIR)\MainFrm.sbr" \
	"$(INTDIR)\ODMATest.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\TestDoc.sbr" \
	"$(INTDIR)\TestView.sbr"

"$(OUTDIR)\ODMATest32.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=..\lib/ODMA32.lib /nologo /base:"0x40c80000" /subsystem:windows\
 /incremental:yes /pdb:"$(OUTDIR)\ODMATest32.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\ODMATest32.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\ChildFrm.obj" \
	"$(INTDIR)\CntrItem.obj" \
	"$(INTDIR)\DMSOpt.obj" \
	"$(INTDIR)\DMSQuery.obj" \
	"$(INTDIR)\DOCFrmt.obj" \
	"$(INTDIR)\MainFrm.obj" \
	"$(INTDIR)\ODMATest.obj" \
	"$(INTDIR)\ODMATest32.res" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\TestDoc.obj" \
	"$(INTDIR)\TestView.obj" \
	"..\lib\ODMA32.lib"

"$(OUTDIR)\ODMATest32.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(CFG)" == "ODMATest32 - Win32 Release" || "$(CFG)" ==\
 "ODMATest32 - Win32 Debug"
SOURCE=.\ChildFrm.cpp

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

DEP_CPP_CHILD=\
	"..\include\odma.h"\
	".\ChildFrm.h"\
	".\ODMATest.h"\
	".\StdAfx.h"\
	
NODEP_CPP_CHILD=\
	".\Resource.h"\
	

"$(INTDIR)\ChildFrm.obj" : $(SOURCE) $(DEP_CPP_CHILD) "$(INTDIR)"\
 "$(INTDIR)\ODMATest32.pch"


!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

DEP_CPP_CHILD=\
	"..\include\odma.h"\
	".\ChildFrm.h"\
	".\ODMATest.h"\
	

"$(INTDIR)\ChildFrm.obj"	"$(INTDIR)\ChildFrm.sbr" : $(SOURCE) $(DEP_CPP_CHILD)\
 "$(INTDIR)" "$(INTDIR)\ODMATest32.pch"


!ENDIF 

SOURCE=.\CntrItem.cpp

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

DEP_CPP_CNTRI=\
	"..\include\odma.h"\
	".\cntritem.h"\
	".\ODMATest.h"\
	".\StdAfx.h"\
	".\TestDoc.h"\
	".\TestView.h"\
	
NODEP_CPP_CNTRI=\
	".\Resource.h"\
	

"$(INTDIR)\CntrItem.obj" : $(SOURCE) $(DEP_CPP_CNTRI) "$(INTDIR)"\
 "$(INTDIR)\ODMATest32.pch"


!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

DEP_CPP_CNTRI=\
	"..\include\odma.h"\
	".\cntritem.h"\
	".\ODMATest.h"\
	".\TestDoc.h"\
	".\TestView.h"\
	

"$(INTDIR)\CntrItem.obj"	"$(INTDIR)\CntrItem.sbr" : $(SOURCE) $(DEP_CPP_CNTRI)\
 "$(INTDIR)" "$(INTDIR)\ODMATest32.pch"


!ENDIF 

SOURCE=.\DMSOpt.cpp

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

DEP_CPP_DMSOP=\
	"..\include\odma.h"\
	".\DMSOpt.h"\
	".\ODMATest.h"\
	".\StdAfx.h"\
	".\TestDoc.h"\
	
NODEP_CPP_DMSOP=\
	".\Resource.h"\
	

"$(INTDIR)\DMSOpt.obj" : $(SOURCE) $(DEP_CPP_DMSOP) "$(INTDIR)"\
 "$(INTDIR)\ODMATest32.pch"


!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

DEP_CPP_DMSOP=\
	"..\include\odma.h"\
	".\DMSOpt.h"\
	".\ODMATest.h"\
	".\TestDoc.h"\
	

"$(INTDIR)\DMSOpt.obj"	"$(INTDIR)\DMSOpt.sbr" : $(SOURCE) $(DEP_CPP_DMSOP)\
 "$(INTDIR)" "$(INTDIR)\ODMATest32.pch"


!ENDIF 

SOURCE=.\DMSQuery.cpp

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

DEP_CPP_DMSQU=\
	"..\include\odma.h"\
	".\DMSQuery.h"\
	".\ODMATest.h"\
	".\StdAfx.h"\
	".\TestDoc.h"\
	
NODEP_CPP_DMSQU=\
	".\Resource.h"\
	

"$(INTDIR)\DMSQuery.obj" : $(SOURCE) $(DEP_CPP_DMSQU) "$(INTDIR)"\
 "$(INTDIR)\ODMATest32.pch"


!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

DEP_CPP_DMSQU=\
	"..\include\odma.h"\
	".\DMSQuery.h"\
	".\ODMATest.h"\
	".\TestDoc.h"\
	

"$(INTDIR)\DMSQuery.obj"	"$(INTDIR)\DMSQuery.sbr" : $(SOURCE) $(DEP_CPP_DMSQU)\
 "$(INTDIR)" "$(INTDIR)\ODMATest32.pch"


!ENDIF 

SOURCE=.\DOCFrmt.cpp

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

DEP_CPP_DOCFR=\
	"..\include\odma.h"\
	".\DOCFrmt.h"\
	".\ODMATest.h"\
	".\StdAfx.h"\
	
NODEP_CPP_DOCFR=\
	".\Resource.h"\
	

"$(INTDIR)\DOCFrmt.obj" : $(SOURCE) $(DEP_CPP_DOCFR) "$(INTDIR)"\
 "$(INTDIR)\ODMATest32.pch"


!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

DEP_CPP_DOCFR=\
	"..\include\odma.h"\
	".\DOCFrmt.h"\
	".\ODMATest.h"\
	

"$(INTDIR)\DOCFrmt.obj"	"$(INTDIR)\DOCFrmt.sbr" : $(SOURCE) $(DEP_CPP_DOCFR)\
 "$(INTDIR)" "$(INTDIR)\ODMATest32.pch"


!ENDIF 

SOURCE=.\MainFrm.cpp

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

DEP_CPP_MAINF=\
	"..\include\odma.h"\
	".\MainFrm.h"\
	".\ODMATest.h"\
	".\StdAfx.h"\
	
NODEP_CPP_MAINF=\
	".\Resource.h"\
	

"$(INTDIR)\MainFrm.obj" : $(SOURCE) $(DEP_CPP_MAINF) "$(INTDIR)"\
 "$(INTDIR)\ODMATest32.pch"


!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

DEP_CPP_MAINF=\
	"..\include\odma.h"\
	".\MainFrm.h"\
	".\ODMATest.h"\
	

"$(INTDIR)\MainFrm.obj"	"$(INTDIR)\MainFrm.sbr" : $(SOURCE) $(DEP_CPP_MAINF)\
 "$(INTDIR)" "$(INTDIR)\ODMATest32.pch"


!ENDIF 

SOURCE=.\ODMATest.cpp

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

DEP_CPP_ODMAT=\
	"..\include\odma.h"\
	".\ChildFrm.h"\
	".\DMSOpt.h"\
	".\DMSQuery.h"\
	".\MainFrm.h"\
	".\ODMATest.h"\
	".\StdAfx.h"\
	".\TestDoc.h"\
	".\TestView.h"\
	
NODEP_CPP_ODMAT=\
	".\Resource.h"\
	

"$(INTDIR)\ODMATest.obj" : $(SOURCE) $(DEP_CPP_ODMAT) "$(INTDIR)"\
 "$(INTDIR)\ODMATest32.pch"


!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

DEP_CPP_ODMAT=\
	"..\include\odma.h"\
	".\ChildFrm.h"\
	".\DMSOpt.h"\
	".\DMSQuery.h"\
	".\MainFrm.h"\
	".\ODMATest.h"\
	".\TestDoc.h"\
	".\TestView.h"\
	

"$(INTDIR)\ODMATest.obj"	"$(INTDIR)\ODMATest.sbr" : $(SOURCE) $(DEP_CPP_ODMAT)\
 "$(INTDIR)" "$(INTDIR)\ODMATest32.pch"


!ENDIF 

SOURCE=.\ODMATest32.rc
DEP_RSC_ODMATE=\
	".\res\ODMATest.ico"\
	".\res\ODMATest.rc2"\
	".\res\TestDoc.ico"\
	

"$(INTDIR)\ODMATest32.res" : $(SOURCE) $(DEP_RSC_ODMATE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /I "..\Include" /D "WIN32" /D "NDEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /Fp"$(INTDIR)\ODMATest32.pch" /Yc"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\ODMATest32.pch" : $(SOURCE) $(DEP_CPP_STDAF)\
 "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /I "..\Include" /D "WIN32" /D\
 "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\"\
 /Fp"$(INTDIR)\ODMATest32.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\"\
 /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\ODMATest32.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\TestDoc.cpp

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

DEP_CPP_TESTD=\
	"..\include\odma.h"\
	".\cntritem.h"\
	".\DOCFrmt.h"\
	".\ODMATest.h"\
	".\StdAfx.h"\
	".\TestDoc.h"\
	
NODEP_CPP_TESTD=\
	".\Resource.h"\
	

"$(INTDIR)\TestDoc.obj" : $(SOURCE) $(DEP_CPP_TESTD) "$(INTDIR)"\
 "$(INTDIR)\ODMATest32.pch"


!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

DEP_CPP_TESTD=\
	"..\include\odma.h"\
	".\cntritem.h"\
	".\DOCFrmt.h"\
	".\ODMATest.h"\
	".\TestDoc.h"\
	

"$(INTDIR)\TestDoc.obj"	"$(INTDIR)\TestDoc.sbr" : $(SOURCE) $(DEP_CPP_TESTD)\
 "$(INTDIR)" "$(INTDIR)\ODMATest32.pch"


!ENDIF 

SOURCE=.\TestView.cpp

!IF  "$(CFG)" == "ODMATest32 - Win32 Release"

DEP_CPP_TESTV=\
	"..\include\odma.h"\
	".\ODMATest.h"\
	".\StdAfx.h"\
	".\TestDoc.h"\
	".\TestView.h"\
	
NODEP_CPP_TESTV=\
	".\Resource.h"\
	

"$(INTDIR)\TestView.obj" : $(SOURCE) $(DEP_CPP_TESTV) "$(INTDIR)"\
 "$(INTDIR)\ODMATest32.pch"


!ELSEIF  "$(CFG)" == "ODMATest32 - Win32 Debug"

DEP_CPP_TESTV=\
	"..\include\odma.h"\
	".\ODMATest.h"\
	".\TestDoc.h"\
	".\TestView.h"\
	

"$(INTDIR)\TestView.obj"	"$(INTDIR)\TestView.sbr" : $(SOURCE) $(DEP_CPP_TESTV)\
 "$(INTDIR)" "$(INTDIR)\ODMATest32.pch"


!ENDIF 


!ENDIF 

