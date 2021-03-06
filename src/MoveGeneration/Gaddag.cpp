
//INCLUDES:

#include <iostream>
#include <math.h>
#include <unordered_map>
#include "Gaddag.h"
#include "LoadGaddag.h"
using namespace std;

#define ADDRESS_OFFSET_CASTING 0x00FFFFFF // To get the address part of a node's first child from the "node info" data member.
#define LAST_CHILD_OFFSET_CASTING 0x40000000
/* To get the flag part from the "node info" data member of the "lastchild" which indicates if '1'
means this node's last child else '0' .*/
#define END_OF_WORD_OFFSET_CASTING 0x20000000 /* To get the flag part from the "node info" data member of the "lastchar" which indicates if '1'
means a valid word is formed else '0' .*/
#define CHAR_OFFSET_CASTING 0x0000001F // To get the compressed 5-bit data character.
#define CHAR_SHIFT_VALUE 24 // Shifting value as the the char is stored in the "5-bits most signincant bits".

Node::Node(){
    //nothing
	nodeInfo = 0;
}

/*
The Function findChildChar is given a letter it finds the child (domain of search only in this parent's childs)
with this specific letter returns NULL if not found.
*/
Node* Node::findChildChar(char letter){
    Node*child = getFirstChild();
    //cout<<std::hex<<this<<endl;
    while(child!=NULL){
    	//cout<<std::hex<<this<<" .. "<<++index<<endl;
    	char temp = child->getNodeLetter();
        if(temp == letter){return child;}
        child = child->getNextChild();
    }

    return NULL; // not found.
}


//The function getFirstChild it gets first childs uncompressed.
Node* Node::getFirstChild(){
    int addressCastOffset = (nodeInfo & ADDRESS_OFFSET_CASTING);

    return addressCastOffset != 0 ? this + (addressCastOffset) : 0;
}

//The Function isLastChild the node is last character in a valid word.
bool Node::isLastChild(){
    return ((nodeInfo & LAST_CHILD_OFFSET_CASTING) == LAST_CHILD_OFFSET_CASTING);
}

//The Function getNextChild it gets a successor in parent's childs.
Node* Node::getNextChild(){
    if (!isLastChild()){
        return this + 1;
    }
    else {return 0;}
}

//Function getNodeLetter it retuns the node character.
char Node::getNodeLetter(){
    if(((nodeInfo>>CHAR_SHIFT_VALUE) & CHAR_OFFSET_CASTING) ==  COMPRESSED_GADDAG_DELIMITER){
        return GADDAG_DELIMITER;
    }
    return (char)(CHAR_OFFSET + ((nodeInfo>>CHAR_SHIFT_VALUE) & CHAR_OFFSET_CASTING));
}

//The Function getNodeInfo it returns node info.
int Node :: getNodeInfo(){
	return nodeInfo;
}

//The Function isEndofWord the node is EOW .. end of word means a word or sub-word has been reached.
bool Node::isEndOfWord(){
    return ((nodeInfo & END_OF_WORD_OFFSET_CASTING) == END_OF_WORD_OFFSET_CASTING);
 }

