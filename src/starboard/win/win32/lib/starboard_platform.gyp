# Copyright 2017 Google Inc. All Rights Reserved.
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
  'includes': [
    '../starboard_platform.gypi',
  ],
  'variables': {
    'starboard_platform_dependent_files': [
      '<@(base_win32_starboard_platform_dependent_files)',
      '<@(win32_media_player_files)',
      '<@(win32_shared_drm_files)',
      '<@(win32_shared_media_player_files)',
    ]
  },
}