#pragma once
#include <JuceHeader.h>

template<typename T>
class RingBuffer
{
public:
  RingBuffer(const int numChannelsToAllocate, const int numSamplesToAllocate)
    : bufferSize(numSamplesToAllocate)
    , numChannels(numChannelsToAllocate)
    , position(0)
    , buffer(std::make_unique<AudioBuffer<T>>(numChannelsToAllocate,
                                              numSamplesToAllocate))
  {
  }

  void read(AudioBuffer<T>& targetBuffer) const noexcept
  {
    const int startingPosition = position.get();
    for (int sample = 0; sample < bufferSize; ++sample) {
      const int ringPosition = (startingPosition + sample) % bufferSize;
      for (int channel = 0; channel < numChannels; ++channel) {
        targetBuffer.copyFrom(
          channel, sample, *buffer, channel, ringPosition, 1);
      }
    }
  }

  void write(const AudioBuffer<T>& bufferToWrite) noexcept
  {
    // If bufferToWrite is larger than the RingBuffer we need to return early
    if (bufferToWrite.getNumChannels() > numChannels ||
        bufferToWrite.getNumSamples() > bufferSize) {
      return;
    }
    // Caching the atomic should be cheaper than calling get() every iteration
    const int startingPosition = position.get();
    // Iterate the samples first to improve thread safety
    for (int sample = 0; sample < bufferSize; ++sample) {
      // We use modulo to wrap the index around the buffer
      const int ringPosition = (startingPosition + sample) % bufferSize;
      // Iterate the channels second to improve thread safety
      for (int channel = 0; channel < numChannels; ++channel) {
        // Copy the sample from bufferToWrite to the RingBuffer
        buffer->copyFrom(
          channel, ringPosition, bufferToWrite, channel, sample, 1);
      }
    }
    // We update the position for the readers after we've written the buffer
    position.set((startingPosition + bufferSize) % bufferSize);
  }

private:
  const int bufferSize;
  const int numChannels;
  juce::Atomic<int> position;
  std::unique_ptr<AudioBuffer<T>> buffer;
};
