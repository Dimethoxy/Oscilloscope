//==============================================================================
#include "../src/utility/RingBuffer.h"
#include <JuceHeader.h>
#include <gtest/gtest.h>
//==============================================================================
namespace RingBufferTest {
//==============================================================================
// Helper Functions
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
//==============================================================================
// Unit Tests
TEST(RingBuffer, read_write_correctness)
{
  // Maximum number of channels and buffer size to test
  const int maxNumChannels = 9;
  const int maxBufferSize = 2048;
  // Test all possible combinations of channels and buffer sizes
  for (int numChannels = 1; numChannels < maxNumChannels; ++numChannels) {
    for (int bufferSize = 1; bufferSize < maxBufferSize; ++bufferSize) {
      // Generate a test data buffer
      const auto testBuffer = generateTestBuffer(numChannels, bufferSize);
      // Create a ring buffer and write the test buffer to it
      RingBuffer<float> ringBuffer(numChannels, bufferSize);
      ringBuffer.write(testBuffer);
      // Create a buffer to read the ring buffer into
      juce::AudioBuffer<float> readBuffer(numChannels, bufferSize);
      ringBuffer.read(readBuffer);
      // Compare the test buffer to the read buffer
      for (int channel = 0; channel < numChannels; ++channel) {
        for (int sample = 0; sample < bufferSize; sample *= 2) {
          EXPECT_EQ(testBuffer.getSample(channel, sample),
                    readBuffer.getSample(channel, sample));
          if (channel == 0)
            channel = 1;
        }
      }
    }
  }
}
TEST(RingBufferTest, size_mismatch)
{
  const int numChannels = 2;
  const int bufferSize = 1024;

  RingBuffer<float> ringBuffer(numChannels, bufferSize);

  // Create a buffer to write with incorrect size
  AudioBuffer<float> writeBuffer(numChannels, bufferSize / 2);

  // Write the buffer to the ring buffer
  RingBuffer<float>::OperationResult writeResult =
    ringBuffer.write(writeBuffer);
  EXPECT_EQ(writeResult, RingBuffer<float>::OperationResult::ErrorSizeMismatch);

  // Create a buffer to read into with incorrect size
  AudioBuffer<float> readBuffer(numChannels, bufferSize / 2);

  // Read from the ring buffer
  RingBuffer<float>::OperationResult readResult = ringBuffer.read(readBuffer);
  EXPECT_EQ(readResult, RingBuffer<float>::OperationResult::ErrorSizeMismatch);
}
} // namespace RingBufferTest
