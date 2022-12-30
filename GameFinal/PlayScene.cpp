#include <iostream>
#include <fstream>
#include "AssetIDs.h"

#include "PlayScene.h"
#include "Utils.h"
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Coin.h"
#include "Platform.h"
#include "ColorBox.h"
#include "Camera.h"
#include "QuestionBrick.h"
#include "Koopas.h"
#include "Pipe.h"
#include "KoopasFly.h"
#include "GoombaRed.h"
#include "FirePlant.h"
#include "Mushroom.h"
#include "Tail.h"
#include "BrokenEffect.h"
#include "Pbutton.h"
#include "Leaf.h"

#include "SampleKeyEventHandler.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath):
	CScene(id, filePath)
{
	player = NULL;
	key_handler = new CSampleKeyHandler(this);
}


#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_ASSETS	1
#define SCENE_SECTION_OBJECTS	2
#define SCENE_SECTION_MAPS 3

#define ASSETS_SECTION_UNKNOWN -1
#define ASSETS_SECTION_SPRITES 1
#define ASSETS_SECTION_ANIMATIONS 2

#define MAX_SCENE_LINE 1024

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPTEXTURE tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return; 
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ASSETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;

	wstring path = ToWSTR(tokens[0]);
	
	LoadAssets(path.c_str());
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i+1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_MAP(string line) {
	vector<string> tokens = split(line);
	if (tokens.size() < 6) return;
	int ID = atoi(tokens[0].c_str());
	wstring mapPath = ToWSTR(tokens[1]);
	int Row = atoi(tokens[2].c_str());
	int Column = atoi(tokens[3].c_str());
	int tileSet = atoi(tokens[4].c_str());
	int tileColumn = atoi(tokens[5].c_str());

	map = new Map(ID, mapPath.c_str(), Row, Column, tileSet, tileColumn);
}

