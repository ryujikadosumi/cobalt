// Copyright 2018 The Cobalt Authors. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "starboard/shared/starboard/player/filter/media_time_provider_impl.h"

#include "starboard/shared/starboard/player/job_queue.h"
#include "starboard/thread.h"
#include "starboard/time.h"
#include "testing/gmock/include/gmock/gmock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace starboard {
namespace shared {
namespace starboard {
namespace player {
namespace filter {
namespace testing {
namespace {

typedef MediaTimeProviderImpl::MonotonicSystemTimeProvider
    MonotonicSystemTimeProvider;

using ::testing::AssertionResult;
using ::testing::Return;
using ::testing::StrictMock;

::testing::AssertionResult AlmostEqual(SbTime left, SbTime right) {
  // Use 1 millisecond as epsilon.
  const SbTime kEpsilon = kSbTimeSecond / 1000;
  SbTime diff = left > right ? left - right : right - left;

  if (diff <= kEpsilon)
    return ::testing::AssertionSuccess();
  else
    return ::testing::AssertionFailure()
           << left << " is not almost equal to " << right
           << " with a difference of " << diff;
}

class MockMonotonicSystemTimeProvider : public MonotonicSystemTimeProvider {
 public:
  MockMonotonicSystemTimeProvider() : current_time_(kDefaultSystemTime) {
    ResetExpectation();
  }
  void SetCurrentTime(SbTimeMonotonic time) {
    current_time_ = time;
    ResetExpectation();
  }
  void AdvanceTime(SbTimeMonotonic time) {
    current_time_ += time;
    ResetExpectation();
  }
  MOCK_CONST_METHOD0(GetMonotonicNow, SbTimeMonotonic());

 private:
  // return a non-zero time by default.
  const SbTimeMonotonic kDefaultSystemTime = kSbTimeSecond;

  void ResetExpectation() {
    EXPECT_CALL(*this, GetMonotonicNow()).WillRepeatedly(Return(current_time_));
  }

  SbTimeMonotonic current_time_;
};

// TODO: Write tests to cover callbacks.
class MediaTimeProviderImplTest : public ::testing::Test {
 protected:
  MediaTimeProviderImplTest()
      : system_time_provider_(new StrictMock<MockMonotonicSystemTimeProvider>),
        // |system_time_provider_| still holds the raw pointer after the object
        // is passed to and owned by |media_time_provider_impl_|, so the tests
        // can adjust expectation on it.  This is safe in the context of the
        // tests.
        media_time_provider_impl_(make_scoped_ptr<MonotonicSystemTimeProvider>(
            system_time_provider_)) {
    media_time_provider_impl_.SetPlaybackRate(1.0);
  }

  JobQueue job_queue_;
  StrictMock<MockMonotonicSystemTimeProvider>* system_time_provider_;
  MediaTimeProviderImpl media_time_provider_impl_;
};

TEST_F(MediaTimeProviderImplTest, DefaultStates) {
  bool is_playing = true, is_eos_played = true, is_underflow = true;
  double playback_rate = -1.0;
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      0));
  EXPECT_FALSE(is_playing);
  EXPECT_FALSE(is_eos_played);
  EXPECT_FALSE(is_underflow);
  EXPECT_EQ(playback_rate, 1.0);
}

TEST_F(MediaTimeProviderImplTest, GetCurrentMediaTimeWhileNotPlaying) {
  system_time_provider_->AdvanceTime(kSbTimeSecond);

  bool is_playing = true, is_eos_played = true, is_underflow = true;
  double playback_rate = -1.0;
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      0));
  EXPECT_FALSE(is_playing);
  EXPECT_FALSE(is_eos_played);
  EXPECT_FALSE(is_underflow);
  EXPECT_EQ(playback_rate, 1.0);
}

TEST_F(MediaTimeProviderImplTest, GetCurrentMediaTimeWhilePlaying) {
  media_time_provider_impl_.Play();

  bool is_playing = false, is_eos_played = true, is_underflow = true;
  double playback_rate = -1.0;
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      0));
  EXPECT_TRUE(is_playing);
  EXPECT_FALSE(is_eos_played);
  EXPECT_FALSE(is_underflow);
  EXPECT_EQ(playback_rate, 1.0);

  system_time_provider_->AdvanceTime(kSbTimeSecond);

  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      kSbTimeSecond));
  EXPECT_TRUE(is_playing);
  EXPECT_FALSE(is_eos_played);
  EXPECT_FALSE(is_underflow);
  EXPECT_EQ(playback_rate, 1.0);
}

