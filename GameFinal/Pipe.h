#include "GameObject.h"
class CPipe : public CGameObject
{
	int width;
	int height;
public:
	CPipe(float l, float t, float r, float b);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	virtual int GetWidth() { return width; };
	virtual void Render();
	virtual int IsCollidable() { return 1; };
	//virtual int IsBlockingOnSide(){ return 0; };
	//virtual int IsBlockingOnTop() { return 1; };
	virtual void DirectBlocking(int& l, int& t, int& r, int& b) { l = 1; t = 1; b = 0; r = 1; }
};