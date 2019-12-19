PP=g++
FLEX=flex
BISON=bison


.lex: lex.l
	$(FLEX) lex.l
.pro_3: pro_3.y
	$(BISON) -v -t -d pro_3.y
splc: .lex .pro_3
	$(PP) pro_3.tab.c  -o splc.out
clean:
	@rm -f lex.yy.c pro_3.tab.* *.out *.so *.aux *.log *.gz *.output test/*.out test/*.ir
