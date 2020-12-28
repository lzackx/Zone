/*
 * Copyright (C) 2019 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#if ENABLE(GPU_PROCESS)

#include "Connection.h"
#include <wtf/RefCounted.h>
#include <wtf/text/WTFString.h>

namespace IPC {
class DataReference;
}

namespace WebKit {

class GPUProcessConnection : public RefCounted<GPUProcessConnection>, IPC::Connection::Client {
public:
    static Ref<GPUProcessConnection> create(IPC::Connection::Identifier connectionIdentifier)
    {
        return adoptRef(*new GPUProcessConnection(connectionIdentifier));
    }
    ~GPUProcessConnection();
    
    IPC::Connection& connection() { return m_connection.get(); }

private:
    GPUProcessConnection(IPC::Connection::Identifier);

    // IPC::Connection::Client
    void didClose(IPC::Connection&) override;
    void didReceiveMessage(IPC::Connection&, IPC::Decoder&) final;
    void didReceiveInvalidMessage(IPC::Connection&, IPC::StringReference messageReceiverName, IPC::StringReference messageName) override;

    // The connection from the web process to the GPU process.
    Ref<IPC::Connection> m_connection;
};

} // namespace WebKit

#endif // ENABLE(GPU_PROCESS)
