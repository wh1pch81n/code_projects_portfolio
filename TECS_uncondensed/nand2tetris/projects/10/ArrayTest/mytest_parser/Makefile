EXE = /Users/derrickho/Dropbox/Documents/XcodeProjects/jackParser/jackParser.py
TARGET1 = ../Main
MY_OUT_XML = tokenCMP

run_and_compare: 
	make A

A:
	python $(EXE) $(TARGET1)T.xml > $(MY_OUT_XML)_1.xml && diff -w -B -y ./$(MY_OUT_XML)_1.xml $(TARGET1).xml > diff_report_1.txt

clean:
	rm tokenCMP_* diff_report_*
