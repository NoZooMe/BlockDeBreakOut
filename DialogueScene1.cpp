#include "DialogueScene1.h"
#include "DialogueScriptLoader.h"
#include "ISceneChangedListener.h"

DialogueScene1::DialogueScene1(ISceneChangedListener* impl, const Parameter& param) : AbstractDialogueScene(impl, param) {

}

void DialogueScene1::InitDialogueScript() {
	_dialogues = DialogueScriptLoader::LoadDialogueFromJson("Dialogue1Script.json");
}

void DialogueScene1::CallSceneChange() {
	Parameter param;
	_implSceneChangedListener->onSceneChanged(eScene::Stage1, param, true);
}