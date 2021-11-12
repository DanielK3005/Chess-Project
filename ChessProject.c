#include "ChessProject.h"

/* this function make a list empty */
void makeEmptyList(chessPosList* lst)
{
	lst->head = NULL;
	lst->tail = NULL;
}
/* seif 4*/
chessPosList* findKnightPathCoveringAllBoard(pathTree* pathTree)
{
	chessPosList* lst = (chessPosList*)malloc(1 * sizeof(chessPosList));
	allocCheck(&lst);
	makeEmptyList(lst);

	int level = 0;
	bool pathFound = false;
	findKnightPathCoveringAllBoardHelper(pathTree->root->next_possible_positions, lst, &level, &pathFound);

	if (lst->head)
	{
		insertDataToStartList(lst, pathTree->root->position);
		return lst;
	}
	else
	{
		return NULL;
	}
}
/* seif 4 helper */
void findKnightPathCoveringAllBoardHelper(treeNodeListCell* position, chessPosList* lst, int* level, bool* pathFound)
{
	if (position == NULL)
	{
		*level -= 1;
		return;
	}

	else
	{
		*level += 1;
		findKnightPathCoveringAllBoardHelper(position->node->next_possible_positions, lst, level, pathFound);
		if (*level >= (SIZE * SIZE) - 2 || *pathFound == true)
		{
			*pathFound = true;
			insertDataToStartList(lst, position->node->position);
			return;
		}

		if (position->next)
		{
			findKnightPathCoveringAllBoardHelper(position->next, lst, level, pathFound);
			*level += 1;
		}
		*level -= 1;
	}

}
/* memory alloc check */
void allocCheck(void* address)
{
	if (address == NULL)
	{
		printf("Memory alloc failiere!");
		exit(1);
	}
}
/* create a list node of knight location */
chessPosCell* createNewListNode(chessPos position, chessPosCell* next)
{
	chessPosCell* res;
	res = (chessPosCell*)malloc(sizeof(chessPosCell));
	allocCheck(&res);
	res->position[0] = position[0];
	res->position[1] = position[1];
	res->next = next;
	return res;
}
/* insert data to start list */
void insertDataToStartList(chessPosList* lst, chessPos position)
{
	chessPosCell* newHaed;
	newHaed = createNewListNode(position, NULL);
	insertNodeToStartList1(lst, newHaed);
}
/* insert a list node to start of a list */
void insertNodeToStartList1(chessPosList* lst, chessPosCell* head)
{
	if (isEmptyList(lst))
	{
		head->next = NULL;
		lst->head = lst->tail = head;
	}
	else
	{
		head->next = lst->head;
		lst->head = head;
	}
}
/* check if list is empty */
bool isEmptyList(chessPosList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}
/* print list data */
void printList(chessPosList* lst)
{
	if (isEmptyList(lst))
	{
		return;
	}
	chessPosCell* curr;
	curr = lst->head;
	while (curr != NULL)
	{
		printf("%c%c ", curr->position[0], curr->position[1]);
		curr = curr->next;
	}
	printf("\n");
}
/* seif 1*/
chessPosArray*** validKnightMoves()
{
	chessPosArray*** KnightMoves;
	int i, j;

	KnightMoves = (chessPosArray***)malloc(SIZE * sizeof(chessPosArray**));
	if (KnightMoves == NULL)
		exit(1);

	for (i = 0; i < SIZE; i++)
	{
		KnightMoves[i] = (chessPosArray**)malloc(SIZE * sizeof(chessPosArray*));
		if (KnightMoves[i] == NULL)
			exit(1);
	}

	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			KnightMoves[i][j] = CheckCellMoves(i, j);
		}
	}

	return KnightMoves;
}
/* second function for seif 1*/
chessPosArray* CheckCellMoves(int row, int col)
{
	chessPosArray* res = (chessPosArray*)malloc(sizeof(chessPosArray));
	if (res == NULL)
		exit(1);

	res->positions = (chessPos*)malloc(MAXPOS * sizeof(chessPos));
	int count = 0;

	if (res->positions == NULL)
		exit(1);

	if (row - 2 >= 0 && col - 1 >= 0) /*Up Left*/
	{
		res->positions[count][0] = (row - 2) + 'A';
		res->positions[count][1] = (col - 1) + '1';
		count++;
	}
	if (row - 2 >= 0 && col + 1 < SIZE) /*Up Right*/
	{
		res->positions[count][0] = (row - 2) + 'A';
		res->positions[count][1] = (col + 1) + '1';
		count++;
	}
	if (col + 2 < SIZE && row - 1 >= 0) /*Right Up*/
	{
		res->positions[count][0] = (row - 1) + 'A';
		res->positions[count][1] = (col + 2) + '1';
		count++;
	}
	if (col + 2 < SIZE && row + 1 < SIZE) /*Right Down*/
	{
		res->positions[count][0] = (row + 1) + 'A';
		res->positions[count][1] = (col + 2) + '1';
		count++;
	}
	if (row + 2 < SIZE && col - 1 >= 0) /*Down Left*/
	{
		res->positions[count][0] = (row + 2) + 'A';
		res->positions[count][1] = (col - 1) + '1';
		count++;
	}
	if (row + 2 < SIZE && col + 1 < SIZE) /*Down Right*/
	{
		res->positions[count][0] = (row + 2) + 'A';
		res->positions[count][1] = (col + 1) + '1';
		count++;
	}
	if (col - 2 >= 0 && row - 1 >= 0) /*Left Up*/
	{
		res->positions[count][0] = (row - 1) + 'A';
		res->positions[count][1] = (col - 2) + '1';
		count++;
	}
	if (col - 2 >= 0 && row + 1 < SIZE) /*Left Down*/
	{
		res->positions[count][0] = (row + 1) + 'A';
		res->positions[count][1] = (col - 2) + '1';
		count++;
	}

	res->size = count;
	res->positions = (chessPos*)realloc(res->positions, count * sizeof(chessPos));
	allocCheck(&res->positions);

	return res;
}
/* seif 3 */
pathTree findAllPossibleKnightPaths(chessPos startingPosition)
{
	bool path[SIZE][SIZE];
	initTable(path, SIZE, SIZE);
	chessPosArray*** mat = validKnightMoves();

	pathTree tr;

	tr.root = findAllPossibleKnightPathsHelper(startingPosition, mat, path);

	freeMat(mat);
	return tr;
}
/* seif 3 helper */
treeNode* findAllPossibleKnightPathsHelper(chessPos rootdata, chessPosArray*** board, bool path[][SIZE])
{
	treeNode* root, * temp;
	unsigned int i, k, l;

	if (checkExistPos(path, rootdata))
		return NULL;
	else
	{
		root = createNewTreeNode(rootdata);
		k = rootdata[0] - 'A';
		l = rootdata[1] - '1';
		path[k][l] = true;
		for (i = 0; i < board[k][l]->size; i++)
		{
			if (!checkExistPos(path, board[k][l]->positions[i]))
			{
				temp = findAllPossibleKnightPathsHelper(board[k][l]->positions[i], board, path);
				insertDNodeToStartList(root, temp);
			}
		}
		path[k][l] = false;
	}
	return root;
}
/* this function intialize a two dimensional array of boolians */
void initTable(bool path[][SIZE], int rows, int cols)
{
	int i, j;
	for (i = 0; i < rows; i++)
		for (j = 0; j < cols; j++)
			path[i][j] = false;
}
/* insert a tree list node to start of tree-list nodes */
void insertDNodeToStartList(treeNode* head, treeNode* Node)
{
	treeNodeListCell* NewNode;
	NewNode = CreateTreeNodeListCell(Node);
	insertNodeToStartList(head, NewNode);
}
/* insert a tree list node to start of tree-list nodes */
void insertNodeToStartList(treeNode* head, treeNodeListCell* NewNode)
{
	if (isEmptyTreeList(head->next_possible_positions) == true)
	{
		head->next_possible_positions = NewNode;
		NewNode->next = NULL;
	}
	else
	{
		NewNode->next = head->next_possible_positions;
		head->next_possible_positions = NewNode;
	}

}
/* create a tree node */
treeNodeListCell* CreateTreeNodeListCell(treeNode* node)
{
	treeNodeListCell* NewCell = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	if (NewCell == NULL)
		exit(1);

	NewCell->node = node;
	NewCell->next = NULL;

	return NewCell;
}
/* check if tree list is empty */
bool isEmptyTreeList(treeNodeListCell* head)
{
	if (head == NULL)
		return true;
	else
		return false;
}
/* check if a chesspos was already been touched  */
bool checkExistPos(bool path[][SIZE], chessPos position)
{
	int i, j;

	i = position[0] - 'A';
	j = position[1] - '1';

	if (path[i][j] == true)
		return true;
	else
		return false;
}
/* create New Tree Node */
treeNode* createNewTreeNode(chessPos position)
{
	treeNode* tNode;

	tNode = (treeNode*)malloc(sizeof(treeNode));
	if (tNode == NULL)
		exit(6);

	tNode->position[0] = position[0];
	tNode->position[1] = position[1];

	tNode->next_possible_positions = NULL;

	return tNode;
}
/* seif 5 */
void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	if (isEmptyList(pos_list))
	{
		printf("List is Empty!..");
		return;
	}

	int i = 0;
	short int size = sizeOfList(pos_list); /* realloc */

	FILE* fpw = fopen(file_name, "wb");
	fileOpenCheck(fpw);

	fwrite(&size, sizeof(short int), 1, fpw); /* write the size of the list */

	int size_of_array = (size * 6 / 8) + 1;

	BYTE* bitsArr = (BYTE*)malloc(size_of_array * sizeof(BYTE));
	allocCheck(&bitsArr);
	BYTE tmp;
	BYTE saver1, saver2;

	chessPosCell* curr = pos_list->head;

	while (curr) /* we will divide it to 3 diffrent options by % 3*/
	{
		/* we have a cycle of 3 steps */

		/* first step */
		tmp = 0x00;
		saver1 = 0x00;
		tmp |= (curr->position[0] - 'A') << 5; /* this gives us 1110_0000 */
		tmp |= (curr->position[1] - '1') << 2; /* this gives us 0001_1100 */
		if (curr->next)
		{
			saver1 = 0x00;
			saver1 |= (curr->next->position[0] - 'A') << 7; /* this give us 1000_0000 we want that for later */
			tmp |= (curr->next->position[0] - 'A') >> 1; /* this give us 0000_0011 to add to the tmp BYTE */

			bitsArr[i] = tmp; /* insert to array */
			i++; /* array index value update */
			curr = curr->next; /* moving on to the next location */
		}
		else
		{
			bitsArr[i] = tmp; /* insert to array */
			i++; /* array index value update */
			break;
		}

		/* second step */

		tmp = 0x00;
		saver2 = 0x00;
		tmp |= saver1; /* which is 1000_0000 */
		tmp |= (curr->position[1] - '1') << 4; /* 0111_0000*/
		if (curr->next)
		{
			tmp |= (curr->next->position[0] - 'A') << 1; /* is 0000_1110 */
			saver2 = 0x00;
			saver2 |= (curr->next->position[1] - '1') << 6; /* which is 1100_0000*/
			tmp |= (curr->next->position[1] - '1') >> 2; /* which gives us this 0000_0001*/

			bitsArr[i] = tmp; /* insert to array*/
			i++;
			if (curr->next->next)
			{
				curr = curr->next->next;
			}
			else
			{
				tmp = 0x00;
				tmp |= saver2;
				bitsArr[i] = tmp;
				i++;
				break; /* since there isn't anymore locations we break and skip the third step */

				/* this case have 6 bits off at the end */
			}
		}
		else
		{
			bitsArr[i] = tmp;
			i++;
			break;

			/* this case have 4 bits off at the end */
		}

		/* third step */

		tmp = 0x00;
		tmp |= saver2;
		tmp |= (curr->position[0] - 'A') << 3; /* this gives us 0011_1000*/
		tmp |= (curr->position[1] - '1'); /* 0000_0111*/

		bitsArr[i] = tmp;
		i++;
		if (curr->next)
		{
			curr = curr->next;
		}
		else
		{
			break;
		}

		/* this case have NONE bits off at the end */

	}
	/* after we got all positions */

	fwrite(bitsArr, sizeof(BYTE), size_of_array, fpw); /* size_of_array == the value of i */
	free(bitsArr);
	fclose(fpw);
}
/* calculate size of list nodes in list */
short int sizeOfList(chessPosList* pos_list)
{
	if (pos_list->head == NULL)
		return 0;

	chessPosCell* curr = pos_list->head;
	short int counter = 0;
	while (curr)
	{
		counter++;
		curr = curr->next;
	}
	return counter;

}
/* file openning seccess check */
void fileOpenCheck(FILE* fp)
{
	if (fp == NULL)
	{
		printf("Failed opening the file. \n");
		exit(1);
	}
}
/* seif 6 */
int checkAndDisplayPathFromFile(char* fileName)
{
	FILE* data;
	chessPosList* lst = (chessPosList*)malloc(sizeof(chessPosList));
	makeEmptyList(lst);

	data = fopen(fileName, "rb");
	if (data == NULL) /*case of file doesn't exist */
	{
		return -1;
	}

	makeListFromFile(data, lst); /* read and create the list from the file */
	fclose(data);

	if (!CheckValidKnightPath(lst))
		return 1;

	display(lst); /* if list is valid we call display func */

	int size = sizeOfList(lst);

	if (size == SIZE * SIZE)
	{
		freeList(lst);
		return 2;
	}
	else
	{
		freeList(lst);
		return 3;
	}

}
/*function that checks if the path in the list is valid*/
bool CheckValidKnightPath(chessPosList* lst)
{
	chessPosCell* curr = lst->head;
	bool validpath = true;

	if (isEmptyList(lst))
		return false;

	while (curr->next != NULL && validpath == true)
	{
		if (!CheckValidMove(curr, curr->next))
		{
			validpath = false;
			break;
		}
		curr = curr->next;
	}
	return validpath;
}
/* function that gets 2 cells and check if the move from the current pos to the next pos is valid*/
bool CheckValidMove(chessPosCell* curr, chessPosCell* nextPos)
{
	int rowCurr, colCurr, rowNext, colNext;

	rowCurr = curr->position[0] - 'A';
	colCurr = curr->position[1] - '1';
	rowNext = nextPos->position[0] - 'A';
	colNext = nextPos->position[1] - '1';

	/*direction: clockwise*/
	if (rowCurr - 2 == rowNext && colCurr + 1 == colNext) /*Up Right*/
		return true;
	else if (colCurr + 2 == colNext && rowCurr - 1 == rowNext) /*Right Up*/
		return true;
	else if (colCurr + 2 == colNext && rowCurr + 1 == rowNext) /*Right Down*/
		return true;
	else if (rowCurr + 2 == rowNext && colCurr + 1 == colNext) /*Down Right*/
		return true;
	else if (rowCurr + 2 == rowNext && colCurr - 1 == colNext) /*Down Left*/
		return true;
	else if (colCurr - 2 == colNext && rowCurr + 1 == rowNext) /*Left Down*/
		return true;
	else if (colCurr - 2 == colNext && rowCurr - 1 == rowNext) /*Left Up*/
		return true;
	else if (rowCurr - 2 == rowNext && colCurr - 1 == colNext) /*Up Left*/
		return true;
	else
		return false;
}
/* seif 2 */
void display(chessPosList* lst)
{
	if (isEmptyList(lst)) /* empty list check */
		return;

	checkDoubleOccurrences(lst); /* checking double occurrences */
	printChessBoard(lst); /* print the chess board */
}
/* this function deletes a node from a list */
void deleteNodeFromChessList(chessPosList* lst, chessPosCell* node)
{
	chessPosCell* curr, * prev;

	if (lst->head == lst->tail) /*  == node)*/
	{
		lst->head = lst->tail = NULL;
		free(node);
	}
	else if (lst->head == node) /* delete the head node */
	{
		lst->head = lst->head->next;
		free(node);
	}
	else if (lst->tail == node) /* delete tail node */
	{
		curr = lst->head;
		while (curr->next)
		{
			if (curr->next->next == NULL) /* in other words Ycurr is one behind the last node we need to delete */
			{
				lst->tail = curr;
				break;
			}
			curr = curr->next;
		}
		lst->tail->next = NULL;
		free(node);
	}
	else /* middle */
	{
		curr = lst->head->next;
		prev = lst->head;
		while (curr)
		{
			if (curr == node)
			{
				prev->next = curr->next;
				free(node);
				break;
			}
			curr = curr->next;
			prev = prev->next;
		}
	}
}
/* this function check if there is same positions in the list */
void checkDoubleOccurrences(chessPosList* lst)
{
	bool posTable[SIZE][SIZE];
	initTable(posTable, SIZE, SIZE);

	if (isEmptyList(lst)) /* check if list is empty */
		return;
	else if (lst->head->next == NULL) /* if list as only one node there is nothing to check */
		return;

	chessPosCell* curr1; /* set up a pointer that will help us run the entire list and check positions */
	curr1 = lst->head;

	while (curr1->next) /* loop to check if there is same positions at the list */
	{
		if (checkExistPosition(posTable, SIZE, SIZE, curr1->position) == true) /* this function checks if the position at the list has double occurrences */
		{
			deleteNodeFromChessList(lst, curr1); /* delete the extra node */
		}
		curr1 = curr1->next;
	}
	/* eficient ~ (N) */;
}
/* this function prints the chess board */
void printChessBoard(chessPosList* lst)
{
	int chessBoard[SIZE][SIZE];
	initBoard(chessBoard, SIZE, SIZE, lst);
	int col, row, count = 0;

	printf("    ");
	for (col = 1; col <= SIZE; col++)
		printf(" %d     ", col);

	printf("\n");
	printf("   ");
	printLine(35, '_');
	char rowCh = 'A';
	for (row = 0; row < SIZE; row++)
	{
		printf("%c |", rowCh);
		rowCh++;
		for (col = 0; col < SIZE; col++)
		{
			if (chessBoard[row][col] >= 0)
				printf("  %d  |", chessBoard[row][col]);
			else
			{
				printf("%s", "   |");
			}
		}
		printf("\n");
	}
	printf("   ");
	printLine(35, '_');
}
/* print a line of sort */
void printLine(int count, char ch)
{
	int i;

	for (i = 0; i < count; i++)
		printf("%c", ch);

	printf("\n");
}
/* this function sets the display board*/
void initBoard(int chessBoard[][SIZE], int rows, int cols, chessPosList* lst)
{
	int i, j, count = 1;
	chessPosCell* curr;
	curr = lst->head;
	while (curr)
	{
		i = curr->position[0] - 'A';
		j = curr->position[1] - '1';
		chessBoard[i][j] = count;
		count++;
		curr = curr->next;
	}
}
/* create a list from binary file */
void makeListFromFile(FILE* data, chessPosList* lst)
{
	int i, numBytes;
	BYTE tempData[3];	/* we read 3 bytes each time and we convert them to 4 locations */

	/* the following is equivalent to fileSize() */
	fseek(data, 0, SEEK_END);
	numBytes = (int)ftell(data) - 2;
	fseek(data, 0, SEEK_SET);   //or, to rewind();

	fseek(data, 2, SEEK_SET); /* skip the short int value of size of locations */
	for (i = 0; i < numBytes; i += 3)   //we read 3 bytes at a time
	{
		if (numBytes % 3 == 0)
		{
			fread(tempData, sizeof(BYTE), 3, data);
			getDecodedData(tempData, lst, 3);
		}
		else if (numBytes % 3 == 1)
		{
			if (numBytes - 1 == i) /* last byte to be read from file */
			{
				fread(tempData, sizeof(BYTE), 1, data);
				getDecodedData(tempData, lst, 1);
			}
			else
			{
				fread(tempData, sizeof(BYTE), 3, data);
				getDecodedData(tempData, lst, 3);
			}
		}
		else if (numBytes % 3 == 2)
		{
			if (numBytes - 2 == i) /* last two bytes to be read from file */
			{
				fread(tempData, sizeof(BYTE), 2, data);
				getDecodedData(tempData, lst, 2);
			}
			else
			{
				fread(tempData, sizeof(BYTE), 3, data);
				getDecodedData(tempData, lst, 3);
			}
		}
	}
}
/* translate binary file to chesspos */
void getDecodedData(BYTE* data, chessPosList* lst, int size)
{
	BYTE mask1 = 0xE0;	/* 11100000  byte 1 (most significant byte - the left most one) */
	BYTE mask2 = 0x1C;	/* 00011100  byte 1 */
	BYTE mask3a = 0x03, mask3b = 0x80;	/* 0000001110000000 bytes 1+2 */
	BYTE mask4 = 0x70;	/* 01110000  byte 2 */
	BYTE mask5 = 0x0E;	/* 00001110  byte 2 */
	BYTE mask6a = 0x01, mask6b = 0xC0;	/* 0000000111000000 bytes 2+3 */
	BYTE mask7 = 0x38;	/* 00111000  byte 3 (least significant byte) */
	BYTE mask8 = 0x07;	/* 00000111	byte 3  */

	chessPos pos1, pos2, pos3, pos4;
	if (size == 3)
	{
		pos1[0] = ((data[0] & mask1) >> 5) + 'A';
		pos1[1] = ((data[0] & mask2) >> 2) + '1';
		pos2[0] = (((data[0] & mask3a) << 1) | ((data[1] & mask3b) >> 7)) + 'A';
		pos2[1] = ((data[1] & mask4) >> 4) + '1';
		pos3[0] = ((data[1] & mask5) >> 1) + 'A';
		pos3[1] = (((data[1] & mask6a) << 2) | ((data[2] & mask6b) >> 6)) + '1';
		pos4[0] = ((data[2] & mask7) >> 3) + 'A';
		pos4[1] = ((data[2] & mask8)) + '1';

		insertNodeToEndList(lst, createNewListNode(pos1, NULL));
		insertNodeToEndList(lst, createNewListNode(pos2, NULL));
		insertNodeToEndList(lst, createNewListNode(pos3, NULL));
		insertNodeToEndList(lst, createNewListNode(pos4, NULL));
	}
	else if (size == 2)
	{
		pos1[0] = ((data[0] & mask1) >> 5) + 'A';
		pos1[1] = ((data[0] & mask2) >> 2) + '1';
		pos2[0] = (((data[0] & mask3a) << 1) | ((data[1] & mask3b) >> 7)) + 'A';
		pos2[1] = ((data[1] & mask4) >> 4) + '1';

		insertNodeToEndList(lst, createNewListNode(pos1, NULL));
		insertNodeToEndList(lst, createNewListNode(pos2, NULL));
	}
	else if (size == 1)
	{
		pos1[0] = ((data[0] & mask1) >> 5) + 'A';
		pos1[1] = ((data[0] & mask2) >> 2) + '1';

		insertNodeToEndList(lst, createNewListNode(pos1, NULL));
	}

}
/* insert Node To End List */
void insertNodeToEndList(chessPosList* lst, chessPosCell* tail)
{
	if (isEmptyList(lst))
	{
		lst->head = lst->tail = tail;
	}
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}
/* check if a chesspos was already been touched  */
bool checkExistPosition(bool posTable[][SIZE], int rows, int cols, chessPos position)
{
	int i, j;
	bool res;

	i = position[0] - 'A';
	j = position[1] - '1';

	if (posTable[i][j] == true)
		res = true;
	else
	{
		posTable[i][j] = true;
		res = false;
	}
	return res;
}
/* free the  list */
void freeList(chessPosList* lst)
{
	chessPosCell* curr, * saver;
	curr = lst->head;
	while (curr)
	{
		saver = curr->next;
		free(curr);
		curr = saver;
	}
	free(lst);
}
/* seif 7  the menu */
void PrintMenu()
{
	printf("1. Enter a knight's starting position\n");
	printf("2. Create all possible knight paths\n");
	printf("3. Find a knight path covering all board\n");
	printf("4. Save knight path covering all board to file\n");
	printf("5. Load and display path from file\n");
	printf("6. Exit\n");
}
/* check if chessPos is valid pos */
bool isValidPos(chessPos pos)
{
	return (pos[0] >= 'A' && pos[0] <= 'H' && pos[1] >= '1' && pos[1] <= '8') ? true : false;
}
/*free tree*/
void FreeTree(pathTree* tr)
{
	if (tr->root == NULL)
		return;

	FreeTreeHelper(tr->root);
}

