#pragma once
#include "Task.h"
#include "Block.h"
#include "Ball.h"
#include "Def.h"

#include <vector>
#include <memory>
class BlockMgr :
    public Task
{
private:
    std::vector<std::shared_ptr<Block>> _vector;
    static const int NUM = BLOCK_NUM;

public:
    BlockMgr();
    void Init() override;
    void Fin() override;
    void Update() override;
    void Draw() const override;

    int Getter_BlockNUM() const { return NUM; };

    //�����Ă���u���b�N�ւ̃|�C���^��Ԃ�
    std::shared_ptr<RectangleObject> Getter_LiveBlock(int num) const;

    //i�Ԗڂ̃u���b�N��_live�t���O��value�̒l��
    void SetBlockFlag_Live(int i, bool value);

    //�����Ă���u���b�N�̐���Ԃ�
    int Getter_LiveNum() const; 

};

