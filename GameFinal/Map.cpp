#include"Map.h"
#include "Camera.h"
#include "debug.h"

Map::Map(int ID, LPCWSTR Filepath, int Rows, int Cols, int Tiles, int TileColumn)
{
	this->id = ID;
	this->FilepathMap = Filepath;
	this->rows = Rows;
	this->columns = Cols;
	this->TileSetWidth = Tiles;
	this->TileSetHeight = TileColumn;

	Load();
}
void Map::Load() {
	ifstream f;
	f.open(FilepathMap);
	int section = MAP_UNKNOWN_SECTION;
	char str[MAP_MAX_LINE];
	while (f.getline(str, MAP_MAX_LINE)) {
		string line(str);
		if (line[0] == '#') continue;
		if (line == "[Map]") {
			section = MAP_SECTION;
			continue;
		}
		if (line[0] == '[') {
			section = MAP_UNKNOWN_SECTION;
			continue;
		}

		switch (section) {
		case MAP_SECTION:
			_ParseSection_LoadTile(line);
			break;
		}
	}
	f.close();
	ReadMap();
}

void Map::_ParseSection_LoadTile(string line)
{
	vector<string> tokens = split(line);
	size_t size = tokens.size();
	if (size < columns) return;
	for (int i = 0; i < columns; i++) {
		TileMapID[row][i] = atoi(tokens[i].c_str())-1;
	}
	row++;
	
}

void Map::ReadMap()
{
	CTextures* texture = CTextures::GetInstance();
	LPTEXTURE texMap = texture->Get(id);
	int id_sprite = 0;
	for (int i = 0; i <= TileSetWidth; i++)
	{
		for (int j = 0; j <= TileSetHeight; j++)
		{
			RECT r;
			r.left = (id_sprite %  TileSetWidth) * FrameWidth ;
			r.top = (id_sprite / TileSetHeight) * FrameHeight;
			r.right = r.left + FrameWidth;
			r.bottom = r.top + FrameHeight;
			CSprites::GetInstance()->Add(id_sprite, r.left, r.top, r.right, r.bottom, texMap);
			id_sprite = id_sprite + 1;
		}
	}  


}
void Map::DrawMap()
{
	//CSprites* sprites = CSprites::GetInstance();

	float camX, camY;
	CGame::GetInstance()->GetCamPos(camX, camY);
	int firstX = (int)(camX / GetMapWidth() * columns);
	int firstY = (int)(camY / GetMapHeight() * rows );
	int lastY = firstY + 22 > rows ? rows : firstY + 22;
	int lastX = firstX + 22 > columns ? columns : firstX + 22;

	for (UINT i = firstY; i < lastY ; i++)
		for (UINT j = firstX; j < lastX; j++)
		{
			float x, y;
			x = FrameHeight * j;
			if (id != 30)
			{
				y = FrameWidth * i;
			}
			else
				y = FrameWidth * i - 16;
			CSprites::GetInstance()->Get(TileMapID[i][j])->Draw(x, y);
		}
}

Map::~Map() {

}