void FreeTreeHelper(treeNode* root)
{
	if (root == NULL)
		return;

	FreetreeNodeListCell(root->next_possible_positions);
	free(root);
}

void FreetreeNodeListCell(treeNodeListCell* headnode)
{
	if (headnode == NULL)
		return;

	treeNodeListCell* saver, * curr = headnode;

	while (curr != NULL)
	{
		saver = curr->next;
		FreeTreeHelper(curr->node);
		free(curr);
		curr = saver;
	}
}

void GameProcess()
{
	int checkInput;
	chessPos startingPos;
	pathTree tr;
	tr.root = NULL;
	chessPosList* lst = NULL;
	int choice;
	bool exit = false;

	while (!exit)
	{
		PrintMenu();
		checkInput = scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			printf("Enter your position: \n"); /* messege to user */
			while ((getchar()) != '\n'); /* buffer clean */
			checkInput = scanf("%c%c", &startingPos[0], &startingPos[1]); /* scan chessPos */

			if (isValidPos(startingPos))
				break;
			else
			{
				printf("Invalid position!! please try again. \n\n");
				break;
			}

		case 2:
			OptionTwo(startingPos, &tr);
			break;
		case 3:
			OptionThree(startingPos, &tr, lst);
			break;
		case 4:
			OptionFour(startingPos, &tr, lst);
			break;
		case 5:
			OptionFive(startingPos);
			break;
		case 6:
			if (lst)
				freeList(lst);
			if (tr.root)
				FreeTree(&tr);
			exit = true;
			break;
		default:
			printf("Invalid choice please try again. \n");
			break;
		}
	}
}

