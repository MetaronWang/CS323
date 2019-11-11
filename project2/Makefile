PP=g++
FLEX=flex
BISON=bison


.lex: lex.l
	$(FLEX) lex.l
.pro_2: pro_2.y
	$(BISON) -v -t -d pro_2.y
sqlc: .lex .pro_2
	$(PP) pro_2.tab.c  -o splc.out
clean:
	@rm -f lex.yy.c pro_2.tab.* *.out *.so
