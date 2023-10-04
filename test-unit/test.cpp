#include "../src/main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("BST Insert", "[flag]"){
	
		tree tree; 
		Node* root=nullptr;
		Node* node=nullptr;
		tree.insertNAMEID(root, "Eman Douglas" , 00000000);
		tree.insertNAMEID(root, "Afer FEfwef" , 10000000);
		tree.insertNAMEID(root, "Sfegew Afreg" , 58000000);
		tree.insertNAMEID(root, "Fvrege Fgfwe" , 80000000);
		tree.insertNAMEID(root, "Ffre Fewf" , 20000000);
		tree.insertNAMEID(root, "Ffrere Fewe" , 90000000);
		tree.insertNAMEID(root, "Fgre Ffe" , 34000000);
		tree.insertNAMEID(root, "Fewe" , 35000000);
		
		
		tree.printLevelCount(node);
		
		
	REQUIRE(1 == 1);
}
