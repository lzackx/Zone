/*
 * Copyright (C) 2018 Apple Inc. All rights reserved.
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

#if HAVE(PENCILKIT)

#include "APIAttachment.h"
#include "MessageReceiver.h"
#include "WebPageProxy.h"
#include <WebCore/GraphicsLayer.h>
#include <wtf/Noncopyable.h>
#include <wtf/WeakObjCPtr.h>
#include <wtf/WeakPtr.h>
#include <wtf/text/WTFString.h>

OBJC_CLASS WKDrawingView;

namespace WebKit {

struct EditableImage {
    WTF_MAKE_STRUCT_FAST_ALLOCATED;
    RetainPtr<WKDrawingView> drawingView;
    String attachmentID;
};

class EditableImageController : private IPC::MessageReceiver {
    WTF_MAKE_FAST_ALLOCATED;
    WTF_MAKE_NONCOPYABLE(EditableImageController);
public:
    explicit EditableImageController(WebPageProxy&);
    ~EditableImageController();

    // IPC::MessageReceiver.
    void didReceiveMessage(IPC::Connection&, IPC::Decoder&) override;

    EditableImage* editableImage(WebCore::GraphicsLayer::EmbeddedViewID);
    EditableImage& ensureEditableImage(WebCore::GraphicsLayer::EmbeddedViewID);

    void invalidateAttachmentForEditableImage(WebCore::GraphicsLayer::EmbeddedViewID);

    WebPageProxy::ShouldUpdateAttachmentAttributes willUpdateAttachmentAttributes(const API::Attachment&);

private:
    void didCreateEditableImage(WebCore::GraphicsLayer::EmbeddedViewID);
    void didDestroyEditableImage(WebCore::GraphicsLayer::EmbeddedViewID);

    void associateWithAttachment(WebCore::GraphicsLayer::EmbeddedViewID, const String& attachmentID);

    void loadStrokesFromAttachment(EditableImage&, const API::Attachment&);

    WeakPtr<WebPageProxy> m_webPageProxy;

    HashMap<WebCore::GraphicsLayer::EmbeddedViewID, std::unique_ptr<EditableImage>> m_editableImages;
};

} // namespace WebKit

#endif // HAVE(PENCILKIT)
