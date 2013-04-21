# the purpose of this make file is to help build vm files and move them to the right spots

PATH = /Users/derrickho/Dropbox/nand2tetris/projects/12
MY_CLASS = /Users/derrickho/Dropbox/nand2tetris/projects/12/MY_CLASS
FOLDER_g =

MOVE = /bin/mv
FIND = /usr/bin/find
######
#default:
#	@echo ""
#	@echo "\tthis will move the vm files from MY_CLASS to a specific test folder"
#	@echo "\tspecify folder name:"
#	@echo "\tmake _<FOLDERNAME>"
#	@echo ""
#
######
all:
	@make BUILDCLASS PREP_GENERIC

BUILDCLASS:
	@/bin/sh ./JackCompiler.sh $(MY_CLASS) && echo "Finished Building Class"
PREP_GENERIC:
	@read -p "    Tell me folder name:  " FOLDER_g ;\
	$(FIND) $(MY_CLASS) -name "*.vm" -exec $(MOVE) {} $(PATH)/$$FOLDER_g  \;


######
FOLDER_1 = StringTest
_$(FOLDER_1) :
	$(FIND) $(MY_CLASS) -name "*.vm" -exec $(MOVE) {} $(PATH)/$(FOLDER_1)  \;


FOLDER_2 = SpecialTests
_$(FOLDER_2) :
	$(FIND) $(MY_CLASS) -name "*.vm" -exec $(MOVE) {} $(PATH)/$(FOLDER_2)  \;

FOLDER_3 = ArrayTest
_$(FOLDER_3) :
	$(FIND) $(MY_CLASS) -name "*.vm" -exec $(MOVE) {} $(PATH)/$(FOLDER_3)  \;

FOLDER_4 = SysTest
_$(FOLDER_4) :
	$(FIND) $(MY_CLASS) -name "*.vm" -exec $(MOVE) {} $(PATH)/$(FOLDER_4)  \;

FOLDER_5 = KeyboardTest
_$(FOLDER_5) :
	$(FIND) $(MY_CLASS) -name "*.vm" -exec $(MOVE) {} $(PATH)/$(FOLDER_5)  \;

FOLDER_6 = MemoryTest
_$(FOLDER_6) :
	$(FIND) $(MY_CLASS) -name "*.vm" -exec $(MOVE) {} $(PATH)/$(FOLDER_6)  \;

