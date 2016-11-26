#include "DIDEngineObjectAction.h"

DIDEngine::ObjectAction::ObjectAction(
	std::vector<DIDEngine::DIDES_t> Descriptions,
	std::vector<std::pair<DIDEngine::ObjectProperty*, DIDEngine::DIDEOPV_t>> Properties,
	DIDEngine::Object* Sender
) : descriptions(Descriptions), sender(Sender) {
	descriptions.resize(3); // DIDEngine::ObjectAction count
	for (std::pair<ObjectProperty*, DIDEOPV_t> prop : Properties)
		properties[prop.first->getDescription(ObjectProperty::NAME)] = std::pair<ObjectProperty*, DIDEngine::DIDEOPV_t>(prop.first, prop.second);
}

DIDEngine::ObjectAction::ObjectAction(
	std::vector<DIDEngine::DIDES_t> Descriptions,
	std::map<DIDEngine::ObjectProperty*, DIDEngine::DIDEOPV_t> Properties,
	DIDEngine::Object* Sender
) : descriptions(Descriptions), sender(Sender) {
	descriptions.resize(3); // DIDEngine::ObjectAction count
	for (std::pair<ObjectProperty*, DIDEOPV_t> prop : Properties)
		properties[prop.first->getDescription(ObjectProperty::NAME)] = std::pair<ObjectProperty*, DIDEngine::DIDEOPV_t>(prop.first, prop.second);
}

DIDEngine::ObjectAction::ObjectAction(
	std::vector<DIDEngine::DIDES_t> Descritpion,
	std::map<DIDEngine::DIDES_t, std::pair<DIDEngine::ObjectProperty*, DIDEngine::DIDEOPV_t>> Properties,
	DIDEngine::Object* Sender
) : descriptions(descriptions), properties(Properties), sender(Sender) {
	descriptions.resize(3); // DIDEngine::ObjectAction count
}

DIDEngine::ObjectAction::~ObjectAction() {
	delete &descriptions;
	delete &properties;
	delete sender;
}

const DIDEngine::DIDEOPV_t DIDEngine::ObjectAction::getPropertyValue(DIDEngine::ObjectProperty* index) const
{
	return properties.at(index->getDescription(ObjectProperty::NAME)).second;
}

const DIDEngine::DIDEOPV_t DIDEngine::ObjectAction::getPropertyValue(DIDEngine::DIDES_t index) const
{
	return properties.at(index).second;
}

const std::pair<DIDEngine::ObjectProperty*, DIDEngine::DIDEOPV_t> DIDEngine::ObjectAction::getPropertyValuePair(DIDEngine::DIDES_t index) const
{
	return properties.at(index);
}

const std::map<DIDEngine::DIDES_t, std::pair<DIDEngine::ObjectProperty*, DIDEngine::DIDEOPV_t>> DIDEngine::ObjectAction::getProperties() const
{
	return properties;
}

const DIDEngine::ObjectProperty* DIDEngine::ObjectAction::getProperty(DIDEngine::DIDES_t index) const
{
	return properties.at(index).first;
}

const DIDEngine::DIDES_t DIDEngine::ObjectAction::getDescription(unsigned index) const
{
	return descriptions[index];
}

const std::vector<DIDEngine::DIDES_t> DIDEngine::ObjectAction::getDescritpions() const
{
	return descriptions;
}

const DIDEngine::Object* DIDEngine::ObjectAction::getSender()
{
	return sender;
}

void DIDEngine::ObjectAction::setPropertyValue(DIDEngine::ObjectProperty* index, DIDEngine::DIDEOPV_t value)
{
	properties[index->getDescription(ObjectProperty::NAME)].second = value;
}

void DIDEngine::ObjectAction::setPropertyValue(DIDEngine::DIDES_t index, DIDEngine::DIDEOPV_t value)
{
	properties[index].second = value;
}

void DIDEngine::ObjectAction::setProperty(DIDEngine::DIDES_t index, DIDEngine::ObjectProperty* value)
{
	properties[index].first = value;
}

void DIDEngine::ObjectAction::addProperty(DIDEngine::ObjectProperty* name, DIDEngine::DIDEOPV_t value)
{
	properties[name->getDescription(ObjectProperty::NAME)] = { name, value };
}

void DIDEngine::ObjectAction::setProperties(std::vector<std::pair<DIDEngine::ObjectProperty*, DIDEngine::DIDEOPV_t>> newProp)
{
	properties.clear();
	for (std::pair<ObjectProperty*, DIDEOPV_t> prop : newProp)
		properties[prop.first->getDescription(ObjectProperty::NAME)] = prop;
}

void DIDEngine::ObjectAction::setProperties(std::map<DIDEngine::DIDES_t, std::pair<DIDEngine::ObjectProperty*, DIDEngine::DIDEOPV_t>> newProp)
{
	properties = newProp;
}

void DIDEngine::ObjectAction::setDescription(unsigned index, DIDEngine::DIDES_t value)
{
	if (index == NAME && sender != nullptr) {
		sender->removeAction(this);
		descriptions[index] = value;
		sender->addAction(this);
	}
	else descriptions[index] = value;
}

void DIDEngine::ObjectAction::setDescritpions(std::vector<DIDEngine::DIDES_t> newDesc)
{
	descriptions = newDesc;
}

bool DIDEngine::ObjectAction::setSender(DIDEngine::Object* newSender)
{
	if (sender == newSender) return true;
	if(sender != nullptr) sender->removeAction(this);
	sender = newSender;
	return sender->addAction(this);
}

void DIDEngine::ObjectAction::operator()(int args) { // args?
	DEBUG_LOG(sender->getDescription(Object::NAME) + L" runned: " + descriptions[NAME]);
	for (std::pair<DIDEngine::DIDES_t, std::pair<ObjectProperty*, DIDEngine::DIDEOPV_t>> prop : properties)
		prop.second.first->inc(prop.second.second, sender);
}