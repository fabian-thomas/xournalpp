/*
 * Xournal++
 *
 * Handle the Page Spin Widget
 *
 * @author Xournal++ Team
 * https://github.com/xournalpp/xournalpp
 *
 * @license GNU GPLv2 or later
 */

#pragma once

#include <cassert>
#include <list>
#include <string>
#include <vector>

#include <gtk/gtk.h>

#include "XournalType.h"

class SpinPageListener;

class SpinPageAdapter {
public:
    SpinPageAdapter();
    virtual ~SpinPageAdapter();

public:
    bool hasWidget();
    void setWidget(GtkWidget* widget);
    void removeWidget();

    int getPage() const;
    void setPage(size_t page);
    void setMinMaxPage(size_t min, size_t max);

    void addListener(SpinPageListener* listener);
    void removeListener(SpinPageListener* listener);

private:
    static bool pageNrSpinChangedTimerCallback(SpinPageAdapter* adapter);
    static void pageNrSpinChangedCallback(GtkSpinButton* spinbutton, SpinPageAdapter* adapter);

    void firePageChanged();

private:
    GtkWidget* widget;
    gulong pageNrSpinChangedHandlerId;
    size_t page;

    int lastTimeoutId;
    std::list<SpinPageListener*> listener;

    size_t min, max;
};

class SpinPageListener {
public:
    virtual void pageChanged(size_t page) = 0;
    virtual ~SpinPageListener();
};
