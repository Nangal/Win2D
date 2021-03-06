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

#include "pch.h"

using namespace Microsoft::Graphics::Canvas::DirectX::Direct3D11;

TEST_CLASS(Direct3D11EnumTests)
{
public:
    TEST_METHOD(Direct3DUsageMatchesD3D11_USAGE)
    {
#define CHECK(WINRT, D3D11) Assert::AreEqual(static_cast<int>(Direct3DUsage::WINRT), static_cast<int>(D3D11))

        CHECK(Default   , D3D11_USAGE_DEFAULT);
        CHECK(Immutable , D3D11_USAGE_IMMUTABLE);
        CHECK(Dynamic   , D3D11_USAGE_DYNAMIC);
        CHECK(Staging   , D3D11_USAGE_STAGING);

#undef CHECK
    }

    TEST_METHOD(Direct3DBindingsMatchesD3D11_BIND_FLAG)
    {
#define CHECK(WINRT, D3D11) Assert::AreEqual(static_cast<uint32>(Direct3DBindings::WINRT), static_cast<uint32>(D3D11))

        CHECK(VertexBuffer    , D3D11_BIND_VERTEX_BUFFER);
        CHECK(IndexBuffer     , D3D11_BIND_INDEX_BUFFER);
        CHECK(ConstantBuffer  , D3D11_BIND_CONSTANT_BUFFER);
        CHECK(ShaderResource  , D3D11_BIND_SHADER_RESOURCE);
        CHECK(StreamOutput    , D3D11_BIND_STREAM_OUTPUT);
        CHECK(RenderTarget    , D3D11_BIND_RENDER_TARGET);
        CHECK(DepthStencil    , D3D11_BIND_DEPTH_STENCIL);
        CHECK(UnorderedAccess , D3D11_BIND_UNORDERED_ACCESS);
        CHECK(Decoder         , D3D11_BIND_DECODER);
        CHECK(VideoEncoder    , D3D11_BIND_VIDEO_ENCODER);

#undef CHECK
    }
};