TEST_F(MediaTimeProviderImplTest, SetPlaybackRateWhilePlaying) {
  media_time_provider_impl_.Play();

  system_time_provider_->AdvanceTime(kSbTimeSecond);
  bool is_playing = true, is_eos_played = true, is_underflow = true;
  double playback_rate = -1.0;
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      kSbTimeSecond));
  EXPECT_EQ(playback_rate, 1.0);
  EXPECT_EQ(playback_rate, 1.0);

  media_time_provider_impl_.SetPlaybackRate(2.0);

  system_time_provider_->AdvanceTime(kSbTimeSecond);
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      kSbTimeSecond * 3));
  EXPECT_EQ(playback_rate, 2.0);

  media_time_provider_impl_.SetPlaybackRate(0.0);
  system_time_provider_->AdvanceTime(kSbTimeSecond);
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      kSbTimeSecond * 3));
  EXPECT_EQ(playback_rate, 0.0);
}

TEST_F(MediaTimeProviderImplTest, SeekWhileNotPlaying) {
  const SbTime kSeekToTime = 100 * kSbTimeSecond;

  media_time_provider_impl_.Seek(kSeekToTime);
  bool is_playing = true, is_eos_played = true, is_underflow = true;
  double playback_rate = -1.0;
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      kSeekToTime));
  EXPECT_FALSE(is_playing);
  EXPECT_FALSE(is_eos_played);
  EXPECT_FALSE(is_underflow);
  EXPECT_EQ(playback_rate, 1.0);

  system_time_provider_->AdvanceTime(kSbTimeSecond);

  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      kSeekToTime));
}

TEST_F(MediaTimeProviderImplTest, SeekForwardWhilePlaying) {
  const SbTime kSeekToTime = 100 * kSbTimeSecond;

  media_time_provider_impl_.Play();

  media_time_provider_impl_.Seek(kSeekToTime);
  bool is_playing = false, is_eos_played = true, is_underflow = true;
  double playback_rate = -1.0;
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      kSeekToTime));
  EXPECT_TRUE(is_playing);
  EXPECT_FALSE(is_eos_played);
  EXPECT_FALSE(is_underflow);
  EXPECT_EQ(playback_rate, 1.0);

  system_time_provider_->AdvanceTime(kSbTimeSecond);

  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      kSeekToTime + kSbTimeSecond));
  EXPECT_TRUE(is_playing);
  EXPECT_FALSE(is_eos_played);
  EXPECT_FALSE(is_underflow);
  EXPECT_EQ(playback_rate, 1.0);
}

TEST_F(MediaTimeProviderImplTest, SeekBackwardWhilePlaying) {
  media_time_provider_impl_.Play();

  system_time_provider_->AdvanceTime(kSbTimeSecond);

  bool is_playing = true, is_eos_played = true, is_underflow = true;
  double playback_rate = -1.0;
  // Query for media time and ignore the result.
  media_time_provider_impl_.GetCurrentMediaTime(&is_playing, &is_eos_played,
                                                &is_underflow, &playback_rate);

  const SbTime kSeekToTime = 0;
  media_time_provider_impl_.Seek(kSeekToTime);
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      kSeekToTime));
}

TEST_F(MediaTimeProviderImplTest, Pause) {
  media_time_provider_impl_.Play();

  system_time_provider_->AdvanceTime(kSbTimeSecond);

  bool is_playing = true, is_eos_played = true, is_underflow = true;
  double playback_rate = -1.0;
  // Query for media time and ignore the result.
  media_time_provider_impl_.GetCurrentMediaTime(&is_playing, &is_eos_played,
                                                &is_underflow, &playback_rate);

  media_time_provider_impl_.Pause();
  system_time_provider_->AdvanceTime(kSbTimeSecond);
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      kSbTimeSecond));

  media_time_provider_impl_.Seek(0);
  system_time_provider_->AdvanceTime(kSbTimeSecond);
  EXPECT_TRUE(AlmostEqual(
      media_time_provider_impl_.GetCurrentMediaTime(
          &is_playing, &is_eos_played, &is_underflow, &playback_rate),
      0));
}

}  // namespace
}  // namespace testing
}  // namespace filter
}  // namespace player
}  // namespace starboard
}  // namespace shared
}  // namespace starboard
