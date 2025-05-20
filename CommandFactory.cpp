#include "CommandFactory.h"
#include "OmniShotCommand.h"
#include "OmniSpiralCommand.h"
#include "Define.h"
#include "ConvertUtils.h"
#include "ExprEval.h"

std::shared_ptr<BulletCommand> CommandFactory::CreateFromJSON(const nlohmann::json& j) {



	std::string type = j.value("type", "");
    if (type == "OmniShot") {
        auto posArray = j["position"];
        Vector2<float> pos = {
            posArray[0].is_string() ? EvaluateExpr(posArray[0]) : posArray[0].get<float>(),
            posArray[1].is_string() ? EvaluateExpr(posArray[1]) : posArray[1].get<float>()
        };

        float speed = j.value("speed", 5.0f);
        int numBullets = j.value("numBullets", 8);
        int color = j.value("color", 0);

        std::string sizeStr = j.value("size", "Small");
        eBulletSize size = ConvertUtils::StringToSize(sizeStr);

        return std::make_shared<OmniShotCommand>(pos, speed, numBullets, color, size);
    }
    if (type == "OmniSpiral") {
        auto posArray = j["position"];
        Vector2<float> pos = {
            posArray[0].is_string() ? EvaluateExpr(posArray[0]) : posArray[0].get<float>(),
            posArray[1].is_string() ? EvaluateExpr(posArray[1]) : posArray[1].get<float>()
        };

        int numBullets = j.value("numBullets", 5);
        float speed = j.value("speed", 5.0f);
        int color = j.value("color", 0);

        std::string sizeStr = j.value("size", "Small");
        eBulletSize size = ConvertUtils::StringToSize(sizeStr);

        return std::make_shared<OmniSpiralCommand>(pos, numBullets, speed, color, size);
    }

    throw std::runtime_error("Unknown command type: " + type);
}