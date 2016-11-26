#ifndef DID_ENGINE_OBJECT_PROPERTY_H

#define DID_ENGINE_OBJECT_PROPERTY_H

#include "DIDEngineDefinitions.h"
#include "DIDEngineObject.h"
#include <vector>

class DIDEngine::ObjectProperty {
private:
	static const DIDEOPV_t minimumValue = -100;
	static const DIDEOPV_t maximumValue = 99;
	DIDEOPV_t currentValue;
	Object* target;
	std::vector<DIDES_t> descriptions; // indexes -- enum DIDEngine::ObjectProperty::Descriptions

	void safetyCall(Object*, bool);

public:
	enum Descriptions {
		TYPE = 0,
		NAME = 2,
		DESCRIPTION = 1
	};

	ObjectProperty(
		DIDEOPV_t = 0,
		Object* = nullptr,
		std::vector<DIDES_t> = std::vector<DIDES_t>(),
		void(*)(Object*, Object*) = nullptr,
		void(*)(Object*, Object*) = nullptr
	);

	const DIDES_t getDescription(unsigned) const;
	const std::vector<DIDES_t> getDescriptions() const;
	const Object* getTarget() const;
	void setDescription(unsigned, DIDES_t);
	void setDescriptions(std::vector<DIDES_t>);
	bool setTarget(Object*);

	void(*onMinValueReached)(Object*, Object*);
	void(*onMaxValueReached)(Object*, Object*);
	void set(DIDEOPV_t, Object* = nullptr);
	void inc(DIDEOPV_t, Object* = nullptr);
	DIDEOPV_t get() const;
};

#endif // !DID_ENGINE_OBJECT_PROPERTY_H