EXE = /Users/derrickho/Dropbox/Documents/XcodeProjects/jackParser/jackParser.py
TARGET1 = ../Main
TARGET2 = ../Square
TARGET3 = ../SquareGame
MY_OUT_XML = tokenCMP

run_and_compare: 
	make A B C

A:
	python $(EXE) $(TARGET1)T.xml > $(MY_OUT_XML)_1.xml && diff -w -B -y ./$(MY_OUT_XML)_1.xml $(TARGET1).xml > diff_report_1.txt
B:
	python $(EXE) $(TARGET2)T.xml > $(MY_OUT_XML)_2.xml && diff -w -B -y ./$(MY_OUT_XML)_2.xml $(TARGET2).xml > diff_report_2.txt
C:
	python $(EXE) $(TARGET3)T.xml > $(MY_OUT_XML)_3.xml && diff -w -B -y ./$(MY_OUT_XML)_3.xml $(TARGET3).xml > diff_report_3.txt
clean:
	rm tokenCMP_* *~ diff_report_*
