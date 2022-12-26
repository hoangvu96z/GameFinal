#pragma once
#include"Textures.h"
#include "Game.h"
#include "Sprites.h"
#include "Utils.h"
#include <fstream>
#include <string>

#define FrameHeight 16
#define FrameWidth	16
#define MAX	300
#define MAP_SECTION 1
#define MAP_UNKNOWN_SECTION -1
#define MAP_MAX_LINE	1024
class Map
{
public:
	LPCWSTR FilepathMap;
	int id;
	int columns;
	int rows;
	int TileSetWidth;
	int TileSetHeight;
	int TileMapID[MAX][MAX];
	int row = 0;

public:
	Map(int ID, LPCWSTR Filepath, int Rows, int Cols, int Tiles, int TileColumn);
	void ReadMap();
	void DrawMap();
	void Load();
	void _ParseSection_LoadTile(string line);
	int GetMapWidth() { return columns * FrameWidth; }
	int GetMapHeight() { return rows * FrameHeight; }
	~Map();
};