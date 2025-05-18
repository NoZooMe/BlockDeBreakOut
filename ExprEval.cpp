#include "ExprEval.h"
#include "Define.h"
#include <tinyexpr-master/tinyexpr.h>
#include <stdexcept>

float EvaluateExpr(const std::string& expr) {
    static double PI = Define::PI;
    static double PLAYER_INIY = Define::PLAYER_INIY;
    static double SCREEN_WIDTH = Define::SCREEN_WIDTH;
    static double SCREEN_HEIGHT = Define::SCREEN_HEIGHT;

    te_variable vars[] = {
        {"PI", &PI},
        {"PLAYER_INIY", &PLAYER_INIY},
        {"SCREEN_WIDTH", &SCREEN_WIDTH},
        {"SCREEN_HEIGHT", &SCREEN_HEIGHT},
    };

    int err;
    te_expr* e = te_compile(expr.c_str(), vars, sizeof(vars) / sizeof(te_variable), &err);
    if (!e) {
        throw std::runtime_error("Failed to parse expression: \"" + expr + "\" at position " + std::to_string(err));
    }

    double result = te_eval(e);
    te_free(e);
    return static_cast<float>(result);
}