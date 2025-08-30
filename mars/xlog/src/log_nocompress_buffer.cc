// Tencent is pleased to support the open source community by making Mars available.
// Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.

// Licensed under the MIT License (the "License"); you may not use this file except in
// compliance with the License. You may obtain a copy of the License at
// http://opensource.org/licenses/MIT

// Unless required by applicable law or agreed to in writing, software distributed under the License is
// distributed on an "AS IS" basis, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
// either express or implied. See the License for the specific language governing permissions and
// limitations under the License.

/*
 * log_nocompress_buffer.cc
 *
 *  Created on: 2024-12-19
 *      Author: AI Assistant
 */

#include "log_nocompress_buffer.h"

#include "crypt/log_crypt.h"
#include "crypt/log_magic_num.h"
#include "mars/comm/autobuffer.h"
#include "mars/comm/ptrbuffer.h"

namespace mars {
namespace xlog {

LogNoCompressBuffer::LogNoCompressBuffer(void* _pbuffer, size_t _len, bool _is_compress, const char* _pubkey)
    : LogBaseBuffer(_pbuffer, _len, _is_compress, _pubkey) {
    __Reset();
}

LogNoCompressBuffer::~LogNoCompressBuffer() {
    // 不需要特殊的清理工作
}

size_t LogNoCompressBuffer::Compress(const void* src, size_t inLen, void* dst, size_t outLen) {
    // 不压缩模式：直接复制数据
    if (inLen > outLen) {
        return -1;  // 输出缓冲区太小
    }
    
    memcpy(dst, src, inLen);
    return inLen;
}

void LogNoCompressBuffer::Flush(AutoBuffer& _buff) {
    // 不压缩模式：直接写入数据，不需要压缩
    LogBaseBuffer::Flush(_buff);
}

bool LogNoCompressBuffer::__Reset() {
    if (!LogBaseBuffer::__Reset()) {
        return false;
    }
    
    // 不压缩模式不需要初始化压缩器
    return true;
}

char LogNoCompressBuffer::__GetMagicSyncStart() {
    return is_crypt_ ? LogMagicNum::kMagicSyncNoCompressStart : LogMagicNum::kMagicSyncNoCryptNoCompressStart;
}

char LogNoCompressBuffer::__GetMagicAsyncStart() {
    return is_crypt_ ? LogMagicNum::kMagicAsyncNoCompressStart : LogMagicNum::kMagicAsyncNoCryptNoCompressStart;
}

}  // namespace xlog
}  // namespace mars
