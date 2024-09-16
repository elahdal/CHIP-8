##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Projet_CHIP8
ConfigurationName      :=Debug
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/yass/Documents/projet_chip8/Projet_CHIP8
ProjectPath            :=/home/yass/Documents/projet_chip8/Projet_CHIP8/Projet_CHIP8
IntermediateDirectory  :=../build-$(ConfigurationName)/Projet_CHIP8
OutDir                 :=../build-$(ConfigurationName)/Projet_CHIP8
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Yass
Date                   :=04/02/24
CodeLitePath           :=/home/yass/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  -lprovided -lSDL2
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)libprovided/include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)libprovided/lib/debug/x64 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=../build-$(ConfigurationName)/Projet_CHIP8/Processeur.c$(ObjectSuffix) ../build-$(ConfigurationName)/Projet_CHIP8/ram.c$(ObjectSuffix) ../build-$(ConfigurationName)/Projet_CHIP8/emulateur.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/Projet_CHIP8/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/Projet_CHIP8"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/Projet_CHIP8"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/Projet_CHIP8/.d:
	@mkdir -p "../build-$(ConfigurationName)/Projet_CHIP8"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/Projet_CHIP8/Processeur.c$(ObjectSuffix): Processeur.c ../build-$(ConfigurationName)/Projet_CHIP8/Processeur.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/yass/Documents/projet_chip8/Projet_CHIP8/Projet_CHIP8/Processeur.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Processeur.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/Projet_CHIP8/Processeur.c$(DependSuffix): Processeur.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/Projet_CHIP8/Processeur.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/Projet_CHIP8/Processeur.c$(DependSuffix) -MM Processeur.c

../build-$(ConfigurationName)/Projet_CHIP8/Processeur.c$(PreprocessSuffix): Processeur.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/Projet_CHIP8/Processeur.c$(PreprocessSuffix) Processeur.c

../build-$(ConfigurationName)/Projet_CHIP8/ram.c$(ObjectSuffix): ram.c ../build-$(ConfigurationName)/Projet_CHIP8/ram.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/yass/Documents/projet_chip8/Projet_CHIP8/Projet_CHIP8/ram.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ram.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/Projet_CHIP8/ram.c$(DependSuffix): ram.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/Projet_CHIP8/ram.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/Projet_CHIP8/ram.c$(DependSuffix) -MM ram.c

../build-$(ConfigurationName)/Projet_CHIP8/ram.c$(PreprocessSuffix): ram.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/Projet_CHIP8/ram.c$(PreprocessSuffix) ram.c

../build-$(ConfigurationName)/Projet_CHIP8/emulateur.c$(ObjectSuffix): emulateur.c ../build-$(ConfigurationName)/Projet_CHIP8/emulateur.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/yass/Documents/projet_chip8/Projet_CHIP8/Projet_CHIP8/emulateur.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/emulateur.c$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/Projet_CHIP8/emulateur.c$(DependSuffix): emulateur.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/Projet_CHIP8/emulateur.c$(ObjectSuffix) -MF../build-$(ConfigurationName)/Projet_CHIP8/emulateur.c$(DependSuffix) -MM emulateur.c

../build-$(ConfigurationName)/Projet_CHIP8/emulateur.c$(PreprocessSuffix): emulateur.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/Projet_CHIP8/emulateur.c$(PreprocessSuffix) emulateur.c


-include ../build-$(ConfigurationName)/Projet_CHIP8//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


