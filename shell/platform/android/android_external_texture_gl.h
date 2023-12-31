// Copyright 2013 The Flutter Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_SHELL_PLATFORM_ANDROID_EXTERNAL_TEXTURE_GL_H_
#define FLUTTER_SHELL_PLATFORM_ANDROID_EXTERNAL_TEXTURE_GL_H_

#include <GLES/gl.h>

#include "flutter/common/graphics/texture.h"
#include "flutter/shell/platform/android/platform_view_android_jni_impl.h"

namespace flutter {

class AndroidExternalTextureGL : public flutter::Texture {
 public:
  AndroidExternalTextureGL(
      int64_t id,
      const fml::jni::ScopedJavaGlobalRef<jobject>& surface_texture,
      std::shared_ptr<PlatformViewAndroidJNI> jni_facade);

  ~AndroidExternalTextureGL() override;

  void Paint(PaintContext& context,
             const SkRect& bounds,
             bool freeze,
             const DlImageSampling sampling) override;

  void OnGrContextCreated() override;

  void OnGrContextDestroyed() override;

  void MarkNewFrameAvailable() override;

  void OnTextureUnregistered() override;

 private:
  void Attach(jint textureName);

  void Update();

  void Detach();

  void UpdateTransform();

  enum class AttachmentState { kUninitialized, kAttached, kDetached };

  std::shared_ptr<PlatformViewAndroidJNI> jni_facade_;

  fml::jni::ScopedJavaGlobalRef<jobject> surface_texture_;

  AttachmentState state_ = AttachmentState::kUninitialized;

  bool new_frame_ready_ = false;

  GLuint texture_name_ = 0;

  SkMatrix transform;

  FML_DISALLOW_COPY_AND_ASSIGN(AndroidExternalTextureGL);
};

}  // namespace flutter

#endif  // FLUTTER_SHELL_PLATFORM_ANDROID_EXTERNAL_TEXTURE_GL_H_
