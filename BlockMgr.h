#pragma once
#include "Task.h"
#include "Block.h"

#include <vector>
#include <memory>
class BlockMgr :
    public Task
{
private:
    std::vector<std::shared_ptr<Block>> _vector;
    static const int NUM;

public:
    BlockMgr();
    void Initialize() override;
    void Finalize() override;
    void Update() override;
    void Draw() const override;

    int Getter_BlockNUM() const { return NUM; };

    //生きているブロックへのポインタを返す。ここ、生ポインタでいい気がする。
    std::shared_ptr<RectangleObject> Getter_LiveBlock(int num) const;

    //i番目のブロックの_liveフラグをvalueの値に
    void SetBlockFlag_Live(int i, bool value);

    //生きているブロックの数を返す
    int Getter_LiveNum() const; 

};