/*
	Parse a line in section [OBJECTS] 
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	// skip invalid lines - an object set must have at least id, x, y
	if (tokens.size() < 2) return;

	int object_type = atoi(tokens[0].c_str());
	float x = (float)atof(tokens[1].c_str());
	float y = (float)atof(tokens[2].c_str());

	CGameObject *obj = NULL;
	KoopasObject* koo = NULL;
	CTail* tail = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x, y);
		player = (CMario*)obj;
		CMario::SetInstance((CMario*)obj);

		tail = new CTail(x, y);
		objects.push_back(tail);
		CMario* ma = dynamic_cast<CMario*>(obj);
		ma->tail = tail;
		DebugOut(L"[INFO] Player object has been created!\n");
	}
		break;
	case OBJECT_TYPE_GOOMBA: obj = new CGoomba(x, y); break;
	case OBJECT_TYPE_KOOPAS:
	{
		obj = new CKoopas(x, y); 
		break; 
	}
	case OBJECT_TYPE_KOOPASFLY: obj = new CKoopasFly(x, y); break;
	case OBJECT_TYPE_REDGOOMBA: obj = new CGoombaRed(x, y); break;
	case OBJECT_TYPE_BRICK:
	{
		obj = new CBrick(x, y); 
		CBrick* cb = dynamic_cast<CBrick*>(obj);
		BrokenEffect* br1 = new BrokenEffect(x, y , -1);
		br1->SetPosition(x, y);
		objects.push_back(br1);
		cb->b1 = br1;
		BrokenEffect* br2 = new BrokenEffect(x, y, 1);
		br2->SetPosition(x, y);
		objects.push_back(br2);
		cb->b2 = br2;
		BrokenEffect* br3 = new BrokenEffect(x, y, -1);
		br3->SetPosition(x, y);
		objects.push_back(br3);
		cb->b3 = br3;
		BrokenEffect* br4 = new BrokenEffect(x, y, 1);
		br4->SetPosition(x, y);
		objects.push_back(br4);
		cb->b4 = br4;
		break;
	}
	case OBJECT_TYPE_FIREPLANT:
	{
		int Type = atoi(tokens[3].c_str());
		obj = new CFirePlant(x, y, Type); 
		break;
	}
	case OBJECT_TYPE_QUESTIONBRICK:
	{
		int Type = atoi(tokens[3].c_str());
		obj = new CQuestionBrick(x, y, Type); 
		qb.push_back(dynamic_cast<CQuestionBrick*>(obj));
		break;
	}
	case OBJECT_TYPE_ITEM:
	{
		int typeitem = atoi(tokens[3].c_str());
		switch (typeitem)
		{
		case ItemType::Coin:
			obj = new CCoin(x, y);
			break;
		case ItemType::Mushroom:
			obj = new CMushroom(x, y);
			break;
		case ItemType::pbutton:
			obj = new Pbutton(x, y);
			break;
		case ItemType::leaf:
			obj = new Leaf(x, y);
			break;
			
		default: 
			break;
		}
		items.push_back(dynamic_cast<Item*>(obj));
		break;
	}
	case OBJECT_TYPE_PLATFORM:
	{
		
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_begin = atoi(tokens[6].c_str());
		int sprite_middle = atoi(tokens[7].c_str());
		int sprite_end = atoi(tokens[8].c_str());

		obj = new CPlatform(
			x, y,
			cell_width, cell_height, length,
			sprite_begin, sprite_middle, sprite_end
		);

		break;
	}
	case OBJECT_TYPE_COLORBOX: {
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		obj = new ColorBox(x, y, cell_width * length, cell_height,
			cell_width, cell_height, length);
		break;
	}
	case OBJECT_TYPE_PIPE: {
		float cell_width = (float)atof(tokens[3].c_str());
		float cell_height = (float)atof(tokens[4].c_str());
		int length = atoi(tokens[5].c_str());
		int sprite_id_1 = atoi(tokens[6].c_str());
		int sprite_id_2 = atoi(tokens[7].c_str());
		int sprite_id_3 = atoi(tokens[8].c_str());
		int sprite_id_4 = atoi(tokens[9].c_str());
		obj = new CPipe(x, y, cell_width * length, cell_height,
			cell_width, cell_height, length, sprite_id_1, sprite_id_2, sprite_id_3, sprite_id_4);
		break;
	}
	case OBJECT_TYPE_PORTAL:
	{
		float r = (float)atof(tokens[3].c_str());
		float b = (float)atof(tokens[4].c_str());
		int scene_id = atoi(tokens[5].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;


	default:
		DebugOut(L"[ERROR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	obj->SetPosition(x, y);


	objects.push_back(obj);
}

void CPlayScene::LoadAssets(LPCWSTR assetFile)
{
	DebugOut(L"[INFO] Start loading assets from : %s \n", assetFile);

	ifstream f;
	f.open(assetFile);

	int section = ASSETS_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[SPRITES]") { section = ASSETS_SECTION_SPRITES; continue; };
		if (line == "[ANIMATIONS]") { section = ASSETS_SECTION_ANIMATIONS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case ASSETS_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case ASSETS_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		}
	}

	f.close();

	DebugOut(L"[INFO] Done loading assets from %s\n", assetFile);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;					

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	
		if (line == "[ASSETS]") { section = SCENE_SECTION_ASSETS; continue; };
		if (line == "[OBJECTS]") { section = SCENE_SECTION_OBJECTS; continue; };
		if (line == "[MAP]") { section = SCENE_SECTION_MAPS; continue; };
		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }	

		//
		// data section
		//
		switch (section)
		{ 
			case SCENE_SECTION_ASSETS: _ParseSection_ASSETS(line); break;
			case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
			case SCENE_SECTION_MAPS: _ParseSection_MAP(line); break;
		}
	}

	f.close();
	for (size_t i = 0; i < qb.size(); i++) {
		qb[i]->setItem(items[i]);
	}
	qb = vector<CQuestionBrick*>();
	items = vector<Item*>();


	DebugOut(L"[INFO] Done loading scene  %s\n", sceneFilePath);
}

void CPlayScene::Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (size_t i = 1; i < objects.size(); i++)
	{
		if (i >= 2)
		{
			coObjects.push_back(objects[i]);
		}
	}

	for (size_t i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return; 

	// Update camera to follow mario
	float cx, cy;
	player->GetPosition(cx, cy);

	CGame *game = CGame::GetInstance();
	cx -= game->GetBackBufferWidth() / 2;
	cy -= game->GetBackBufferHeight() / 2;

	if (cx < 0) cx = 0;
	if (cy < 0) cy = 0;
	if (cx > map->GetMapWidth() - game->GetBackBufferWidth() - ScreenH) {
		cx = float(map->GetMapWidth() - game->GetBackBufferWidth()- ScreenH);
	}
	if (cy > map->GetMapHeight() - game->GetBackBufferHeight())
	{
		cy = float(map->GetMapHeight() - game->GetBackBufferHeight());
	}

	CGame::GetInstance()->SetCamPos(cx, cy + ScreenH);

	PurgeDeletedObjects();
}

void CPlayScene::Render()
{
	map->DrawMap();
	for (int i = 0; i < objects.size(); i++)
		objects[i]->Render();
	hud->Render();
}

/*
*	Clear all objects from this scene
*/
void CPlayScene::Clear()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		delete (*it);
	}
	objects.clear();
}

/*
	Unload scene

	TODO: Beside objects, we need to clean up sprites, animations and textures as well 

*/
void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
	player = NULL;

	DebugOut(L"[INFO] Scene %d unloaded! \n", id);
}

bool CPlayScene::IsGameObjectDeleted(const LPGAMEOBJECT& o) { return o == NULL; }

void CPlayScene::PurgeDeletedObjects()
{
	vector<LPGAMEOBJECT>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	{
		LPGAMEOBJECT o = *it;
		if (o->IsDeleted())
		{
			delete o;
			*it = NULL;
		}
	}

	// NOTE: remove_if will swap all deleted items to the end of the vector
	// then simply trim the vector, this is much more efficient than deleting individual items
	objects.erase(
		std::remove_if(objects.begin(), objects.end(), CPlayScene::IsGameObjectDeleted),
		objects.end());
}