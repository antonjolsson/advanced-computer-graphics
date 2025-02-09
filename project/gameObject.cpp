
#include "gameObject.h"


#include <glm/gtx/euler_angles.inl>
#include <glm/mat4x2.hpp>



#include "../external/SDL2_mixer/include/SDL_mixer.h"
#include "BehaviourComponent.h"

void GameObject::create() {
	
}

void GameObject::addComponent(Component* _component) {
	components.push_back(_component);
}

void GameObject::addComponents(const std::vector<Component*>& _components) {
    for (auto comp : _components)
        addComponent(comp);
}

void GameObject::init() {
	for (auto& component : components)
        component->init();
    setEnabled(true);
}

void GameObject::update(const float _dt) {
	if (!isEnabled()) return;
	for (auto& component : components) {
        component->update(_dt);
	}

	modelMatrix[3] = glm::vec4(getPosition(), 1);
}

void GameObject::destroy() {
	for (auto& component : components)
        component->destroy();
}

GameObject::~GameObject() = default;

void GameObject::addReceiver(GameObject* _go) {
	receivers.push_back(_go);
}

void GameObject::send(const Message _m) {
	for (auto& receiver : receivers) {
		if (!receiver->isEnabled())
			continue;
        receiver->receive(_m);
	}
}

void GameObject::receive(const Message _m) {
    mailbox.insert(_m);
}

void GameObject::readMessages() {
    if (!isEnabled()) return;
    for (Message m : mailbox) {
	    switch (m) {
        case MOVED_LEFT: case MOVED_RIGHT:
            sendComponents(m);
        case NO_INPUT:
            sendComponents(m);
            break;
        case FIRE:
            sendComponents(m);
            break;
        case BULLET_HIT: case PLAYER_HIT:
            sendComponents(m);
            break;
        case OBJ_IN_AIR:
            mode = IN_AIR;
            sendComponents(m);
            break;
        case GAME_OVER:
            gameOver = true;
            sendComponents(m);
            break;
        case LEVEL_WON:
            levelWon = true;
            break;
        default: break;
		}
    }
    mailbox.clear();
}

void GameObject::sendComponents(Message _message) {
    for (auto& component : components)
        component->receive(_message);
}

void GameObject::create(unsigned int _gameWidth) {
    
}

int GameObject::getAttackDamage() {
	const BehaviourComponent behaviour = *getComponent<BehaviourComponent>();
    return behaviour.getAttackDamage();
}

bool GameObject::isInvincibleAfterHit() {
    const BehaviourComponent behaviour = *getComponent<BehaviourComponent>();
    return behaviour.isInvincibleAfterHit();
}

void GameObject::init(const int _hp, const int _attackDamage) {
    init();
}

void GameObject::setEnabled(const bool _enabled) {
	enabled = _enabled;
}

glm::mat4& GameObject::getModelMatrix(){
	return modelMatrix;
}

glm::vec3 GameObject::getPosition() const {
	return transform.position;
}

glm::vec3 GameObject::getRotation() const {
	return transform.position;
}

glm::vec3 GameObject::getScale() const {
	return  transform.position;
}

void GameObject::setPosition(const glm::vec3 _position)
{
    transform.position = _position;
}

void GameObject::setRotation(const glm::vec3 _rotation)
{
    transform.rotation = _rotation;
}

void GameObject::setScale(const glm::vec3 _scale)
{
    transform.scale = _scale;
}

GameObject::Transform& GameObject::getTransform()
{
    return transform;
}

GameObject::GameObject() {
	enabled = true;
	modelMatrix = glm::mat4(1.f);
}

GameObject::GameObject(const glm::vec3 _position, const glm::vec3 _rotation, const glm::vec3 _scale)
{
    transform = { _position, _rotation, _scale };
	modelMatrix = glm::eulerAngleYXZ(transform.rotation.y, transform.rotation.x, transform.rotation.z);
	modelMatrix[3] = glm::vec4(_position, 1.f);
}

bool GameObject::isEnabled() const
{
	return enabled;
}

bool GameObject::isGameOver() const {
    return gameOver;
}

bool GameObject::isLevelWon() const {
    return levelWon;
}
