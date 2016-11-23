#include <stdio.h>
#include <SymbolTable.h>
#include <Parser.h>
#include <Scanner.h>
#include <sys/timeb.h>
#include <wchar.h>

using namespace trix;

int main (int argc, char *argv[]) {

	if (argc == 2) {
		wchar_t *fileName = coco_string_create(argv[1]);
		Scanner *scanner = new Scanner(fileName);
		Parser *parser = new Parser(scanner);
		parser->tab = new SymbolTable(parser);
		parser->Parse();

		coco_string_delete(fileName);
		delete parser->tab;
		delete parser;
		delete scanner;
	} else {
		printf("-- No source file specified\n");
	}

	return 0;

}
