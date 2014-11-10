#pragma once
class ContactListener : public b2ContactListener
{
public:
	ContactListener(){}
	~ContactListener(){}

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact* contact);
	virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
};

