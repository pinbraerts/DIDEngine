#ifndef DID_ENGINE_OBJECT_ACTION

#define DID_ENGINE_OBJECT_ACTION

#include "DIDEngineDefinitions.h"
#include "DIDEngineObject.h"
#include "DIDEngineObjectProperty.h"
#include <map>
#include <vector>

class DIDEngine::ObjectAction {
private:
	std::vector<DIDES_t> descriptions;
	std::map<DIDES_t, std::pair<ObjectProperty*, DIDEOPV_t>> properties;
	Object* sender;

public:
	enum Decsriptions {
		NAME = 0,
		DESCRIPTION = 1,
		TYPE = 2
	};

	// Constructors and Destructors
	ObjectAction(
		std::vector<DIDES_t>,
		std::vector<std::pair<ObjectProperty*, DIDEOPV_t>>,
		Object* = nullptr
	);
	ObjectAction(
		std::vector<DIDES_t>,
		std::map<ObjectProperty*, DIDEOPV_t>,
		Object* = nullptr
	);
	ObjectAction(
		std::vector<DIDES_t> = std::vector<DIDES_t>(),
		std::map<DIDES_t, std::pair<ObjectProperty*, DIDEOPV_t>> = std::map<DIDES_t, std::pair<ObjectProperty*, DIDEOPV_t>>(),
		Object* = nullptr
	);
	~ObjectAction();

	// Getters and setters
	const DIDEOPV_t getPropertyValue(ObjectProperty*) const;
	const DIDEOPV_t getPropertyValue(DIDES_t) const;
	const std::pair<ObjectProperty*, DIDEOPV_t> getPropertyValuePair(DIDES_t) const;
	const std::map<DIDES_t, std::pair<ObjectProperty*, DIDEOPV_t>> getProperties() const;
	const ObjectProperty* getProperty(DIDES_t) const;
	const DIDES_t getDescription(unsigned) const;
	const std::vector<DIDES_t> getDescritpions() const;
	const Object* getSender();
	void setPropertyValue(ObjectProperty*, DIDEOPV_t);
	void setPropertyValue(DIDES_t, DIDEOPV_t);
	void setProperty(DIDES_t, ObjectProperty*);
	void addProperty(ObjectProperty*, DIDEOPV_t);
	void setProperties(std::vector<std::pair<ObjectProperty*, DIDEOPV_t>>);
	void setProperties(std::map<DIDES_t, std::pair<ObjectProperty*, DIDEOPV_t>>);
	void setDescription(unsigned, DIDES_t);
	void setDescritpions(std::vector<DIDES_t>);
	bool setSender(Object*);

	// Methods
	void operator()(int = 0); // int -> struct DIDEngine::ActionArguments
};

#endif // !DID_ENGINE_OBJECT_ACTION