/**
 * @file observer_pattern.h
 * @author PFA03027@nifty.com
 * @brief base class of observer pattern
 * @version 0.1
 * @date 2022-09-23
 * 
 * @copyright Copyright (c) 2022, PFA03027@nifty.com
 * 
 * この実装はGoFのデザインパターンを、そのまま実装したobserver patternの実装です。
 * update()によるコールバックによって、subjectクラスの更新をobserverクラスへ通知する構成です。
 * observerへのポインタは、ダングリングポインタを避けるためstd::weak_ptrを使用した実装としてみました。
 * 
 * このパターンの注意点は、updateの無限連鎖です。
 * 具体的には、
 * (1) subjectクラスがobserverのupdate()を呼び出す
 * (2) Observerクラスからsubjectクラスの操作
 * (3) (1)に戻る。あるいは、さらに別のクラスを経由して(1)に戻る
 * という流れです。
 * observerパターンの実装をライブラリ化して提供する場合、特にこの状況に対策する必要があります。
 * 
 * 対策基本は、update()の呼び出しに対し、subjectを変更する操作を呼び出さないことです。
 * これを上手く強制する実装上のテクニックとしては、
 * * observerクラスがsubjectの操作を行わない役割とし、observerクラスが参照するsubjectクラスへのポインタはconst型とする。
 * 方法があります。
 * 
 * また、無限連鎖が引き起こす具体的な現象として再帰呼び出しがあります(*1)。
 * 再帰呼び出しを検出して、再帰呼び出しの場合はupdateの呼び出しをスキップする方法もあります。
 * ただ、この場合は、変更 -> 通知の流れに前提条件が発生するために、使用者側に注意を促す必要があります。
 * 
 * (*1) メッセージシステムobserver patternを実現する場合は、メッセージ無限生成といった現象として現れます。
 */

#ifndef OBSERVER_PATTERN_H_
#define OBSERVER_PATTERN_H_

#include <memory>
#include <vector>

class base_subject;

class base_observer {
public:
    virtual void update(const base_subject*) = 0;
};

class base_subject {
public:
    void subscribe_observer(std::weak_ptr<base_observer> wp_obsvr) {
        std::shared_ptr<base_observer> sp_candidate_obs = wp_obsvr.lock();
        if( sp_candidate_obs == nullptr ) return;

        for (auto it = obsvrs_.begin(); it != obsvrs_.end();) {
            // wpが監視しているshared_ptrオブジェクトの
            // 寿命が切れていなければ処理する
            if (std::shared_ptr<base_observer> r = it->lock()) {
                if( r == sp_candidate_obs ) {
                    // すでに登録されているので、登録しない
                    return;
                }
                ++it;
            } else {
                // shared_ptrオブジェクトの寿命が切れているため、observerリストから削除する
                it = obsvrs_.erase(it); // C++11 specification.
            }
        }
        obsvrs_.push_back(wp_obsvr);
    }
    void unsubscribe_observer(std::weak_ptr<base_observer> wp_obsvr) {
        std::shared_ptr<base_observer> sp_candidate_obs = wp_obsvr.lock();
        if( sp_candidate_obs == nullptr ) return;

        for (auto it = obsvrs_.begin(); it != obsvrs_.end();) {
            // wpが監視しているshared_ptrオブジェクトの
            // 寿命が切れていなければ処理する
            if (std::shared_ptr<base_observer> r = it->lock()) {
                if( r == sp_candidate_obs ) {
                    // 登録されているweak_ptrを発見したので、削除する
                    obsvrs_.erase(it);
                    return;
                }
                ++it;
            } else {
                // shared_ptrオブジェクトの寿命が切れているため、observerリストから削除する
                it = obsvrs_.erase(it); // C++11 specification.
            }
        }
    }

protected:
    void notify_update(void) {
        if( recursive_count_ >= max_recursive_count_ ) {
            // 再帰呼び出しの深さが深すぎる場合は、即終了。
            // 実装不具合の場合もあるので、例外を呼び出すのも対処方法としてはあり。
            return;
        }

        recursive_count_++;
        if( recursive_count_ == 1 ) {
            // イテレート中に要素削除をする可能性があるため、範囲for文は使用できない
            for (auto it = obsvrs_.begin(); it != obsvrs_.end();) {
                // wpが監視しているshared_ptrオブジェクトの
                // 寿命が切れていなければ処理する
                if (std::shared_ptr<base_observer> r = it->lock()) {
                    r->update(this);
                    ++it;
                } else {
                    // shared_ptrオブジェクトの寿命が切れているため、observerリストから削除する
                    it = obsvrs_.erase(it); // C++11 specification.
                }
            }
        }
        recursive_count_--;
    }

private:
    using container = std::vector<std::weak_ptr<base_observer>>;

    container obsvrs_;
    int  recursive_count_ = 0;
    static const int max_recursive_count_ = 64;
};

#endif
