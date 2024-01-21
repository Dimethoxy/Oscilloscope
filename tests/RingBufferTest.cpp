#include "../src/utility/RingBuffer.h"
#include <JuceHeader.h>
#include <gtest/gtest-printers.h>
#include <gtest/gtest.h>
#include <iostream>
#include <sstream> // Add this header

//==============================================================================
namespace RingBufferTest {
//==============================================================================

const juce::AudioBuffer<float>
generateTestBuffer(int numChannels, int numSamples)
{
  juce::AudioBuffer<float> buffer(numChannels, numSamples);
  for (int channel = 0; channel < numChannels; ++channel) {
    for (int sample = 0; sample < numSamples; ++sample) {
      juce::Random random;
      const auto randomSample = random.nextFloat();
      buffer.setSample(channel, sample, randomSample);
    }
  }
  return buffer;
}

// Unit Tests
TEST(RingBuffer, read_write_correctness)
{
  const auto testBuffer = generateTestBuffer(7, 2048);

  RingBuffer<float> ringBuffer(7, 2048);
  ringBuffer.write(testBuffer);

  juce::AudioBuffer<float> readBuffer(7, 2048);
  ringBuffer.read(readBuffer);

  for (int channel = 0; channel < 7; ++channel) {
    for (int sample = 0; sample < 2048; ++sample) {
      EXPECT_EQ(testBuffer.getSample(channel, sample),
                readBuffer.getSample(channel, sample));
    }
  }
}
} // namespace RingBufferTest
