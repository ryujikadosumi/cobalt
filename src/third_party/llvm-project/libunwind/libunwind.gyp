# Copyright 2019 The Cobalt Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

{
  'targets': [
    {
      'target_name': 'unwind_evergreen',
      'type': 'static_library',
      'include_dirs': [
        'include',
        '<(DEPTH)/third_party/llvm-project/libunwind/include',
      ],
      'dependencies': [
        '<(DEPTH)/starboard/common/common.gyp:common',
        '<(DEPTH)/third_party/musl/musl.gyp:c',
      ],
      'cflags': [
        '-nostdinc',
        '-Wno-unused-command-line-argument',
      ],
      'cflags_cc': [
        '-std=c++11',
        '-nostdinc++',
        '-fPIC',
        '-Werror=return-type',
        '-fvisibility-inlines-hidden',
        '-fms-compatibility-version=19.00',
        '-funwind-tables',
        '-W',
        '-Wall',
        '-Wextra',
        '-Wwrite-strings',
        '-Wshorten-64-to-32',
        '-Wno-error',
        '-Wno-unused-parameter',
      ],
      'defines': [
        # Ensure that __external_threading is used for threading support.
        '_LIBCPP_HAS_THREAD_API_EXTERNAL',
        # Build libunwind with concurrency built upon Starboard mutexes and
        # condition variables.
        '_LIBUNWIND_HAS_STARBOARD_THREADS',
        'LIBUNWIND_PRINT_APIS',
        'LIBUNWIND_PRINT_DWARF',
        'LIBUNWIND_PRINT_UNWINDING',
        'LLVM_PATH="<(DEPTH)/third_party/llvm-project/llvm/"',
      ],
      'sources': [
        'src/AddressSpace.hpp',
        'src/assembly.h',
        'src/CMakeLists.txt',
        'src/CompactUnwinder.hpp',
        'src/config.h',
        'src/dwarf2.h',
        'src/DwarfInstructions.hpp',
        'src/DwarfParser.hpp',
        'src/EHHeaderParser.hpp',
        'src/libunwind.cpp',
        'src/libunwind_ext.h',
        'src/Registers.hpp',
        'src/RWMutex.hpp',
        'src/UnwindCursor.hpp',
        'src/Unwind-EHABI.cpp',
        'src/Unwind-EHABI.h',
        'src/UnwindLevel1.c',
        'src/UnwindLevel1-gcc-ext.c',
        'src/UnwindRegistersRestore.S',
        'src/UnwindRegistersSave.S',
        'src/Unwind-sjlj.c',
      ],
      'all_dependent_settings': {
        'include_dirs': [
          '<(DEPTH)/third_party/llvm-project/libunwind/include',
        ],
        'defines': [
          # Ensure that __external_threading is used for threading support.
          '_LIBCPP_HAS_THREAD_API_EXTERNAL',
          'LLVM_PATH="<(DEPTH)/third_party/llvm-project/llvm/"',
        ],
      },
      'conditions': [
        ['target_os == "tvos"', {
          'sources': [
            'src/Unwind_AppleExtras.cpp',
          ],
        }],
      ],
    },
    {
      'target_name': 'unwind_starboard',
      'type': 'static_library',
      'include_dirs': [
        'include',
        '<(DEPTH)/third_party/llvm-project/libunwind/include',
      ],
      'dependencies': [
        '<(DEPTH)/starboard/common/common.gyp:common',
        '<(DEPTH)/starboard/elf_loader/evergreen_info.gyp:evergreen_info',
      ],
      'cflags': [
        '-Wno-unused-command-line-argument',
      ],
      'cflags_cc': [
        '-std=c++11',
        '-fPIC',
        '-Werror=return-type',
        '-fvisibility-inlines-hidden',
        '-funwind-tables',
        '-W',
        '-Wall',
        '-Wextra',
        '-Wwrite-strings',
        '-Wno-error',
        '-Wno-unused-parameter',
      ],
      'defines': [
        'STARBOARD_IMPLEMENTATION',
        # Ensure that __external_threading is used for threading support.
        '_LIBCPP_HAS_THREAD_API_EXTERNAL',
        # Build libunwind with concurrency built upon Starboard mutexes and
        # condition variables.
        '_LIBUNWIND_HAS_STARBOARD_THREADS',
        'LLVM_PATH="<(DEPTH)/third_party/llvm-project/llvm/"',
      ],
      'sources': [
        'src/AddressSpace.hpp',
        'src/assembly.h',
        'src/CMakeLists.txt',
        'src/CompactUnwinder.hpp',
        'src/config.h',
        'src/dwarf2.h',
        'src/DwarfInstructions.hpp',
        'src/DwarfParser.hpp',
        'src/EHHeaderParser.hpp',
        'src/libunwind.cpp',
        'src/libunwind_ext.h',
        'src/Registers.hpp',
        'src/RWMutex.hpp',
        'src/UnwindCursor.hpp',
        'src/Unwind-EHABI.cpp',
        'src/Unwind-EHABI.h',
        'src/UnwindLevel1.c',
        'src/UnwindLevel1-gcc-ext.c',
        'src/UnwindRegistersRestore.S',
        'src/UnwindRegistersSave.S',
        'src/Unwind-sjlj.c',
      ],
      'all_dependent_settings': {
        'include_dirs': [
          '<(DEPTH)/third_party/llvm-project/libunwind/include',
        ],
        'defines': [
          # Ensure that __external_threading is used for threading support.
          '_LIBCPP_HAS_THREAD_API_EXTERNAL',
          'LLVM_PATH="<(DEPTH)/third_party/llvm-project/llvm/"',
        ],
      },
      'conditions': [
        ['target_os == "tvos"', {
          'sources': [
            'src/Unwind_AppleExtras.cpp',
          ],
        }],
      ],
    }
  ]
}
