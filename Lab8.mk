##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=Lab8
ConfigurationName      :=Debug
WorkspacePath          :=/u/b/blackiek/Documents/2019_APS105/myworkspace
ProjectPath            :=/u/b/blackiek/Documents/2019_APS105/myworkspace/Lab8
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Kyle Ian  Blackie
Date                   :=31/03/19
CodeLitePath           :=/u/b/blackiek/.codelite
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="Lab8.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/lab8part1.c$(ObjectSuffix) $(IntermediateDirectory)/lab8part2.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/lab8part1.c$(ObjectSuffix): lab8part1.c $(IntermediateDirectory)/lab8part1.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/u/b/blackiek/Documents/2019_APS105/myworkspace/Lab8/lab8part1.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lab8part1.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lab8part1.c$(DependSuffix): lab8part1.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lab8part1.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lab8part1.c$(DependSuffix) -MM lab8part1.c

$(IntermediateDirectory)/lab8part1.c$(PreprocessSuffix): lab8part1.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lab8part1.c$(PreprocessSuffix) lab8part1.c

$(IntermediateDirectory)/lab8part2.c$(ObjectSuffix): lab8part2.c $(IntermediateDirectory)/lab8part2.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/u/b/blackiek/Documents/2019_APS105/myworkspace/Lab8/lab8part2.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/lab8part2.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/lab8part2.c$(DependSuffix): lab8part2.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/lab8part2.c$(ObjectSuffix) -MF$(IntermediateDirectory)/lab8part2.c$(DependSuffix) -MM lab8part2.c

$(IntermediateDirectory)/lab8part2.c$(PreprocessSuffix): lab8part2.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/lab8part2.c$(PreprocessSuffix) lab8part2.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


