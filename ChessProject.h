#pragma once


#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 5
#define MAXPOS 8
#define INIT_SIZE 1

typedef unsigned char BYTE;

typedef char chessPos[2];

typedef struct _chessPosArray
{
	unsigned int size;
	chessPos* positions;
} chessPosArray;

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode
{
	chessPos position;
	treeNodeListCell* next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell
{
	treeNode* node;
	struct _treeNodeListCell* next;
} treeNodeListCell;

typedef struct _pathTree
{
	treeNode* root;
} pathTree;

typedef struct _chessPosCell
{
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList
{
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;

void makeEmptyList(chessPosList* lst);
chessPosList* findKnightPathCoveringAllBoard(pathTree* pathTree);
void findKnightPathCoveringAllBoardHelper(treeNodeListCell* position, chessPosList* lst, int* level, bool* pathFound);
void allocCheck(void* address);
chessPosCell* createNewListNode(chessPos position, chessPosCell* next);
void insertDataToStartList(chessPosList* lst, chessPos position);
void insertNodeToStartList1(chessPosList* lst, chessPosCell* head);
bool isEmptyList(chessPosList* lst);
chessPosArray*** validKnightMoves();
chessPosArray* CheckCellMoves(int row, int col);
pathTree findAllPossibleKnightPaths(chessPos startingPosition);
treeNode* findAllPossibleKnightPathsHelper(chessPos rootdata, chessPosArray*** board, bool path[][SIZE]);
void printList(chessPosList* lst);
bool checkExistPos(bool path[][SIZE], chessPos position);
treeNodeListCell* CreateTreeNodeListCell(treeNode* node);
void initTable(bool path[][SIZE], int rows, int cols);
void insertDNodeToStartList(treeNode* head, treeNode* Node);
void insertNodeToStartList(treeNode* head, treeNodeListCell* NewNode);
treeNode* createNewTreeNode(chessPos position);
bool isEmptyTreeList(treeNodeListCell* head);
void saveListToBinFile(char* file_name, chessPosList* pos_list);
short int sizeOfList(chessPosList* pos_list);
void fileOpenCheck(FILE* fp);
int checkAndDisplayPathFromFile(char* fileName);
bool CheckValidKnightPath(chessPosList* lst);
bool CheckValidMove(chessPosCell* curr, chessPosCell* nextPos);
void display(chessPosList* lst);
void deleteNodeFromChessList(chessPosList* lst, chessPosCell* node);
void checkDoubleOccurrences(chessPosList* lst);
void printChessBoard(chessPosList* lst);
void printLine(int count, char ch);
void initBoard(int chessBoard[][SIZE], int rows, int cols, chessPosList* lst);
void makeListFromFile(FILE* data, chessPosList* lst);
void getDecodedData(BYTE* data, chessPosList* lst, int size);
bool checkExistPosition(bool posTable[][SIZE], int rows, int cols, chessPos position);
void insertNodeToEndList(chessPosList* lst, chessPosCell* tail);
void freeList(chessPosList* lst);
void FreeTree(pathTree* tr);
void FreeTreeHelper(treeNode* root);
void FreetreeNodeListCell(treeNodeListCell* headnode);
void PrintMenu();
bool isValidPos(chessPos pos);
void GameProcess();
void OptionTwo(chessPos startingPos, pathTree* tr);
void OptionThree(chessPos startingPos, pathTree* tr, chessPosList* lst);
void OptionFour(chessPos startingPos, pathTree* tr, chessPosList* lst);
void OptionFive(chessPos startingPos);
bool checkListIsEmpty(chessPosList* lst);
char* getName();
void freeMat(chessPosArray*** mat);
