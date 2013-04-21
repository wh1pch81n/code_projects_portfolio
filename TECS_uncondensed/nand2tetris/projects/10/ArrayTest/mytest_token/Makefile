
run_and_compare: 
	python /Users/derrickho/Dropbox/Documents/XcodeProjects/jackTokenizerModule/jackTokenizer.py ../Main.jack > tokenCMP.xml && diff -w -B -y ./tokenCMP.xml ../MainT.xml > diff_report.txt

clean:
	rm tokenCMP.xml *~ diff_report.txt
