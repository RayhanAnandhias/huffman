#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	//char* text = "abbcccddddeeeeeffffffggggggghhhhhhhh";
	//char* text = "abcd";
	//char* text = "streets are stone stars are not";
	//char* text = "LIKA-LIKU LAKI-LAKI TAK LAKU-LAKU";
	char* text = "A SIMPLE STRING TO BE ENCODED USING A MINIMAL NUMBER OF BITS";
	huffman(text);
	return 0;
}
