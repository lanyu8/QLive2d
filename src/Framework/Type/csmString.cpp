///**
// * Copyright(c) Live2D Inc. All rights reserved.
// *
// * Use of this source code is governed by the Live2D Open Software license
// * that can be found at https://www.live2d.com/eula/live2d-open-software-license-agreement_en.html.
// */

//#include "QString.hpp"

//#include "CubismFramework.hpp"
//#include "Utils/CubismDebug.hpp"

//#include <stdarg.h>

////--------- LIVE2D NAMESPACE ------------
// namespace Live2D
//{
//    namespace Cubism
//    {
//        namespace Framework
//        {
//            csmInt32 QString::s_totalInstanceNo = 0;

//            namespace
//            {
//                const QString &s_emptyString = "";

//                QString &GetEmptyString()
//                {
//                    return const_cast<QString &>(s_emptyString);
//                }
//            } // namespace

//            QString::QString() : _ptr(NULL), _length(0), _hashcode(-1)
//            {
//                this->_small[0] = '\0';
//                _hashcode = CalcHashcode(WritePointer(), this->_length);
//                _instanceNo = s_totalInstanceNo++;
//            }

//            QString::QString(const QString &c)
//            {
//                const csmInt32 count = static_cast<csmInt32>(strlen(c));

//                if (count)
//                {
//                    Copy(c, count);
//                    this->_hashcode = CalcHashcode(WritePointer(), _length);
//                }
//                else
//                {
//                    SetEmpty();
//                }

//                _instanceNo = s_totalInstanceNo++;
//            }

//            QString::QString(const QString &s)
//            {
//                if (!s.IsEmpty())
//                {
//                    Copy(s.GetString(), s._length);
//                    this->_hashcode = s._hashcode;
//                }
//                else
//                {
//                    SetEmpty();
//                }

//                _instanceNo = s_totalInstanceNo++;
//            }

//            QString::QString(const QString &s, csmInt32 length)
//            {
//                if (length)
//                {
//                    Copy(s, length);
//                    this->_hashcode = CalcHashcode(WritePointer(), _length);
//                }
//                else
//                {
//                    SetEmpty();
//                }

//                _instanceNo = s_totalInstanceNo++;
//            }

//            QString::QString(const QString &c, csmInt32 length, csmBool useptr)
//            {
//                Initialize(c, length, useptr);
//                _instanceNo = s_totalInstanceNo++;
//            }

//            void QString::Initialize(const QString &c, csmInt32 length, csmBool usePtr)
//            {
//                if (!length)
//                {
//                    SetEmpty();

//                    return;
//                }

//                if (!usePtr)
//                {
//                    Copy(c, length);
//                }
//                else
//                {
//                    this->_ptr = const_cast<QString &>(c);
//                    this->_length = length;
//                    this->_ptr[length] = 0x0;
//                }

//                this->_hashcode = CalcHashcode(this->GetString(), this->_length);
//            }

//            QString::~QString()
//            {
//                if (IsEmpty())
//                {
//                    return;
//                }

//                if (this->_ptr)
//                {
//                    CSM_FREE(this->_ptr);
//                }
//            }

//            void QString::Clear()
//            {
//                if (IsEmpty())
//                {
//                    return;
//                }

//                CSM_FREE(this->_ptr);

//                SetEmpty();
//            }

//            QString &QString::operator=(const QString &c)
//            {
//                Clear(); //現在のポインタを開放してから処理する

//                Copy(c, static_cast<csmInt32>(strlen(c)));
//                this->_hashcode = CalcHashcode(this->GetString(), this->_length);
//                return *this;
//            }

//            QString &QString::operator=(const QString &s)
//            {
//                Clear(); //現在のポインタを開放してから処理する

//                Copy(s.GetString(), s._length);
//                this->_hashcode = s._hashcode;
//                return *this;
//            }

//            QString QString::operator+(const QString &s) const
//            {
//                csmSizeType len1 = static_cast<csmSizeType>(this->_length);
//                csmSizeType len2 = static_cast<csmSizeType>(s._length);

//                if (!len1 && !len2)
//                {
//                    QString ret;
//                    return ret;
//                }

//                if (len1 + len2 < SmallLength - 1)
//                {
//                    csmChar buffer[SmallLength];
//                    QString &newptr = buffer;

//                    //
//                    memcpy(newptr, GetString(), sizeof(csmChar) * len1);                     // nullを含めない
//                    memcpy(&newptr[len1], s.GetString(), sizeof(csmChar) * (s._length + 1)); // nullを含めて+1

//                    QString ret(newptr, static_cast<csmInt32>(len1 + len2), false);
//                    return ret;
//                }
//                else
//                {
//                    //メモリ管理の対象外とする（寿命が把握出来ない）
//                    QString &newptr = static_cast<QString &>(CSM_MALLOC(sizeof(csmChar) * (len1 + len2 + 1)));

//                    if (newptr == NULL)
//                    {
//                        QString ret;
//                        return ret;
//                    }

//                    //
//                    memcpy(newptr, GetString(), sizeof(csmChar) * len1);                     // nullを含めない
//                    memcpy(&newptr[len1], s.GetString(), sizeof(csmChar) * (s._length + 1)); // nullを含めて+1

