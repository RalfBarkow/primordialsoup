// Copyright (c) 2019, the Newspeak project authors. Please see the AUTHORS file
// for details. All rights reserved. Use of this source code is governed by a
// BSD-style license that can be found in the LICENSE file.

#include "vm/globals.h"
#if defined(OS_EMSCRIPTEN)

#include "vm/os.h"

#include <emscripten.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "vm/assert.h"

namespace psoup {

void OS::Startup() {}
void OS::Shutdown() {}


int64_t OS::CurrentMonotonicNanos() {
  double now = emscripten_get_now();
  return now * kNanosecondsPerMillisecond;
}


const char* OS::Name() { return "emscripten"; }


intptr_t OS::NumberOfAvailableProcessors() {
  return 1;
}


void OS::DebugBreak() {
  emscripten_debugger();
}


static void VFPrint(FILE* stream, const char* format, va_list args) {
  vfprintf(stream, format, args);
  fflush(stream);
}


void OS::Print(const char* format, ...) {
  va_list args;
  va_start(args, format);
  VFPrint(stdout, format, args);
  va_end(args);
}


void OS::PrintErr(const char* format, ...) {
  va_list args;
  va_start(args, format);
  VFPrint(stderr, format, args);
  va_end(args);
}


char* OS::PrintStr(const char* format, ...) {
  va_list args;
  va_start(args, format);
  va_list measure_args;
  va_copy(measure_args, args);
  intptr_t len = vsnprintf(NULL, 0, format, measure_args);
  va_end(measure_args);

  char* buffer = reinterpret_cast<char*>(malloc(len + 1));

  va_list print_args;
  va_copy(print_args, args);
  int r = vsnprintf(buffer, len + 1, format, print_args);
  ASSERT(r >= 0);
  va_end(print_args);
  va_end(args);
  return buffer;
}


void OS::Abort() {
  abort();
}


void OS::Exit(int code) {
  exit(code);
}

}  // namespace psoup

#endif  // defined(OS_EMSCRIPTEN)
