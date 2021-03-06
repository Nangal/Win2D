// Copyright (c) Microsoft Corporation. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License"); you may
// not use these files except in compliance with the License. You may obtain
// a copy of the License at http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
// License for the specific language governing permissions and limitations
// under the License.

#pragma once

#include <ppl.h>
#include <ppltasks.h>

using namespace concurrency;
using namespace Windows::Foundation;

namespace Microsoft
{
    namespace VisualStudio
    {
        namespace CppUnitTestFramework
        {
            static inline std::wstring PointerToString(const wchar_t* name, void* value)
            {
                wchar_t buf[64];
                ThrowIfFailed(StringCchPrintf(
                    buf,
                    _countof(buf),
                    L"%s(%x)",
                    name,
                    value));
                return std::wstring(buf);
            }

#define TO_STRING(T)                                            \
            template<>                                          \
            static inline std::wstring ToString<T>(T* value)    \
            {                                                   \
                return PointerToString(L#T, value);             \
            }

            TO_STRING(ID2D1Device1);
            TO_STRING(ID2D1DeviceContext1);
            TO_STRING(ID2D1SolidColorBrush);
            TO_STRING(ID3D11Device);
            TO_STRING(ID3D11Texture2D);
            TO_STRING(IDXGIDevice);
            TO_STRING(IDXGISurface);
            TO_STRING(ID2D1StrokeStyle1);
            TO_STRING(IDWriteFactory2);

#undef TO_STRING

            template<>
            static inline std::wstring ToString<Windows::UI::Color>(Windows::UI::Color* value)
            {
                return value->ToString()->Data();
            }

            template<>
            static inline std::wstring ToString<Windows::UI::Color>(Windows::UI::Color const& value)
            {
                return L"Color";
            }

            template<>
            static inline std::wstring ToString<Microsoft::Graphics::Canvas::Numerics::Matrix3x2>(Microsoft::Graphics::Canvas::Numerics::Matrix3x2 const& value)
            {
                wchar_t buf[256];
                ThrowIfFailed(StringCchPrintf(
                    buf,
                    _countof(buf),
                    L"Numerics.Matrix{M11=%f,M12=%f,M21=%f,M22=%f,M31=%f,M32=%f}",
                    value.M11, value.M12,
                    value.M21, value.M22,
                    value.M31, value.M32));

                return buf;
            }

#define CX_VALUE_TO_STRING(T)                                       \
            template<>                                              \
            static inline std::wstring ToString<T>(T const& value)  \
            {                                                       \
                return value.ToString()->Data();                    \
            }
            
            CX_VALUE_TO_STRING(Microsoft::Graphics::Canvas::CanvasHardwareAcceleration);
            CX_VALUE_TO_STRING(Microsoft::Graphics::Canvas::CanvasCapStyle);
            CX_VALUE_TO_STRING(Microsoft::Graphics::Canvas::CanvasLineJoin);
            CX_VALUE_TO_STRING(Microsoft::Graphics::Canvas::CanvasDashStyle);
            CX_VALUE_TO_STRING(Microsoft::Graphics::Canvas::CanvasStrokeTransformBehavior);
            CX_VALUE_TO_STRING(Microsoft::Graphics::Canvas::CanvasAntialiasing);
            CX_VALUE_TO_STRING(Microsoft::Graphics::Canvas::CanvasBlend);
            CX_VALUE_TO_STRING(Microsoft::Graphics::Canvas::CanvasTextAntialiasing);
            CX_VALUE_TO_STRING(Microsoft::Graphics::Canvas::CanvasUnits);

#undef CX_VALUE_TO_STRING

            template<>
            static inline std::wstring ToString<D2D1_ANTIALIAS_MODE>(D2D1_ANTIALIAS_MODE const& value)
            {
                switch (value)
                {
                    case D2D1_ANTIALIAS_MODE_PER_PRIMITIVE: return L"D2D1_ANTIALIAS_MODE_PER_PRIMITIVE";
                    case D2D1_ANTIALIAS_MODE_ALIASED: return L"D2D1_ANTIALIAS_MODE_ALIASED";
                    default: assert(false); return L"<unknown D2D1_ANTIALIAS_MODE>";
                }
            }

            template<>
            static inline std::wstring ToString<D2D1_PRIMITIVE_BLEND>(D2D1_PRIMITIVE_BLEND const& value)
            {
                switch (value)
                {
                    case D2D1_PRIMITIVE_BLEND_SOURCE_OVER: return L"D2D1_PRIMITIVE_BLEND_SOURCE_OVER";
                    case D2D1_PRIMITIVE_BLEND_COPY: return L"D2D1_PRIMITIVE_BLEND_COPY";
                    case D2D1_PRIMITIVE_BLEND_MIN: return L"D2D1_PRIMITIVE_BLEND_MIN";
                    case D2D1_PRIMITIVE_BLEND_ADD: return L"D2D1_PRIMITIVE_BLEND_ADD";
                    default: assert(false); return L"<unknown D2D1_PRIMITIVE_BLEND>";
                }
            }

            template<>
            static inline std::wstring ToString<D2D1_TEXT_ANTIALIAS_MODE>(D2D1_TEXT_ANTIALIAS_MODE const& value)
            {
                switch (value)
                {
                    case D2D1_TEXT_ANTIALIAS_MODE_DEFAULT: return L"D2D1_TEXT_ANTIALIAS_MODE_DEFAULT";
                    case D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE: return L"D2D1_TEXT_ANTIALIAS_MODE_CLEARTYPE";
                    case D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE: return L"D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE";
                    case D2D1_TEXT_ANTIALIAS_MODE_ALIASED: return L"D2D1_TEXT_ANTIALIAS_MODE_ALIASED";
                    default: assert(false); return L"<unknown D2D1_TEXT_ANTIALIAS_MODE>";
                }
            }

            template<>
            static inline std::wstring ToString<D2D1_UNIT_MODE>(D2D1_UNIT_MODE const& value)
            {
                switch (value)
                {
                    case D2D1_UNIT_MODE_DIPS: return L"D2D1_UNIT_MODE_DIPS";
                    case D2D1_UNIT_MODE_PIXELS: return L"D2D1_UNIT_MODE_PIXELS";
                    default: assert(false); return L"<unknown D2D1_UNIT_MODE>";
                }
            }

            inline bool operator==(Windows::UI::Color const& a, Windows::UI::Color const& b)
            {
                return a.A == b.A &&
                    a.R == b.R &&
                    a.G == b.G &&
                    a.B == b.B;
            }

            inline bool operator==(Microsoft::Graphics::Canvas::Numerics::Matrix3x2 const& a, Microsoft::Graphics::Canvas::Numerics::Matrix3x2 const& b)
            {
                return
                    a.M11 == b.M11 && a.M12 == b.M12 &&
                    a.M21 == b.M21 && a.M22 == b.M22 &&
                    a.M31 == b.M31 && a.M32 == b.M32;
            }

            inline bool operator==(Windows::UI::Text::FontWeight const& a, Windows::UI::Text::FontWeight const& b)
            {
                return a.Weight == b.Weight;
            }
        }
    }
}


inline ComPtr<ID3D11Device> CreateD3DDevice()
{
    ComPtr<ID3D11Device> d3dDevice;
    D3D_FEATURE_LEVEL featureLevel;
    ComPtr<ID3D11DeviceContext> immediateContext;

    ThrowIfFailed(D3D11CreateDevice(
        nullptr,            // adapter
        D3D_DRIVER_TYPE_WARP,
        nullptr,            // software
        D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT,
        nullptr,            // feature levels
        0,                  // feature levels count
        D3D11_SDK_VERSION,
        &d3dDevice,
        &featureLevel,
        &immediateContext));

    return d3dDevice;
}

template<typename ACTION_ON_CLOSED_OBJECT>
void ExpectObjectClosed(ACTION_ON_CLOSED_OBJECT&& fn)
{
    Assert::ExpectException<Platform::ObjectDisposedException^>(
        [&]
        {
            fn();
        });
}

//
// Executes the given code on the UI thread.  Any C++ exception that is thrown
// by this code is captured and re-thrown from the CppUnitTestFramework.Executor
// thread so that it gets picked up by the test framework.
//
// NOTE: unfortunately, it seems that Assert::FailImpl uses SEH rather than C++
// exceptions, so these don't get caught and transported.  This means that if
// 'code' contains unit test Asserts that fail then the only way to find out
// more is to attach a debugger.
//
template<typename CODE>
void RunOnUIThread(CODE&& code)
{
    using namespace Microsoft::WRL::Wrappers;
    using namespace Windows::ApplicationModel::Core;
    using namespace Windows::UI::Core;

    // 'code' will be executed on the UI thread.  This event is used to notify
    // this thread when the UI thread has completed executing 'code'.
    Event event(CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS));
    if (!event.IsValid())
        throw std::bad_alloc();

