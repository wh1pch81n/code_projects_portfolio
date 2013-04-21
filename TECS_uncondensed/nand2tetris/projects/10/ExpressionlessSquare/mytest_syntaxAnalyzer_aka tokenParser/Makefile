PARSER = /Users/derrickho/Dropbox/Documents/XcodeProjects/jackParser/jackParser.py
TOKEN =  /Users/derrickho/Dropbox/Documents/XcodeProjects/jackTokenizerModule/jackTokenizer.py
TARGET1 = ../Main
TARGET2 = ../Square
TARGET3 = ../SquareGame
MY_OUT_XML_t = tokenCMP
MY_OUT_XML_p = parseCMP


run_and_compare: 
	make A B C

A:
	python $(TOKEN) $(TARGET1).jack > $(MY_OUT_XML_t)_1.xml;
	python $(PARSER) $(MY_OUT_XML_t)_1.xml > $(MY_OUT_XML_p)_1.xml;
	diff -w -B -y ./$(MY_OUT_XML_p)_1.xml $(TARGET1).xml > diff_report_1.txt
B:
	python $(TOKEN) $(TARGET2).jack > $(MY_OUT_XML_t)_2.xml;
	python $(PARSER) $(MY_OUT_XML_t)_2.xml > $(MY_OUT_XML_p)_2.xml;
	diff -w -B -y ./$(MY_OUT_XML_p)_2.xml $(TARGET2).xml > diff_report_2.txt
C:
	python $(TOKEN) $(TARGET3).jack > $(MY_OUT_XML_t)_3.xml;
	python $(PARSER) $(MY_OUT_XML_t)_3.xml > $(MY_OUT_XML_p)_3.xml;
	diff -w -B -y ./$(MY_OUT_XML_p)_3.xml $(TARGET3).xml > diff_report_3.txt
clean:
	rm $(MY_OUT_XML_t)* $(MY_OUT_XML_p)* diff_report_*
