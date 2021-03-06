/*
 * Copyright (C) 2012, 2014, 2019 Igalia S.L.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#pragma once

#include <WebCore/CompositionUnderline.h>
#include <WebCore/IntPoint.h>
#include <wtf/Noncopyable.h>
#include <wtf/Vector.h>
#include <wtf/glib/GRefPtr.h>

typedef struct _WebKitInputMethodContext WebKitInputMethodContext;

#if PLATFORM(GTK)
typedef struct _GdkEventKey GdkEventKey;
#elif PLATFORM(WPE)
struct wpe_input_keyboard_event;
#endif

namespace WebCore {
class IntRect;
}

namespace WebKit {

class InputMethodFilter {
    WTF_MAKE_NONCOPYABLE(InputMethodFilter);
public:

    InputMethodFilter() = default;
    ~InputMethodFilter();

    void setContext(WebKitInputMethodContext*);
    WebKitInputMethodContext* context() const { return m_context.get(); }

    void setEnabled(bool);

#if PLATFORM(GTK)
    using PlatformEventKey = GdkEventKey;
#elif PLATFORM(WPE)
    using PlatformEventKey = struct wpe_input_keyboard_event;
#endif
    struct FilterResult {
        bool handled { false };
        String keyText;
    };
    FilterResult filterKeyEvent(PlatformEventKey*);

    void notifyFocusedIn();
    void notifyFocusedOut();
    void notifyMouseButtonPress();
    void notifyCursorRect(const WebCore::IntRect&);

    void cancelComposition();

private:
    static void preeditStartedCallback(InputMethodFilter*);
    static void preeditChangedCallback(InputMethodFilter*);
    static void preeditFinishedCallback(InputMethodFilter*);
    static void committedCallback(InputMethodFilter*, const char*);

    void preeditStarted();
    void preeditChanged();
    void preeditFinished();
    void committed(const char*);

    bool isViewFocused() const;

    WebCore::IntRect platformTransformCursorRectToViewCoordinates(const WebCore::IntRect&);
    bool platformEventKeyIsKeyPress(PlatformEventKey*) const;

    bool m_enabled { false };
    GRefPtr<WebKitInputMethodContext> m_context;

    struct {
        String text;
        Vector<WebCore::CompositionUnderline> underlines;
        unsigned cursorOffset;
    } m_preedit;

    struct {
        bool isActive { false };
        bool preeditChanged { false };
    } m_filteringContext;

    String m_compositionResult;
    WebCore::IntPoint m_cursorLocation;
};

} // namespace WebKit
