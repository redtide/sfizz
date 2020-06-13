// SPDX-License-Identifier: BSD-2-Clause

// This code is part of the sfizz library and is licensed under a BSD 2-clause
// license. You should have receive a LICENSE.md file along with the code.
// If not, contact the sfizz maintainers at https://github.com/sfztools/sfizz

#include "Editor.h"
#include "EditorController.h"
#include "Res.h"
#include "UI.h"
#include <elements.hpp>
#include <elements/support/font.hpp>
#include <elements/support/resource_paths.hpp>
#include <algorithm>
namespace el = cycfi::elements;

namespace cycfi {
namespace elements {

void* get_native_window_id(base_view& w);
void show_window(base_view& w);
void hide_window(base_view& w);
void process_events(base_view& w);

} // namespace elements
} // namespace cycfi

constexpr int Editor::fixedWidth;
constexpr int Editor::fixedHeight;

struct Editor::Impl : EditorController::Receiver {
    std::unique_ptr<el::view> view_;
    EditorController* ctrl_ = nullptr;

    std::unique_ptr<UI> ui_;

    static void initializeResourcePaths();

    // EditorController::Receiver
    void uiReceiveNumber(EditId id, float v) override;
    void uiReceiveString(EditId id, absl::string_view v) override;
};

///

Editor::Editor(EditorController& ctrl)
    : impl_(new Impl)
{
    impl_->ctrl_ = &ctrl;
    ctrl.decorate(impl_.get());
}

Editor::~Editor()
{
    impl_->ctrl_->decorate(nullptr);
}

bool Editor::open(void* parentWindowId)
{
    // make the resource path known to Elements
    impl_->initializeResourcePaths();

    el::view* view = new el::view(parentWindowId);
    impl_->view_.reset(view);

    if (!view->host()) {
        impl_->view_.reset();
        return false;
    }

    view->size(el::extent(fixedWidth, fixedHeight));

    ///
    UI* ui = new UI(*view);
    impl_->ui_.reset(ui);

    ///
    return true;
}

void Editor::close()
{
    impl_->view_.reset();
}

bool Editor::isOpen() const
{
    return impl_->view_ != nullptr;
}

void* Editor::getNativeWindowId()
{
    if (!impl_->view_)
        return nullptr;

    return el::get_native_window_id(*impl_->view_);
}

void Editor::show()
{
    if (impl_->view_)
        el::show_window(*impl_->view_);
}

void Editor::hide()
{
    if (impl_->view_)
        el::hide_window(*impl_->view_);
}

void Editor::processEvents()
{
    if (impl_->view_)
        el::process_events(*impl_->view_);
}

void Editor::Impl::initializeResourcePaths()
{
    const cycfi::fs::path resourcePath = Res::getRootPath();
    if (resourcePath.empty())
        return;

    auto addIfNotExisting = [](
        std::vector<cycfi::fs::path>& list, const cycfi::fs::path& value)
    {
        auto it = std::find(list.begin(), list.end(), value);
        if (it == list.end())
            list.push_back(value);
    };

    auto& resPaths = el::resource_paths;
    auto& fontPaths = el::font_paths();

    addIfNotExisting(resPaths, resourcePath);
    addIfNotExisting(fontPaths, resourcePath);
}

///
void Editor::Impl::uiReceiveNumber(EditId id, float v)
{
    // TODO
    switch (id) {
        
    default:
        break;
    }
}

void Editor::Impl::uiReceiveString(EditId id, absl::string_view v)
{
    // TODO
    switch (id) {
        
    default:
        break;
    }
}
