#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
	char* text = "LIKA-LIKU LAKI-LAKI TAK LAKU-LAKU";
	//char* text = "abbcccddddeeeeeffffffggggggghhhhhhhh";
	huffman(text);
	return 0;
}
