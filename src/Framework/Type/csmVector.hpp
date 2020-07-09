/**
 * Copyright(c) Live2D Inc. All rights reserved.
 *
 * Use of this source code is governed by the Live2D Open Software license
 * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
 */

#pragma once

#include "CubismFramework.hpp"
#include "Utils/CubismDebug.hpp"

#include <QString>

#ifndef NULL
    #define NULL 0
#endif

//--------- LIVE2D NAMESPACE ------------
namespace Live2D
{
    namespace Cubism
    {
        namespace Framework
        {
            ////========================テンプレートの宣言==============================
            //
            ///**
            // * @brief   ベクター型（可変配列型）<br>
            // *           コンシューマゲーム機等でSTLの組み込みを避けるための実装。std::vector の簡易版
            // *
            // */
            // template<class T>
            // class QVector
            //{
            //  public:
            //    /**
            //     * @brief   コンストラクタ
            //     */
            //    QVector();
            //
            //    /**
            //     * @brief   引数付きコンストラクタ
            //     *
            //     * @param[in]   initialCapacity ->  初期化後のキャパシティ。データサイズは_capacity * sizeof(T)
            //     * @param[in]   zeroClear       ->  trueなら初期化時に確保した領域を0で埋める
            //     *
            //     */
            //    QVector(int initialCapacity, bool zeroClear = false);
            //
            //    /**
            //     * @brief   デストラクタ
            //     *
            //     */
            //    virtual ~QVector();
            //
            //    /**
            //     * @brief   コンテナの先頭アドレスを返す
            //     *
            //     */
            //    T *GetPtr()
            //    {
            //        return _ptr;
            //    }
            //
            //    /**
            //     * @brief   []演算子のオーバーロード
            //     *
            //     */
            //    T &operator[](int index)
            //    {
            //        return _ptr[index];
            //    }
            //
            //    /**
            //     * @brief   []演算子のオーバーロード(const)
            //     *
            //     */
            //    const T &operator[](int index) const
            //    {
            //        return _ptr[index];
            //    }
            //
            //    /**
            //     * @brief   インデックスで指定した要素を返す
            //     *
            //     */
            //    T &At(int index)
            //    {
            //        return _ptr[index];
            //    }
            //
            //    /**
            //     * @brief   PushBack処理.コンテナに新たな要素を追加する。
            //     *
            //     * @param[in]   value            -> PushBack処理で追加する値。
            //     * @param[in]   callPlacementNew -> PushBack時に配置newを呼び出す場合はtrue（クラスインスタンス）
            //     *                                   PushBack時に値を単純に代入する場合はfalse（プリミティブ、ポインタ）
            //     */
            //    void PushBack(const T &value, bool callPlacementNew = true);
            //
            //    /**
            //     * @brief   コンテナの全要素を解放する
            //     *
            //     */
            //    void Clear();
            //
            //    /**
            //     * @brief   コンテナの要素数を返す
            //     *
            //     * @return  コンテナの要素数
            //     */
            //    csmUint32 GetSize() const
            //    {
            //        return _size;
            //    }
            //
            //    /**
            //     * @brief   vector#resize()に相当するサイズ変更<br>
            //     *           プリミティブ、ポインタ型などの時には、UpdateSize(size,value,
            //     * false)で呼び出すと多少パフォーマンスが改善する場合がある。
            //     *
            //     */
            //    void Resize(int size, T value = T())
            //    {
            //        UpdateSize(size, value, true);
            //    }
            //
            //    /***
            //     * @brief vector#resize()に相当するサイズ変更
            //     *
            //     * @param[in]   size    ->  新しいサイズ
            //     * @param[in]   value   ->  リサイズ時に埋める値
            //     * @param[in]   callPlacementNew    ->  UpdateSize時に配置newを呼び出す場合はtrue（クラスインスタンス）<br>
            //     *                                       UpdateSize時に値を単純に代入する場合はfalse(プリミティブ、ポインタ）
            //     *
            //     */
            //    void UpdateSize(int size, T value = T(), bool callPlacementNew = true);
            //
            //    /**
            //     * @brief   コンテナのキャパシティを確保する<br>
            //     *
            //     * @param[in]   newSize -> 新たなキャパシティ。引数の値が現在のサイズ未満の場合は何もしない。
            //     */
            //    void PrepareCapacity(int newSize);
            //
            //    /**
            //     * @brief   QVector<T>のイテレータの前方宣言
            //     */
            //    class iterator;
            //
            //    /**
            //     * @brief   コンテナにコンテナ要素を挿入する
            //     *
            //     * @param[in]   position    ->  挿入する位置
            //     * @param[in]   begin       ->  挿入するコンテナの開始位置
            //     * @param[in]   end         ->  挿入するコンテナの終端位置
            //     * @param[in]   callPlacementNew    ->  Insert時に配置newを呼び出す場合はtrue（クラスインスタンス）
            //     *                                       Insert時に値を単純に代入する場合はfalse（プリミティブ、ポインタ）
            //     */
            //    void Insert(iterator position, iterator begin, iterator end, bool callPlacementNew = true);
            //
            //    /**
            //     * @brief   コンテナの全要素に対して代入処理を行う。
            //     *
            //     * @param[in]   newSize ->  代入処理後のサイズ
            //     * @param[in]   value   ->  要素に代入する値
            //     * @param[in]   callPlacementNew    -> Assign時に配置newを呼び出す場合はtrue（クラスインスタンス）<br>
            //     *                                      Assign時に値を単純に代入する場合はfalse(プリミティブ、ポインタ）
            //     *
            //     */
            //    void Assign(int newSize, T value = T(), bool callPlacementNew = true);
            //
            //    /**
            //     * @brief   コンテナからインデックスで指定した要素を削除する
            //     *
            //     * @param[in]   index   ->  インデックス値
            //     * @retval      true    ->  削除実行
            //     * @retval      false   ->  削除範囲外
            //     */
            //    bool Remove(int index)
            //    {
            //        if (index < 0 || _size <= index)
            //            return false; // 削除範囲外
            //        _ptr[index].~T();
            //
            //        // 削除(メモリをシフトする)、最後の一つを削除する場合はmove不要
            //        if (index < _size - 1)
            //            memmove(&(_ptr[index]), &(_ptr[index + 1]), sizeof(T) * (_size - index - 1));
            //        --_size;
            //        return true;
            //    }
            //
            //    /**
            //     * @brief   QVector<T>のイテレータ
            //     *
            //     */
            //    class iterator
            //    {
            //        // QVector<T>をフレンドクラスとする
            //        friend class QVector;
            //
            //      public:
            //        /**
            //         * @brief   コンストラクタ
            //         *
            //         */
            //        iterator() : _index(0), _vector(NULL)
            //        {
            //        }
            //
            //        /**
            //         * @brief   引数付きコンストラクタ
            //         *
            //         * @param[in]   v   ->  QVector<T>のオブジェクト
            //         *
            //         */
            //        iterator(QVector<T> *v) : _index(0), _vector(v)
            //        {
            //        }
            //
            //        /**
            //         * @brief   引数付きコンストラクタ
            //         *
            //         * @param[in]   v   ->  QVector<T>のオブジェクト
            //         * @param[in]   idx ->  コンテナから参照するインデックス値
            //         */
            //        iterator(QVector<T> *v, int idx) : _index(idx), _vector(v)
            //        {
            //        }
            //
            //        /**
            //         * @brief   =演算子のオーバーロード
            //         *
            //         */
            //        iterator &operator=(const iterator &ite)
            //        {
            //            this->_index = ite._index;
            //            this->_vector = ite._vector;
            //            return *this;
            //        }
            //
            //        /**
            //         * @brief   前置++演算子のオーバーロード
            //         *
            //         */
            //        iterator &operator++()
            //        {
            //            ++this->_index;
            //            return *this;
            //        }
            //
            //        /**
            //         * @brief   前置--演算子のオーバーロード
            //         *
            //         */
            //        iterator &operator--()
            //        {
            //            --this->_index;
            //            return *this;
            //        }
            //
            //        /**
            //         * @brief   後置++演算子のオーバーロード(intは後置用のダミー引数)
            //         *
            //         */
            //        iterator operator++(int)
            //        {
            //            return iterator(this->_vector, this->_index++); // 古い値を保存, 古い値を返す
            //        }
            //
            //        /**
            //         * @brief   後置--演算子のオーバーロード(intは後置用のダミー引数)
            //         *
            //         */
            //        iterator operator--(int)
            //        {
            //            iterator iteold(this->_vector, this->_index--); // 古い値を保存
            //            return iteold;
            //        }
            //
            //        /**
            //         * @brief    *演算子のオーバーロード
            //         *
            //         */
            //        T &operator*() const
            //        {
            //            return this->_vector->_ptr[this->_index];
            //        }
            //
            //        /**
            //         * @brief   !=演算子のオーバーロード
            //         *
            //         */
            //        bool operator!=(const iterator &ite) const
            //        {
            //            return (this->_index != ite._index) || (this->_vector != ite._vector);
            //        }
            //
            //      private:
            //        int _index;       ///< コンテナのインデックス値
            //        QVector<T> *_vector; ///< コンテナの参照
            //    };
            //
            //    /**
            //     * @brief   QVector<T>のイテレータ（const）
            //     *
            //     */
            //    class const_iterator
            //    {
            //        // QVector<T>をフレンドクラスとする
            //        friend class QVector;
            //
            //      public:
            //        /**
            //         * @brief   コンストラクタ
            //         *
            //         */
            //        const_iterator() : _index(0), _vector(NULL)
            //        {
            //        }
            //
            //        /**
            //         * @brief   引数付きコンストラクタ
            //         *
            //         * @param[in]   v   ->  QVector<T>のオブジェクト
            //         *
            //         */
            //        const_iterator(const QVector<T> *v) : _index(0), _vector(v)
            //        {
            //        }
            //
            //        /**
            //         * @brief   引数付きコンストラクタ
            //         *
            //         * @param[in]   v   ->  QVector<T>のオブジェクト
            //         * @param[in]   idx ->  コンテナから参照するインデックス値
            //         */
            //        const_iterator(const QVector<T> *v, int idx) : _index(idx), _vector(v)
            //        {
            //        }
            //        /**
            //         * @brief   =演算子のオーバーロード
            //         *
            //         */
            //        const_iterator &operator=(const const_iterator &ite)
            //        {
            //            this->_index = ite._index;
            //            this->_vector = ite._vector;
            //            return *this;
            //        }
            //
            //        /**
            //         * @brief   前置++演算子のオーバーロード
            //         *
            //         */
            //        const_iterator &operator++()
            //        {
            //            ++this->_index;
            //            return *this;
            //        }
            //
            //        /**
            //         * @brief   前置--演算子のオーバーロード
            //         *
            //         */
            //        const_iterator &operator--()
            //        {
            //            --this->_index;
            //            return *this;
            //        }
            //
            //        /**
            //         * @brief   後置++演算子のオーバーロード(intは後置用のダミー引数)
            //         *
            //         */
            //        const_iterator operator++(int)
            //        {
            //            const_iterator iteold(this->_vector, this->_index++); // 古い値を保存
            //            return iteold;                                        // 古い値を返す
            //        }
            //
            //        /**
            //         * @brief   後置--演算子のオーバーロード(intは後置用のダミー引数)
            //         *
            //         */
            //        const_iterator operator--(int)
            //        {
            //            const_iterator iteold(this->_vector, this->_index--); // 古い値を保存
            //            return iteold;
            //        }
            //
            //        /**
            //         * @brief    *演算子のオーバーロード
            //         *
            //         */
            //        T &operator*() const
            //        {
            //            return this->_vector->_ptr[this->_index];
            //        }
            //
            //        /**
            //         * @brief   !=演算子のオーバーロード
            //         *
            //         */
            //        bool operator!=(const const_iterator &ite) const
            //        {
            //            return (this->_index != ite._index) || (this->_vector != ite._vector);
            //        }
            //
            //      private:
            //        int _index;             ///< コンテナのインデックス値
            //        const QVector<T> *_vector; ///< コンテナのポインタ
            //    };
            //
            //    /**
            //     * @brief   コンテナの先頭要素を返す
            //     *
            //     */
            //    const iterator Begin()
            //    {
            //        return iterator(this, 0);
            //    }
            //
            //    /**
            //     * @bief    コンテナの終端要素を返す
            //     *
            //     */
            //    const iterator End()
            //    {
            //        return iterator(this, _size); // 終了
            //    }
            //
            //    /**
            //     * @brief   コンテナの先頭要素を返す
            //     *
            //     */
            //    const const_iterator Begin() const
            //    {
            //        return const_iterator(this, 0);
            //    }
            //
            //    /**
            //     * @bief    コンテナの終端要素を返す
            //     */
            //    const const_iterator End() const
            //    {
            //        return const_iterator(this, _size); // 終了
            //    }
            //
            //    /**
            //     * @brief   コンテナから要素を削除して他の要素をシフトする
            //     *
            //     * @param[in]   ite ->  削除する要素
            //     *
            //     */
            //    const iterator Erase(const iterator &ite)
            //    {
            //        int index = ite._index;
            //        if (index < 0 || _size <= index)
            //            return ite; // 削除範囲外
            //
            //        // 削除(メモリをシフトする)、最後の一つを削除する場合はmove不要
            //        if (index < _size - 1)
            //            memmove(&(_ptr[index]), &(_ptr[index + 1]), sizeof(T) * (_size - index - 1));
            //        --_size;
            //
            //        return iterator(this, index); // 終了
            //    }
            //
            //    /**
            //     * @brief   コンテナから要素を削除して他の要素をシフトする
            //     *
            //     * @param[in]   ite ->  削除する要素
            //     *
            //     */
            //    const const_iterator Erase(const const_iterator &ite)
            //    {
            //        int index = ite._index;
            //        if (index < 0 || _size <= index)
            //            return ite; // 削除範囲外
            //
            //        // 削除(メモリをシフトする)、最後の一つを削除する場合はmove不要
            //        if (index < _size - 1)
            //            memmove(&(_ptr[index]), &(_ptr[index + 1]), sizeof(T) * (_size - index - 1));
            //
            //        --_size;
            //
            //        const_iterator ite2(this, index); // 終了
            //        return ite2;
            //    }
            //
            //    /**
            //     * @brief   コンテナの値を32ビット符号付き整数型でダンプする
            //     *
            //     */
            //    void DumpAsInt()
            //    {
            //        for (int i = 0; i < _size; i++) CubismLogDebug("%d ,", _ptr[i]);
            //        CubismLogDebug("\n");
            //    }
            //
            //    /**
            //     * @brief   コピーコンストラクタ
            //     *
            //     * @param[in]   c   ->  QVector<T>のインスタンス
            //     */
            //    QVector(const QVector &c)
            //    {
            //        Copy(c);
            //    }
            //
            //    /**
            //     * @brief   コピーコンストラクタ
            //     *
            //     * @param[in]   c   ->  QVector<T>のインスタンス
            //     */
            //    QVector &operator=(const QVector &c)
            //    {
            //        if (this != &c)
            //        {
            //            Clear();
            //            Copy(c);
            //        }
            //
            //        return *this;
            //    }
            //
            //  private:
            //    static const int s_defaultSize = 10; ///< コンテナ初期化のデフォルトサイズ
            //
            //    /**
            //     * @brief   QVector<T>のコピー関数
            //     *
            //     * @param[in]   c   ->  QVector<T>のインスタンス
            //     */
            //    void Copy(const QVector &c)
            //    {
            //        _size = c._size;
            //        _capacity = c._capacity;
            //
            //        _ptr = (T *) CSM_MALLOC(_capacity * sizeof(T));
            //
            //        for (int i = 0; i < _size; ++i)
            //        {
            //            CSM_PLACEMENT_NEW(&_ptr[i]) T(c._ptr[i]);
            //        }
            //    }
            //
            //    T *_ptr;            ///< コンテナの先頭アドレス（ポインタ）
            //    int _size;     ///< コンテナの要素数（サイズ）
            //    int _capacity; ///< コンテナのキャパシティ
            //};
            //
            ////========================テンプレートの定義==============================
            //
            // template<class T>
            // QVector<T>::QVector() : _ptr(NULL), _size(0), _capacity(0)
            //{
            //}
            //
            // template<class T>
            // QVector<T>::QVector(int initialCapacity, bool zeroClear)
            //{
            //    if (initialCapacity < 1)
            //    {
            //        _ptr = NULL;
            //        _capacity = 0;
            //        _size = 0;
            //    }
            //    else
            //    {
            //        _ptr = static_cast<T *>(CSM_MALLOC(sizeof(T) * initialCapacity)); // ここだけ calloc により、確保したバイトを0で埋める
            //
            //        CSM_ASSERT(_ptr != NULL);
            //
            //        if (zeroClear)
            //        {
            //            memset(_ptr, 0, sizeof(T) * initialCapacity);
            //        }
            //
            //        _capacity = initialCapacity;
            //        _size = 0;
            //    }
            //}
            //
            // template<class T>
            // QVector<T>::~QVector()
            //{
            //    Clear();
            //}
            //
            // template<class T>
            // void QVector<T>::PushBack(const T &value, bool callPlacementNew)
            //{
            //    if (_size >= _capacity)
            //    {
            //        PrepareCapacity(_capacity == 0 ? s_defaultSize : _capacity * 2);
            //    }
            //
            //    // placement new 指定のアドレスに、実体を生成する
            //    if (callPlacementNew)
            //    {
            //        CSM_PLACEMENT_NEW(&_ptr[_size++]) T(value);
            //    }
            //    else
            //    {
            //        _ptr[_size++] = value;
            //    }
            //}
            //
            // template<class T>
            // void QVector<T>::PrepareCapacity(int newSize)
            //{
            //    if (newSize > _capacity)
            //    {
            //        if (_capacity == 0)
            //        {
            //            _ptr = static_cast<T *>(CSM_MALLOC(sizeof(T) * newSize));
            //
            //            CSM_ASSERT(_ptr != NULL);
            //
            //            _capacity = newSize;
            //        }
            //        else
            //        {
            //            int tmp_capacity = newSize;
            //            T *tmp = static_cast<T *>(CSM_MALLOC(sizeof(T) * tmp_capacity));
            //
            //            CSM_ASSERT(tmp != NULL);
            //
            //            memcpy(static_cast<void *>(tmp), static_cast<void *>(_ptr), sizeof(T) * _capacity); //
            //            通常のMALLOCになったためコピーする CSM_FREE(_ptr);
            //
            //            _ptr = tmp;
            //            _capacity = newSize;
            //        }
            //    }
            //}
            //
            // template<class T>
            // void QVector<T>::Clear()
            //{
            //    for (int i = 0; i < _size; i++)
            //    {
            //        _ptr[i].~T();
            //    }
            //
            //    CSM_FREE(_ptr);
            //
            //    _ptr = NULL;
            //    _size = 0;
            //    _capacity = 0;
            //}
            //
            // template<class T>
            // void QVector<T>::UpdateSize(int newSize, T value, bool callPlacementNew)
            //{
            //    int cur_size = this->_size;
            //    if (cur_size < newSize)
            //    {
            //        PrepareCapacity(newSize); // capacity更新
            //
            //        if (callPlacementNew)
            //        {
            //            for (int i = _size; i < newSize; i++)
            //            {
            //                // placement new 指定のアドレスに、実体を生成する
            //                CSM_PLACEMENT_NEW(&_ptr[i]) T(value);
            //            }
            //        }
            //        else
            //        {
            //            for (int i = _size; i < newSize; i++)
            //            {
            //                _ptr[i] = value;
            //            }
            //        }
            //    }
            //    else
            //    {
            //        // new_size <= _size
            //        //---
            //        for (int i = newSize; i < _size; i++)
            //        {
            //            _ptr[i].~T(); // 不要なので破棄する
            //        }
            //    }
            //    this->_size = newSize;
            //}
            //
            // template<class T>
            // void QVector<T>::Assign(int newSize, T value, bool callPlacementNew)
            //{
            //    int cur_size = this->_size;
            //
            //    // 全てデストラクト
            //    for (int i = 0; i < _size; i++)
            //    {
            //        _ptr[i].~T();
            //    }
            //
            //    //
            //    if (cur_size < newSize)
            //    {
            //        PrepareCapacity(newSize); // capacity更新
            //    }
            //
            //    if (callPlacementNew)
            //    {
            //        for (int i = 0; i < newSize; i++)
            //        {
            //            CSM_PLACEMENT_NEW(&_ptr[i]) T(value); // placement new 指定のアドレスに、実体を生成する
            //        }
            //    }
            //    else
            //    {
            //        for (int i = 0; i < newSize; i++)
            //        {
            //            _ptr[i] = value;
            //        }
            //    }
            //
            //    this->_size = newSize;
            //}
            //
            // template<class T>
            // void QVector<T>::Insert(iterator position, iterator begin, iterator end, bool callPlacementNew)
            //{
            //    int dst_si = position._index;
            //    int src_si = begin._index;
            //    int src_ei = end._index;
            //
            //    int addcount = src_ei - src_si;
            //
            //    PrepareCapacity(_size + addcount);
            //
            //    // 挿入用に既存データをシフトして隙間を作る
            //    if (_size - dst_si > 0)
            //    {
            //        memmove(&(_ptr[dst_si + addcount]), &(_ptr[dst_si]), sizeof(T) * (_size - dst_si));
            //    }
            //
            //    // placement new 指定のアドレスに、実体を生成する
            //    if (callPlacementNew)
            //    {
            //        for (int i = src_si; i < src_ei; i++, dst_si++)
            //        {
            //            CSM_PLACEMENT_NEW(&_ptr[i]) T(begin._vector->_ptr[i]);
            //        }
            //    }
            //    else
            //    {
            //        for (int i = src_si; i < src_ei; i++, dst_si++)
            //        {
            //            _ptr[dst_si] = begin._vector->_ptr[i];
            //        }
            //    }
            //
            //    this->_size = _size + addcount;
            //}
        } // namespace Framework
    }     // namespace Cubism
} // namespace Live2D