    // If 'code' throws then we capture the exception here and rethrow.
    std::exception_ptr exceptionDuringTest = nullptr;

    // Dispatch 'code' to run on the UI thread
    CoreWindow^ wnd = CoreApplication::MainView->CoreWindow;
    CoreDispatcher^ dispatcher = wnd->Dispatcher;
    dispatcher->RunAsync(CoreDispatcherPriority::Normal,
        ref new DispatchedHandler(
            [&event, code, &exceptionDuringTest]
            {
                try
                {
                    code();
                }
                catch (...)
                {
                    exceptionDuringTest = std::current_exception();
                }

                SetEvent(event.Get());
            }));

    // Wait for the UI thread to run 'code', but don't wait forever.
    auto timeout = 1000 * 5;
    auto waitResult = WaitForSingleObjectEx(event.Get(), timeout, FALSE);
    Assert::AreEqual(WAIT_OBJECT_0, waitResult);

    // Rethrow any exception we caught
    if (exceptionDuringTest)
        std::rethrow_exception(exceptionDuringTest);
}

template<typename T>
T WaitExecution(IAsyncOperation<T>^ asyncOperation)
{
    using namespace Microsoft::WRL::Wrappers;

    Event emptyEvent(CreateEventEx(NULL, NULL, CREATE_EVENT_MANUAL_RESET, EVENT_ALL_ACCESS));
    if (!emptyEvent.IsValid())
        throw std::bad_alloc();

    task_options options;
    options.set_continuation_context(task_continuation_context::use_arbitrary());

    task<T> asyncTask(asyncOperation);

    asyncTask.then([&](task<T>)
    {
        SetEvent(emptyEvent.Get());
    }, options);

    // waiting before event executed
    auto timeout = 1000 * 5;
    auto waitResult = WaitForSingleObjectEx(emptyEvent.Get(), timeout, true);
    Assert::AreEqual(WAIT_OBJECT_0, waitResult);

    return asyncTask.get();
};

ComPtr<ID2D1DeviceContext1> CreateTestD2DDeviceContext();
