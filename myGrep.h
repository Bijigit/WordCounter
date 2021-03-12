typedef struct OccurrenceNode OccurrenceNode;

struct OccurrenceNode{
    char lineText[150];
    int lineNumber;
    int wordPosition;
    OccurrenceNode * next;
};

int updateLongestLine(int currentLongestLength, char * longestLine, char * currentLine);
void printLinkedList(OccurrenceNode * head, OccurrenceNode * temp);