bool checkListIsEmpty(chessPosList* lst)
{
	if (lst == NULL)
		return true;
	else
		return false;
}

char* getName()
{
	int checkInput, logSize = 0, phsSize = INIT_SIZE;
	char* NewFileName = (char*)malloc(INIT_SIZE * sizeof(char));
	allocCheck(&NewFileName);
	char ch;

	while ((getchar()) != '\n');

	checkInput = scanf("%c", &ch);
	while (ch != '\n')
	{
		if (phsSize == logSize)
		{
			phsSize *= 2;
			NewFileName = (char*)realloc(NewFileName, phsSize * sizeof(char));
			allocCheck(&NewFileName);
		}

		NewFileName[logSize] = ch;
		logSize++;
		checkInput = scanf("%c", &ch);
	}
	NewFileName[logSize] = '\0';

	return NewFileName;
}

void freeMat(chessPosArray*** mat)
{
	int i, j;
	for (i = 0; i < SIZE; i++)
	{
		for (j = 0; j < SIZE; j++)
		{
			free(mat[i][j]->positions);
			free(mat[i][j]);
		}
		free(mat[i]);
	}
	free(mat);
}

/*Menu Options, covering all the cases, every case in a function*/
void OptionTwo(chessPos startingPos, pathTree* tr)
{
	if (isValidPos(startingPos))
	{
		if (tr->root)
		{
			FreeTree(tr);
		}

		*tr = findAllPossibleKnightPaths(startingPos);
		printf("tree has been built properly!! \n");
	}
	else
	{
		printf("Please insert a starting position.\n\n");
	}
}