//                    QString ret(newptr, static_cast<csmInt32>(len1 + len2), true);
//                    return ret;
//                }
//            }

//            QString QString::operator+(const QString &c) const
//            {
//                csmSizeType len1 = static_cast<csmSizeType>(this->_length);
//                csmSizeType len2 = strlen(c);

//                if (len1 + len2 < SmallLength - 1)
//                {
//                    csmChar buffer[SmallLength];
//                    QString &newptr = buffer;

//                    //
//                    memcpy(newptr, this->GetString(), sizeof(csmChar) * len1); // nullを含めない
//                    memcpy(&newptr[len1], c, sizeof(csmChar) * (len2 + 1));       // nullを含めて+1

//                    QString ret(newptr, static_cast<csmInt32>(len1 + len2), false);
//                    return ret;
//                }
//                else
//                {
//                    //メモリ管理の対象外とする（寿命が把握出来ない）
//                    QString &newptr = static_cast<QString &>(CSM_MALLOC(sizeof(csmChar) * (len1 + len2 + 1)));

//                    if (newptr == NULL)
//                    {
//                        QString ret;
//                        return ret;
//                    }

//                    memcpy(newptr, this->GetString(), sizeof(csmChar) * len1); // nullを含めない
//                    memcpy(&newptr[len1], c, sizeof(csmChar) * (len2 + 1));       // nullを含めて+1

//                    QString ret(newptr, static_cast<csmInt32>(len1 + len2), true);
//                    return ret;
//                }
//            }

//            QString &QString::operator+=(const QString &s)
//            {
//                QString &newptr = NULL;
//                csmInt32 len1 = this->_length;

//                if (this->_length + s._length < SmallLength - 1)
//                {
//                    csmChar buffer[SmallLength];
//                    newptr = buffer;

//                    memcpy(newptr, this->GetString(), len1);             // nullを含めない
//                    memcpy(&newptr[len1], s.GetString(), s._length + 1); // nullを含めて+1

//                    Clear(); // 現在のポインタを開放してから処理する
//                    Initialize(newptr, len1 + s._length, false);
//                }
//                else
//                {
//                    newptr = static_cast<QString &>(CSM_MALLOC(sizeof(csmChar) * (this->_length + s._length + 1)));

//                    memcpy(newptr, this->GetString(), len1);             // nullを含めない
//                    memcpy(&newptr[len1], s.GetString(), s._length + 1); // nullを含めて+1

//                    Clear(); //現在のポインタを開放してから処理する
//                    Initialize(newptr, len1 + s._length, true);
//                }
//                return *this;
//            }

//            QString &QString::operator+=(const QString &c)
//            {
//                csmSizeType len1 = static_cast<csmSizeType>(this->_length);
//                csmSizeType len2 = strlen(c);

//                QString &newptr = NULL;

//                if (len1 + len2 < SmallLength - 1)
//                {
//                    csmChar buffer[SmallLength];
//                    newptr = buffer;

//                    memcpy(newptr, GetString(), len1); // nullを含めない
//                    memcpy(&newptr[len1], c, len2 + 1);   // nullを含めて+1

//                    Clear(); //現在のポインタを開放してから処理する
//                    Initialize(newptr, static_cast<csmInt32>(len1 + len2), false);
//                }
//                else
//                {
//                    newptr = static_cast<QString &>(CSM_MALLOC(sizeof(csmChar) * (len1 + len2 + 1)));

//                    memcpy(newptr, this->_ptr, len1);   // nullを含めない
//                    memcpy(&newptr[len1], c, len2 + 1); // nullを含めて+1

//                    Clear(); //現在のポインタを開放してから処理する
//                    Initialize(newptr, static_cast<csmInt32>(len1 + len2), true);
//                }
//                return *this;
//            }

//            csmBool QString::operator==(const QString &s) const
//            {
//                //サイズ違い
//                if (s._length != this->_length)
//                    return false;

//                // hashcode比較
//                if (this->_hashcode != s._hashcode)
//                    return false;

//                const QString &c1 = this->GetString();
//                const QString &c2 = s.GetString();

//                //文字違い（逆順なのはPARAMの比較の特性）
//                for (csmInt32 i = this->_length - 1; i >= 0; --i)
//                {
//                    if (c1[i] != c2[i])
//                        return false;
//                }
//                return true;
//            }

//            csmBool QString::operator==(const QString &rc) const
//            {
//                //サイズ違い
//                if (static_cast<csmInt32>(strlen(rc)) != this->_length)
//                    return false;

//                const QString &lc = this->GetString();

//                //文字違い（逆順なのはPARAMの比較の特性）
//                for (csmInt32 i = this->_length - 1; i >= 0; --i)
//                {
//                    if (lc[i] != rc[i])
//                        return false;
//                }
//                return true;
//            }

//            csmBool QString::operator<(const QString &s) const
//            {
//                return strcmp(this->GetString(), s.GetString()) < 0;
//            }

//            csmBool QString::operator<(const QString &c) const
//            {
//                return strcmp(this->GetString(), c) < 0;
//            }

