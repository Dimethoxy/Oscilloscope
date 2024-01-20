#pragma once
//==============================================================================
#include "../src/utility/RingBuffer.h"
#include <JuceHeader.h>
#include <benchmark/benchmark.h>
#include <format>
#include <gtest/gtest.h>
//==============================================================================
namespace RingBufferTest {
//==============================================================================
// Unit Tests
TEST(RingBuffer, read_write_correctness)
{
  float values[2][5]{ { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f },
                      { 6.0f, 7.0f, 8.0f, 9.0f, 10.0f } };

  juce::AudioBuffer<float> buffer(2, 5);

  for (int channel = 0; channel < 2; ++channel) {
    for (int sample = 0; sample < 5; ++sample) {
      buffer.setSample(channel, sample, values[channel][sample]);
    }
  }

  RingBuffer<float> ringBuffer(2, 5);
  ringBuffer.write(buffer);

  juce::AudioBuffer<float> targetBuffer(2, 5);
  ringBuffer.read(targetBuffer);

  for (int channel = 0; channel < 2; ++channel) {
    for (int sample = 0; sample < 5; ++sample) {
      ASSERT_EQ(buffer.getSample(channel, sample),
                targetBuffer.getSample(channel, sample));
    }
  }
}
//==============================================================================
static void
BM_WriteOperation(benchmark::State& state)
{
  RingBuffer<float> ringBuffer(2, 5);
  juce::AudioBuffer<float> buffer(2, 5);

  while (state.KeepRunning()) {
    ringBuffer.write(buffer);
  }
}
BENCHMARK(BM_WriteOperation);

static void
BM_ReadOperation(benchmark::State& state)
{
  RingBuffer<float> ringBuffer(2, 5);
  juce::AudioBuffer<float> buffer(2, 5);

  while (state.KeepRunning()) {
    ringBuffer.read(buffer);
  }
}
BENCHMARK(BM_ReadOperation);
}