PARSER = /Users/derrickho/Dropbox/Documents/XcodeProjects/jackParser/jackParser.py
TOKEN =  /Users/derrickho/Dropbox/Documents/XcodeProjects/jackTokenizerModule/jackTokenizer.py
TARGET1 = ../Main

MY_OUT_XML_t = tokenCMP
MY_OUT_XML_p = parseCMP


run_and_compare: 
	make A

A:
	python $(TOKEN) $(TARGET1).jack > $(MY_OUT_XML_t)_1.xml;
	python $(PARSER) $(MY_OUT_XML_t)_1.xml > $(MY_OUT_XML_p)_1.xml;
	#diff -w -B -y ./$(MY_OUT_XML_p)_1.xml $(TARGET1).xml > diff_report_1.txt
clean:
	rm $(MY_OUT_XML_t)* $(MY_OUT_XML_p)* diff_report_*
