#include "AbstractScene.h"

AbstractScene::AbstractScene(ISceneChangedListener* impl, const Parameter& parameter) : _implSceneChangedListener(impl), _parameter(parameter) {

}