.PHONY: all test clean
.SILENT: clean
all:
	(cd lexicalAnalyzer; make)
	(cd parser; make)

clean:
	make -s -C lexicalAnalyzer clean
	make -s -C parser clean
    
test:
	(cd lexicalAnalyzer; make test)
	(cd parser; make test)