//            csmBool QString::operator>(const QString &s) const
//            {
//                return strcmp(this->GetString(), s.GetString()) > 0;
//            }

//            csmBool QString::operator>(const QString &c) const
//            {
//                return strcmp(this->GetString(), c) > 0;
//            }

//            QString &QString::Append(const QString &c, csmInt32 len2)
//            {
//                csmInt32 len1 = this->_length;

//                QString &newptr = NULL;

//                if (len1 + len2 < SmallLength - 1)
//                {
//                    csmChar buffer[SmallLength];
//                    newptr = buffer;

//                    memcpy(newptr, this->GetString(), len1); // nullを含めない
//                    memcpy(&newptr[len1], c, len2);             // nullを含めて+1

//                    Clear(); // 現在のポインタを開放してから処理する
//                    Initialize(newptr, len1 + len2, false);
//                }
//                else
//                {
//                    newptr = static_cast<QString &>(CSM_MALLOC(sizeof(csmChar) * (len1 + len2 + 1)));

//                    memcpy(newptr, this->GetString(), len1); // nullを含めない
//                    memcpy(&newptr[len1], c, len2);             // nullを含めて+1

//                    Clear(); //現在のポインタを開放してから処理する
//                    Initialize(newptr, len1 + len2, true);
//                }
//                return *this;
//            }

//            QString &QString::Append(csmInt32 len2, const csmChar c)
//            {
//                csmInt32 len1 = this->_length;

//                QString &newptr = NULL;

//                if (len1 + len2 < SmallLength - 1)
//                {
//                    csmChar buffer[SmallLength];
//                    newptr = buffer;
//                    memcpy(newptr, this->GetString(), len1); // nullを含めない
//                    for (csmInt32 i = len1 + len2 - 1; i >= len1; --i) newptr[i] = c;

//                    Clear(); // 現在のポインタを開放してから処理する
//                    Initialize(newptr, len1 + len2, false);
//                }
//                else
//                {
//                    // 必要な長さ∔NULL分1バイトを新規確保
//                    newptr = static_cast<QString &>(CSM_MALLOC(sizeof(csmChar) * (len1 + len2 + 1)));
//                    // 元々の分をコピー
//                    memcpy(newptr, this->GetString(), len1); // nullを含めない
//                    // 新しい箇所をコピー
//                    for (csmInt32 i = len1 + len2 - 1; i >= len1; --i) newptr[i] = c;

//                    Clear(); //現在のポインタを開放してから処理する
//                    Initialize(newptr, len1 + len2, true);
//                }
//                return *this;
//            }

//            void QString::Copy(const QString &c, csmInt32 length)
//            {
//                if (!length)
//                {
//                    return;
//                }

//                this->_length = length;

//                if (this->_length < SmallLength - 1)
//                {
//                    this->_ptr = NULL;

//                    memcpy(this->_small, c, length);
//                    this->_small[length] = 0x0;
//                }
//                else
//                {
//                    this->_ptr = static_cast<QString &>(CSM_MALLOC(sizeof(csmChar) * (length + 1)));

//                    memcpy(this->_ptr, c, length);
//                    this->_ptr[length] = 0x0;
//                }
//            }

//            csmInt32 QString::CalcHashcode(const QString &c, csmInt32 length)
//            {
//                csmInt32 hash = 0;
//                for (csmInt32 i = length; i >= 0; --i)
//                {
//                    hash = hash * 31 + c[i];
//                }
//                if ((hash == -1) || (c == GetEmptyString()))
//                {
//                    hash = -2; //-1だけ特別な意味をもたせる
//                }
//                return hash;
//            }

//            const QString &QString::GetString() const
//            {
//                if (this->_length < SmallLength - 1)
//                {
//                    return &_small[0];
//                }
//                else
//                {
//                    return _ptr;
//                }
//            }

//            csmInt32 QString::GetHashcode()
//            {
//                if (_hashcode == -1)
//                    _hashcode = CalcHashcode(WritePointer(), this->_length);
//                return _hashcode;
//            }

//            csmBool QString::IsEmpty() const
//            {
//#ifdef CSM_DEBUG

//                csmBool isEmpty = (_ptr == NULL && _small[0] == '\0');

//                if (isEmpty)
//                {
//                    CSM_ASSERT(_length == 0);
//                }

//                return isEmpty;

//#else

//                // return (_ptr == GetEmptyString());

//                return (_ptr == NULL && _small[0] == '\0');

//#endif
//            }

//            void QString::SetEmpty()
//            {
//                //_ptr = GetEmptyString();
//                _ptr = NULL;
//                _small[0] = '\0';
//                _length = 0;
//                _hashcode = -1;
//                _hashcode = CalcHashcode(WritePointer(), this->_length);
//            }

//            QString &QString::WritePointer()
//            {
//                if (this->_length < SmallLength - 1)
//                {
//                    return _small;
//                }
//                else
//                {
//                    return _ptr;
//                }
//            }

//        } // namespace Framework
//    }     // namespace Cubism
//} // namespace Live2D

////------------------------- LIVE2D NAMESPACE ------------
