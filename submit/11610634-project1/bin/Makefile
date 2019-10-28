PP=g++
FLEX=flex
BISON=bison


.lex: lex.l
	$(FLEX) lex.l
.pro_1: pro_1.y
	$(BISON) -v -t -d pro_1.y
sqlc: .lex .pro_1
	$(PP) pro_1.tab.c  -o splc
	@rm pro_1.tab.* lex.yy.*
clean:
	@rm -f lex.yy.c pro_1.tab.* *.out *.so
