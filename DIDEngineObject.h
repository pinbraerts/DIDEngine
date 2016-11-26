#ifndef DID_ENGINE_OBJECT_H

#define DID_ENGINE_OBJECT_H

#include "DIDEngineDefinitions.h"
#include "DIDEngineObjectAction.h"
#include "DIDEngineObjectProperty.h"
#include <vector>
#include <map>

class DIDEngine::Object {
private:
	std::vector<DIDES_t> descriptions; // indexes -- enum Object::Descriptions
	std::map<DIDES_t, ObjectAction*> actions;
	std::map<DIDES_t, ObjectProperty*> properties;

public:
	class ErrorNullPointer {};

	enum Descriptions {
		TYPE = 0,
		NAME = 2,
		DESCRIPTION = 1
	};
	
	// Constructors and destructors
	Object(
		std::vector<DIDES_t> = std::vector<DIDES_t>(),
		std::map<DIDES_t, ObjectProperty*> = std::map<DIDES_t, ObjectProperty*>(),
		std::map<DIDES_t, ObjectAction*> = std::map<DIDES_t, ObjectAction*>()
	);
	Object(
		std::vector<DIDES_t>,
		std::map<DIDES_t, ObjectProperty*>,
		std::vector<ObjectAction*>
	);
	Object(
		std::vector<DIDES_t>,
		std::vector<ObjectProperty*>,
		std::map<DIDES_t, ObjectAction*> = std::map<DIDES_t, ObjectAction*>()
	);
	Object(
		std::vector<DIDES_t>,
		std::vector<ObjectProperty*>,
		std::vector<ObjectAction*>
	);
	~Object();

	// Getters and setters
	const DIDES_t getDescription(unsigned) const;
	const std::vector<DIDES_t> getDescriptions() const;
	const DIDEOPV_t getProperty(DIDES_t) const;
	const std::vector<ObjectProperty> getProperties() const;
	const ObjectAction* getAction(DIDES_t) const;
	const std::vector<ObjectAction*> getActions() const;
	void setDescription(unsigned, DIDES_t);
	void setDescritpions(std::vector<DIDES_t>);
	void setProperty(DIDES_t, DIDEOPV_t);
	void setProperty(DIDES_t, ObjectProperty*);
	void incProperty(DIDES_t, DIDEOPV_t);
	bool addProperty(ObjectProperty*);
	void removeProperty(ObjectProperty*);
	void removeProperty(DIDES_t);
	void setProperties(std::map<DIDES_t, ObjectProperty*>);
	void setProperties(std::vector<ObjectProperty*>);
	void setAction(DIDES_t, ObjectAction*);
	bool addAction(ObjectAction*);
	void setActions(std::map<DIDES_t, ObjectAction*>);
	void setActions(std::vector<ObjectAction*>);
	void removeAction(ObjectAction*);
	void removeAction(DIDES_t);

	void runAction(DIDES_t, int args = 0);
};

#endif // !DID_ENGINE_OBJECT_H
