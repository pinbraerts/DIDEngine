#include "DIDEngineObjectProperty.h"

DIDEngine::ObjectProperty::ObjectProperty(
	DIDEOPV_t Curval,
	DIDEngine::Object* Target,
	std::vector<DIDEngine::DIDES_t> Pdescriptions,
	void(*Onmvr)(DIDEngine::Object*, DIDEngine::Object*),
	void(*Onmxvr)(DIDEngine::Object*, DIDEngine::Object*)
) : currentValue(Curval), target(Target), descriptions(Pdescriptions), onMinValueReached(Onmvr), onMaxValueReached(Onmxvr) {
	descriptions.resize(3); // DIDEngine::ObjectProperty::Descriptions count
}

bool DIDEngine::ObjectProperty::setTarget(DIDEngine::Object* newTar)
{
	if (target == newTar) return true;
	if(target != nullptr) target->removeProperty(this);
	target = newTar;
	return target->addProperty(this);
}

void DIDEngine::ObjectProperty::safetyCall(DIDEngine::Object* Sender, bool onMinValueCh)
{
	if (onMinValueCh)
		if (onMinValueReached != nullptr) (*onMinValueReached)(Sender, target);
		else return;
	else if (onMaxValueReached != nullptr) (*onMaxValueReached)(Sender, target);
}

const DIDEngine::DIDES_t DIDEngine::ObjectProperty::getDescription(unsigned index) const
{
	return descriptions[index];
}

const std::vector<DIDEngine::DIDES_t> DIDEngine::ObjectProperty::getDescriptions() const
{
	return descriptions;
}

const DIDEngine::Object * DIDEngine::ObjectProperty::getTarget() const
{
	return target;
}

void DIDEngine::ObjectProperty::setDescription(unsigned index, DIDEngine::DIDES_t value)
{
	if (index == NAME && target != nullptr) {
		target->removeProperty(this);
		descriptions[NAME] = value;
		target->addProperty(this);
	}
	else descriptions[index] = value;
}

void DIDEngine::ObjectProperty::setDescriptions(std::vector<DIDEngine::DIDES_t> newDescs)
{
	descriptions = newDescs;
}

void DIDEngine::ObjectProperty::set(DIDEOPV_t value, DIDEngine::Object* sender) {
	if (value <= minimumValue) {
		safetyCall(sender, true); // (*onMinValueReached)(sender, target);
		DEBUG_LOG(descriptions[NAME] + L": minimum value reached, sender: " + sender->getDescription(DIDEngine::Object::NAME));
	}
	else if (value >= maximumValue) {
		safetyCall(sender, false); // (*onMaxValueReached)(sender, target);
		DEBUG_LOG(descriptions[NAME] + L": maximum value reached, sender: " + sender->getDescription(DIDEngine::Object::NAME));
	}
	currentValue = value;
}

void DIDEngine::ObjectProperty::inc(DIDEOPV_t value, DIDEngine::Object* sender) {
	DIDEOPV_t temval = currentValue + value;
	if (value <= minimumValue || temval <= minimumValue) {
		safetyCall(sender, true); // (*onMinValueReached)(sender, target);
		DEBUG_LOG(descriptions[NAME] + L": minimum value reached, sender: " + sender->getDescription(DIDEngine::Object::NAME));
	}
	else if (value >= maximumValue || temval >= maximumValue) {
		safetyCall(sender, false); // (*onMaxValueReached)(sender, target);
		DEBUG_LOG(descriptions[NAME] + L": maximum value reached, sender: " + sender->getDescription(DIDEngine::Object::NAME));
	}
	currentValue = temval;
}

DIDEngine::DIDEOPV_t DIDEngine::ObjectProperty::get() const {
	return currentValue;
}