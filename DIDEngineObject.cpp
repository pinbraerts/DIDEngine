#include "DIDEngineObject.h"

DIDEngine::Object::Object(
	std::vector<DIDEngine::DIDES_t> Descs,
	std::map<DIDEngine::DIDES_t, DIDEngine::ObjectProperty*> Properties,
	std::map<DIDEngine::DIDES_t, DIDEngine::ObjectAction*> Actions
) : descriptions(Descs), properties(Properties), actions(Actions) {
	descriptions.resize(3); // DIDEngine::Object::Descriptions count
}

DIDEngine::Object::Object(
	std::vector<DIDEngine::DIDES_t> Descs,
	std::map<DIDEngine::DIDES_t, DIDEngine::ObjectProperty*> Properties,
	std::vector<DIDEngine::ObjectAction*> Actions
	) : descriptions(Descs), properties(Properties) {
	descriptions.resize(3); // DIDEngine::Object::Descriptions count
	for (ObjectAction* action : Actions)
		actions[action->getDescription(ObjectAction::NAME)] = action;
}

DIDEngine::Object::Object(
	std::vector<DIDEngine::DIDES_t> Descs,
	std::vector<DIDEngine::ObjectProperty*> Properties,
	std::map<DIDEngine::DIDES_t, DIDEngine::ObjectAction*> Actions
) : descriptions(Descs), actions(Actions) {
	descriptions.resize(3); // DIDEngine::Object::Descriptions count
	for (ObjectProperty* prop : Properties)
		properties[prop->getDescription(ObjectProperty::DESCRIPTION)] = prop;
}

DIDEngine::Object::Object(
	std::vector<DIDEngine::DIDES_t> Descs,
	std::vector<DIDEngine::ObjectProperty*> Properties,
	std::vector<DIDEngine::ObjectAction*> Actions
) {
	descriptions.resize(3); // DIDEngine::Object::Descriptions count
	for (ObjectAction* action : Actions)
		actions[action->getDescription(ObjectAction::NAME)] = action;
	for (ObjectProperty* prop : Properties)
		properties[prop->getDescription(ObjectProperty::DESCRIPTION)] = prop;
}

DIDEngine::Object::~Object() {
	delete &properties;
	delete &descriptions;
	delete &actions;
}

void DIDEngine::Object::setDescription(unsigned index, DIDEngine::DIDES_t value) {
	if (this != nullptr) descriptions[index] = value;
	else throw ErrorNullPointer();
}

void DIDEngine::Object::setDescritpions(std::vector<DIDEngine::DIDES_t> newDescs)
{
	if (this != nullptr) descriptions = newDescs;
	else throw ErrorNullPointer();
}

const DIDEngine::DIDES_t DIDEngine::Object::getDescription(unsigned index) const {
	if (this != nullptr) return descriptions[index];
	else throw ErrorNullPointer();
}

const std::vector<DIDEngine::DIDES_t> DIDEngine::Object::getDescriptions() const {
	if (this != nullptr) return descriptions;
	else throw ErrorNullPointer();
}

void DIDEngine::Object::setProperty(DIDEngine::DIDES_t index, DIDEOPV_t value) {
	if (this != nullptr) properties[index]->set(value);
	else throw ErrorNullPointer();
}

void DIDEngine::Object::setProperty(DIDEngine::DIDES_t index, DIDEngine::ObjectProperty* value)
{
	if (this != nullptr) properties[index] = value;
	else throw ErrorNullPointer();
}

void DIDEngine::Object::incProperty(DIDEngine::DIDES_t index, DIDEOPV_t value) {
	if (this != nullptr) properties[index]->inc(value);
	else throw ErrorNullPointer();
}

bool DIDEngine::Object::addProperty(DIDEngine::ObjectProperty* prop)
{
	if (this == nullptr) throw ErrorNullPointer();
	if(prop->setTarget(this))
		properties[prop->getDescription(ObjectProperty::NAME)] = prop;
	return false;
}

void DIDEngine::Object::removeProperty(DIDEngine::ObjectProperty* prop)
{
	if (this != nullptr) properties.erase(prop->getDescription(ObjectProperty::NAME));
	else throw ErrorNullPointer();
}

void DIDEngine::Object::removeProperty(DIDEngine::DIDES_t index)
{
	if (this != nullptr) properties.erase(index);
	else throw ErrorNullPointer();
}

void DIDEngine::Object::setProperties(std::map<DIDEngine::DIDES_t, DIDEngine::ObjectProperty*> newProps)
{
	if (this != nullptr) properties = newProps;
	else throw ErrorNullPointer();
}

void DIDEngine::Object::setProperties(std::vector<DIDEngine::ObjectProperty*> newProps)
{
	if (this != nullptr)
		for (ObjectProperty* prop : newProps)
			properties[prop->getDescription(ObjectProperty::NAME)] = prop;
	else throw ErrorNullPointer();
}

void DIDEngine::Object::setAction(DIDEngine::DIDES_t index, DIDEngine::ObjectAction* value)
{
	if (this != nullptr) actions[index] = value;
	else throw ErrorNullPointer();
}

bool DIDEngine::Object::addAction(DIDEngine::ObjectAction* action)
{
	if (this == nullptr) throw ErrorNullPointer();
	if(action->setSender(this))
		actions[action->getDescription(ObjectAction::NAME)] = action;
	return false;
}

void DIDEngine::Object::setActions(std::map<DIDEngine::DIDES_t, DIDEngine::ObjectAction*> newActions)
{
	if (this != nullptr) actions = newActions;
	else throw ErrorNullPointer();
}

void DIDEngine::Object::setActions(std::vector<DIDEngine::ObjectAction*> newActions)
{
	if (this != nullptr)
		for (ObjectAction* action : newActions)
			actions[action->getDescription(ObjectAction::NAME)] = action;
	else throw ErrorNullPointer();
}

void DIDEngine::Object::removeAction(DIDEngine::ObjectAction* action)
{
	if(this != nullptr)	actions.erase(action->getDescription(ObjectAction::NAME));
	else throw ErrorNullPointer();
}

void DIDEngine::Object::removeAction(DIDEngine::DIDES_t index)
{
	if (this != nullptr) actions.erase(index);
	else throw ErrorNullPointer();
}

void DIDEngine::Object::runAction(DIDEngine::DIDES_t index, int args)
{
	if (this != nullptr) actions[index]->operator()(args);
	else throw ErrorNullPointer();
}

const DIDEngine::DIDEOPV_t DIDEngine::Object::getProperty(DIDEngine::DIDES_t index) const {
	if (this != nullptr) return properties.at(index)->get();
	else throw ErrorNullPointer();
}

const std::vector<DIDEngine::ObjectProperty> DIDEngine::Object::getProperties() const {
	if (this == nullptr) throw ErrorNullPointer();
	std::vector<DIDEngine::ObjectProperty> temvec;
	for (std::pair<DIDEngine::DIDES_t, DIDEngine::ObjectProperty*> prop : properties)
		temvec.push_back(*prop.second);
	return temvec;
}

const DIDEngine::ObjectAction* DIDEngine::Object::getAction(DIDEngine::DIDES_t index) const
{
	if (this != nullptr) return actions.at(index);
	else throw ErrorNullPointer();
}

const std::vector<DIDEngine::ObjectAction*> DIDEngine::Object::getActions() const
{
	if (this == nullptr) throw ErrorNullPointer();
	std::vector<DIDEngine::ObjectAction*> temvec;
	for (std::pair<DIDEngine::DIDES_t, DIDEngine::ObjectAction*> action : actions)
		temvec.push_back(action.second);
	return temvec;
}