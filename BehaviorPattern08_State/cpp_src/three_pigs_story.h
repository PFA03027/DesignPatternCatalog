/**
 * @file three_pigs_story.h
 * @author PFA03027@nifty.com
 * @brief state pattern header file base on three little pigs story
 * @version 0.1
 * @date 2022-11-10
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * ３匹の子ブタの物語をテーマに、Stateパターンの実装サンプルです。
 * 物語の推移をStateで表現したサンプルです。ただし、中のStateは隠蔽した実装サンプルとしました。
 * three_pigs_storyクラスのクライアントは、中の状態に関わらず、物語を進めるリクエストを発行する事ができます。
 * その結果、three_pigs_storyの状態設計も外部へのI/Fに影響を与えることなく変更することが可能になります。
 */

#ifndef STATE_PATTERN_H_
#define STATE_PATTERN_H_

#include <memory>
#include <iostream>
#include <vector>


class state {
public:
    virtual bool handle(void) = 0;
};

class three_pigs_story {
public:
    three_pigs_story(void);
    ~three_pigs_story();

    void request_next(void);

private:
    std::vector<std::unique_ptr<state>>  states_;
    int cur_state_idx_;
};

#endif