void OptionThree(chessPos startingPos, pathTree* tr, chessPosList* lst)
{
	if (isValidPos(startingPos))  /* starting pos is valid */
	{
		if (tr->root) /* tree is built */
		{
			if (!checkListIsEmpty(lst))
			{
				freeList(lst);
			}
			lst = findKnightPathCoveringAllBoard(tr);
			if (lst == NULL)
			{
				printf("PATH NOT FOUND ! \n");
				return;
			}
			printf("List has been built properly!! \n\n");
		}
		else
		{
			*tr = findAllPossibleKnightPaths(startingPos); /* if tree isnt built already we build it now */
			if (!checkListIsEmpty(lst))
			{
				freeList(lst);
			}
			lst = findKnightPathCoveringAllBoard(tr); /* we search for a path to cover all board */
			if (lst == NULL)
			{
				printf("PATH NOT FOUND ! \n");
				return;
			}
			printf("List has been built properly!! \n\n");
		}
	}
	else
	{
		printf("Please insert a starting position.\n\n");
		return;
	}
}

void OptionFour(chessPos startingPos, pathTree* tr, chessPosList* lst)
{
	char* fileName;

	if (isValidPos(startingPos))
	{
		printf("Please enter your file-name: \n\n");

		fileName = getName(); /* get the name */

		if (!checkListIsEmpty(lst))
		{
			saveListToBinFile(fileName, lst);
			free(fileName);
		}
		else
		{
			if (tr->root) /* tree is built */
			{
				lst = findKnightPathCoveringAllBoard(tr); /* get the list */
				if (lst == NULL) /* check seccess */
				{
					printf("PATH NOT FOUND ! \n");
					return;
				}

				saveListToBinFile(fileName, lst);
				free(fileName);
			}
			else
			{
				*tr = findAllPossibleKnightPaths(startingPos); /* if tree isnt built already we build it now */
				lst = findKnightPathCoveringAllBoard(tr); /* we search for a path to cover all board */
				if (lst == NULL)
				{
					printf("PATH NOT FOUND ! \n");
					return;
				}
				else
				{
					saveListToBinFile(fileName, lst);
					free(fileName);
				}
			}
		}
	}
	else
		printf("Please insert a starting position.\n\n");
}

void OptionFive(chessPos startingPos)
{
	char* fileName;
	int checkInput;

	printf("Please enter your file-name: \n\n");
	fileName = getName();

	checkInput = checkAndDisplayPathFromFile(fileName);
	if (checkInput == -1)
	{
		printf("File isnt exist!. \n");
		return;
	}
	else if (checkInput == 1)
	{
		printf("List is illegal!. \n");
	}
	else if (checkInput == 2)
	{
		printf("Path is covering all the board !! \n");
	}
	else if (checkInput == 3)
	{
		printf("Path is not covering all the board !! \n");
	}
}